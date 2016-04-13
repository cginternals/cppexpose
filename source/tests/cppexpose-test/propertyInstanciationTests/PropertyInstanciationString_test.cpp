
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

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

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<string>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<string>("TestObject");
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::constgetterconst, &MyObject<string>::setterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<string>("TestObject");
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::getterconst, &MyObject<string>::setterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<string>("TestObject");
    auto prop = new Property<string>("stringProperty", obj, &MyObject<string>::getterconst, &MyObject<string>::setter);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return string();};

    auto prop = new Property<const string>("stringProperty", get);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const string>("stringProperty", &staticGetter);

    ASSERT_EQ(typeid(string), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<string>("TestObject");
    auto prop = new Property<const string>("stringProperty", obj, &MyObject<string>::constgetterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceString_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<string>("TestObject");
    auto prop = new Property<const string>("stringProperty", obj, &MyObject<string>::getterconst);

    ASSERT_EQ(typeid(string), prop->type());


    delete prop;
    delete obj;
} */
