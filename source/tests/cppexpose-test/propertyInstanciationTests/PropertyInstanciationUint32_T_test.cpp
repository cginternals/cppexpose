
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint32_T_test : public testing::Test
{
public:
    PropertyInstanceUint32_T_test()
    {
    }

protected:
};

namespace {
uint32_t staticGetter()
{
    return uint32_t();
}

void staticSetter(uint32_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint32_t();};
    auto set = [] (const uint32_t & /*val*/) {};

    auto prop = new Property<uint32_t>("uint32_t-test", get, set);

    ASSERT_EQ(typeid(uint32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<uint32_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(uint32_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint32_t>("TestObject");
    auto prop = new Property<uint32_t>("uint32_tProperty", obj, &MyObject<uint32_t>::constgetterconst, &MyObject<uint32_t>::setterconst);

    ASSERT_EQ(typeid(uint32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint32_t>("TestObject");
    auto prop = new Property<uint32_t>("uint32_tProperty", obj, &MyObject<uint32_t>::getterconst, &MyObject<uint32_t>::setterconst);

    ASSERT_EQ(typeid(uint32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint32_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint32_t>("TestObject");
    auto prop = new Property<uint32_t>("uint32_tProperty", obj, &MyObject<uint32_t>::getterconst, &MyObject<uint32_t>::setter);

    ASSERT_EQ(typeid(uint32_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceUint32_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return uint32_t();};

    auto prop = new Property<const uint32_t>("uint32_tProperty", get);

    ASSERT_EQ(typeid(uint32_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceUint32_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const uint32_t>("uint32_tProperty", &staticGetter);

    ASSERT_EQ(typeid(uint32_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceUint32_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<uint32_t>("TestObject");
    auto prop = new Property<const uint32_t>("uint32_tProperty", obj, &MyObject<uint32_t>::constgetterconst);

    ASSERT_EQ(typeid(uint32_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint32_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<uint32_t>("TestObject");
    auto prop = new Property<const uint32_t>("uint32_tProperty", obj, &MyObject<uint32_t>::getterconst);

    ASSERT_EQ(typeid(uint32_t), prop->type());


    delete prop;
    delete obj;
} */
