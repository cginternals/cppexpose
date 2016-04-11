
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint32_T_test : public testing::Test
{
public:
    PropertyInstanceUint32_T_test()
    {
    }

protected:
};

namespace {
uint32_t staticGetter()
{
    return uint32_t();
}

void staticSetter(uint32_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint32_t();};
    auto set = [] (const uint32_t & /*val*/) {};

    auto prop = new Property<uint32_t>("uint32_t-test", get, set);

    ASSERT_EQ(typeid(uint32_t), prop->type());

    delete prop;
}

