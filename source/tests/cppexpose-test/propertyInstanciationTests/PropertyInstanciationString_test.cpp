
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceString_test : public testing::Test
{
public:
    PropertyInstanceString_test()
    {
    }

protected:
};

namespace {
string staticGetter()
{
    return string();
}

void staticSetter(string /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return string();};
    auto set = [] (const string & /*val*/) {};

    auto prop = new Property<string>("string-test", get, set);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

