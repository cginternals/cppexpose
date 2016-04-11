
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceDouble_test : public testing::Test
{
public:
    PropertyInstanceDouble_test()
    {
    }

protected:
};

namespace {
double staticGetter()
{
    return double();
}

void staticSetter(double /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return double();};
    auto set = [] (const double & /*val*/) {};

    auto prop = new Property<double>("double-test", get, set);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

