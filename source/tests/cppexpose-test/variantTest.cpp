#include <gmock/gmock.h>

#include <cppexpose/variant/Variant.h>
#include <utility>

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
}

void testType(Variant& var, memberFunc trueFunc, const std::vector<memberFunc>& methods)
{
    for(auto& method : methods)
    {
        bool test = (var.*method)();
        if(method == trueFunc)
            ASSERT_TRUE(test);
        else
            ASSERT_FAILED(test);
    }
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
    
    ASSERT_TRUE(var.isString());
    ASSERT_EQ(str, var.toString());
    ASSERT_FALSE(var.isEnum());
}
