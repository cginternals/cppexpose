
#include <string>

#include <gmock/gmock.h>

#include <reflectionzeug/base/Color.h>


using namespace reflectionzeug;


class Color_test : public testing::Test
{
public:
    Color_test()
    {
    }
};


TEST_F(Color_test, FromStringShouldFail)
{
    const auto hexString = std::string{"Not a hex value"};

    auto success = true;
    Color::fromString(hexString, &success);

    ASSERT_FALSE(success);
}

TEST_F(Color_test, FromStringWithoutAlphaShouldSucceed)
{
    const auto expectedColor = Color{254, 196, 45};
    const auto hexString = std::string{"#FEC42D"};
    
    auto success = true;
    const auto color = Color::fromString(hexString, &success);

    ASSERT_TRUE(success);
    ASSERT_EQ(expectedColor, color);
}

TEST_F(Color_test, FromStringWithAlphaShouldSucceed)
{
    const auto expectedColor = Color{21, 134, 191, 127};
    const auto hexString = std::string{"#7F1586BF"};

    auto success = true;
    const auto color = Color::fromString(hexString, &success);

    ASSERT_TRUE(success);
    ASSERT_EQ(expectedColor, color);
}

TEST_F(Color_test, AsHexForBlack)
{
    const auto expectedHex = std::string{"#000000"};
    const auto color = Color{0, 0, 0};
    
    const auto hexString = color.asHex(false);
    
    ASSERT_EQ(expectedHex, hexString);
}

TEST_F(Color_test, AsHexWithAlpha)
{
    const auto expectedHex = std::string{"#7F1586BF"};
    const auto color = Color{21, 134, 191, 127};
    
    const auto hexString = color.asHex(true);
    
    ASSERT_EQ(expectedHex, hexString);
}
