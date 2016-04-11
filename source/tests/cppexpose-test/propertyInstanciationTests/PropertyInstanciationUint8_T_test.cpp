
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint8_T_test : public testing::Test
{
public:
    PropertyInstanceUint8_T_test()
    {
    }

protected:
};

namespace {
uint8_t staticGetter()
{
    return uint8_t();
}

void staticSetter(uint8_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint8_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint8_t();};
    auto set = [] (const uint8_t & /*val*/) {};

    auto prop = new Property<uint8_t>("uint8_t-test", get, set);

    ASSERT_EQ(typeid(uint8_t), prop->type());

    delete prop;
}

