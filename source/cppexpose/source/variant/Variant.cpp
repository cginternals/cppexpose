
#include <cppexpose/variant/Variant.h>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/json/JSON.h>
#include <cppexpose/value/InternalValue.h>


namespace cppexpose
{


Variant Variant::array()
{
    return Variant::fromValue(VariantArray());
}

Variant Variant::array(size_t count)
{
    return Variant::fromValue(VariantArray(count));
}

Variant Variant::map()
{
    return Variant::fromValue(VariantMap());
}

Variant::Variant()
: m_value(nullptr)
{
}

Variant::Variant(const Variant & variant)
: m_value(variant.m_value ? variant.m_value->createCopy() : nullptr)
{
}

Variant::Variant(bool value)
: m_value(cppassist::make_unique<InternalValue<bool>>(value))
{
}

Variant::Variant(char value)
: m_value(cppassist::make_unique<InternalValue<char>>(value))
{
}

Variant::Variant(unsigned char value)
: m_value(cppassist::make_unique<InternalValue<unsigned char>>(value))
{
}

Variant::Variant(short value)
: m_value(cppassist::make_unique<InternalValue<short>>(value))
{
}

Variant::Variant(unsigned short value)
: m_value(cppassist::make_unique<InternalValue<unsigned short>>(value))
{
}

Variant::Variant(int value)
: m_value(cppassist::make_unique<InternalValue<int>>(value))
{
}

Variant::Variant(unsigned int value)
: m_value(cppassist::make_unique<InternalValue<unsigned int>>(value))
{
}

Variant::Variant(long value)
: m_value(cppassist::make_unique<InternalValue<long>>(value))
{
}

Variant::Variant(unsigned long value)
: m_value(cppassist::make_unique<InternalValue<unsigned long>>(value))
{
}

Variant::Variant(long long value)
: m_value(cppassist::make_unique<InternalValue<long long>>(value))
{
}

Variant::Variant(unsigned long long value)
: m_value(cppassist::make_unique<InternalValue<unsigned long long>>(value))
{
}

Variant::Variant(float value)
: m_value(cppassist::make_unique<InternalValue<float>>(value))
{
}

Variant::Variant(double value)
: m_value(cppassist::make_unique<InternalValue<double>>(value))
{
}

Variant::Variant(const char * value)
: m_value(cppassist::make_unique<InternalValue<std::string>>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
: m_value(cppassist::make_unique<InternalValue<std::string>>(value))
{
}

Variant::Variant(const std::vector<std::string> & value)
: m_value(cppassist::make_unique<InternalValue< std::vector<std::string> >>(value))
{
}

Variant::Variant(const VariantArray & array)
: m_value(cppassist::make_unique<InternalValue<VariantArray>>(array))
{
}

Variant::Variant(const VariantMap & map)
: m_value(cppassist::make_unique<InternalValue<VariantMap>>(map))
{
}

Variant::~Variant()
{
}

Variant & Variant::operator=(const Variant & variant)
{
    m_value = variant.m_value ? variant.m_value->createCopy() : nullptr;

    return *this;
}

/*
std::string Variant::toJSON(JSON::OutputMode outputMode) const
{
    return JSON::stringify(*this, outputMode);
}
*/

Type & Variant::type()
{
    static Type nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

const Type & Variant::type() const
{
    static Type nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

Type & Variant::elementType()
{
    static Type nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

const Type & Variant::elementType() const
{
    static Type nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

std::string Variant::typeName() const
{
    if (m_value) return m_value->typeName();
    else         return "undefined";
}

bool Variant::isNull() const
{
    if (m_value) return m_value->isNull();
    else         return true;
}

bool Variant::isConst() const
{
    if (m_value) return m_value->isConst();
    else         return false;
}

bool Variant::isArray() const
{
    if (m_value) return m_value->isArray();
    else         return false;
}

bool Variant::isDynamicArray() const
{
    if (m_value) return m_value->isDynamicArray();
    else         return false;
}

bool Variant::isMap() const
{
    if (m_value) return m_value->isMap();
    else         return false;
}

bool Variant::isBoolean() const
{
    if (m_value) return m_value->isBoolean();
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

bool Variant::isUnsigned() const
{
    if (m_value) return m_value->isUnsigned();
    else         return false;
}

bool Variant::isFloatingPoint() const
{
    if (m_value) return m_value->isFloatingPoint();
    else         return false;
}

bool Variant::isString() const
{
    if (m_value) return m_value->isString();
    else         return false;
}

bool Variant::isType() const
{
    if (m_value) return m_value->isType();
    else         return false;
}

bool Variant::hasSymbolicNames() const
{
    return type().hasSymbolicNames();
}

std::vector<std::string> Variant::symbolicNames() const
{
    return type().symbolicNames();
}


} // namespace cppexpose
