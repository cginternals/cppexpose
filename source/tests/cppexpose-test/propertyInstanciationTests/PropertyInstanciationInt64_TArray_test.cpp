

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;


class PropertyInstanceInt64_TArray_test : public testing::Test
{
public:
    PropertyInstanceInt64_TArray_test()
    {
    }

protected:
};

namespace {
int64_t staticGetter(size_t)
{
    return int64_t();
}

void staticSetter(size_t, int64_t /*value*/)
{
}
}


