

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceFloatArray_test : public testing::Test
{
public:
    PropertyInstanceFloatArray_test()
    {
    }

protected:
};

namespace {
float staticGetter(size_t)
{
    return float();
}

void staticSetter(size_t, float /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceFloatArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return float();};
    auto set = [] (size_t, const float & /*val*/) {};

    auto prop = new PropertyArray<float, 1>("floatProperty", get, set);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<float, 1>("floatProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new PropertyArray<float, 1>("floatProperty", obj, &MyObject<float>::arrayConstgetterconst, &MyObject<float>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new PropertyArray<float, 1>("floatProperty", obj, &MyObject<float>::arrayGetterconst, &MyObject<float>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<float>;
    auto prop = new PropertyArray<float, 1>("floatProperty", obj, &MyObject<float>::arrayGetterconst, &MyObject<float>::arraySetter);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceFloatArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return float();};

    auto prop = new PropertyArray<const float, 1>("floatProperty", get);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const float, 1>("floatProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new PropertyArray<const float, 1>("floatProperty", obj, &MyObject<float>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<float>;
    auto prop = new PropertyArray<const float, 1>("floatProperty", obj, &MyObject<float>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<float, 1>();
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<float, 1>(std::array<float, 1>());
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return float();};
    auto set = [] (size_t, const float & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<float, 1>(get, set);

    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<float, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new ArrayAccessorGetSet<float, 1>(obj, &MyObject<float>::arrayConstgetterconst, &MyObject<float>::arraySetterconst);
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new ArrayAccessorGetSet<float, 1>(obj, &MyObject<float>::arrayGetterconst, &MyObject<float>::arraySetterconst);
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<float>;
    auto accessor = new ArrayAccessorGetSet<float, 1>(obj, &MyObject<float>::arrayGetterconst, &MyObject<float>::arraySetter);
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const float, 1>();
    auto prop = new PropertyArray<const float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const float, 1>(std::array<float, 1>());
    auto prop = new PropertyArray<float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return float();};
    auto accessor = new ArrayAccessorGetSet<const float, 1>(get);

    auto prop = new PropertyArray<const float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const float, 1>(&staticGetter);

    auto prop = new PropertyArray<const float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new ArrayAccessorGetSet<const float, 1>(obj, &MyObject<float>::arrayConstgetterconst);
    auto prop = new PropertyArray<const float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceFloatArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<float>;
    auto accessor = new ArrayAccessorGetSet<const float, 1>(obj, &MyObject<float>::arrayGetterconst);
    auto prop = new PropertyArray<const float, 1>("floatProperty", accessor);

    ASSERT_EQ(typeid(std::array<float, 1>), prop->type());


    delete prop;
    delete obj;
}


