
#include <cppexpose/JSON.h>

#include <sstream>

#include <cppassist/string/conversion.h>
#include <cppassist/logging/logging.h>
#include <cppassist/tokenizer/Tokenizer.h>

#include <cppexpose/Object.h>
#include <cppexpose/Array.h>
#include <cppexpose/Variant.h>


using namespace cppassist;
using namespace cppexpose;


namespace
{


Variant readValue(Tokenizer::Token & token, Tokenizer & tokenizer);
bool readArray(Array & array, Tokenizer & tokenizer);
bool readObject(Object & obj, Tokenizer & tokenizer);


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

std::string getStringValue(const AbstractVar & value)
{
    // Primitive data types
    if (value.canConvertToString())
    {
        return value.toString();
    }

    // Invalid type for JSON output
    return "null";
}

void jsonStringify(std::ostream & stream, const AbstractVar & root, bool beautify, const std::string & indent)
{
    // Value is an object
    if (root.isObject())
    {
        // Get object
        const Object & obj = *root.asObject();

        // Quick output: {} if empty
        if (obj.empty()) {
            stream << "{}";
            return;
        }

        // Begin output
        stream << "{";
        if (beautify) {
            stream << "\n";
        }

        // Add all variables
        bool first = true;
        for (auto it : obj.properties())
        {
            // Get name and property
            std::string   name = it.first;
            AbstractVar * prop = it.second;
            if (!prop) continue;
            if (prop->isFunction()) continue;

            // Add separator (",")
            if (!first) {
                stream << (beautify ? ",\n" : ",");
            } else {
                first = false;
            }

            // Add name to JSON
            if (beautify) {
                stream << indent << "    \"" << name << "\": ";
            } else {
                stream << "\"" << name << "\":";
            }

            // Add value to JSON
            if (prop->isObject() || prop->isArray())
            {
                jsonStringify(stream, *prop, beautify, indent + "    ");
            }
            else if (prop->isNull())
            {
                stream << "null";
            }
            else
            {
                auto escaped = escapeString(getStringValue(*prop));

                if (prop->isString()) {
                    stream << "\"" << escaped << "\"";
                } else {
                    stream << escaped;
                }
            }

        }

        // Finish JSON
        stream << (beautify ? "\n" + indent + "}" : "}");
    }

    // Variant is an array
    else if (root.isArray())
    {
        // Get array
        const Array & array = *root.asArray();

        // Quick output: [] if empty
        if (array.empty()) {
            stream << "[]";
            return;
        }

        // Begin output
        stream << "[";
        if (beautify) {
            stream << "\n";
        }

        // Add all elements
        bool first = true;
        for (size_t i=0; i<array.size(); i++)
        {
            // Get property
            auto * prop = array.at(i);
            if (!prop) continue;
            if (prop->isFunction()) continue;

            // Add separator (",")
            if (!first)
                stream << (beautify ? ",\n" : ",");
            else
                first = false;

            // Add indentation to JSON
            if (beautify) {
                stream << indent << "    ";
            }

            // Get value
            std::string value;
            if (prop->isObject() || prop->isArray())
            {
                jsonStringify(stream, *prop, beautify, indent + "    ");
            }
            else if (prop->isNull())
            {
                stream << "null";
            }
            else
            {
                auto escaped = escapeString(getStringValue(*prop));

                if (prop->isString()) {
                    stream << "\"" << escaped << "\"";
                } else {
                    stream << escaped;
                }
            }
        }

        // Finish JSON
        stream << (beautify ? "\n" + indent + "]" : "]");
    }

    // Primitive data types
    else
    {
        stream << getStringValue(root);
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
        Object obj;
        readObject(obj, tokenizer);
        return std::move(obj);
    }

    else if (token.content == "[")
    {
        Array array;
        readArray(array, tokenizer);
        return std::move(array);
    }

    else if (token.type == Tokenizer::TokenString)
    {
        return Variant(token.stringValue);
    }

    else if (token.type == Tokenizer::TokenNumber)
    {
        if (token.isDouble) return Variant(token.numberValue);
        else                return Variant(token.intValue);
    }

    else if (token.type == Tokenizer::TokenBoolean)
    {
        return Variant(token.booleanValue);
    }

    else if (token.type == Tokenizer::TokenNull)
    {
        return Variant();
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

bool readArray(Array & array, Tokenizer & tokenizer)
{
    // Clear array
    array.clear();

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
            // Abort
            return false;
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
            return true;
        }
        else
        {
            // Unexpected token
            cppassist::critical()
                << "Unexpected token in array: '"
                << token.content
                << "'"
                << std::endl;

            // Abort
            return false;
        }
    }
}

bool readObject(Object & obj, Tokenizer & tokenizer)
{
    // Clear object
    obj.clear();

    // Read next token
    Tokenizer::Token token = tokenizer.parseToken();

    // Empty object?
    if (token.content == "}")
    {
        return true;
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

            // Abort
            return false;
        }

        std::string name = token.stringValue;

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

            // Abort
            return false;
        }

        // Read next token
        token = tokenizer.parseToken();

        // Read value
        Variant value = readValue(token, tokenizer);
        if (value.isNull())
        {
            // Abort
            return false;
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
            return true;
        }
        else
        {
            // Unexpected token
            cppassist::critical()
                << "Unexpected token in object: '"
                << token.content
                << "'"
                << std::endl;

            // Abort
            return false;
        }
    }
}

Variant readDocument(Tokenizer & tokenizer)
{
    // The first value in a document must be either an object or an array
    Tokenizer::Token token = tokenizer.parseToken();

    if (token.content == "{")
    {
        Object obj;
        readObject(obj, tokenizer);
        return std::move(obj);
    }

    else if (token.content == "[")
    {
        Array array;
        readArray(array, tokenizer);
        return std::move(array);
    }

    else
    {
        cppassist::critical()
            << "A valid JSON document must be either an array or an object value."
            << std::endl;

        return Variant();
    }
}

bool readDocument(Object & obj, Tokenizer & tokenizer)
{
    // The first value in a document must be an object
    Tokenizer::Token token = tokenizer.parseToken();

    if (token.content == "{") {
        return readObject(obj, tokenizer);
    } else {
        cppassist::critical()
            << "Expected an object value."
            << std::endl;

        return false;
    }
}

bool readDocument(Array & array, Tokenizer & tokenizer)
{
    // The first value in a document must be an array
    Tokenizer::Token token = tokenizer.parseToken();

    if (token.content == "[") {
        return readArray(array, tokenizer);
    } else {
        cppassist::critical()
            << "Expected an array value."
            << std::endl;

        return false;
    }
}


} // namespace


namespace cppexpose
{


std::string JSON::stringify(const AbstractVar & root, JSON::OutputMode outputMode)
{
    std::stringstream ss;
    jsonStringify(ss, root, outputMode == Beautify, "");

    return ss.str();
}

void JSON::stringify(std::ostream & stream, const AbstractVar & root, OutputMode outputMode)
{
    jsonStringify(stream, root, outputMode == Beautify, "");
}

Variant JSON::load(const std::string & filename)
{
    auto tokenizer = createJSONTokenizer();

    // Load file
    if (!tokenizer.loadDocument(filename))
    {
        return Variant();
    }

    // Begin parsing
    return readDocument(tokenizer);
}

bool JSON::load(Object & obj, const std::string & filename)
{
    auto tokenizer = createJSONTokenizer();

    // Load file
    if (!tokenizer.loadDocument(filename))
    {
        return false;
    }

    // Begin parsing
    return readDocument(obj, tokenizer);
}

bool JSON::load(Array & array, const std::string & filename)
{
    auto tokenizer = createJSONTokenizer();

    // Load file
    if (!tokenizer.loadDocument(filename))
    {
        return false;
    }

    // Begin parsing
    return readDocument(array, tokenizer);
}

Variant JSON::parse(const std::string & document)
{
    auto tokenizer = createJSONTokenizer();

    // Set document
    tokenizer.setDocument(document);

    // Begin parsing
    return readDocument(tokenizer);
}

bool JSON::parse(Object & obj, const std::string & document)
{
    auto tokenizer = createJSONTokenizer();

    // Set document
    tokenizer.setDocument(document);

    // Begin parsing
    return readDocument(obj, tokenizer);
}

bool JSON::parse(Array & array, const std::string & document)
{
    auto tokenizer = createJSONTokenizer();

    // Set document
    tokenizer.setDocument(document);

    // Begin parsing
    return readDocument(array, tokenizer);
}


} // namespace cppexpose
