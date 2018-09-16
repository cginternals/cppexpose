
#include <cppexpose/json/JSON.h>

#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/logging/logging.h>

#include <cppexpose/base/Tokenizer.h>
#include <cppexpose/variant/Variant.h>


namespace
{


bool readValue(cppexpose::Variant & value, cppexpose::Tokenizer::Token & token, cppexpose::Tokenizer & tokenizer);
bool readArray(cppexpose::Variant & root, cppexpose::Tokenizer & tokenizer);
bool readObject(cppexpose::Variant & root, cppexpose::Tokenizer & tokenizer);


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

std::string jsonStringifyPrimitive(const cppexpose::Variant & value)
{
    if (value.canConvert<std::string>())
    {
        return value.toString();
    }

    // Invalid type for JSON output
    return "null";
}

void jsonStringify(std::ostream & stream, const cppexpose::Variant & root, bool beautify, const std::string & indent)
{
    // Variant is an object
    if (root.isVariantMap())
    {
        // Quick output: {} if empty
        if (root.asMap()->empty()){
            stream << "{}";
            return;
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

            // Add variable name
            if (beautify)
                stream << indent << "    \"" << name << "\": ";
            else
                stream << "\"" << name << "\":";

            // Add variable value
            if (var.isVariantMap() || var.isVariantArray())
            {
                jsonStringify(stream, var, beautify, indent + "    ");
            }
            else
            {
                auto escaped = escapeString(jsonStringifyPrimitive(var));

                if (var.hasType<std::string>())
                    stream << "\"" << escaped << "\"";
                else
                    stream << escaped;
            }
        }

        // Finish JSON
        if (beautify)
            stream << "\n" << indent;

        stream << "}";

        return;
    }

    // Variant is an array
    else if (root.isVariantArray())
    {
        // Quick output: [] if empty
        if (root.asArray()->empty())
        {
            stream << "[]";
            return;
        }

        // Begin output
        stream << "[";

        if (beautify)
            stream << "\n";

        // Add all elements
        bool first = true;
        for (const cppexpose::Variant & var : *root.asArray())
        {
            // Add separator (",")
            if (!first)
                stream << (beautify ? ",\n" : ",");
            else
                first = false;

            // Add indent
            if (beautify)
                stream << indent << "    ";

            // Add next value
            if (var.isVariantMap() || var.isVariantArray())
            {
                jsonStringify(stream, var, beautify, indent + "    ");
            }
            else
            {
                auto escaped = escapeString(jsonStringifyPrimitive(var));

                if (var.hasType<std::string>())
                    stream << "\"" << escaped << "\"";
                else
                    stream << escaped;
            }
        }

        // Finish JSON
        if (beautify)
            stream << "\n" << indent;

        stream << "]";

        return;
    }

    // Primitive data types
    stream << jsonStringifyPrimitive(root);
}

cppexpose::Tokenizer createJSONTokenizer()
{
    // Create tokenizer for JSON
    cppexpose::Tokenizer tokenizer;

    tokenizer.setOptions(
        cppexpose::Tokenizer::OptionParseStrings
      | cppexpose::Tokenizer::OptionParseNumber
      | cppexpose::Tokenizer::OptionParseBoolean
      | cppexpose::Tokenizer::OptionParseNull
      | cppexpose::Tokenizer::OptionCStyleComments
      | cppexpose::Tokenizer::OptionCppStyleComments
    );

    tokenizer.setQuotationMarks("\"");
    tokenizer.setSingleCharacters("{}[],:");

    return tokenizer;
}

bool readValue(cppexpose::Variant & value, cppexpose::Tokenizer::Token & token, cppexpose::Tokenizer & tokenizer)
{
    if (token.content == "{")
    {
        return readObject(value, tokenizer);
    }

    else if (token.content == "[")
    {
        return readArray(value, tokenizer);
    }

    else if (token.type == cppexpose::Tokenizer::TokenString ||
             token.type == cppexpose::Tokenizer::TokenNumber ||
             token.type == cppexpose::Tokenizer::TokenBoolean ||
             token.type == cppexpose::Tokenizer::TokenNull)
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

bool readArray(cppexpose::Variant & root, cppexpose::Tokenizer & tokenizer)
{
    // Create array
    root = cppexpose::Variant::array();

    // Read next token
    cppexpose::Tokenizer::Token token = tokenizer.parseToken();

    // Empty array?
    if (token.content == "]")
    {
        return true;
    }

    // Read array values
    while (true)
    {
        // Add new value to array
        root.asArray()->push_back(cppexpose::Variant());
        cppexpose::Variant & value = (*root.asArray())[root.asArray()->size() - 1];

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

bool readObject(cppexpose::Variant & root, cppexpose::Tokenizer & tokenizer)
{
    // Create object
    root = cppexpose::Variant::map();

    // Read next token
    cppexpose::Tokenizer::Token token = tokenizer.parseToken();

    // Empty object?
    if (token.content == "}")
    {
        return true;
    }

    // Read object members
    while (true)
    {
        // Expect name of field
        if (token.type != cppexpose::Tokenizer::TokenString)
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
        (*root.asMap())[name] = cppexpose::Variant();
        cppexpose::Variant & value = (*root.asMap())[name];

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

bool readDocument(cppexpose::Variant & root, cppexpose::Tokenizer & tokenizer)
{
    // The first value in a document must be either an object or an array
    cppexpose::Tokenizer::Token token = tokenizer.parseToken();

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

void JSON::stringify(std::ostream & stream, const Variant & root, JSON::OutputMode outputMode)
{
    jsonStringify(stream, root, outputMode == Beautify, "");
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
