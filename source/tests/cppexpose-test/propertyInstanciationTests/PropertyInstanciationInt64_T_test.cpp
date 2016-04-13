
#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>

#include "../MyObject.h"

using namespace cppexpose;
using std::string;



class PropertyInstanceInt64_T_test : public testing::Test
{
public:
    PropertyInstanceInt64_T_test()
    {
    }

protected:
};

namespace {
int64_t staticGetter()
{
    return int64_t();
}

void staticSetter(int64_t /*value*/)
{
}
}


// Propterty instanciaton (read/write)

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return int64_t();};
    auto set = [] (const int64_t & /*val*/) {};

    auto prop = new Property<int64_t>("int64_t-test", get, set);

    ASSERT_EQ(typeid(int64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_StaticGetter_StaticSetter)
{
    auto prop = new StoredValue<int64_t>(&staticGetter, &staticSetter);

    ASSERT_EQ(typeid(int64_t), prop->type());

    delete prop;
}

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<int64_t>("TestObject");
    auto prop = new Property<int64_t>("int64_tProperty", obj, &MyObject<int64_t>::constgetterconst, &MyObject<int64_t>::setterconst);

    ASSERT_EQ(typeid(int64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<int64_t>("TestObject");
    auto prop = new Property<int64_t>("int64_tProperty", obj, &MyObject<int64_t>::getterconst, &MyObject<int64_t>::setterconst);

    ASSERT_EQ(typeid(int64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt64_T_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<int64_t>("TestObject");
    auto prop = new Property<int64_t>("int64_tProperty", obj, &MyObject<int64_t>::getterconst, &MyObject<int64_t>::setter);

    ASSERT_EQ(typeid(int64_t), prop->type());


    delete prop;
    delete obj;
}

// Propterty instanciaton (read only)

TEST_F(PropertyInstanceInt64_T_test, instanciateConstPropertyWith_String_LambdaGetter)
{
    auto get = [] () {return int64_t();};

    auto prop = new Property<const int64_t>("int64_tProperty", get);

    ASSERT_EQ(typeid(int64_t), prop->type());

    delete prop;
}


TEST_F(PropertyInstanceInt64_T_test, instanciateConstPropertyWith_String_StaticGetter)
{
    auto prop = new Property<const int64_t>("int64_tProperty", &staticGetter);

    ASSERT_EQ(typeid(int64_t), prop->type());

    delete prop;
}

/*TEST_F(PropertyInstanceInt64_T_test, instanciateConstPropertyWith_String_Object_ConstGetterConst)
{
    auto obj = new MyObject<int64_t>("TestObject");
    auto prop = new Property<const int64_t>("int64_tProperty", obj, &MyObject<int64_t>::constgetterconst);

    ASSERT_EQ(typeid(int64_t), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstanceInt64_T_test, instanciateConstPropertyWith_String_Object_GetterConst)
{
    auto obj = new MyObject<int64_t>("TestObject");
    auto prop = new Property<const int64_t>("int64_tProperty", obj, &MyObject<int64_t>::getterconst);

    ASSERT_EQ(typeid(int64_t), prop->type());


    delete prop;
    delete obj;
} */
