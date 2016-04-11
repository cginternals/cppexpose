
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt32_T_test : public testing::Test
{
public:
    PropertyInstanceInt32_T_test()
    {
    }

protected:
};

namespace {
int32_t staticGetter()
{
    return int32_t();
}

void staticSetter(int32_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt32_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int32_t();};
    auto set = [] (const int32_t & /*val*/) {};

    auto prop = new Property<int32_t>("int32_t-test", get, set);

    ASSERT_EQ(typeid(int32_t), prop->type());

    delete prop;
}

