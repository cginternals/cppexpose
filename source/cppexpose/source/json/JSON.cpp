
#include <cppexpose/json/JSON.h>

#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/logging/logging.h>

#include <cppexpose/base/Tokenizer.h>
#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>
#include <cppexpose/expose/Variant.h>


using namespace cppassist;
using namespace cppexpose;


namespace
{


bool readValue(Variant & value, Tokenizer::Token & token, Tokenizer & tokenizer);
bool readArray(Variant & root, Tokenizer & tokenizer);
bool readObject(Variant & root, Tokenizer & tokenizer);


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
        auto & obj = static_cast<const Object &>(root);

        // Quick output: {} if empty
        if (obj.empty()) return "{}";

        // Begin output
        std::string json = "{"; // [TODO] maybe a stringstream can be more performant

        if (beautify)
            json += "\n";

        // Add all variables
        bool first = true;
        for (auto name : obj.properties())
        {
            // Get property
            auto * prop = obj.property(name);
            if (!prop) continue;

            // Add separator (",")
            if (!first)
                json += beautify ? ",\n" : ",";
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
            json += (beautify ? (indent + "    \"" + name + "\": " + value) : ("\"" + name + "\":" + value));
        }

        // Finish JSON
        json += (beautify ? "\n" + indent + "}" : "}");

        return json;
    }

    // Variant is an array
    else if (root.isArray())
    {
        // Get array
        auto & array = static_cast<const Array &>(root);

        // Quick output: [] if empty
        if (array.empty())
            return "[]";

        // Begin output
        std::string json = "["; // [TODO] maybe a stringstream can be more performant
        if (beautify) json += "\n";

        // Add all elements
        bool first = true;
        for (size_t i=0; i<array.size(); i++)
        {
            // Get property
            auto * prop = array.at(i);
            if (!prop) continue;

            // Add separator (",")
            if (!first)
                json += beautify ? ",\n" : ",";
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
            json += (beautify ? (indent + "    " + value) : value);
        }

        // Finish JSON
        json += (beautify ? "\n" + indent + "]" : "]");

        return json;
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

bool readValue(Variant & value, Tokenizer::Token & token, Tokenizer & tokenizer)
{
    if (token.content == "{")
    {
        return readObject(value, tokenizer);
    }

    else if (token.content == "[")
    {
        return readArray(value, tokenizer);
    }

    else if (token.type == Tokenizer::TokenString ||
             token.type == Tokenizer::TokenNumber ||
             token.type == Tokenizer::TokenBoolean ||
             token.type == Tokenizer::TokenNull)
    {
        value = token.value;
        return true;
    }

    else
    {
        cppassist::critical()
            << "Syntax error: value, object or array expected. Found '"
            << token.content
            << "'"
            << std::endl;

        return false;
    }
}

bool readArray(Variant & root, Tokenizer & tokenizer)
{
    // Create array
    root = Array();

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
        // Add new value to array
        root.asArray()->push_back(Variant());
        Variant & value = (*root.asArray())[root.asArray()->size() - 1];

        // Read value
        if (!readValue(value, token, tokenizer))
        {
            return false;
        }

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

            return false;
        }
    }

    // Couldn't actually happen but makes compilers happy
    return false;
}

bool readObject(Variant & root, Tokenizer & tokenizer)
{
    // Create object
    root = Variant::map();

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

            return false;
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

            return false;
        }

        // Read next token
        token = tokenizer.parseToken();

        // Add new value to object
        (*root.asMap())[name] = Variant();
        Variant & value = (*root.asMap())[name];

        // Read value
        if (!readValue(value, token, tokenizer))
        {
            return false;
        }

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

            return false;
        }
    }

    // Couldn't actually happen but makes compilers happy
    return false;
}

bool readDocument(Variant & root, Tokenizer & tokenizer)
{
    // The first value in a document must be either an object or an array
    Tokenizer::Token token = tokenizer.parseToken();

    if (token.content == "{")
    {
        return readObject(root, tokenizer);
    }

    else if (token.content == "[")
    {
        return readArray(root, tokenizer);
    }

    else
    {
        cppassist::critical()
            << "A valid JSON document must be either an array or an object value."
            << std::endl;

        return false;
    }
}


} // namespace


namespace cppexpose
{


std::string JSON::stringify(const Variant & root, JSON::OutputMode outputMode)
{
    return jsonStringify(root, outputMode == Beautify, "");
}

bool JSON::load(Variant & root, const std::string & filename)
{
    auto tokenizer = createJSONTokenizer();

    // Load file
    if (!tokenizer.loadDocument(filename))
    {
        return false;
    }

    // Begin parsing
    return readDocument(root, tokenizer);
}

bool JSON::parse(Variant & root, const std::string & document)
{
    auto tokenizer = createJSONTokenizer();

    // Set document
    tokenizer.setDocument(document);

    // Begin parsing
    return readDocument(root, tokenizer);
}


} // namespace cppexpose
