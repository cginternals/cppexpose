

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceFloatArray_test : public testing::Test
{
public:
    PropertyInstanceFloatArray_test()
    {
    }

protected:
};

namespace {
float staticGetter(size_t)
{
    return float();
}

void staticSetter(size_t, float /*value*/)
{
}
}


