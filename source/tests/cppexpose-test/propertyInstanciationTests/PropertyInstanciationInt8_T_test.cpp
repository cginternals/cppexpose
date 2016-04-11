
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt8_T_test : public testing::Test
{
public:
    PropertyInstanceInt8_T_test()
    {
    }

protected:
};

namespace {
int8_t staticGetter()
{
    return int8_t();
}

void staticSetter(int8_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int8_t();};
    auto set = [] (const int8_t & /*val*/) {};

    auto prop = new Property<int8_t>("int8_t-test", get, set);

    ASSERT_EQ(typeid(int8_t), prop->type());

    delete prop;
}

