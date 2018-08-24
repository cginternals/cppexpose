
#include <cppexpose/JSON.h>

#include <sstream>

#include <cppassist/string/conversion.h>
#include <cppassist/logging/logging.h>

#include <cppexpose/Tokenizer.h>
#include <cppexpose/Object.h>
#include <cppexpose/Array.h>
#include <cppexpose/Variant.h>


using namespace cppassist;
using namespace cppexpose;


namespace
{


Variant readValue(Tokenizer::Token & token, Tokenizer & tokenizer);
Variant readArray(Tokenizer & tokenizer);
Variant readObject(Tokenizer & tokenizer);


const char * const g_hexdig = "0123456789ABCDEF";


std::string escapeString(const std::string & in)
{
    std::string out = "";

    for (unsigned char c : in)
    {
        if (c >= ' ' && c <= '~' && c != '\\' && c != '"')
        {
            out.append(1, c);
        }
        else
        {
            out = out + '\\';
            switch(c) {
                case '"':  out = out + "\"";  break;
                case '\\': out = out + "\\"; break;
                case '\t': out = out + "t";  break;
                case '\r': out = out + "r";  break;
                case '\n': out = out + "n";  break;
                default:
                    out = out + "x";
                    out.append(1, g_hexdig[c >> 4]);
                    out.append(1, g_hexdig[c & 0xF]);
                    break;
            }
        }
    }

    return out;
}

std::string jsonStringify(const AbstractVar & root, bool beautify, const std::string & indent)
{
    // Value is an object
    if (root.isObject())
    {
        // Get object
        const Object & obj = *root.asObject();

        // Quick output: {} if empty
        if (obj.empty()) return "{}";

        // Begin output
        std::stringstream ss;
        ss << "{";
        if (beautify) {
            ss << "\n";
        }

        // Add all variables
        bool first = true;
        for (auto it : obj.properties())
        {
            // Get name and property
            std::string   name = it.first;
            AbstractVar * prop = it.second;
            if (!prop) continue;

            // Add separator (",")
            if (!first) {
                ss << (beautify ? ",\n" : ",");
            } else {
                first = false;
            }

            // Get value
            std::string value;
            if (prop->isObject() || prop->isArray())
            {
                value = jsonStringify(*prop, beautify, indent + "    ");
            }
            else if (prop->isNull())
            {
                value = "null";
            }
            else
            {
                value = escapeString(jsonStringify(*prop, beautify, ""));

                if (prop->isString())
                {
                    value = "\"" + value + "\"";
                }
            }

            // Add value to JSON
            ss << (beautify ? (indent + "    \"" + name + "\": " + value) : ("\"" + name + "\":" + value));
        }

        // Finish JSON
        ss << (beautify ? "\n" + indent + "}" : "}");
        return ss.str();
    }

    // Variant is an array
    else if (root.isArray())
    {
        // Get array
        const Array & array = *root.asArray();

        // Quick output: [] if empty
        if (array.empty()) {
            return "[]";
        }

        // Begin output
        std::stringstream ss;
        ss << "[";
        if (beautify) {
            ss << "\n";
        }

        // Add all elements
        bool first = true;
        for (size_t i=0; i<array.size(); i++)
        {
            // Get property
            auto * prop = array.at(i);
            if (!prop) continue;

            // Add separator (",")
            if (!first)
                ss << (beautify ? ",\n" : ",");
            else
                first = false;

            // Get value
            std::string value;
            if (prop->isObject() || prop->isArray())
            {
                value = jsonStringify(*prop, beautify, indent + "    ");
            }
            else if (prop->isNull())
            {
                value = "null";
            }
            else
            {
                value = escapeString(jsonStringify(*prop, beautify, ""));

                if (prop->isString())
                {
                    value = "\"" + value + "\"";
                }
            }

            // Add value to JSON
            ss << (beautify ? (indent + "    " + value) : value);
        }

        // Finish JSON
        ss << (beautify ? "\n" + indent + "]" : "]");

        return ss.str();
    }

    // Primitive data types
    else if (root.canConvertToString())
    {
        return root.toString();
    }

    // Invalid type for JSON output
    else
    {
        return "null";
    }
}

Tokenizer createJSONTokenizer()
{
    // Create tokenizer for JSON
    Tokenizer tokenizer;

    tokenizer.setOptions(
        Tokenizer::OptionParseStrings
      | Tokenizer::OptionParseNumber
      | Tokenizer::OptionParseBoolean
      | Tokenizer::OptionParseNull
      | Tokenizer::OptionCStyleComments
      | Tokenizer::OptionCppStyleComments
    );

    tokenizer.setQuotationMarks("\"");
    tokenizer.setSingleCharacters("{}[],:");

    return tokenizer;
}

Variant readValue(Tokenizer::Token & token, Tokenizer & tokenizer)
{
    if (token.content == "{")
    {
        return readObject(tokenizer);
    }

    else if (token.content == "[")
    {
        return readArray(tokenizer);
    }

    else if (token.type == Tokenizer::TokenString ||
             token.type == Tokenizer::TokenNumber ||
             token.type == Tokenizer::TokenBoolean ||
             token.type == Tokenizer::TokenNull)
    {
        return std::move(Variant(token.value));
    }

    else
    {
        cppassist::critical()
            << "Syntax error: value, object or array expected. Found '"
            << token.content
            << "'"
            << std::endl;

        return Variant();
    }
}

Variant readArray(Tokenizer & tokenizer)
{
    // Create array
    Array array;

    // Read next token
    Tokenizer::Token token = tokenizer.parseToken();

    // Empty array?
    if (token.content == "]")
    {
        return true;
    }

    // Read array values
    while (true)
    {
        // Read value
        Variant value = readValue(token, tokenizer);
        if (value.isNull())
        {
            return Variant();
        }

        // Add value to array
        array.push(std::move(value));

        // Read next token
        token = tokenizer.parseToken();

        // Expect ',' or ']'
        if (token.content == ",")
        {
            // Read next token
            token = tokenizer.parseToken();
        }
        else if (token.content == "]")
        {
            // End of array
            return std::move(array);
        }
        else
        {
            // Unexpected token
            cppassist::critical()
                << "Unexpected token in array: '"
                << token.content
                << "'"
                << std::endl;

            // Return error
            return Variant();
        }
    }

    // Couldn't actually happen but makes compilers happy
    return Variant();
}

Variant readObject(Tokenizer & tokenizer)
{
    // Create object
    Object obj;

    // Read next token
    Tokenizer::Token token = tokenizer.parseToken();

    // Empty object?
    if (token.content == "}")
    {
        return std::move(obj);
    }

    // Read object members
    while (true)
    {
        // Expect name of field
        if (token.type != Tokenizer::TokenString)
        {
            cppassist::critical()
                << "Syntax error: object member name expected. Found '"
                << token.content
                << "'"
                << std::endl;

            return Variant();
        }

        std::string name = token.value.toString();

        // Read next token
        token = tokenizer.parseToken();

        // Expect ':'
        if (token.content != ":")
        {
            cppassist::critical()
                << "Syntax error: ':' expected. Found '"
                << token.content
                << "'"
                << std::endl;

            return Variant();
        }

        // Read next token
        token = tokenizer.parseToken();

        // Read value
        Variant value = readValue(token, tokenizer);
        if (value.isNull())
        {
            return Variant();
        }

        // Add new value to object
        obj.addProperty(name, std::move(value));

        // Read next token
        token = tokenizer.parseToken();

        // Expect ',' or '}'
        if (token.content == ",")
        {
            // Read next token
            token = tokenizer.parseToken();
        }
        else if (token.content == "}")
        {
            // End of object
            return std::move(obj);
        }
        else
        {
            // Unexpected token
            cppassist::critical()
                << "Unexpected token in object: '"
                << token.content
                << "'"
                << std::endl;

            return Variant();
        }
    }

    // Couldn't actually happen but makes compilers happy
    return Variant();
}

Variant readDocument(Tokenizer & tokenizer)
{
    // The first value in a document must be either an object or an array
    Tokenizer::Token token = tokenizer.parseToken();

    if (token.content == "{")
    {
        return readObject(tokenizer);
    }

    else if (token.content == "[")
    {
        return readArray(tokenizer);
    }

    else
    {
        cppassist::critical()
            << "A valid JSON document must be either an array or an object value."
            << std::endl;

        return Variant();
    }
}


} // namespace


namespace cppexpose
{


std::string JSON::stringify(const AbstractVar & root, JSON::OutputMode outputMode)
{
    return jsonStringify(root, outputMode == Beautify, "");
}

Variant JSON::load(const std::string & filename)
{
    auto tokenizer = createJSONTokenizer();

    // Load file
    if (!tokenizer.loadDocument(filename))
    {
        return false;
    }

    // Begin parsing
    return readDocument(tokenizer);
}

Variant JSON::parse(const std::string & document)
{
    auto tokenizer = createJSONTokenizer();

    // Set document
    tokenizer.setDocument(document);

    // Begin parsing
    return readDocument(tokenizer);
}


} // namespace cppexpose
