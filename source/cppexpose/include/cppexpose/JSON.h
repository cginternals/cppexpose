
#pragma once


#include <string>
#include <ostream>

#include <cppexpose/cppexpose_api.h>


namespace cppexpose
{


class AbstractVar;
class Variant;
class Object;
class Array;


/**
*  @brief
*    JSON import/export
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
    *    Save data to JSON
    *
    *  @param[in] root
    *    Typed value
    *  @param[in] outputMode
    *    JSON output mode
    *
    *  @return
    *    JSON string
    */
    static std::string stringify(const AbstractVar & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Save data to JSON
    *
    *  @param[in] stream
    *    Stream to write results to
    *  @param[in] root
    *    Typed value
    *  @param[in] outputMode
    *    JSON output mode
    */
    static void stringify(std::ostream & stream, const AbstractVar & root, OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Load JSON from file
    *
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    Read value, empty on error
    */
    static Variant load(const std::string & filename);

    /**
    *  @brief
    *    Load JSON object from file
    *
    *  @param[out] obj
    *    Object
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    'true' if object could be parsed without error, else 'false'
    */
    static bool load(Object & obj, const std::string & filename);

    /**
    *  @brief
    *    Load JSON array from file
    *
    *  @param[out] array
    *    Array
    *  @param[in] filename
    *    Filename of JSON file
    *
    *  @return
    *    'true' if array could be parsed without error, else 'false'
    */
    static bool load(Array & array, const std::string & filename);

    /**
    *  @brief
    *    Parse JSON from string
    *
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    Read value, empty on error
    */
    static Variant parse(const std::string & document);

    /**
    *  @brief
    *    Parse JSON object from string
    *
    *  @param[out] obj
    *    Object
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    'true' if object could be parsed without error, else 'false'
    */
    static bool parse(Object & obj, const std::string & document);

    /**
    *  @brief
    *    Parse JSON array from string
    *
    *  @param[out] array
    *    Array
    *  @param[in] document
    *    JSON string
    *
    *  @return
    *    'true' if array could be parsed without error, else 'false'
    */
    static bool parse(Array & array, const std::string & document);
};


} // namespace cppexpose
