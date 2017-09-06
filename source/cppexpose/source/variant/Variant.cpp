
#include <cppexpose/variant/Variant.h>

#include <cppassist/memory/make_unique.h>

#include <cppexpose/json/JSON.h>
#include <cppexpose/type/Value.h>


namespace cppexpose
{


Variant Variant::array()
{
    Variant variant;
    variant.m_value = cppassist::make_unique<Value<VariantArray>>(VariantArray());
    return variant;
}

Variant Variant::array(size_t count)
{
    Variant variant;
    variant.m_value = cppassist::make_unique<Value<VariantArray>>(VariantArray(count));
    return variant;
}

Variant Variant::map()
{
    Variant variant;
    variant.m_value = cppassist::make_unique<Value<VariantMap>>(VariantMap());
    return variant;
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
: m_value(cppassist::make_unique<Value<bool>>(value))
{
}

Variant::Variant(char value)
: m_value(cppassist::make_unique<Value<char>>(value))
{
}

Variant::Variant(unsigned char value)
: m_value(cppassist::make_unique<Value<unsigned char>>(value))
{
}

Variant::Variant(short value)
: m_value(cppassist::make_unique<Value<short>>(value))
{
}

Variant::Variant(unsigned short value)
: m_value(cppassist::make_unique<Value<unsigned short>>(value))
{
}

Variant::Variant(int value)
: m_value(cppassist::make_unique<Value<int>>(value))
{
}

Variant::Variant(unsigned int value)
: m_value(cppassist::make_unique<Value<unsigned int>>(value))
{
}

Variant::Variant(long value)
: m_value(cppassist::make_unique<Value<long>>(value))
{
}

Variant::Variant(unsigned long value)
: m_value(cppassist::make_unique<Value<unsigned long>>(value))
{
}

Variant::Variant(long long value)
: m_value(cppassist::make_unique<Value<long long>>(value))
{
}

Variant::Variant(unsigned long long value)
: m_value(cppassist::make_unique<Value<unsigned long long>>(value))
{
}

Variant::Variant(float value)
: m_value(cppassist::make_unique<Value<float>>(value))
{
}

Variant::Variant(double value)
: m_value(cppassist::make_unique<Value<double>>(value))
{
}

Variant::Variant(const char * value)
: m_value(cppassist::make_unique<Value<std::string>>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
: m_value(cppassist::make_unique<Value<std::string>>(value))
{
}

Variant::Variant(const std::vector<std::string> & value)
: m_value(cppassist::make_unique<Value< std::vector<std::string> >>(value))
{
}

Variant::Variant(const VariantArray & array)
: m_value(cppassist::make_unique<Value<VariantArray>>(array))
{
}

Variant::Variant(const VariantMap & map)
: m_value(cppassist::make_unique<Value<VariantMap>>(map))
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

const AbstractType & Variant::type() const
{
    static Type<void> nullType;

    if (m_value) return m_value->type();
    else         return nullType;
}

const AbstractType & Variant::elementType() const
{
    return type();
}

const std::type_info & Variant::typeInfo() const
{
    if (m_value) return m_value->typeInfo();
    else         return typeid(void);
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
