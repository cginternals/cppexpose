
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt16_T_test : public testing::Test
{
public:
    PropertyInstanceInt16_T_test()
    {
    }

protected:
};

namespace {
int16_t staticGetter()
{
    return int16_t();
}

void staticSetter(int16_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int16_t();};
    auto set = [] (const int16_t & /*val*/) {};

    auto prop = new Property<int16_t>("int16_t-test", get, set);

    ASSERT_EQ(typeid(int16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<int16_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(int16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int16_t>("TestObject");
    auto prop = new Property<int16_t>("int16_tProperty", obj, &MyObject<int16_t>::constgetterconst, &MyObject<int16_t>::setterconst);

    ASSERT_EQ(typeid(int16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int16_t>("TestObject");
    auto prop = new Property<int16_t>("int16_tProperty", obj, &MyObject<int16_t>::getterconst, &MyObject<int16_t>::setterconst);

    ASSERT_EQ(typeid(int16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt16_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int16_t>("TestObject");
    auto prop = new Property<int16_t>("int16_tProperty", obj, &MyObject<int16_t>::getterconst, &MyObject<int16_t>::setter);

    ASSERT_EQ(typeid(int16_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceInt16_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return int16_t();};

    auto prop = new Property<const int16_t>("int16_tProperty", get);

    ASSERT_EQ(typeid(int16_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceInt16_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const int16_t>("int16_tProperty", &staticGetter);

    ASSERT_EQ(typeid(int16_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceInt16_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int16_t>("TestObject");
    auto prop = new Property<const int16_t>("int16_tProperty", obj, &MyObject<int16_t>::constgetterconst);

    ASSERT_EQ(typeid(int16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt16_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int16_t>("TestObject");
    auto prop = new Property<const int16_t>("int16_tProperty", obj, &MyObject<int16_t>::getterconst);

    ASSERT_EQ(typeid(int16_t), prop->type());


    delete prop;
    delete obj;
} */
