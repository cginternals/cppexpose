
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt8_T_test : public testing::Test
{
public:
    PropertyInstanceInt8_T_test()
    {
    }

protected:
};

namespace {
int8_t staticGetter()
{
    return int8_t();
}

void staticSetter(int8_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int8_t();};
    auto set = [] (const int8_t & /*val*/) {};

    auto prop = new Property<int8_t>("int8_t-test", get, set);

    ASSERT_EQ(typeid(int8_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<int8_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(int8_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>("TestObject");
    auto prop = new Property<int8_t>("int8_tProperty", obj, &MyObject<int8_t>::constgetterconst, &MyObject<int8_t>::setterconst);

    ASSERT_EQ(typeid(int8_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>("TestObject");
    auto prop = new Property<int8_t>("int8_tProperty", obj, &MyObject<int8_t>::getterconst, &MyObject<int8_t>::setterconst);

    ASSERT_EQ(typeid(int8_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int8_t>("TestObject");
    auto prop = new Property<int8_t>("int8_tProperty", obj, &MyObject<int8_t>::getterconst, &MyObject<int8_t>::setter);

    ASSERT_EQ(typeid(int8_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceInt8_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return int8_t();};

    auto prop = new Property<const int8_t>("int8_tProperty", get);

    ASSERT_EQ(typeid(int8_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceInt8_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const int8_t>("int8_tProperty", &staticGetter);

    ASSERT_EQ(typeid(int8_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceInt8_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int8_t>("TestObject");
    auto prop = new Property<const int8_t>("int8_tProperty", obj, &MyObject<int8_t>::constgetterconst);

    ASSERT_EQ(typeid(int8_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int8_t>("TestObject");
    auto prop = new Property<const int8_t>("int8_tProperty", obj, &MyObject<int8_t>::getterconst);

    ASSERT_EQ(typeid(int8_t), prop->type());


    delete prop;
    delete obj;
} */
