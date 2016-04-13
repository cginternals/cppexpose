
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

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

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<float>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<float>("TestObject");
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::constgetterconst, &MyObject<float>::setterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<float>("TestObject");
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::getterconst, &MyObject<float>::setterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<float>("TestObject");
    auto prop = new Property<float>("floatProperty", obj, &MyObject<float>::getterconst, &MyObject<float>::setter);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return float();};

    auto prop = new Property<const float>("floatProperty", get);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const float>("floatProperty", &staticGetter);

    ASSERT_EQ(typeid(float), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<float>("TestObject");
    auto prop = new Property<const float>("floatProperty", obj, &MyObject<float>::constgetterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloat_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<float>("TestObject");
    auto prop = new Property<const float>("floatProperty", obj, &MyObject<float>::getterconst);

    ASSERT_EQ(typeid(float), prop->type());


    delete prop;
    delete obj;
} */
