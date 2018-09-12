
#include <array>

#include <gmock/gmock.h>

#include <cppexpose/reflection/Property.h>


using namespace cppexpose;
using std::string;


template <typename T>
using memberFunc = bool (cppexpose::Property<T>::*)() const;


class PropertyTest : public testing::Test
{
public:
    PropertyTest()
    {
    }
};

template <typename T>
class TypeTester
{
public:
    TypeTester();
    void testType(Property<T> & var, std::vector<memberFunc<T>> trueFuncs);
    void testType(Property<T> & var, memberFunc<T> trueFunc);

protected:
    std::vector<memberFunc<T>> methods;
};

template <typename T>
TypeTester<T>::TypeTester()
{
    methods.emplace_back(&Property<T>::isBool);
    methods.emplace_back(&Property<T>::isEnum);
    methods.emplace_back(&Property<T>::isString);
    methods.emplace_back(&Property<T>::isNumber);
    methods.emplace_back(&Property<T>::isIntegral);
    methods.emplace_back(&Property<T>::isSignedIntegral);
    methods.emplace_back(&Property<T>::isUnsignedIntegral);
    methods.emplace_back(&Property<T>::isFloatingPoint);
}

template <typename T>
void TypeTester<T>::testType(Property<T> & var, std::vector<memberFunc<T>> trueFuncs)
{
    for (auto & method : methods)
    {
        bool test = (var.*method)();
        if(std::find(trueFuncs.begin(), trueFuncs.end(), method) != trueFuncs.end())
            ASSERT_TRUE(test);
        else
            ASSERT_FALSE(test);
    }
}

template <typename T>
void TypeTester<T>::testType(Property<T> & var, memberFunc<T> trueFunc)
{
    testType(var, std::vector<memberFunc<T>>({trueFunc}));
}

TEST_F(PropertyTest, boolSet)
{
    Object object;
    bool callbackVar = false;

    auto callback = [&callbackVar](const bool& newVal){
        ASSERT_FALSE(newVal);
        callbackVar = true;
    };

    bool value = true;

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const bool & val)
    {
        value = val;
    };

    auto prop = cppassist::make_unique<Property<bool>>("Property", &object, get, set);

    prop->valueChanged.connect(callback);

    prop->setValue(false);

    ASSERT_FALSE(prop->toBool());
    ASSERT_TRUE(callbackVar);
}

TEST_F(PropertyTest, ArraySet)
{
    Object object;

    std::array<int, 4> value{ {1, 2, 3, 4} };

    auto getter = [&value](){return value;};
    auto setter = [&value](const std::array<int, 4> & arr){value = arr;};

    auto elementGetter = [&value](const int & index) -> int {return value[index];};
    auto elementSetter = [&value](const int & index, const int & val){value[index] = val;};

    auto prop = cppassist::make_unique<Property<std::array<int, 4>>>("Property", &object, getter, setter, elementGetter, elementSetter);

    prop->setElement(0, 10);
    ASSERT_EQ(10, prop->getElement(0));
}

TEST_F(PropertyTest, stringSet)
{
    Object object;
    bool callbackVar = false;

    auto callback = [&callbackVar](const std::string &)
    {
        callbackVar = true;
    };

    std::string value = "foo";

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const std::string & val)
    {
        value = val;
    };

    auto prop = cppassist::make_unique<Property<std::string>>("Property", &object, get, set);

    prop->valueChanged.connect(callback);

    prop->setValue("bar");

    ASSERT_EQ("bar", prop->toString());
    ASSERT_TRUE(callbackVar);
}

TEST_F(PropertyTest, conversionTest_int)
{
    Object object;

    int intVar = 0;

    auto intProp = cppassist::make_unique<Property<int>>("intProperty", &object, [&](){return intVar;}, [](const int&){});

    ASSERT_DOUBLE_EQ(intVar, intProp->toDouble());
    ASSERT_EQ(intVar, intProp->toLongLong());
    ASSERT_EQ(intVar, intProp->toULongLong());
    ASSERT_EQ("0", intProp->toString());
}

TEST_F(PropertyTest, conversionTest_negative_int)
{
    Object object;

    int intVar = -3;

    auto intProp = cppassist::make_unique<Property<int>>("intProperty", &object, [&](){return intVar;}, [](const int&){});

    ASSERT_DOUBLE_EQ(intVar, intProp->toDouble());
    ASSERT_EQ(intVar, intProp->toLongLong());
    ASSERT_EQ(intVar, intProp->toULongLong());
    ASSERT_EQ("-3", intProp->toString());
}

TEST_F(PropertyTest, conversionTest_string)
{
    Object object;

    std::string strVar = "3";

    auto intProp = cppassist::make_unique<Property<std::string>>("stringProperty", &object, [&](){return strVar;}, [](const std::string&){});

    ASSERT_DOUBLE_EQ(3, intProp->toDouble());
    ASSERT_EQ(3, intProp->toLongLong());
    ASSERT_EQ(3, intProp->toULongLong());
    ASSERT_EQ("3", intProp->toString());
}

TEST_F(PropertyTest, conversionTest_string_variant)
{
    Object object;

    std::string strVar = "test";

    auto strProp = cppassist::make_unique<Property<std::string>>("stringProperty", &object, [&](){return strVar;}, [](const std::string&){});

    ASSERT_EQ("test", strProp->toVariant().toString());
}

TEST_F(PropertyTest, typesBool)
{
    TypeTester<bool> tester;
    Object object;
    bool value = true;

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const bool & val)
    {
        value = val;
    };

    auto prop = Property<bool>("Property", &object, get, set);

    tester.testType(prop, &Property<bool>::isBool);
    prop.setValue(true);
    ASSERT_TRUE(prop.toBool());
    auto b = prop.value();
    ASSERT_TRUE(b);
}

TEST_F(PropertyTest, typesSignedIntegral)
{
    using curType = int;

    TypeTester<curType> tester;
    Object object;

    curType value{};

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const curType & val)
    {
        value = val;
    };

    auto prop = Property<curType>("Property", &object, get, set);

    tester.testType(prop, {&Property<curType>::isIntegral, &Property<curType>::isNumber, &Property<curType>::isSignedIntegral});
    ASSERT_EQ(value, prop.toLongLong());
}

TEST_F(PropertyTest, typesUnsignedIntegral)
{
    using curType = unsigned int;

    TypeTester<curType> tester;
    Object object;

    curType value{};

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const curType & val)
    {
        value = val;
    };

    auto prop = Property<curType>("Property", &object, get, set);

    tester.testType(prop, {&Property<curType>::isIntegral, &Property<curType>::isNumber, &Property<curType>::isUnsignedIntegral});
    ASSERT_EQ(value, prop.toLongLong());
}


TEST_F(PropertyTest, typesString)
{
    using curType = std::string;

    TypeTester<curType> tester;
    Object object;

    curType value = "test";

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const curType & val)
    {
        value = val;
    };

    auto prop = Property<curType>("Property", &object, get, set);

    tester.testType(prop, &Property<curType>::isString);
    ASSERT_EQ(value, prop.toString());
}

TEST_F(PropertyTest, typesFloat)
{
    using curType = float;

    TypeTester<curType> tester;
    Object object;

    curType value{};

    auto get = [&value] ()
    {
        return value;
    };

    auto set = [&value] (const curType & val)
    {
        value = val;
    };

    auto prop = Property<curType>("Property", &object, get, set);

    tester.testType(prop, {&Property<curType>::isNumber, &Property<curType>::isFloatingPoint});
    ASSERT_EQ(value, prop.toLongLong());
}
