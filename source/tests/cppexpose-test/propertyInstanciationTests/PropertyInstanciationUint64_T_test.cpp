
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint64_T_test : public testing::Test
{
public:
    PropertyInstanceUint64_T_test()
    {
    }

protected:
};

namespace {
uint64_t staticGetter()
{
    return uint64_t();
}

void staticSetter(uint64_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint64_t();};
    auto set = [] (const uint64_t & /*val*/) {};

    auto prop = new Property<uint64_t>("uint64_t-test", get, set);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

