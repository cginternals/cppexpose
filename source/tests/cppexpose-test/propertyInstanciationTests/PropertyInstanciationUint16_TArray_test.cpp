

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceUint16_TArray_test : public testing::Test
{
public:
    PropertyInstanceUint16_TArray_test()
    {
    }

protected:
};

namespace {
uint16_t staticGetter(size_t)
{
    return uint16_t();
}

void staticSetter(size_t, uint16_t /*value*/)
{
}
}


