/*********************************************************\
 *  Based on JsonCpp
 *  Copyright (c) 2007-2010 Baptiste Lepilleur
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy,
 *  modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 *  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 *  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
\*********************************************************/
#include <cppexpose/base/JSONReader.h>

#include <stdlib.h>
#include <sstream>

#include <cppexpose/base/string_helpers.h>
#include <cppexpose/variant/Variant.h>


static const int           MIN_INT  = int( ~(unsigned(-1)/2) );
static const int           MAX_INT  = int(  (unsigned(-1)/2) );
static const unsigned int  MAX_UINT = unsigned(-1);


namespace cppexpose
{


static inline bool in(char c, char c1, char c2, char c3, char c4)
{
    return c == c1  ||  c == c2  ||  c == c3  ||  c == c4;
}

static inline bool in(char c, char c1, char c2, char c3, char c4, char c5)
{
    return c == c1  ||  c == c2  ||  c == c3  ||  c == c4  ||  c == c5;
}

static std::string codePointToUTF8(unsigned int cp)
{
    std::string result;

    // based on description from http://en.wikipedia.org/wiki/UTF-8

    if (cp <= 0x7f) {
        result.resize(1);
        result[0] = static_cast<char>(cp);
    } else if (cp <= 0x7FF) {
        result.resize(2);
        result[1] = static_cast<char>(0x80 | (0x3f & cp));
        result[0] = static_cast<char>(0xC0 | (0x1f & (cp >> 6)));
    } else if (cp <= 0xFFFF) {
        result.resize(3);
        result[2] = static_cast<char>(0x80 | (0x3f & cp));
        result[1] = 0x80 | static_cast<char>((0x3f & (cp >> 6)));
        result[0] = 0xE0 | static_cast<char>((0xf & (cp >> 12)));
    } else if (cp <= 0x10FFFF) {
        result.resize(4);
        result[3] = static_cast<char>(0x80 | (0x3f & cp));
        result[2] = static_cast<char>(0x80 | (0x3f & (cp >> 6)));
        result[1] = static_cast<char>(0x80 | (0x3f & (cp >> 12)));
        result[0] = static_cast<char>(0xF0 | (0x7 & (cp >> 18)));
    }

    return result;
}


JSONReader::JSONReader()
: m_begin(nullptr)
, m_end(nullptr)
, m_current(nullptr)
, m_lastValueEnd(nullptr)
, m_lastValue(nullptr)
{
}

bool JSONReader::parse(const std::string & document, Variant & root)
{
    m_document         = document;
    const char * begin = document.c_str();
    const char * end   = begin + document.size();
    return parse(begin, end, root);
}

bool JSONReader::parse(const char * beginDoc, const char * endDoc, Variant & root)
{
    m_begin           = beginDoc;
    m_end             = endDoc;
    m_current         = m_begin;
    m_lastValueEnd    = nullptr;
    m_lastValue       = nullptr;
    m_errors.clear();

    while (!m_nodes.empty()) {
        m_nodes.pop_back();
    }
    m_nodes.push_back(&root);

    bool successful = readValue();
    Token token;
    skipCommentTokens(token);

    if (!root.isVariantArray() && !root.isVariantMap())
    {
        // Set error location to start of doc, ideally should be first token found in doc
        token.type  = TokenError;
        token.begin = beginDoc;
        token.end   = endDoc;
        addError("A valid JSON document must be either an array or an object value.", token);
        return false;
    }

    return successful;
}

std::string JSONReader::getErrors() const
{
    std::string formattedMessage;
    for (std::vector<ErrorInfo>::const_iterator itError = m_errors.begin(); itError != m_errors.end(); ++itError)
    {
        const ErrorInfo &error = *itError;
        formattedMessage += "* " + getLocationLineAndColumn(error.token.begin) + "\n";
        formattedMessage += "  " + error.message + "\n";

        if (error.extra) {
            formattedMessage += "See " + getLocationLineAndColumn(error.extra) + " for detail.\n";
        }
    }

    return formattedMessage;
}

bool JSONReader::readValue()
{
    Token token;
    skipCommentTokens(token);
    bool successful = true;

    switch (token.type)
    {
        case TokenObjectBegin:
            successful = readObject(token);
            break;

        case TokenArrayBegin:
            successful = readArray(token);
            break;

        case TokenNumber:
            successful = decodeNumber(token);
            break;

        case TokenString:
            successful = decodeString(token);
            break;

        case TokenTrue:
            currentValue() = true;
            break;

        case TokenFalse:
            currentValue() = false;
            break;

        case TokenNull:
            currentValue() = Variant();
            break;
        default:
            return addError("Syntax error: value, object or array expected.", token);
    }

    return successful;
}

void JSONReader::skipCommentTokens(Token & token)
{
    do {
       readToken(token);
    } while (token.type == TokenComment);
}


bool JSONReader::expectToken(TokenType type, Token & token, const char * message)
{
    readToken(token);

    if (token.type != type) {
        return addError(message, token);
    }

    return true;
}

bool JSONReader::readToken(Token & token)
{
    skipSpaces();
    token.begin = m_current;
    char c = getNextChar();
    bool ok = true;
    switch (c)
    {
        case '{':
            token.type = TokenObjectBegin;
            break;

        case '}':
            token.type = TokenObjectEnd;
            break;

        case '[':
            token.type = TokenArrayBegin;
            break;

        case ']':
            token.type = TokenArrayEnd;
            break;

        case '"':
            token.type = TokenString;
            ok = readString();
            break;

        case '/':
            token.type = TokenComment;
            ok = readComment();
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            token.type = TokenNumber;
            readNumber();
            break;

        case 't':
            token.type = TokenTrue;
            ok = match( "rue", 3 );
            break;

        case 'f':
            token.type = TokenFalse;
            ok = match( "alse", 4 );
            break;

        case 'n':
            token.type = TokenNull;
            ok = match( "ull", 3 );
            break;

        case ',':
            token.type = TokenArraySeparator;
            break;

        case ':':
            token.type = TokenMemberSeparator;
            break;

        case 0:
            token.type = TokenEndOfStream;
            break;

        default:
            ok = false;
            break;
    }

    if (!ok) {
        token.type = TokenError;
    }

    token.end = m_current;

    return true;
}

void JSONReader::skipSpaces()
{
    while (m_current != m_end)
    {
        char c = *m_current;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            ++m_current;
        } else {
            break;
        }
    }
}

bool JSONReader::match(const char * pattern, int patternLength)
{
    if (m_end - m_current < patternLength) {
        return false;
    }

    int index = patternLength;

    while (index--) {
        if (m_current[index] != pattern[index]){
            return false;
        }
    }

    m_current += patternLength;
    return true;
}

bool JSONReader::readComment()
{
    char c = getNextChar();
    bool successful = false;

    if (c == '*') {
        successful = readCStyleComment();
    } else if (c == '/') {
        successful = readCppStyleComment();
    }

    return successful;
}

bool JSONReader::readCStyleComment()
{
    while (m_current != m_end)
    {
        char c = getNextChar();

        if (c == '*' && *m_current == '/') {
            break;
        }
    }

    return getNextChar() == '/';
}

bool JSONReader::readCppStyleComment()
{
    while (m_current != m_end)
    {
        char c = getNextChar();

        if (c == '\r' || c == '\n') {
            break;
        }
    }

    return true;
}

void JSONReader::readNumber()
{
    while (m_current != m_end)
    {
        if (!(*m_current >= '0' && *m_current <= '9') && !in(*m_current, '.', 'e', 'E', '+', '-')) {
            break;
        }

        ++m_current;
    }
}

bool JSONReader::readString()
{
    char c = 0;
    while (m_current != m_end)
    {
        c = getNextChar();

        if (c == '\\') {
            getNextChar();
        } else if (c == '"') {
            break;
        }
    }

    return c == '"';
}

bool JSONReader::readObject(Token & /*tokenStart*/)
{
    Token tokenName;
    std::string name;
    currentValue() = Variant::map();

    while (readToken(tokenName))
    {
        bool initialTokenOk = true;

        while (tokenName.type == TokenComment && initialTokenOk) {
            initialTokenOk = readToken( tokenName );
        }

        if (!initialTokenOk) {
            break;
        }

        if (tokenName.type == TokenObjectEnd && name.empty()) { // empty object
            return true;
        }

        if (tokenName.type != TokenString) {
            break;
        }

        name = "";
        if (!decodeString(tokenName, name)) {
            return recoverFromError(TokenObjectEnd);
        }

        Token colon;
        if (!readToken(colon) || colon.type != TokenMemberSeparator) {
            return addErrorAndRecover("Missing ':' after object member name", colon, TokenObjectEnd);
        }

        Variant & value = (*currentValue().asMap())[name];
        m_nodes.push_back(&value);
        bool ok = readValue();
        m_nodes.pop_back();
        if (!ok) { // error already set
            return recoverFromError(TokenObjectEnd);
        }

        Token comma;
        if (!readToken(comma) ||
            (comma.type != TokenObjectEnd && comma.type != TokenArraySeparator && comma.type != TokenComment) )
        {
            return addErrorAndRecover("Missing ',' or '}' in object declaration", comma, TokenObjectEnd);
        }

        bool finalizeTokenOk = true;
        while (comma.type == TokenComment && finalizeTokenOk) {
            finalizeTokenOk = readToken(comma);
        }

        if (comma.type == TokenObjectEnd) {
            return true;
        }
    }

    return addErrorAndRecover("Missing '}' or object member name", tokenName, TokenObjectEnd);
}

bool JSONReader::readArray(Token & /*tokenStart*/)
{
    currentValue() = Variant::array();
    skipSpaces();

    if (*m_current == ']') { // empty array
        Token endArray;
        readToken( endArray );
        return true;
    }

    while (true)
    {
        Variant value;
        m_nodes.push_back(&value);
        bool ok = readValue();
        m_nodes.pop_back();

        currentValue().asArray()->push_back(value);

        if (!ok) {// error already set
            return recoverFromError( TokenArrayEnd );
        }

        Token token;

        // Accept Comment after last item in the array.
        ok = readToken(token);
        while (token.type == TokenComment && ok) {
            ok = readToken( token );
        }

        bool badTokenType = (token.type == TokenArraySeparator && token.type == TokenArrayEnd);
        if (!ok || badTokenType) {
            return addErrorAndRecover("Missing ',' or ']' in array declaration", token, TokenArrayEnd);
        }

        if (token.type == TokenArrayEnd) {
            break;
        }
    }

    return true;
}

bool JSONReader::decodeNumber(Token & token)
{
    bool isDouble = false;

    for (const char * inspect = token.begin; inspect != token.end; ++inspect) {
        isDouble = isDouble ||
                   in(*inspect, '.', 'e', 'E', '+') ||
                   (*inspect == '-' && inspect != token.begin);
    }

    if (isDouble) {
        return decodeDouble(token);
    }

    const char * current = token.begin;
    bool isNegative = *current == '-';
    if (isNegative) {
        ++current;
    }

    unsigned int largest = (isNegative ? (unsigned)(MAX_INT) : MAX_UINT);
    unsigned int threshold = largest / 10;
    unsigned int value = 0;

    while (current < token.end)
    {
        char c = *current++;

        if (c < '0' || c > '9') {
            return addError("'" + std::string(token.begin, token.end-token.begin) + "' is not a number.", token);
        }

        if (value >= threshold) {
            return decodeDouble(token);
        }

        value = value * 10 + unsigned(c - '0');
    }

    if (isNegative) {
        currentValue() = -int( value );
    } else if (value <= unsigned(MAX_INT)) {
        currentValue() = int(value);
    } else {
        currentValue() = value;
    }

    return true;
}

bool JSONReader::decodeDouble(Token & token)
{
    double value = 0.0;
    //bool ok = false;

    std::string buffer(token.begin, token.end-token.begin);
    value = helper::fromString<double>(buffer);

    //if (ok)
    //    return addError( "'" + std::string(token.begin, token.end-token.begin) + "' is not a number.", token );

    currentValue() = value;
    return true;
}

bool JSONReader::decodeString(Token & token)
{
    std::string decoded;

    if (!decodeString(token, decoded)) {
        return false;
    }

    currentValue() = decoded;
    return true;
}

bool JSONReader::decodeString(Token & token, std::string & decoded)
{
    decoded.reserve(token.end - token.begin - 2);
    const char * current = token.begin + 1; // skip '"'
    const char * end = token.end - 1;      // do not include '"'

    while (current != end)
    {
        char c = *current++;

        if (c == '"') {
            break;
        } else if (c == '\\') {
            if (current == end) {
                return addError("Empty escape sequence in string", token, current);
            }

            char escape = *current++;
            switch (escape) {
                case '"': decoded += '"'; break;
                case '/': decoded += '/'; break;
                case '\\': decoded += '\\'; break;
                case 'b': decoded += '\b'; break;
                case 'f': decoded += '\f'; break;
                case 'n': decoded += '\n'; break;
                case 'r': decoded += '\r'; break;
                case 't': decoded += '\t'; break;
                case 'u':
                {
                    unsigned int unicode;

                    if (!decodeUnicodeCodePoint(token, current, end, unicode)) {
                        return false;
                    }

                    decoded += codePointToUTF8(unicode);
                    break;
                }

                default:
                    return addError("Bad escape sequence in string", token, current);
            }
        } else {
            decoded += c;
        }
    }

    return true;
}

bool JSONReader::decodeUnicodeCodePoint(Token & token, const char * & current, const char * end, unsigned int & unicode)
{
    if (!decodeUnicodeEscapeSequence( token, current, end, unicode )) {
        return false;
    }

    if (unicode >= 0xD800 && unicode <= 0xDBFF)
    {
        // surrogate pairs
        if (end - current < 6) {
            return addError( "additional six characters expected to parse unicode surrogate pair.", token, current );
        }

        unsigned int surrogatePair;

        if (*(current++) == '\\' && *(current++)== 'u') {
            if (decodeUnicodeEscapeSequence(token, current, end, surrogatePair)) {
                unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
            } else {
                return false;
            }
        } else {
            return addError("expecting another \\u token to begin the second half of a unicode surrogate pair", token, current);
        }
    }

    return true;
}

bool JSONReader::decodeUnicodeEscapeSequence(Token & token, const char * & current, const char * end, unsigned int & unicode)
{
    if (end - current < 4) {
        return addError( "Bad unicode escape sequence in string: four digits expected.", token, current );
    }

    unicode = 0;
    for (int index=0; index<4; ++index)
    {
        char c = *current++;
        unicode *= 16;
        if (c >= '0' && c <= '9') {
            unicode += c - '0';
        } else if (c >= 'a' && c <= 'f') {
            unicode += c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            unicode += c - 'A' + 10;
        } else {
            return addError("Bad unicode escape sequence in string: hexadecimal digit expected.", token, current);
        }
    }

    return true;
}

bool JSONReader::addError(const std::string & message, Token & token, const char * extra)
{
    ErrorInfo info;
    info.token   = token;
    info.message = message;
    info.extra   = extra;
    m_errors.push_back(info);

    return false;
}

bool JSONReader::recoverFromError(TokenType skipUntilToken)
{
    int errorCount = int(m_errors.size());
    Token skip;

    while (true)
    {
        if (!readToken(skip)) {
            m_errors.resize(errorCount); // discard errors caused by recovery
        }

        if (skip.type == skipUntilToken || skip.type == TokenEndOfStream) {
            break;
        }
    }

    m_errors.resize(errorCount);
    return false;
}

bool JSONReader::addErrorAndRecover(const std::string & message, Token & token, TokenType skipUntilToken)
{
    addError(message, token);
    return recoverFromError(skipUntilToken);
}

Variant & JSONReader::currentValue()
{
    return *(m_nodes.back());
}

char JSONReader::getNextChar()
{
    if (m_current == m_end) {
        return 0;
    }

    return *m_current++;
}

void JSONReader::getLocationLineAndColumn(const char * location, int & line, int & column) const
{
    const char * current       = m_begin;
    const char * lastLineStart = current;
    line = 0;

    while (current < location && current != m_end)
    {
        char c = *current++;

        if (c == '\r') {
            if (*current == '\n')
                ++current;
            lastLineStart = current;
            ++line;
        } else if (c == '\n') {
            lastLineStart = current;
            ++line;
        }
    }

    // column & line start at 1
    column = int(location - lastLineStart) + 1;
    ++line;
}

std::string JSONReader::getLocationLineAndColumn(const char * location) const
{
    int line, column;
    getLocationLineAndColumn(location, line, column);

    std::stringstream out;
    out << "Line " << line << ", Column " << column;
    return out.str();
}


} // namespace cppexpose
