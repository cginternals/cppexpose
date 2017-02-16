
#include <array>

#include <gmock/gmock.h>

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
     bool value = true;

    auto store = StoredValue<bool>([&value](){return value;}, [&value](const bool & val){value = val;});

	bool trueTest = store.isBool();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isEnum()
		|| store.isNumber()
		|| store.isString()
		|| store.isIntegral()
		|| store.isUnsignedIntegral()
		|| store.isSignedIntegral()
		|| store.isFloatingPoint()
		|| store.isArray();
	ASSERT_FALSE(falseTest);

    ASSERT_TRUE(store.value());
}

TEST_F(StoredValueTest, typesSignedIntegral)
{
    using curType = int;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

	bool trueTest = store.isNumber() 
		&& store.isIntegral() 
		&& store.isSignedIntegral();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isBool()
		|| store.isEnum()
		|| store.isString()
		|| store.isUnsignedIntegral()
		|| store.isFloatingPoint()
		|| store.isArray();
	ASSERT_FALSE(falseTest);

	ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesUnsignedIntegral)
{
    using curType = unsigned int;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});
 
	bool trueTest = store.isNumber()
		&& store.isIntegral()
		&& store.isUnsignedIntegral();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isBool()
		|| store.isEnum()
		|| store.isString()
		|| store.isSignedIntegral()
		|| store.isFloatingPoint()
		|| store.isArray();
	ASSERT_FALSE(falseTest);
	
	ASSERT_EQ(value, store.value());
}


TEST_F(StoredValueTest, typesString)
{
    using curType = std::string;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});

	bool trueTest = store.isString();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isBool()
		|| store.isEnum()
		|| store.isNumber()
		|| store.isIntegral()
		|| store.isUnsignedIntegral()
		|| store.isSignedIntegral()
		|| store.isFloatingPoint()
		|| store.isArray();
	ASSERT_FALSE(falseTest);

    ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesFloat)
{
    using curType = float;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const curType & val){value = val;});
   
	bool trueTest = store.isNumber()
		&& store.isFloatingPoint();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isBool()
		|| store.isEnum()
		|| store.isString()
		|| store.isIntegral()
		|| store.isSignedIntegral()
		|| store.isUnsignedIntegral()
		|| store.isArray();
	ASSERT_FALSE(falseTest);
	
	ASSERT_EQ(value, store.value());
}

TEST_F(StoredValueTest, typesArray)
{
    using curType = std::array<int, 4>;

    curType value{};

    auto store = StoredValue<curType>([&value](){return value;}, [&value](const int & index) -> int {return value[index];});

	bool trueTest = store.isArray();
	ASSERT_TRUE(trueTest);

	bool falseTest = store.isBool()
		|| store.isEnum()
		|| store.isNumber()
		|| store.isString()
		|| store.isIntegral()
		|| store.isUnsignedIntegral()
		|| store.isSignedIntegral()
		|| store.isFloatingPoint();
	ASSERT_FALSE(falseTest);
    ASSERT_EQ(value, store.value());
}
