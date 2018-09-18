
#include <array>

#include <gmock/gmock.h>

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
    auto val = DirectValue<std::array<int, 4>>(std::array<int, 4>{ {1, 2, 3, 4} });

    ASSERT_EQ(1, val.getElement(0));
}

TEST_F(DirectValueTest, arraySet)
{
    auto val = DirectValue<std::array<int, 4>>(std::array<int, 4>{ {1, 2, 3, 4} });

    val.setElement(0,10);

    ASSERT_EQ(10, val.getElement(0));
}

TEST_F(DirectValueTest, constSet)
{
    auto val = DirectValue<const bool>(false);

    ASSERT_FALSE(val.value());

    val.setValue(true);

    ASSERT_FALSE(val.value());
}

TEST_F(DirectValueTest, typesBool)
{
    bool value = true;

    auto val = DirectValue<bool>(value);

    bool trueTest = val.isBool();
    ASSERT_TRUE(trueTest);

    bool falseTest = val.isEnum()
        || val.isNumber()
        || val.isString()
        || val.isIntegral()
        || val.isUnsignedIntegral()
        || val.isSignedIntegral()
        || val.isFloatingPoint()
        || val.isArray();
    ASSERT_FALSE(falseTest);

    ASSERT_TRUE(val.value());
}

TEST_F(DirectValueTest, typesSignedIntegral)
{
    using curType = int;

    curType value{};

    auto val = DirectValue<curType>(value);

    bool trueTest = val.isNumber()
        && val.isIntegral()
        && val.isSignedIntegral();
    ASSERT_TRUE(trueTest);

    bool falseTest = val.isBool()
        || val.isEnum()
        || val.isString()
        || val.isUnsignedIntegral()
        || val.isFloatingPoint()
        || val.isArray();
    ASSERT_FALSE(falseTest);

    ASSERT_EQ(value, val.value());
}


TEST_F(DirectValueTest, typesUnsignedIntegral)
{
    using curType = unsigned int;

    curType value{};

    auto val = DirectValue<curType>(value);

    bool trueTest = val.isNumber()
        && val.isIntegral()
        && val.isUnsignedIntegral();
    ASSERT_TRUE(trueTest);

    bool falseTest = val.isBool()
        || val.isEnum()
        || val.isString()
        || val.isSignedIntegral()
        || val.isFloatingPoint()
        || val.isArray();
    ASSERT_FALSE(falseTest);

    ASSERT_EQ(value, val.value());
}


TEST_F(DirectValueTest, typesString)
{
    using curType = std::string;

    curType value{};

    auto val = DirectValue<curType>(value);

    bool trueTest = val.isString();
    ASSERT_TRUE(trueTest);

    bool falseTest = val.isBool()
        || val.isEnum()
        || val.isNumber()
        || val.isIntegral()
        || val.isUnsignedIntegral()
        || val.isSignedIntegral()
        || val.isFloatingPoint()
        || val.isArray();
    ASSERT_FALSE(falseTest);

    ASSERT_EQ(value, val.value());
}

TEST_F(DirectValueTest, typesFloat)
{
    using curType = float;

    curType value{};

    auto val = DirectValue<curType>(value);

    bool trueTest = val.isNumber()
        && val.isFloatingPoint();
    ASSERT_TRUE(trueTest);

    bool falseTest = val.isBool()
        || val.isEnum()
        || val.isString()
        || val.isIntegral()
        || val.isUnsignedIntegral()
        || val.isSignedIntegral()
        || val.isArray();
    ASSERT_FALSE(falseTest);

    ASSERT_EQ(value, val.value());
}
