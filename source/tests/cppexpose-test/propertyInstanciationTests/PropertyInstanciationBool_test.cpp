
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceBool_test : public testing::Test
{
public:
    PropertyInstanceBool_test()
    {
    }

protected:
};

namespace {
bool staticGetter()
{
    return bool();
}

void staticSetter(bool /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return bool();};
    auto set = [] (const bool & /*val*/) {};

    auto prop = new Property<bool>("bool-test", get, set);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

