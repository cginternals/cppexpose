
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>

#include "MyObject.h"


using namespace cppexpose;
using std::string;


template <typename T>
class PropertyInstantiation_test : public testing::Test
{
public:
    PropertyInstantiation_test()
    {
    }
};


typedef ::testing::Types<bool, float, double, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, string> InstantiationTypes;
TYPED_TEST_CASE(PropertyInstantiation_test, InstantiationTypes);


namespace
{


template <typename T>
T staticGetter()
{
    return T{};
}

template <typename T>
void staticSetter(T /*value*/)
{
}


}


// Property instantiaton (read/write)

TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] ()
    {
        return TypeParam();
    };

    auto set = [] (const TypeParam & /*val*/)
    {
    };

    auto prop = new Property<TypeParam>("Property", get, set);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}


TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<TypeParam>(&staticGetter<TypeParam>, &staticSetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}

/*
TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<TypeParam>("TestObject");
    auto prop = new Property<TypeParam>("Property", obj, &MyObject<TypeParam>::constgetterconst, &MyObject<TypeParam>::setterconst);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
    delete obj;
}
*/

TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<TypeParam>("TestObject");
    auto prop = new Property<TypeParam>("Property", obj, &MyObject<TypeParam>::getterconst, &MyObject<TypeParam>::setterconst);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
    delete obj;
}

/*
TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<TypeParam>("TestObject");
    auto prop = new Property<TypeParam>("Property", obj, &MyObject<TypeParam>::getterconst, &MyObject<TypeParam>::setter);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
    delete obj;
}
*/

// Property instantiaton (read only)

TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] ()
    {
        return TypeParam();
    };

    auto prop = new Property<const TypeParam>("Property", get);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}


TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const TypeParam>("Property", &staticGetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}

/*
TYPED_TEST(PropertyInstanceBool_test, instantiateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::constgetterconst);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
    delete obj;
}

TYPED_TEST(PropertyInstanceBool_test, instantiateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>("TestObject");
    auto prop = new Property<const bool>("boolProperty", obj, &MyObject<bool>::getterconst);

    ASSERT_EQ(typeid(bool), prop->type());

    delete prop;
    delete obj;
}
*/
