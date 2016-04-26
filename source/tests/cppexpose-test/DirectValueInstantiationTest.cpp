
#include <gmock/gmock.h>

#include <cppexpose/typed/DirectValue.h>
#include <utility>

#include "MyObject.h"

using namespace cppexpose;
using std::string;


template <typename T>
class DirectValueInstantiation_test : public testing::Test
{
public:
    DirectValueInstantiation_test()
    {
    }

protected:
};

typedef ::testing::Types<bool, float, double, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, string> InstantiationTypes;
TYPED_TEST_CASE(DirectValueInstantiation_test, InstantiationTypes);

namespace {

}


// Propterty instanciaton (read/write)

TYPED_TEST(DirectValueInstantiation_test, instantiateDirectValue)
{

    auto directVal = new DirectValue<TypeParam>(TypeParam{});

    ASSERT_EQ(typeid(typename std::remove_cv<TypeParam>::type), directVal->type());

    delete directVal;
}

