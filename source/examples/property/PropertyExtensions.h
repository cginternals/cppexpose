
#pragma once


#include <cppexpose/reflection/Property.h>

#include "Mood.h"


namespace cppexpose
{


template <>
struct EnumDefaultStrings<Mood>
{
    std::map<Mood, std::string> operator()()
    {
        std::map<Mood, std::string> values;
        values[Mood::Neutral] = "Neutral";
        values[Mood::Happy]   = "Happy";
        values[Mood::Sad]     = "Sad";
        return values;
    }
};


}
