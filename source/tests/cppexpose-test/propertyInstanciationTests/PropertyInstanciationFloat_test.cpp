
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceFloat_test : public testing::Test
{
public:
    PropertyInstanceFloat_test()
    {
    }

protected:
};

namespace {
float staticGetter()
{
    return float();
}

void staticSetter(float /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return float();};
    auto set = [] (const float & /*val*/) {};

    auto prop = new Property<float>("float-test", get, set);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

