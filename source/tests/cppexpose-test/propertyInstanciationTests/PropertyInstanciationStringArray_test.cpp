

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceStringArray_test : public testing::Test
{
public:
    PropertyInstanceStringArray_test()
    {
    }

protected:
};

namespace {
string staticGetter(size_t)
{
    return string();
}

void staticSetter(size_t, string /*value*/)
{
}
}


