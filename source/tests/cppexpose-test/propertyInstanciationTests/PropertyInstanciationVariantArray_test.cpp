

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceVariantArray_test : public testing::Test
{
public:
    PropertyInstanceVariantArray_test()
    {
    }

protected:
};

namespace {
Variant staticGetter(size_t)
{
    return Variant();
}

void staticSetter(size_t, Variant /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceVariantArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return Variant();};
    auto set = [] (size_t, const Variant & /*val*/) {};

    auto prop = new PropertyArray<Variant, 1>("VariantProperty", get, set);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", obj, &MyObject<Variant>::arrayConstgetterconst, &MyObject<Variant>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", obj, &MyObject<Variant>::arrayGetterconst, &MyObject<Variant>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<Variant>;
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", obj, &MyObject<Variant>::arrayGetterconst, &MyObject<Variant>::arraySetter);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceVariantArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return Variant();};

    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", get);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", obj, &MyObject<Variant>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<Variant>;
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", obj, &MyObject<Variant>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<Variant, 1>();
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<Variant, 1>(std::array<Variant, 1>());
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return Variant();};
    auto set = [] (size_t, const Variant & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<Variant, 1>(get, set);

    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<Variant, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new ArrayAccessorGetSet<Variant, 1>(obj, &MyObject<Variant>::arrayConstgetterconst, &MyObject<Variant>::arraySetterconst);
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new ArrayAccessorGetSet<Variant, 1>(obj, &MyObject<Variant>::arrayGetterconst, &MyObject<Variant>::arraySetterconst);
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new ArrayAccessorGetSet<Variant, 1>(obj, &MyObject<Variant>::arrayGetterconst, &MyObject<Variant>::arraySetter);
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const Variant, 1>();
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const Variant, 1>(std::array<Variant, 1>());
    auto prop = new PropertyArray<Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return Variant();};
    auto accessor = new ArrayAccessorGetSet<const Variant, 1>(get);

    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const Variant, 1>(&staticGetter);

    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new ArrayAccessorGetSet<const Variant, 1>(obj, &MyObject<Variant>::arrayConstgetterconst);
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceVariantArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<Variant>;
    auto accessor = new ArrayAccessorGetSet<const Variant, 1>(obj, &MyObject<Variant>::arrayGetterconst);
    auto prop = new PropertyArray<const Variant, 1>("VariantProperty", accessor);

    ASSERT_EQ(typeid(std::array<Variant, 1>), prop->type());


    delete prop;
    delete obj;
}


