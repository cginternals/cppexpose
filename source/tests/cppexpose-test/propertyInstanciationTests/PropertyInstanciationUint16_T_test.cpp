
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint16_T_test : public testing::Test
{
public:
    PropertyInstanceUint16_T_test()
    {
    }

protected:
};

namespace {
uint16_t staticGetter()
{
    return uint16_t();
}

void staticSetter(uint16_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint16_t();};
    auto set = [] (const uint16_t & /*val*/) {};

    auto prop = new Property<uint16_t>("uint16_t-test", get, set);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<uint16_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>("TestObject");
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::constgetterconst, &MyObject<uint16_t>::setterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint16_t>("TestObject");
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint16_t>("TestObject");
    auto prop = new Property<uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst, &MyObject<uint16_t>::setter);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return uint16_t();};

    auto prop = new Property<const uint16_t>("uint16_tProperty", get);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const uint16_t>("uint16_tProperty", &staticGetter);

    ASSERT_EQ(typeid(uint16_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<uint16_t>("TestObject");
    auto prop = new Property<const uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::constgetterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint16_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<uint16_t>("TestObject");
    auto prop = new Property<const uint16_t>("uint16_tProperty", obj, &MyObject<uint16_t>::getterconst);

    ASSERT_EQ(typeid(uint16_t), prop->type());


    delete prop;
    delete obj;
} */
