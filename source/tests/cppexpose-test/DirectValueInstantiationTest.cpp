
#include <array>

#include <gmock/gmock.h>

#include <cppexpose/typed/DirectValue.h>

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

typedef ::testing::Types<bool, float, double, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, string, std::array<int, 4>> InstantiationTypes;
TYPED_TEST_CASE(DirectValueInstantiation_test, InstantiationTypes);


// DirectValue instantiaton (read/write)

TYPED_TEST(DirectValueInstantiation_test, instantiateDirectValue)
{
    auto directVal = cppassist::make_unique<DirectValue<TypeParam>>(TypeParam{});

    ASSERT_EQ(typeid(typename std::remove_cv<TypeParam>::type), directVal->type());
}

