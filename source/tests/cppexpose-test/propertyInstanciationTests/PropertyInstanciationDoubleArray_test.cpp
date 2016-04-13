

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceDoubleArray_test : public testing::Test
{
public:
    PropertyInstanceDoubleArray_test()
    {
    }

protected:
};

namespace {
double staticGetter(size_t)
{
    return double();
}

void staticSetter(size_t, double /*value*/)
{
}
}


