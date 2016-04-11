
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt64_T_test : public testing::Test
{
public:
    PropertyInstanceInt64_T_test()
    {
    }

protected:
};

namespace {
int64_t staticGetter()
{
    return int64_t();
}

void staticSetter(int64_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int64_t();};
    auto set = [] (const int64_t & /*val*/) {};

    auto prop = new Property<int64_t>("int64_t-test", get, set);

    ASSERT_EQ(typeid(int64_t), prop->type());

    delete prop;
}

