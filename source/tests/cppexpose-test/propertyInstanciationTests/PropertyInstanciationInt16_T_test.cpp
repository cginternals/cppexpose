
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt16_T_test : public testing::Test
{
public:
    PropertyInstanceInt16_T_test()
    {
    }

protected:
};

namespace {
int16_t staticGetter()
{
    return int16_t();
}

void staticSetter(int16_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int16_t();};
    auto set = [] (const int16_t & /*val*/) {};

    auto prop = new Property<int16_t>("int16_t-test", get, set);

    ASSERT_EQ(typeid(int16_t), prop->type());

    delete prop;
}

