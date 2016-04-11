

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceStringArray_test : public testing::Test
{
public:
    PropertyInstanceStringArray_test()
    {
    }

protected:
};

namespace {
string staticGetter(size_t)
{
    return string();
}

void staticSetter(size_t, string /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceStringArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return string();};
    auto set = [] (size_t, const string & /*val*/) {};

    auto prop = new PropertyArray<string, 1>("stringProperty", get, set);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<string, 1>("stringProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new PropertyArray<string, 1>("stringProperty", obj, &MyObject<string>::arrayConstgetterconst, &MyObject<string>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new PropertyArray<string, 1>("stringProperty", obj, &MyObject<string>::arrayGetterconst, &MyObject<string>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<string>;
    auto prop = new PropertyArray<string, 1>("stringProperty", obj, &MyObject<string>::arrayGetterconst, &MyObject<string>::arraySetter);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceStringArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return string();};

    auto prop = new PropertyArray<const string, 1>("stringProperty", get);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const string, 1>("stringProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new PropertyArray<const string, 1>("stringProperty", obj, &MyObject<string>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<string>;
    auto prop = new PropertyArray<const string, 1>("stringProperty", obj, &MyObject<string>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<string, 1>();
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<string, 1>(std::array<string, 1>());
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return string();};
    auto set = [] (size_t, const string & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<string, 1>(get, set);

    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<string, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new ArrayAccessorGetSet<string, 1>(obj, &MyObject<string>::arrayConstgetterconst, &MyObject<string>::arraySetterconst);
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new ArrayAccessorGetSet<string, 1>(obj, &MyObject<string>::arrayGetterconst, &MyObject<string>::arraySetterconst);
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<string>;
    auto accessor = new ArrayAccessorGetSet<string, 1>(obj, &MyObject<string>::arrayGetterconst, &MyObject<string>::arraySetter);
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const string, 1>();
    auto prop = new PropertyArray<const string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const string, 1>(std::array<string, 1>());
    auto prop = new PropertyArray<string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return string();};
    auto accessor = new ArrayAccessorGetSet<const string, 1>(get);

    auto prop = new PropertyArray<const string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const string, 1>(&staticGetter);

    auto prop = new PropertyArray<const string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new ArrayAccessorGetSet<const string, 1>(obj, &MyObject<string>::arrayConstgetterconst);
    auto prop = new PropertyArray<const string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceStringArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<string>;
    auto accessor = new ArrayAccessorGetSet<const string, 1>(obj, &MyObject<string>::arrayGetterconst);
    auto prop = new PropertyArray<const string, 1>("stringProperty", accessor);

    ASSERT_EQ(typeid(std::array<string, 1>), prop->type());


    delete prop;
    delete obj;
}


