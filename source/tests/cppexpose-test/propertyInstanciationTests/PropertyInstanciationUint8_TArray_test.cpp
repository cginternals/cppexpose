

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceUint8_TArray_test : public testing::Test
{
public:
    PropertyInstanceUint8_TArray_test()
    {
    }

protected:
};

namespace {
uint8_t staticGetter(size_t)
{
    return uint8_t();
}

void staticSetter(size_t, uint8_t /*value*/)
{
}
}


