

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceVariantArray_test : public testing::Test
{
public:
    PropertyInstanceVariantArray_test()
    {
    }

protected:
};

namespace {
Variant staticGetter(size_t)
{
    return Variant();
}

void staticSetter(size_t, Variant /*value*/)
{
}
}


