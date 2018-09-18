
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>

#include <cppexpose/base/Tokenizer.h>
#include <cppexpose/json/JSON.h>
#include <cppexpose/variant/Variant.h>


static std::string json = R"(
{ // Beginning
    /* Some type of glossary,
       I would guess ... */
    "glossary": {
        "title": "example glossary",
        "GlossDiv": {
            "title": "S",
            "GlossList": {
                "GlossEntry": {
                    "ID": "SGML",
                    "SortAs": "SGML",
                    "GlossTerm": "Standard Generalized Markup Language",
                    "Acronym": "SGML",
                    "Abbrev": "ISO 8879:1986",
                    "GlossDef": {
                        "para": "A meta-markup language, used to create markup languages such as DocBook.",
                        "GlossSeeAlso": ["GML", "XML"]
                    },
                    "GlossSee": "markup",
                    "Number": -12e+4,
                    "Number2": 130,
                    "Boolean": true/*haha*/,
                    "Boolean": false,
                    "test": "a+==b"
                }
            }
        }
    }
} // End
)";


int main(int, char * [])
{
    // Begin parsing JSON
    std::cout << "Parsing JSON" << std::endl;
    std::cout << std::endl;

    // Initialize tokenizer
    cppexpose::Tokenizer tokenizer;
    tokenizer.setOptions(
        cppexpose::Tokenizer::OptionParseStrings
      | cppexpose::Tokenizer::OptionParseNumber
      | cppexpose::Tokenizer::OptionCStyleComments
      | cppexpose::Tokenizer::OptionCppStyleComments
      | cppexpose::Tokenizer::OptionShellStyleComments
      | cppexpose::Tokenizer::OptionIncludeComments
    );
    tokenizer.setQuotationMarks("\"'");
    tokenizer.setStandalones( { "+==", "+=" } );
    tokenizer.setSingleCharacters("{}[],:");

    // Parse document
    tokenizer.setDocument(json);
    cppexpose::Tokenizer::Token token = tokenizer.parseToken();
    while (token.type != cppexpose::Tokenizer::TokenEndOfStream)
    {
        std::cout
            << "[" << cppassist::string::toString(token.line) << ", " << cppassist::string::toString(token.column) << "] "
            << token.content
            << std::endl;

        token = tokenizer.parseToken();
    }
    std::cout << std::endl;

    // Load JSON to variant
    cppexpose::Variant obj;
    cppexpose::JSON::parse(obj, json);

    // Print variant as compact JSON
    std::cout << cppexpose::JSON::stringify(obj) << std::endl;
    std::cout << std::endl;

    // Print variant as beautified JSON
    std::cout << cppexpose::JSON::stringify(obj, cppexpose::JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Exit application
    return 0;
}
