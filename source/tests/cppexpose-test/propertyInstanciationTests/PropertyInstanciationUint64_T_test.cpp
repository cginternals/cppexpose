
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceUint64_T_test : public testing::Test
{
public:
    PropertyInstanceUint64_T_test()
    {
    }

protected:
};

namespace {
uint64_t staticGetter()
{
    return uint64_t();
}

void staticSetter(uint64_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return uint64_t();};
    auto set = [] (const uint64_t & /*val*/) {};

    auto prop = new Property<uint64_t>("uint64_t-test", get, set);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<uint64_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>("TestObject");
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::constgetterconst, &MyObject<uint64_t>::setterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<uint64_t>("TestObject");
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<uint64_t>("TestObject");
    auto prop = new Property<uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst, &MyObject<uint64_t>::setter);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return uint64_t();};

    auto prop = new Property<const uint64_t>("uint64_tProperty", get);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const uint64_t>("uint64_tProperty", &staticGetter);

    ASSERT_EQ(typeid(uint64_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<uint64_t>("TestObject");
    auto prop = new Property<const uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::constgetterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceUint64_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<uint64_t>("TestObject");
    auto prop = new Property<const uint64_t>("uint64_tProperty", obj, &MyObject<uint64_t>::getterconst);

    ASSERT_EQ(typeid(uint64_t), prop->type());


    delete prop;
    delete obj;
} */
