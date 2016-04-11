
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint16_T_test : public testing::Test
{
public:
    PropertyInstanceUint16_T_test()
    {
    }

protected:
};

namespace {
uint16_t staticGetter()
{
    return uint16_t();
}

void staticSetter(uint16_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint16_t();};
    auto set = [] (const uint16_t & /*val*/) {};

    auto prop = new Property<uint16_t>("uint16_t-test", get, set);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

