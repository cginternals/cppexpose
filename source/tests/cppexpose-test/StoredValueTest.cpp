
#include <gmock/gmock.h>

#include <array>

#include <cppexpose/typed/StoredValue.h>


using namespace cppexpose;
using std::string;


template <typename T>
using memberFunc = bool (cppexpose::StoredValue<T>::*)() const;


class StoredValueTest : public testing::Test
{
public:
    StoredValueTest()
    {
    }
};

template <typename T>
class TypeTester
{
public:
    TypeTester();
    void testType(StoredValue<T> & var, std::vector<memberFunc<T>> trueFuncs);
    void testType(StoredValue<T> & var, memberFunc<T> trueFunc);

protected:
    std::vector<memberFunc<T>> methods;
};

template <typename T>
TypeTester<T>::TypeTester()
{
    methods.emplace_back(&StoredValue<T>::isBool);
    methods.emplace_back(&StoredValue<T>::isEnum);
    methods.emplace_back(&StoredValue<T>::isString);
    methods.emplace_back(&StoredValue<T>::isNumber);
    methods.emplace_back(&StoredValue<T>::isIntegral);
    methods.emplace_back(&StoredValue<T>::isSignedIntegral);
    methods.emplace_back(&StoredValue<T>::isUnsignedIntegral);
    methods.emplace_back(&StoredValue<T>::isFloatingPoint);
    methods.emplace_back(&StoredValue<T>::isArray);
}

template <typename T>
void TypeTester<T>::testType(StoredValue<T> & var, std::vector<memberFunc<T>> trueFuncs)
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
void TypeTester<T>::testType(StoredValue<T> & var, memberFunc<T> trueFunc)
{
    testType(var, std::vector<memberFunc<T>>({trueFunc}));
}

TEST_F(StoredValueTest, boolSet)
{
    auto value = false;

    auto store = StoredValue<bool>([&value](){return value;}, [&value](const bool & val){value = val;});

    ASSERT_FALSE(store.value());

    store.setValue(true);

    ASSERT_TRUE(store.value());
}

TEST_F(StoredValueTest, stringSet)
{
    std::string value = "foo";
    auto val = StoredValue<std::string>([&value](){return value;}, [&value](const std::string & val){value = val;});

    ASSERT_EQ("foo", val.value());

    val.setValue("bar");

    ASSERT_EQ("bar", val.value());
}

TEST_F(StoredValueTest, arrayGet)
{
    std::array<int, 4> value { {1, 2, 3, 4} };

    auto store = StoredValue<std::array<int, 4>>([&value](){return value;},
    [&value](const int & index) -> int
    {
        return value[index];}
    );

    ASSERT_EQ(value[0], store.getElement(0));
    ASSERT_EQ(value[1], store.getElement(1));
    ASSERT_EQ(value[2], store.getElement(2));
    ASSERT_EQ(value[3], store.getElement(3));
}

TEST_F(StoredValueTest, arraySet)
{
    std::array<int, 4> value { {1, 2, 3, 4} };

    auto getter = [&value](){return value;};
    auto setter = [&value](const std::array<int, 4> & arr){value = arr;};

    auto elementGetter = [&value](const int & index) -> int {return value[index];};
    auto elementSetter = [&value](const int & index, const int & val){value[index] = val;};

    auto store = StoredValue<std::array<int, 4>>(getter, setter, elementGetter, elementSetter);


    store.setElement(0, 10);
    ASSERT_EQ(value[0], 10);
}

TEST_F(StoredValueTest, typesBool)
{
    TypeTester<bool> tester;
    bool value = true;

    auto store = StoredValue<bool>([&value](){return value;}, [&value](const bool & val){value = val;});

    tester.testType(store, &StoredValue<bool>::isBool);
    ASSERT_TRUE(store.value());
}

TEST_F(StoredValueTest, typesSignedIntegral)
{
    using curType = int;

    TypeTester<curType> tester;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

    tester.testType(store, {&StoredValue<curType>::isIntegral, &StoredValue<curType>::isNumber, &StoredValue<curType>::isSignedIntegral});
    ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesUnsignedIntegral)
{
    using curType = unsigned int;

    TypeTester<curType> tester;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

    tester.testType(store, {&StoredValue<curType>::isIntegral, &StoredValue<curType>::isNumber, &StoredValue<curType>::isUnsignedIntegral});
    ASSERT_EQ(value, store.value());
}


TEST_F(StoredValueTest, typesString)
{
    using curType = std::string;

    TypeTester<curType> tester;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

    tester.testType(store, &StoredValue<curType>::isString);
    ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesFloat)
{
    using curType = float;

    TypeTester<curType> tester;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

    tester.testType(store, {&StoredValue<curType>::isNumber, &StoredValue<curType>::isFloatingPoint});
    ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesArray)
{
    using curType = std::array<int, 4>;

    TypeTester<curType> tester;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const int & index) -> int {return value[index];});

    tester.testType(store, {&StoredValue<curType>::isArray});
    ASSERT_EQ(value, store.value());
}
