

#include <gmock/gmock.h>

#include <array>

#include <cppexpose/typed/DirectValue.h>

using namespace cppexpose;
using std::string;

template <typename T>
using memberFunc = bool (cppexpose::DirectValue<T>::*)() const;


class DirectValueTest : public testing::Test
{
public:
    DirectValueTest()
    {
    }
};

template <typename T>
class TypeTester
{
public:
    TypeTester();
    void testType(DirectValue<T> & var, std::vector<memberFunc<T>> trueFuncs);
    void testType(DirectValue<T> & var, memberFunc<T> trueFunc);

protected:
    std::vector<memberFunc<T>> methods;
};

template <typename T>
TypeTester<T>::TypeTester()
{
    methods.emplace_back(&DirectValue<T>::isBool);
    methods.emplace_back(&DirectValue<T>::isEnum);
    methods.emplace_back(&DirectValue<T>::isString);
    methods.emplace_back(&DirectValue<T>::isNumber);
    methods.emplace_back(&DirectValue<T>::isIntegral);
    methods.emplace_back(&DirectValue<T>::isSignedIntegral);
    methods.emplace_back(&DirectValue<T>::isUnsignedIntegral);
    methods.emplace_back(&DirectValue<T>::isFloatingPoint);
}

template <typename T>
void TypeTester<T>::testType(DirectValue<T> & var, std::vector<memberFunc<T>> trueFuncs)
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
void TypeTester<T>::testType(DirectValue<T> & var, memberFunc<T> trueFunc)
{
    testType(var, std::vector<memberFunc<T>>({trueFunc}));
}

TEST_F(DirectValueTest, boolSet)
{
    auto val = DirectValue<bool>(false);

    ASSERT_FALSE(val.value());

    val.setValue(true);

    ASSERT_TRUE(val.value());
}

TEST_F(DirectValueTest, stringSet)
{
    auto val = DirectValue<std::string>("foo");

    ASSERT_EQ("foo", val.value());

    val.setValue("bar");

    ASSERT_EQ("bar", val.value());
}

TEST_F(DirectValueTest, arrayGet)
{
    auto val = DirectValue<std::array<int, 4>>(std::array<int, 4>{1,2,3,4});

    ASSERT_EQ(1, val.getElement(0));
}

TEST_F(DirectValueTest, arraySet)
{
    auto val = DirectValue<std::array<int, 4>>(std::array<int, 4>{1,2,3,4});

    val.setElement(0,10);

    ASSERT_EQ(10, val.getElement(0));
}

TEST_F(DirectValueTest, typesBool)
{
    TypeTester<bool> tester;
    bool value = true;

    auto val = DirectValue<bool>(value);

    tester.testType(val, &DirectValue<bool>::isBool);
    ASSERT_TRUE(val.value());
}

TEST_F(DirectValueTest, typesSignedIntegral)
{
    using curType = int;

    TypeTester<curType> tester;

    curType value{};

    auto val = DirectValue<curType>(value);

    tester.testType(val, {&DirectValue<curType>::isIntegral, &DirectValue<curType>::isNumber, &DirectValue<curType>::isSignedIntegral});
    ASSERT_EQ(value, val.value());
}


TEST_F(DirectValueTest, typesUnsignedIntegral)
{
    using curType = unsigned int;

    TypeTester<curType> tester;

    curType value{};

    auto val = DirectValue<curType>(value);

    tester.testType(val, {&DirectValue<curType>::isIntegral, &DirectValue<curType>::isNumber, &DirectValue<curType>::isUnsignedIntegral});
    ASSERT_EQ(value, val.value());
}


TEST_F(DirectValueTest, typesString)
{
    using curType = std::string;

    TypeTester<curType> tester;

    curType value{};

    auto val = DirectValue<curType>(value);

    tester.testType(val, &DirectValue<curType>::isString);
    ASSERT_EQ(value, val.value());
}

TEST_F(DirectValueTest, typesFloat)
{
    using curType = float;

    TypeTester<curType> tester;

    curType value{};

    auto val = DirectValue<curType>(value);

    tester.testType(val, {&DirectValue<curType>::isNumber, &DirectValue<curType>::isFloatingPoint});
    ASSERT_EQ(value, val.value());
}
