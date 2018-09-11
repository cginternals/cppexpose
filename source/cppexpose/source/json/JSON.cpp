
#include <cppexpose/json/JSON.h>

#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/logging/logging.h>

#include <cppexpose/base/Tokenizer.h>
#include <cppexpose/variant/Variant.h>


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

std::ostream & jsonStringify(std::ostream & stream, const Variant & root, bool beautify, const std::string & indent)
{
    // Variant is an object
    if (root.isVariantMap())
    {
        // Quick output: {} if empty
        if (root.asMap()->empty()){
            stream << "{}";
            return stream;
        }

        // Begin output
        stream << "{";

        if (beautify)
            stream << "\n";

        // Add all variables
        bool first = true;
        for (auto it : *root.asMap())
        {
            // Add separator (",")
            if (!first)
                stream << (beautify ? ",\n" : ",");
            else
                first = false;

            // Get variable
            const std::string & name       = it.first;
            const cppexpose::Variant & var = it.second;

            // Get value
            std::stringstream value;
            if (var.isVariantMap() || var.isVariantArray())
            {
                jsonStringify(value, var, beautify, indent + "    ");
            }
            else if (var.isNull())
            {
                value << "null";
            }
            else
            {
                std::stringstream unescaped;
                jsonStringify(unescaped, var, beautify, "");
                auto escaped = escapeString(unescaped.str());

                if (var.hasType<std::string>())
                    value << "\"" << escaped << "\"";
                else
                    value << escaped;
            }

            // Add value to JSON
            stream << (beautify ? (indent + "    \"" + name + "\": " + value.str()) : ("\"" + name + "\":" + value.str()));
        }

        // Finish JSON
        stream << (beautify ? "\n" + indent + "}" : "}");

        return stream;
    }

    // Variant is an array
    else if (root.isVariantArray())
    {
        // Quick output: [] if empty
        if (root.asArray()->empty())
        {
            stream << "[]";
            return stream;
        }

        // Begin output
        stream << "[";
        if (beautify) stream << "\n";

        // Add all elements
        bool first = true;
        for (const cppexpose::Variant & var : *root.asArray())
        {
            // Add separator (",")
            if (!first)
                stream << (beautify ? ",\n" : ",");
            else
                first = false;

            // Get value
            std::stringstream value;
            if (var.isVariantMap() || var.isVariantArray())
            {
                jsonStringify(value, var, beautify, indent + "    ");
            }
            else if (var.isNull())
            {
                value << "null";
            }
            else
            {
                std::stringstream unescaped;
                jsonStringify(unescaped, var, beautify, "");
                auto escaped = escapeString(unescaped.str());

                if (var.hasType<std::string>())
                    value << "\"" << escaped << "\"";
                else
                    value << escaped;
            }

            // Add value to JSON
            stream << (beautify ? (indent + "    " + value.str()) : value.str());
        }

        // Finish JSON
        stream << (beautify ? "\n" + indent + "]" : "]");

        return stream;
    }

    // Primitive data types
    else if (root.canConvert<std::string>())
    {
        stream << root.toString();
        return stream;
    }

    // Invalid type for JSON output
    else
    {
        stream << "null";
        return stream;
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
    root = Variant::array();

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
    std::stringstream stream;
    jsonStringify(stream, root, outputMode == Beautify, "");
    return stream.str();
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
