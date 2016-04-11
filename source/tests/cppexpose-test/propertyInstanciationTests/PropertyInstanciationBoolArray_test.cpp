

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceBoolArray_test : public testing::Test
{
public:
    PropertyInstanceBoolArray_test()
    {
    }

protected:
};

namespace {
bool staticGetter(size_t)
{
    return bool();
}

void staticSetter(size_t, bool /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceBoolArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return bool();};
    auto set = [] (size_t, const bool & /*val*/) {};

    auto prop = new PropertyArray<bool, 1>("boolProperty", get, set);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<bool, 1>("boolProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new PropertyArray<bool, 1>("boolProperty", obj, &MyObject<bool>::arrayConstgetterconst, &MyObject<bool>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new PropertyArray<bool, 1>("boolProperty", obj, &MyObject<bool>::arrayGetterconst, &MyObject<bool>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<bool>;
    auto prop = new PropertyArray<bool, 1>("boolProperty", obj, &MyObject<bool>::arrayGetterconst, &MyObject<bool>::arraySetter);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceBoolArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return bool();};

    auto prop = new PropertyArray<const bool, 1>("boolProperty", get);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const bool, 1>("boolProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new PropertyArray<const bool, 1>("boolProperty", obj, &MyObject<bool>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>;
    auto prop = new PropertyArray<const bool, 1>("boolProperty", obj, &MyObject<bool>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<bool, 1>();
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<bool, 1>(std::array<bool, 1>());
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return bool();};
    auto set = [] (size_t, const bool & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<bool, 1>(get, set);

    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<bool, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new ArrayAccessorGetSet<bool, 1>(obj, &MyObject<bool>::arrayConstgetterconst, &MyObject<bool>::arraySetterconst);
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new ArrayAccessorGetSet<bool, 1>(obj, &MyObject<bool>::arrayGetterconst, &MyObject<bool>::arraySetterconst);
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<bool>;
    auto accessor = new ArrayAccessorGetSet<bool, 1>(obj, &MyObject<bool>::arrayGetterconst, &MyObject<bool>::arraySetter);
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const bool, 1>();
    auto prop = new PropertyArray<const bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const bool, 1>(std::array<bool, 1>());
    auto prop = new PropertyArray<bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return bool();};
    auto accessor = new ArrayAccessorGetSet<const bool, 1>(get);

    auto prop = new PropertyArray<const bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const bool, 1>(&staticGetter);

    auto prop = new PropertyArray<const bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new ArrayAccessorGetSet<const bool, 1>(obj, &MyObject<bool>::arrayConstgetterconst);
    auto prop = new PropertyArray<const bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceBoolArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<bool>;
    auto accessor = new ArrayAccessorGetSet<const bool, 1>(obj, &MyObject<bool>::arrayGetterconst);
    auto prop = new PropertyArray<const bool, 1>("boolProperty", accessor);

    ASSERT_EQ(typeid(std::array<bool, 1>), prop->type());


    delete prop;
    delete obj;
}


