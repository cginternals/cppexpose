
#pragma once


#include <string>

#include <cppexpose/base/Tokenizer.h>


namespace cppexpose
{


class Variant;


/**
*  @brief
*    JSON tools
*/
class CPPEXPOSE_API JSON
{
public:
    /**
    *  @brief
    *    JSON output mode
    */
    enum OutputMode
    {
        Compact = 0, ///< Create JSON without indentation and newlines
        Beautify     ///< Create better readable JSON with indentation and newlines
    };


public:
    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[in] root
    *    Variant value
    *  @param[in] outputMode
    *    JSON output mode
    *
    *  @return
    *    JSON string
    */
    static std::string stringify(const Variant & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Load JSON from file
    *
    *  @param[out] root
    *    Output variant
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool load(Variant & root, const std::string & filename);

    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[out] root
    *    Output variant
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    'true' if all went fine, 'false' on error
    */
    static bool parse(Variant & root, const std::string & document);


private:
    static bool readDocument(Variant & root, Tokenizer & tokenizer);
    static bool readObject(Variant & root, Tokenizer & tokenizer);
    static bool readArray(Variant & root, Tokenizer & tokenizer);
    static bool readValue(Variant & value, Tokenizer::Token & token, Tokenizer & tokenizer);

    static std::string stringify(const Variant & root, bool beautify, const std::string & indent);
    static std::string escapeString(const std::string & in);
};


} // namespace cppexpose
