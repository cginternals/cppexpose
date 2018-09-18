
#include <utility>

#include <gmock/gmock.h>

#include <cppexpose/variant/Variant.h>


using namespace cppexpose;


using memberFunc = bool (Variant::*)() const;


bool equal(memberFunc first, memberFunc second)
{
    return first == second;
}


class variantTest : public testing::Test
{
public:
    variantTest()
    {
    }

    virtual void SetUp() override;


protected:
    std::vector<memberFunc> methods;
};


void variantTest::SetUp()
{
    methods.emplace_back(&Variant::isBool);
    methods.emplace_back(&Variant::isEnum);
    methods.emplace_back(&Variant::isVariant);
    methods.emplace_back(&Variant::isString);
    methods.emplace_back(&Variant::isNumber);
    methods.emplace_back(&Variant::isIntegral);
    methods.emplace_back(&Variant::isSignedIntegral);
    methods.emplace_back(&Variant::isUnsignedIntegral);
    methods.emplace_back(&Variant::isFloatingPoint);
    methods.emplace_back(&Variant::isNull);
    methods.emplace_back(&Variant::isVariantArray);
    methods.emplace_back(&Variant::isVariantMap);
}

void testType(Variant & var, std::vector<memberFunc> trueFuncs, const std::vector<memberFunc> & methods)
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

void testType(Variant & var, memberFunc trueFunc, const std::vector<memberFunc> & methods)
{
    testType(var, std::vector<memberFunc>({trueFunc}), methods);
}

TEST_F(variantTest, constructorBool)
{
    const bool b = true;

    auto var = Variant(b);

    testType(var, &Variant::isBool, methods);
    ASSERT_TRUE(var.toBool());
}

TEST_F(variantTest, constructorString)
{
    const std::string str = "test";

    auto var = Variant(str);

    testType(var, &Variant::isString, methods);
    ASSERT_EQ(str, var.toString());
}

TEST_F(variantTest, constructorSignedIntegral)
{
    int i = -10;

    auto var = Variant(i);

    testType(var, {&Variant::isIntegral, &Variant::isNumber, &Variant::isSignedIntegral}, methods);
    ASSERT_EQ(i, var.toLongLong());
}

TEST_F(variantTest, constructorUnsignedIntegral)
{
    unsigned int i = 10;

    auto var = Variant(i);

    testType(var, {&Variant::isIntegral, &Variant::isNumber, &Variant::isUnsignedIntegral}, methods);
    ASSERT_EQ(i, var.toLongLong());
}

TEST_F(variantTest, constructorFloat)
{
    float f = 100.0f;

    auto var = Variant(f);

    testType(var, {&Variant::isNumber, &Variant::isFloatingPoint}, methods);
    ASSERT_EQ(f, var.toDouble());
}

TEST_F(variantTest, constructorEmpty)
{
    auto var = Variant();

    testType(var, &Variant::isNull, methods);
}

TEST_F(variantTest, constructorVariantArray)
{
    auto var = Variant(VariantArray());

    testType(var, &Variant::isVariantArray, methods);

    std::vector<int> testVector;
    testVector.push_back(4);
    testVector.push_back(2);

    var = Variant::fromVector(testVector);

    testType(var, &Variant::isVariantArray, methods);
    std::vector<int> recoveredVector = var.toVector<int>();
    ASSERT_EQ(4, recoveredVector[0]);
    ASSERT_EQ(2, recoveredVector[1]);
}

TEST_F(variantTest, staticConstructorVariantArray)
{
    auto var = Variant::array();

    testType(var, &Variant::isVariantArray, methods);

    var = Variant::array(100u);

    testType(var, &Variant::isVariantArray, methods);
}

TEST_F(variantTest, constructorVariantMap)
{
    auto var = Variant(VariantMap());

    testType(var, &Variant::isVariantMap, methods);
}

TEST_F(variantTest, staticConstructorVariantMap)
{
    auto var = Variant::map();

    testType(var, &Variant::isVariantMap, methods);
}
