
#include <array>

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/reflection/PropertyGroup.h>

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

    PropertyGroup propGroup;

    auto get = [] ()
    {
        return TypeParam();
    };

    auto set = [] (const TypeParam & /*val*/)
    {
    };

    auto prop = new Property<TypeParam>("Property", &propGroup, get, set);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}


TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_StaticGetter_StaticSetter)
{

    PropertyGroup propGroup;

    auto prop = new Property<TypeParam>("Property", &propGroup, &staticGetter<TypeParam>, &staticSetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}

TYPED_TEST(PropertyInstantiation_test, instantiatePropertyWith_String_Object_GetterConst_SetterConst)
{
    PropertyGroup propGroup;
    auto obj = new MyObject<TypeParam>("TestObject");
    auto prop = new Property<TypeParam>("Property", &propGroup, obj, &MyObject<TypeParam>::getterconst, &MyObject<TypeParam>::setterconst);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
    delete obj;
}

// Property instantiaton (read only)

TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_LambdaGetter)
{
    PropertyGroup propGroup;
    auto get = [] ()
    {
        return TypeParam();
    };

    auto prop = new Property<const TypeParam>("Property", &propGroup, get);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}


TYPED_TEST(PropertyInstantiation_test, instantiateConstPropertyWith_String_StaticGetter)
{
    PropertyGroup propGroup;
    auto prop = new Property<const TypeParam>("Property", &propGroup, &staticGetter<TypeParam>);

    ASSERT_EQ(typeid(TypeParam), prop->type());

    delete prop;
}
