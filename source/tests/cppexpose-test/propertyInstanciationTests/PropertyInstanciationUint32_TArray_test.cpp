

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceUint32_TArray_test : public testing::Test
{
public:
    PropertyInstanceUint32_TArray_test()
    {
    }

protected:
};

namespace {
uint32_t staticGetter(size_t)
{
    return uint32_t();
}

void staticSetter(size_t, uint32_t /*value*/)
{
}
}


