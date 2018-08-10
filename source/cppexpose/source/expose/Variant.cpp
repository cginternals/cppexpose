
#include <cppexpose/expose/Variant.h>

#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>
#include <cppexpose/expose/Var.h>


namespace cppexpose
{


Variant::Variant()
{
}

Variant::Variant(const AbstractVar & value)
: AbstractVar()
, m_value(value.clone())
{
}

Variant::Variant(const Variant & variant)
: AbstractVar()
, m_value(variant.clone())
{
}

Variant::Variant(AbstractVar * var)
: m_value(var)
{
}

Variant::Variant(bool value)
: m_value(new Var<bool>(value))
{
}

Variant::Variant(char value)
: m_value(new Var<char>(value))
{
}

Variant::Variant(unsigned char value)
: m_value(new Var<unsigned char>(value))
{
}

Variant::Variant(short value)
: m_value(new Var<short>(value))
{
}

Variant::Variant(unsigned short value)
: m_value(new Var<unsigned short>(value))
{
}

Variant::Variant(int value)
: m_value(new Var<int>(value))
{
}

Variant::Variant(unsigned int value)
: m_value(new Var<unsigned int>(value))
{
}

Variant::Variant(long value)
: m_value(new Var<long>(value))
{
}

Variant::Variant(unsigned long value)
: m_value(new Var<unsigned long>(value))
{
}

Variant::Variant(long long value)
: m_value(new Var<long long>(value))
{
}

Variant::Variant(unsigned long long value)
: m_value(new Var<unsigned long long>(value))
{
}

Variant::Variant(float value)
: m_value(new Var<float>(value))
{
}

Variant::Variant(double value)
: m_value(new Var<double>(value))
{
}

Variant::Variant(const char * value)
: m_value(new Var<std::string>(std::string(value)))
{
}

Variant::Variant(const std::string & value)
: m_value(new Var<std::string>(value))
{
}

Variant::Variant(const std::vector<std::string> & value)
: m_value(new Var< std::vector<std::string> >(value))
{
}

Variant::~Variant()
{
}

Variant & Variant::operator =(const Variant & value)
{
    m_value.reset(value.clone());
    return *this;
}

AbstractVar * Variant::clone() const
{
    return new Variant(m_value->clone());
}

VarType Variant::type() const
{
    return m_value->type();
}

bool Variant::isNull() const
{
    return m_value->isNull();
}

bool Variant::isBool() const
{
    return m_value->isBool();
}

bool Variant::isNumber() const
{
    return m_value->isNumber();
}

bool Variant::isIntegral() const
{
    return m_value->isIntegral();
}

bool Variant::isSignedIntegral() const
{
    return m_value->isSignedIntegral();
}

bool Variant::isFloatingPoint() const
{
    return m_value->isFloatingPoint();
}

bool Variant::isEnum() const
{
    return m_value->isEnum();
}

bool Variant::isString() const
{
    return m_value->isString();
}

bool Variant::isExternal() const
{
    return m_value->isExternal();
}

bool Variant::isPointer() const
{
    return m_value->isPointer();
}

bool Variant::isObject() const
{
    return m_value->isObject();
}

bool Variant::isArray() const
{
    return m_value->isArray();
}

bool Variant::isFunction() const
{
    return m_value->isFunction();
}

bool Variant::isConst() const
{
    return m_value->isConst();
}

Variant Variant::minimumValue() const
{
    return m_value->minimumValue();
}

Variant Variant::maximumValue() const
{
    return m_value->maximumValue();
}

bool Variant::canConvertToString() const
{
    return m_value->canConvertToString();
}

std::string Variant::toString() const
{
    return m_value->toString();
}

bool Variant::canConvertToBool() const
{
    return m_value->canConvertToBool();
}

bool Variant::toBool() const
{
    return m_value->toBool();
}

bool Variant::canConvertToLongLong() const
{
    return m_value->canConvertToLongLong();
}

long long Variant::toLongLong() const
{
    return m_value->toLongLong();
}

bool Variant::canConvertToULongLong() const
{
    return m_value->canConvertToULongLong();
}

unsigned long long Variant::toULongLong() const
{
    return m_value->toULongLong();
}

bool Variant::canConvertToDouble() const
{
    return m_value->canConvertToDouble();
}

double Variant::toDouble() const
{
    return m_value->toDouble();
}

bool Variant::canConvertToObject() const
{
    return m_value->canConvertToObject();
}

Object Variant::toObject() const
{
    return m_value->toObject();
}

bool Variant::canConvertToArray() const
{
    return m_value->canConvertToArray();
}

Array Variant::toArray() const
{
    return m_value->toArray();
}

bool Variant::canConvertFromVar(const AbstractVar &)
{
    // A variant can take any type
    return true;
}

void Variant::fromVar(const AbstractVar & value)
{
    // Copy value
    m_value.reset(value.clone());
}


} // namespace cppexpose
