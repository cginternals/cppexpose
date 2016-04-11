

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceInt8_TArray_test : public testing::Test
{
public:
    PropertyInstanceInt8_TArray_test()
    {
    }

protected:
};

namespace {
int8_t staticGetter(size_t)
{
    return int8_t();
}

void staticSetter(size_t, int8_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt8_TArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return int8_t();};
    auto set = [] (size_t, const int8_t & /*val*/) {};

    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", get, set);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", obj, &MyObject<int8_t>::arrayConstgetterconst, &MyObject<int8_t>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", obj, &MyObject<int8_t>::arrayGetterconst, &MyObject<int8_t>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int8_t>;
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", obj, &MyObject<int8_t>::arrayGetterconst, &MyObject<int8_t>::arraySetter);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return int8_t();};

    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", get);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", obj, &MyObject<int8_t>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", obj, &MyObject<int8_t>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<int8_t, 1>();
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<int8_t, 1>(std::array<int8_t, 1>());
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return int8_t();};
    auto set = [] (size_t, const int8_t & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<int8_t, 1>(get, set);

    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<int8_t, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto accessor = new ArrayAccessorGetSet<int8_t, 1>(obj, &MyObject<int8_t>::arrayConstgetterconst, &MyObject<int8_t>::arraySetterconst);
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto accessor = new ArrayAccessorGetSet<int8_t, 1>(obj, &MyObject<int8_t>::arrayGetterconst, &MyObject<int8_t>::arraySetterconst);
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int8_t>;
    auto accessor = new ArrayAccessorGetSet<int8_t, 1>(obj, &MyObject<int8_t>::arrayGetterconst, &MyObject<int8_t>::arraySetter);
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const int8_t, 1>();
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const int8_t, 1>(std::array<int8_t, 1>());
    auto prop = new PropertyArray<int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return int8_t();};
    auto accessor = new ArrayAccessorGetSet<const int8_t, 1>(get);

    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const int8_t, 1>(&staticGetter);

    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto accessor = new ArrayAccessorGetSet<const int8_t, 1>(obj, &MyObject<int8_t>::arrayConstgetterconst);
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt8_TArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int8_t>;
    auto accessor = new ArrayAccessorGetSet<const int8_t, 1>(obj, &MyObject<int8_t>::arrayGetterconst);
    auto prop = new PropertyArray<const int8_t, 1>("int8_tProperty", accessor);

    ASSERT_EQ(typeid(std::array<int8_t, 1>), prop->type());


    delete prop;
    delete obj;
}


