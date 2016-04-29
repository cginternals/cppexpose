
#pragma once


#include <string>
#include <vector>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{

class Variant;


/**
*  @brief
*    JSON parser
*/
class CPPEXPOSE_API JSONReader
{
public:
    /**
    *  @brief
    *    Constructor
    */
    JSONReader();

    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[in] document
    *    JSON string
    *  @param[out] root
    *    Output value
    */
    bool parse(const std::string & document, Variant & root);

    /**
    *  @brief
    *    Get a user friendly string that list errors in the parsed document
    *
    *  @return
    *    Formatted error message with the list of errors with their location in 
    *    the parsed document. An empty string is returned if no error occurred
    *    during parsing.
    */
    std::string getErrors() const;


private:
    enum TokenType
    {
        TokenEndOfStream = 0,
        TokenObjectBegin,
        TokenObjectEnd,
        TokenArrayBegin,
        TokenArrayEnd,
        TokenString,
        TokenNumber,
        TokenTrue,
        TokenFalse,
        TokenNull,
        TokenArraySeparator,
        TokenMemberSeparator,
        TokenComment,
        TokenError
    };

    struct Token
    {
        TokenType    type;
        const char * begin;
        const char * end;
    };

    struct ErrorInfo
    {
        Token        token;
        std::string  message;
        const char * extra;
    };


private:
    bool parse(const char * beginDoc, const char * endDoc, Variant & root);
    bool expectToken(TokenType type, Token & token, const char * message);
    bool readToken(Token & token);
    void skipSpaces();
    bool match(const char * pattern, int patternLength);
    bool readComment();
    bool readCStyleComment();
    bool readCppStyleComment();
    bool readString();
    void readNumber();
    bool readValue();
    bool readObject(Token & token);
    bool readArray(Token & token);
    bool decodeNumber(Token & token);
    bool decodeString(Token & token);
    bool decodeString(Token & token, std::string & decoded);
    bool decodeDouble(Token & token);
    bool decodeUnicodeCodePoint(Token & token, const char * & current, const char * end, unsigned int & unicode);
    bool decodeUnicodeEscapeSequence(Token & token, const char * & current, const char * end, unsigned int & unicode);
    bool addError(const std::string & message, Token & token, const char * extra = 0);
    bool recoverFromError(TokenType skipUntilToken);
    bool addErrorAndRecover(const std::string & message, Token & token, TokenType skipUntilToken);
    void skipUntilSpace();
    Variant & currentValue();
    char getNextChar();
    void getLocationLineAndColumn(const char * location, int & line, int & column) const;
    std::string getLocationLineAndColumn(const char * location) const;
    void skipCommentTokens(Token & token);


private:
    std::vector<Variant *>   m_nodes;
    std::vector<ErrorInfo>   m_errors;
    std::string              m_document;
    const char             * m_begin;
    const char             * m_end;
    const char             * m_current;
    const char             * m_lastValueEnd;
    Variant                * m_lastValue;
};


} // namespace cppexpose
