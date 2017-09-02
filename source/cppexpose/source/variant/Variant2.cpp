
#include <cppexpose/variant/Variant2.h>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/json/JSON.h>
#include <cppexpose/type/Value.h>


namespace cppexpose
{


Variant2 Variant2::array()
{
    Variant2 variant;
    variant.m_value = cppassist::make_unique<Value<VariantArray>>(VariantArray());
    return variant;
}

Variant2 Variant2::array(size_t count)
{
    Variant2 variant;
    variant.m_value = cppassist::make_unique<Value<VariantArray>>(VariantArray(count));
    return variant;
}

Variant2 Variant2::map()
{
    Variant2 variant;
    variant.m_value = cppassist::make_unique<Value<VariantMap>>(VariantMap());
    return variant;
}

Variant2::Variant2()
: m_value(nullptr)
{
}

Variant2::Variant2(const Variant2 & variant)
: m_value(variant.m_value ? variant.m_value->createCopy() : nullptr)
{
}

Variant2::Variant2(bool value)
: m_value(cppassist::make_unique<Value<bool>>(value))
{
}

Variant2::Variant2(char value)
: m_value(cppassist::make_unique<Value<char>>(value))
{
}

Variant2::Variant2(unsigned char value)
: m_value(cppassist::make_unique<Value<unsigned char>>(value))
{
}

Variant2::Variant2(short value)
: m_value(cppassist::make_unique<Value<short>>(value))
{
}

Variant2::Variant2(unsigned short value)
: m_value(cppassist::make_unique<Value<unsigned short>>(value))
{
}

Variant2::Variant2(int value)
: m_value(cppassist::make_unique<Value<int>>(value))
{
}

Variant2::Variant2(unsigned int value)
: m_value(cppassist::make_unique<Value<unsigned int>>(value))
{
}

Variant2::Variant2(long value)
: m_value(cppassist::make_unique<Value<long>>(value))
{
}

Variant2::Variant2(unsigned long value)
: m_value(cppassist::make_unique<Value<unsigned long>>(value))
{
}

Variant2::Variant2(long long value)
: m_value(cppassist::make_unique<Value<long long>>(value))
{
}

Variant2::Variant2(unsigned long long value)
: m_value(cppassist::make_unique<Value<unsigned long long>>(value))
{
}

Variant2::Variant2(float value)
: m_value(cppassist::make_unique<Value<float>>(value))
{
}

Variant2::Variant2(double value)
: m_value(cppassist::make_unique<Value<double>>(value))
{
}

Variant2::Variant2(const char * value)
: m_value(cppassist::make_unique<Value<std::string>>(std::string(value)))
{
}

Variant2::Variant2(const std::string & value)
: m_value(cppassist::make_unique<Value<std::string>>(value))
{
}

Variant2::Variant2(const std::vector<std::string> & value)
: m_value(cppassist::make_unique<Value< std::vector<std::string> >>(value))
{
}

Variant2::Variant2(const VariantArray & array)
: m_value(cppassist::make_unique<Value<VariantArray>>(array))
{
}

Variant2::Variant2(const VariantMap & map)
: m_value(cppassist::make_unique<Value<VariantMap>>(map))
{
}

Variant2::~Variant2()
{
}

Variant2 & Variant2::operator=(const Variant2 & variant)
{
    m_value = variant.m_value ? variant.m_value->createCopy() : nullptr;

    return *this;
}

bool Variant2::isNull() const
{
    return !m_value;
}

/*
std::string Variant2::toJSON(JSON::OutputMode outputMode) const
{
    return JSON::stringify(*this, outputMode);
}
*/

const AbstractType & Variant2::type() const
{
    static Type<void> nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

const std::type_info & Variant2::typeInfo() const
{
    if (m_value) return m_value->typeInfo();
    else         return typeid(void);
}

std::string Variant2::typeName() const
{
    if (m_value) return m_value->typeName();
    else         return "undefined";
}

bool Variant2::isConst() const
{
    if (m_value) return m_value->isConst();
    else         return false;
}

bool Variant2::isArray() const
{
    if (m_value) return m_value->isArray();
    else         return false;
}

bool Variant2::isDynamicArray() const
{
    if (m_value) return m_value->isDynamicArray();
    else         return false;
}

bool Variant2::isMap() const
{
    if (m_value) return m_value->isMap();
    else         return false;
}

bool Variant2::isBoolean() const
{
    if (m_value) return m_value->isBoolean();
    else         return false;
}

bool Variant2::isNumber() const
{
    if (m_value) return m_value->isNumber();
    else         return false;
}

bool Variant2::isIntegral() const
{
    if (m_value) return m_value->isIntegral();
    else         return false;
}

bool Variant2::isUnsigned() const
{
    if (m_value) return m_value->isUnsigned();
    else         return false;
}

bool Variant2::isFloatingPoint() const
{
    if (m_value) return m_value->isFloatingPoint();
    else         return false;
}

bool Variant2::isString() const
{
    if (m_value) return m_value->isString();
    else         return false;
}


} // namespace cppexpose
