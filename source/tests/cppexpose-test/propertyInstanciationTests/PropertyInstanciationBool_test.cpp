
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

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

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<bool>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::constgetterconst, &MyObject<bool>::setterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::getterconst, &MyObject<bool>::setterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<bool>("boolProperty", obj, &MyObject<bool>::getterconst, &MyObject<bool>::setter);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return bool();};

    auto prop = new Property<const bool>("boolProperty", get);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const bool>("boolProperty", &staticGetter);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::constgetterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBool_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::getterconst);

    ASSERT_EQ(typeid(bool), prop->type());


    delete prop;
    delete obj;
} */
