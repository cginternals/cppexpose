
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceVariant_test : public testing::Test
{
public:
    PropertyInstanceVariant_test()
    {
    }

protected:
};

namespace {
Variant staticGetter()
{
    return Variant();
}

void staticSetter(Variant /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return Variant();};
    auto set = [] (const Variant & /*val*/) {};

    auto prop = new Property<Variant>("Variant-test", get, set);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

