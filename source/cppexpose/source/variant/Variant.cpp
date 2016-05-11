
#include <cppexpose/variant/Variant.h>

#include <cppexpose/base/SerializerJSON.h>
#include <cppexpose/typed/DirectValue.h>


namespace cppexpose
{


Variant Variant::array()
{
    Variant variant;
    variant.m_value = new DirectValue<VariantArray>(VariantArray());
    return variant;
}

Variant Variant::array(size_t count)
{
    Variant variant;
    variant.m_value = new DirectValue<VariantArray>(VariantArray(count));
    return variant;
}

Variant Variant::map()
{
    Variant variant;
    variant.m_value = new DirectValue<VariantMap>(VariantMap());
    return variant;
}

Variant::Variant()
: m_value(nullptr)
{
}

Variant::Variant(const Variant & variant)
: m_value(variant.m_value ? variant.m_value->clone() : nullptr)
{
}

Variant::Variant(bool value)
: m_value(new DirectValue<bool>(value))
{
}

Variant::Variant(char value)
: m_value(new DirectValue<char>(value))
{
}

Variant::Variant(unsigned char value)
: m_value(new DirectValue<unsigned char>(value))
{
}

Variant::Variant(short value)
: m_value(new DirectValue<short>(value))
{
}

Variant::Variant(unsigned short value)
: m_value(new DirectValue<unsigned short>(value))
{
}

Variant::Variant(int value)
: m_value(new DirectValue<int>(value))
{
}

Variant::Variant(unsigned int value)
: m_value(new DirectValue<unsigned int>(value))
{
}

Variant::Variant(long value)
: m_value(new DirectValue<long>(value))
{
}

Variant::Variant(unsigned long value)
: m_value(new DirectValue<unsigned long>(value))
{
}

Variant::Variant(long long value)
: m_value(new DirectValue<long long>(value))
{
}

Variant::Variant(unsigned long long value)
: m_value(new DirectValue<unsigned long long>(value))
{
}

Variant::Variant(float value)
: m_value(new DirectValue<float>(value))
{
}

Variant::Variant(double value)
: m_value(new DirectValue<double>(value))
{
}

Variant::Variant(const char * value)
: m_value(new DirectValue<std::string>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
: m_value(new DirectValue<std::string>(value))
{
}

Variant::Variant(const std::vector<std::string> & value)
: m_value(new DirectValue< std::vector<std::string> >(value))
{
}

Variant::Variant(const VariantArray & array)
: m_value(new DirectValue<VariantArray>(array))
{
}

Variant::Variant(const VariantMap & map)
: m_value(new DirectValue<VariantMap>(map))
{
}

Variant::~Variant()
{
    if (m_value)
    {
        delete m_value;
    }
}

Variant & Variant::operator=(const Variant & variant)
{
    if (m_value) {
        delete m_value;
    }

    m_value = variant.m_value ? variant.m_value->clone() : nullptr;

    return *this;
}

bool Variant::isNull() const
{
    return !m_value;
}

bool Variant::isVariantArray() const
{
    return hasType<VariantArray>();
}

bool Variant::isVariantMap() const
{
    return hasType<VariantMap>();
}

const std::type_info & Variant::type() const
{
    if (m_value) {
        return m_value->type();
    } else {
        return typeid(void);
    }
}

VariantArray * Variant::asArray()
{
    return ptr<VariantArray>();
}

const VariantArray * Variant::asArray() const
{
    return ptr<VariantArray>();
}

VariantMap * Variant::asMap()
{
    return ptr<VariantMap>();
}

const VariantMap * Variant::asMap() const
{
    return ptr<VariantMap>();
}

std::string Variant::toJSON(SerializerJSON::OutputMode outputMode) const
{
    SerializerJSON json(outputMode);
    return json.toString(*this);
}

bool Variant::isEnum() const
{
    if (m_value) return m_value->isEnum();
    else         return false;
}

bool Variant::isArray() const
{
    if (m_value) return m_value->isArray();
    else         return false;
}

bool Variant::isVariant() const
{
    if (m_value) return m_value->isVariant();
    else         return false;
}

bool Variant::isString() const
{
    if (m_value) return m_value->isString();
    else         return false;
}

bool Variant::isBool() const
{
    if (m_value) return m_value->isBool();
    else         return false;
}

bool Variant::isNumber() const
{
    if (m_value) return m_value->isNumber();
    else         return false;
}

bool Variant::isIntegral() const
{
    if (m_value) return m_value->isIntegral();
    else         return false;
}

bool Variant::isSignedIntegral() const
{
    if (m_value) return m_value->isSignedIntegral();
    else         return false;
}

bool Variant::isUnsignedIntegral() const
{
    if (m_value) return m_value->isUnsignedIntegral();
    else         return false;
}

bool Variant::isFloatingPoint() const
{
    if (m_value) return m_value->isFloatingPoint();
    else         return false;
}

Variant Variant::toVariant() const
{
    if (m_value) return m_value->toVariant();
    else         return Variant();
}

bool Variant::fromVariant(const Variant & value)
{
    if (m_value) return m_value->fromVariant(value);
    else         return false;
}

std::string Variant::toString() const
{
    if (isVariantMap() || isVariantArray())
    {
        return toJSON();
    }

    else if (m_value) {
        return m_value->toString();
    }

    else {
        return "";
    }
}

bool Variant::fromString(const std::string & value)
{
    if (m_value) return m_value->fromString(value);
    else         return false;
}

bool Variant::toBool() const
{
    if (m_value) return m_value->toBool();
    else         return false;
}

bool Variant::fromBool(bool value)
{
    if (m_value) return m_value->fromBool(value);
    else         return false;
}

long long Variant::toLongLong() const
{
    if (m_value) return m_value->toLongLong();
    else         return 0ll;
}

bool Variant::fromLongLong(long long value)
{
    if (m_value) return m_value->fromLongLong(value);
    else         return false;
}

unsigned long long Variant::toULongLong() const
{
    if (m_value) return m_value->toULongLong();
    else         return 0ull;
}

bool Variant::fromULongLong(unsigned long long value)
{
    if (m_value) return m_value->fromULongLong(value);
    else         return false;
}

double Variant::toDouble() const
{
    if (m_value) return m_value->toDouble();
    else         return 0.0;
}

bool Variant::fromDouble(double value)
{
    if (m_value) return m_value->fromDouble(value);
    else         return false;
}


} // namespace cppexpose
