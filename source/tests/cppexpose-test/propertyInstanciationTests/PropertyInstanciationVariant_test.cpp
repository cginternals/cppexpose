
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceVariant_test : public testing::Test
{
public:
    PropertyInstanceVariant_test()
    {
    }

protected:
};

namespace {
Variant staticGetter()
{
    return Variant();
}

void staticSetter(Variant /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return Variant();};
    auto set = [] (const Variant & /*val*/) {};

    auto prop = new Property<Variant>("Variant-test", get, set);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<Variant>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>("TestObject");
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::constgetterconst, &MyObject<Variant>::setterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>("TestObject");
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<Variant>("TestObject");
    auto prop = new Property<Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst, &MyObject<Variant>::setter);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return Variant();};

    auto prop = new Property<const Variant>("VariantProperty", get);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const Variant>("VariantProperty", &staticGetter);

    ASSERT_EQ(typeid(Variant), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<Variant>("TestObject");
    auto prop = new Property<const Variant>("VariantProperty", obj, &MyObject<Variant>::constgetterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariant_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<Variant>("TestObject");
    auto prop = new Property<const Variant>("VariantProperty", obj, &MyObject<Variant>::getterconst);

    ASSERT_EQ(typeid(Variant), prop->type());


    delete prop;
    delete obj;
} */
