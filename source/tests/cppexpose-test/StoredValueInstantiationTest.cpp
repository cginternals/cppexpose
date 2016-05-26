
#include <gmock/gmock.h>
#include <array>

#include <cppexpose/typed/DirectValue.h>
#include <cppexpose/typed/StoredValue.h>
#include <utility>

#include "MyObject.h"

using namespace cppexpose;
using std::string;


template <typename T>
class StoredValueInstantiation_test : public testing::Test
{
public:
    StoredValueInstantiation_test()
    {
    }

protected:
};

typedef ::testing::Types<bool, float, double, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, string, std::array<int, 4>> InstantiationTypes;
TYPED_TEST_CASE(StoredValueInstantiation_test, InstantiationTypes);


// StoredValue instantiaton (read/write)

TYPED_TEST(StoredValueInstantiation_test, instantiateStoredValue)
{
    auto storedVal = new StoredValue<TypeParam>();

    ASSERT_EQ(typeid(typename std::remove_cv<TypeParam>::type), storedVal->type());

    delete storedVal;
}

