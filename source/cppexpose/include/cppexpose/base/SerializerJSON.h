
#pragma once


#include <cppexpose/base/Serializer.h>


namespace cppexpose
{


/**
*  @brief
*    JSON serializer
*/
class CPPEXPOSE_API SerializerJSON : public Serializer
{
public:
    /**
    *  @brief
    *    JSON output mode
    */
    enum OutputMode
    {
        Compact = 0,    ///< Create JSON without indentation and newlines
        Beautify        ///< Create better readable JSON with indentation and newlines
    };


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] outputMode
    *    JSON output mode
    */
    SerializerJSON(OutputMode outputMode = Compact);

    /**
    *  @brief
    *    Constructor
    */
    virtual ~SerializerJSON();

    // Virtual Serializer interface
    virtual bool fromString(Variant & obj, const std::string & string) override;
    virtual std::string toString(const Variant & obj) override;


protected:
    OutputMode m_outputMode;    ///< JSON output mode
};


} // namespace cppexpose
