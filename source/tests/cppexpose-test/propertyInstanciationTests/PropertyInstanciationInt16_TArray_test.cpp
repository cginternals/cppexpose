

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceInt16_TArray_test : public testing::Test
{
public:
    PropertyInstanceInt16_TArray_test()
    {
    }

protected:
};

namespace {
int16_t staticGetter(size_t)
{
    return int16_t();
}

void staticSetter(size_t, int16_t /*value*/)
{
}
}


