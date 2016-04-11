

#include <gmock/gmock.h>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;
using std::string;



class PropertyInstanceDoubleArray_test : public testing::Test
{
public:
    PropertyInstanceDoubleArray_test()
    {
    }

protected:
};

namespace {
double staticGetter(size_t)
{
    return double();
}

void staticSetter(size_t, double /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceDoubleArray_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return double();};
    auto set = [] (size_t, const double & /*val*/) {};

    auto prop = new PropertyArray<double, 1>("doubleProperty", get, set);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new PropertyArray<double, 1>("doubleProperty", &staticGetter, &staticSetter);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new PropertyArray<double, 1>("doubleProperty", obj, &MyObject<double>::arrayConstgetterconst, &MyObject<double>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new PropertyArray<double, 1>("doubleProperty", obj, &MyObject<double>::arrayGetterconst, &MyObject<double>::arraySetterconst);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<double>;
    auto prop = new PropertyArray<double, 1>("doubleProperty", obj, &MyObject<double>::arrayGetterconst, &MyObject<double>::arraySetter);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return double();};

    auto prop = new PropertyArray<const double, 1>("doubleProperty", get);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new PropertyArray<const double, 1>("doubleProperty", &staticGetter);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new PropertyArray<const double, 1>("doubleProperty", obj, &MyObject<double>::arrayConstgetterconst);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<double>;
    auto prop = new PropertyArray<const double, 1>("doubleProperty", obj, &MyObject<double>::arrayGetterconst);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<double, 1>();
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<double, 1>(std::array<double, 1>());
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] (size_t) {return double();};
    auto set = [] (size_t, const double & /*val*/) {};
    auto accessor = new ArrayAccessorGetSet<double, 1>(get, set);

    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_StaticGetter_StaticSetter)
{
    auto accessor = new ArrayAccessorGetSet<double, 1>(&staticGetter, &staticSetter);

    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new ArrayAccessorGetSet<double, 1>(obj, &MyObject<double>::arrayConstgetterconst, &MyObject<double>::arraySetterconst);
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new ArrayAccessorGetSet<double, 1>(obj, &MyObject<double>::arrayGetterconst, &MyObject<double>::arraySetterconst);
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<double>;
    auto accessor = new ArrayAccessorGetSet<double, 1>(obj, &MyObject<double>::arrayGetterconst, &MyObject<double>::arraySetter);
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String)
{
    auto accessor = new ArrayAccessorValue<const double, 1>();
    auto prop = new PropertyArray<const double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new ArrayAccessorValue<const double, 1>(std::array<double, 1>());
    auto prop = new PropertyArray<double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String_LambdaGetter)
{
    auto get = [] (size_t) {return double();};
    auto accessor = new ArrayAccessorGetSet<const double, 1>(get);

    auto prop = new PropertyArray<const double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String_StaticGetter)
{
    auto accessor = new ArrayAccessorGetSet<const double, 1>(&staticGetter);

    auto prop = new PropertyArray<const double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new ArrayAccessorGetSet<const double, 1>(obj, &MyObject<double>::arrayConstgetterconst);
    auto prop = new PropertyArray<const double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceDoubleArray_test, instanciateConstAccessorWith_String_Object_GetterConst)
{
    auto obj = new MyObject<double>;
    auto accessor = new ArrayAccessorGetSet<const double, 1>(obj, &MyObject<double>::arrayGetterconst);
    auto prop = new PropertyArray<const double, 1>("doubleProperty", accessor);

    ASSERT_EQ(typeid(std::array<double, 1>), prop->type());


    delete prop;
    delete obj;
}


