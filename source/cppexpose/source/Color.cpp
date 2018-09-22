
#include <cppexpose/Color.h>

#include <cassert>
#include <sstream>
#include <iomanip>

#include <cppassist/string/regex.h>


namespace cppexpose
{


Color::Color()
: m_argb(0ul)
{
}

Color::Color(const Color & color)
: m_argb(color.m_argb)
{
}

Color::Color(std::uint32_t argb)
: m_argb(argb)
{
}

Color::Color(int red, int green, int blue, int alpha)
{
    m_values[0] = static_cast<unsigned char>(alpha);
    m_values[1] = static_cast<unsigned char>(red);
    m_values[2] = static_cast<unsigned char>(green);
    m_values[3] = static_cast<unsigned char>(blue);
}

Color::Color(float red, float green, float blue, float alpha)
{
    m_values[0] = static_cast<unsigned char>(alpha * 255.0f);
    m_values[1] = static_cast<unsigned char>(red   * 255.0f);
    m_values[2] = static_cast<unsigned char>(green * 255.0f);
    m_values[3] = static_cast<unsigned char>(blue  * 255.0f);
}

bool Color::operator==(const Color & color) const
{
    return m_argb == color.m_argb;
}

bool Color::operator!=(const Color & color) const
{
    return m_argb != color.m_argb;
}

std::uint32_t Color::argb() const
{
    return m_argb;
}

void Color::setArgb(std::uint32_t argb)
{
    m_argb = argb;
}

unsigned char Color::red() const
{
    return m_values[1];
}

void Color::setRed(unsigned char value)
{
    m_values[1] = static_cast<unsigned char>(value);
}

unsigned char Color::green() const
{
    return m_values[2];
}

void Color::setGreen(unsigned char value)
{
    m_values[2] = static_cast<unsigned char>(value);
}

unsigned char Color::blue() const
{
    return m_values[3];
}

void Color::setBlue(unsigned char value)
{
    m_values[3] = static_cast<unsigned char>(value);
}

unsigned char Color::alpha() const
{
    return m_values[0];
}

void Color::setAlpha(unsigned char value)
{
    m_values[0] = static_cast<unsigned char>(value);
}

float Color::redf() const
{
    return m_values[1] / 255.0f;
}

void Color::setRedf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_values[1] = static_cast<unsigned char>(value * 255.0f);
}

float Color::greenf() const
{
    return m_values[2] / 255.0f;
}

void Color::setGreenf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_values[2] = static_cast<unsigned char>(value * 255.0f);
}

float Color::bluef() const
{
    return m_values[3] / 255.0f;
}

void Color::setBluef(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_values[3] = static_cast<unsigned char>(value * 255.0f);
}

float Color::alphaf() const
{
    return m_values[0] / 255.0f;
}

void Color::setAlphaf(float value)
{
    assert(0.0f <= value && value <= 1.0f);
    m_values[0] = static_cast<unsigned char>(value * 255.0f);
}

std::string Color::toHexString() const
{
    std::stringstream stream;

    stream << "#";
    stream << std::hex << std::uppercase;

    stream << std::setw(2) << std::setfill('0') << (int)alpha();
    stream << std::setw(2) << std::setfill('0') << (int)red();
    stream << std::setw(2) << std::setfill('0') << (int)green();
    stream << std::setw(2) << std::setfill('0') << (int)blue();

    return stream.str();
}

bool Color::fromHexString(const std::string & str)
{
    // Check if string is a color
    if (str.size() < 1 || str[0] != '#')
    {
        return false;
    }

    // Convert string to canonical form
    std::string hex = str.substr(1);

    if (hex.size() == 3) // #RGB -> #ARGB
    {
        hex = "F" + hex;
    }

    if (hex.size() == 4) // #ARGB -> #AARRGGBB
    {
        hex = hex.substr(0, 1) + hex.substr(0, 1)
            + hex.substr(1, 1) + hex.substr(1, 1)
            + hex.substr(2, 1) + hex.substr(2, 1)
            + hex.substr(3, 1) + hex.substr(3, 1);
    }

    if (hex.size() == 6) // #RRGGBB -> #AARRGGBB
    {
        hex = "FF" + hex;
    }

    // Check string format
    if (!cppassist::string::matchesRegex(hex, "([0-9A-Fa-f]{8}|[0-9A-Fa-f]{6})"))
    {
        return false;
    }

    // Convert hex string to ARGB integer value
    auto argb = 0u;
    std::stringstream stream(hex);
    stream >> std::hex;
    stream >> argb;

    // Set color
    setBlue(argb & 0xff);
    argb = argb >> 8;
    setGreen(argb & 0xff);
    argb = argb >> 8;
    setRed(argb & 0xff);
    argb = argb >> 8;
    setAlpha(argb & 0xff);

    return true;
}

Color Color::interpolate(const Color & other, float interpolationValue) const
{
    return Color(
        static_cast<unsigned char>(m_values[1] * (1.0f - interpolationValue) + other.red()   * interpolationValue),
        static_cast<unsigned char>(m_values[2] * (1.0f - interpolationValue) + other.green() * interpolationValue),
        static_cast<unsigned char>(m_values[3] * (1.0f - interpolationValue) + other.blue()  * interpolationValue),
        static_cast<unsigned char>(m_values[0] * (1.0f - interpolationValue) + other.alpha() * interpolationValue)
    );
}


} // namespace cppexpose
