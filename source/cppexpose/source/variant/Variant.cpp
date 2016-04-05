
#include <cppexpose/variant/Variant.h>

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
: m_value(new DirectValue<int>(value))
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

bool Variant::isArray() const
{
    return hasType<VariantArray>();
}

bool Variant::isMap() const
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

std::string Variant::toJSON() const
{
    /*
    SerializerJSON json;
    return json.toString(*this);
    */
    return "";
}


} // namespace cppexpose
