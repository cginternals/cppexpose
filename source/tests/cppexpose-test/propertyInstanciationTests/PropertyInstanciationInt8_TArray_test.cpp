

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceInt8_TArray_test : public testing::Test
{
public:
    PropertyInstanceInt8_TArray_test()
    {
    }

protected:
};

namespace {
int8_t staticGetter(size_t)
{
    return int8_t();
}

void staticSetter(size_t, int8_t /*value*/)
{
}
}


