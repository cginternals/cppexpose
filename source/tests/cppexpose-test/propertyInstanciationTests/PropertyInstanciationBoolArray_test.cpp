

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceBoolArray_test : public testing::Test
{
public:
    PropertyInstanceBoolArray_test()
    {
    }

protected:
};

namespace {
bool staticGetter(size_t)
{
    return bool();
}

void staticSetter(size_t, bool /*value*/)
{
}
}


