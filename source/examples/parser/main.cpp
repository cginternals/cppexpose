
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/tokenizer/Tokenizer.h>

#include <cppexpose/JSON.h>
#include <cppexpose/Variant.h>


using namespace cppassist;
using namespace cppexpose;


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
    Tokenizer tokenizer;
    tokenizer.setOptions(
        Tokenizer::OptionParseStrings
      | Tokenizer::OptionParseNumber
      | Tokenizer::OptionCStyleComments
      | Tokenizer::OptionCppStyleComments
      | Tokenizer::OptionShellStyleComments
      | Tokenizer::OptionIncludeComments
    );
    tokenizer.setQuotationMarks("\"'");
    tokenizer.setStandalones( { "+==", "+=" } );
    tokenizer.setSingleCharacters("{}[],:");

    // Parse document
    tokenizer.setDocument(json);
    Tokenizer::Token token = tokenizer.parseToken();
    while (token.type != Tokenizer::TokenEndOfStream)
    {
        std::cout
            << "[" << string::toString(token.line) << ", " << string::toString(token.column) << "] "
            << token.content
            << std::endl;

        token = tokenizer.parseToken();
    }
    std::cout << std::endl;

    // Load JSON to variant
    Variant obj = JSON::parse(json);

    // Print variant as compact JSON
    std::cout << JSON::stringify(obj) << std::endl;
    std::cout << std::endl;

    // Print variant as beautified JSON
    std::cout << JSON::stringify(obj, JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Exit application
    return 0;
}
