
#include <array>

#include <gmock/gmock.h>

#include <cppexpose/reflection/Object.h>
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
    Object object;

    auto get = [] ()
    {
        return TypeParam();
    };

    auto set = [] (const TypeParam & /*val*/)
    {
    };

    auto prop = cppassist::make_unique<Property<TypeParam>>("Property", &object, get, set);

    ASSERT_EQ(typeid(TypeParam), prop->type());
}


TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_StaticGetter_StaticSetter)
{
    Object object;

    auto prop = cppassist::make_unique<Property<TypeParam>>("Property", &object, &staticGetter<TypeParam>, &staticSetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());
}

TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_Object_GetterConst_SetterConst)
{
    Object object;

    auto obj = cppassist::make_unique<MyObject<TypeParam>>("TestObject");
    auto prop = cppassist::make_unique<Property<TypeParam>>("Property", &object, obj.get(), &MyObject<TypeParam>::getterconst, &MyObject<TypeParam>::setterconst);

    ASSERT_EQ(typeid(TypeParam), prop->type());
}

// Property instantiaton (read only)

TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_LambdaGetter)
{
    Object object;

    auto get = [] ()
    {
        return TypeParam();
    };

    auto prop = cppassist::make_unique<Property<const TypeParam>>("Property", &object, get);

    ASSERT_EQ(typeid(TypeParam), prop->type());
}


TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_StaticGetter)
{
    Object object;

    auto prop = cppassist::make_unique<Property<const TypeParam>>("Property", &object, &staticGetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());
}
