
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>

#include <cppexpose/base/Tokenizer.h>


using namespace cppassist;
using namespace cppexpose;


int main(int, char * [])
{
    std::string filename = "/workspace/new/test.json";

    // Begin parsing JSON
    std::cout << "Parsing file '" << filename << "':" << std::endl;
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

    // Parse document
    tokenizer.loadDocument(filename);
    Tokenizer::Token token = tokenizer.parseToken();
    while (token.type != Tokenizer::TokenEndOfStream)
    {
        std::cout
            << "[" << toString(token.line) << ", " << toString(token.column) << "] "
            << token.content
            << std::endl;

        token = tokenizer.parseToken();
    }

    // Exit application
    return 0;
}
