
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

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

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<double>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<double>("TestObject");
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::constgetterconst, &MyObject<double>::setterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<double>("TestObject");
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::getterconst, &MyObject<double>::setterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<double>("TestObject");
    auto prop = new Property<double>("doubleProperty", obj, &MyObject<double>::getterconst, &MyObject<double>::setter);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return double();};

    auto prop = new Property<const double>("doubleProperty", get);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const double>("doubleProperty", &staticGetter);

    ASSERT_EQ(typeid(double), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<double>("TestObject");
    auto prop = new Property<const double>("doubleProperty", obj, &MyObject<double>::constgetterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDouble_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<double>("TestObject");
    auto prop = new Property<const double>("doubleProperty", obj, &MyObject<double>::getterconst);

    ASSERT_EQ(typeid(double), prop->type());


    delete prop;
    delete obj;
} */
