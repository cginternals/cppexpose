
#include <cppexpose/expose/Variant.h>

#include <cppexpose/expose/Object.h>
#include <cppexpose/expose/Array.h>
#include <cppexpose/expose/Var.h>


namespace cppexpose
{


Variant::Variant()
{
}

Variant::Variant(const Variant & variant)
: AbstractVar()
, m_value(variant.clone())
{
}

Variant::Variant(Variant && variant)
: AbstractVar()
, m_value(std::move(variant.m_value))
{
    // [willy]
}

Variant::Variant(const AbstractVar & value)
: AbstractVar()
, m_value(value.clone())
{
}

Variant::Variant(AbstractVar && value)
: AbstractVar()
, m_value(std::move(value.move()))
{
    // [willy]
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

Variant & Variant::operator =(std::unique_ptr<AbstractVar> && value)
{
    m_value = std::move(value);
    return *this;
}

AbstractVar * Variant::clone() const
{
    if (m_value) return new Variant(m_value->clone());
    else         return new Variant;
}

std::unique_ptr<AbstractVar> Variant::move()
{
    // [willy]
    return cppassist::make_unique<Variant>(std::move(*this));
}

VarType Variant::type() const
{
    if (m_value) return m_value->type();
    else         return VarType::Null;
}

bool Variant::isNull() const
{
    if (m_value) return m_value->isNull();
    else         return true;
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

bool Variant::isFloatingPoint() const
{
    if (m_value) return m_value->isFloatingPoint();
    else         return false;
}

bool Variant::isEnum() const
{
    if (m_value) return m_value->isEnum();
    else         return false;
}

bool Variant::isString() const
{
    if (m_value) return m_value->isString();
    else         return false;
}

bool Variant::isExternal() const
{
    if (m_value) return m_value->isExternal();
    else         return false;
}

bool Variant::isPointer() const
{
    if (m_value) return m_value->isPointer();
    else         return false;
}

bool Variant::isObject() const
{
    if (m_value) return m_value->isObject();
    else         return false;
}

bool Variant::isArray() const
{
    if (m_value) return m_value->isArray();
    else         return false;
}

bool Variant::isFunction() const
{
    if (m_value) return m_value->isFunction();
    else         return false;
}

bool Variant::isConst() const
{
    if (m_value) return m_value->isConst();
    else         return false;
}

Variant Variant::minimumValue() const
{
    if (m_value) return m_value->minimumValue();
    else         return Variant();
}

Variant Variant::maximumValue() const
{
    if (m_value) return m_value->maximumValue();
    else         return Variant();
}

bool Variant::canConvertToString() const
{
    if (m_value) return m_value->canConvertToString();
    else         return false;
}

std::string Variant::toString() const
{
    if (m_value) return m_value->toString();
    else         return "";
}

bool Variant::canConvertToBool() const
{
    if (m_value) return m_value->canConvertToBool();
    else         return false;
}

bool Variant::toBool() const
{
    if (m_value) return m_value->toBool();
    else         return false;
}

bool Variant::canConvertToLongLong() const
{
    if (m_value) return m_value->canConvertToLongLong();
    else         return false;
}

long long Variant::toLongLong() const
{
    if (m_value) return m_value->toLongLong();
    else         return 0ll;
}

bool Variant::canConvertToULongLong() const
{
    if (m_value) return m_value->canConvertToULongLong();
    else         return false;
}

unsigned long long Variant::toULongLong() const
{
    if (m_value) return m_value->toULongLong();
    else         return 0ull;
}

bool Variant::canConvertToDouble() const
{
    if (m_value) return m_value->canConvertToDouble();
    else         return false;
}

double Variant::toDouble() const
{
    if (m_value) return m_value->toDouble();
    else         return 0.0;
}

bool Variant::canConvertToObject() const
{
    if (m_value) return m_value->canConvertToObject();
    else         return false;
}

Object Variant::toObject() const
{
    if (m_value) return m_value->toObject();
    else         return Object();
}

bool Variant::canConvertToArray() const
{
    if (m_value) return m_value->canConvertToArray();
    else         return false;
}

Array Variant::toArray() const
{
    if (m_value) return m_value->toArray();
    else         return Array();
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
