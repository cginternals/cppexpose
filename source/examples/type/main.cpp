
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <cppexpose/type/Type.h>
#include <cppexpose/type/ConcreteType.h>
#include <cppexpose/value/InternalValue.h>
#include <cppexpose/value/ExternalValue.h>
#include <cppexpose/variant/Variant.h>
#include <cppexpose/reflection/Property.h>


using namespace cppexpose;


class Test
{
public:
    Test()
    : m_number(0)
    {
    }

    ~Test()
    {
    }

    bool operator==(const Test & test) const
    {
        return test.m_number == m_number;
    }

    int number() const
    {
        return m_number;
    }

    void setNumber(const int & number)
    {
        m_number = number;
    }

    std::array<int, 3> array() const
    {
        return m_array;
    }

    void setArray(const std::array<int, 3> & array)
    {
        m_array = array;
    }

    int arrayElement(size_t i) const
    {
        return m_array[i];
    }

    void setArrayElement(size_t i, const int & value)
    {
        m_array[i] = value;
    }

    void print()
    {
        std::cout << "array = [" << m_array[0] << ", " << m_array[1] << ", " << m_array[2] << "]" << std::endl;
    }

protected:
    int m_number;
    std::array<int, 3> m_array;
};

enum Weather
{
    Rainy,
    Cloudy,
    Sunny
};

namespace cppexpose
{

template <>
class EnumValues<Weather>
{
public:
    static std::map<std::string, Weather> namedValues()
    {
        static std::map<std::string, Weather> values = {
            { "Rainy", Rainy },
            { "Cloudy", Cloudy },
            { "Sunny", Sunny }
        };

        return values;
    }
};

}

int intValue;

int getInt()
{
    return intValue;
}

void setInt(const int & value)
{
    intValue = value;
}

void printType(const std::string & name, const AbstractValueContainer & value)
{
    std::cout << name << " is " << value.type().typeName() << std::endl;

    std::cout << std::endl;
}

void printTypeInfo(const std::string & name, Type & type)
{
    std::cout << "typeof(" << name << "): " << type.typeName() << " ";
    std::cout << "(";
    if (type.isArray()) {
        std::cout << "array[] ";
    }
    if (type.isIntegral() && type.isUnsigned()) {
        std::cout << "min: " << type.minimum().value<unsigned long long>() << " " << "max: " << type.maximum().value<unsigned long long>();
    }
    if (type.isIntegral() && !type.isUnsigned()) {
        std::cout << "min: " << type.minimum().value<long long>() << " " << "max: " << type.maximum().value<long long>();
    }
    if (type.isFloatingPoint()) {
        std::cout << "min: " << type.minimum().value<double>() << " " << "max: " << type.maximum().value<double>();
    }
    std::cout << ")" << std::endl;
}

void printValue(const std::string & name, AbstractValueContainer & value)
{
    std::cout << name << "(int) = " << value.value<int>() << std::endl;
    std::cout << name << "(float) = " << value.value<float>() << std::endl;
    std::cout << name << "(string) = " << value.toString() << std::endl;
    std::cout << name << "(longlong) = " << value.toLongLong() << std::endl;
    std::cout << name << "(ulonglong) = " << value.toULongLong() << std::endl;
    std::cout << name << "(double) = " << value.toDouble() << std::endl;
    std::cout << name << "(bool) = " << value.toBool() << std::endl;

    std::cout << std::endl;
}

int main(int, char * [])
{
    // Types
    ConcreteType<bool> boolType;
    ConcreteType<int> intType;
    ConcreteType<unsigned int> uintType;
    ConcreteType<long> longType;
    ConcreteType<unsigned long> ulongType;
    ConcreteType<float> floatType;
    ConcreteType<double> doubleType;
    ConcreteType<std::string> stringType;
    ConcreteType<std::array<bool, 3>> arrayType1;
    ConcreteType<std::vector<float>> arrayType2;
    ConcreteType<std::map<std::string, float>> mapType;
    ConcreteType<Test> testType;
    ConcreteType<Weather> weatherType;

    if (boolType == weatherType) {
        std::cout << "boolean is weather!! Wait, what?" << std::endl;
    } else {
        std::cout << "everything is fine" << std::endl;
    }

    std::cout << "int: "           << intType.minimumValue()    << " .. " << intType.maximumValue()    << std::endl;
    std::cout << "unsigned int: "  << uintType.minimumValue()   << " .. " << uintType.maximumValue()   << std::endl;
    std::cout << "long: "          << longType.minimumValue()   << " .. " << longType.maximumValue()   << std::endl;
    std::cout << "unsigned long: " << ulongType.minimumValue()  << " .. " << ulongType.maximumValue()  << std::endl;
    std::cout << "float: "         << floatType.minimumValue()  << " .. " << floatType.maximumValue()  << std::endl;
    std::cout << "double: "        << doubleType.minimumValue() << " .. " << doubleType.maximumValue() << std::endl;
    std::cout << std::endl;

    printTypeInfo("bool",               boolType);
    printTypeInfo("int",                intType);
    printTypeInfo("uint",               uintType);
    printTypeInfo("long",               longType);
    printTypeInfo("ulong",              ulongType);
    printTypeInfo("float",              floatType);
    printTypeInfo("double",             doubleType);
    printTypeInfo("string",             stringType);
    printTypeInfo("array<bool, 3>",     arrayType1);
    printTypeInfo("vector<float>",      arrayType2);
    printTypeInfo("map<string, float>", mapType);
    printTypeInfo("test",               testType);
    printTypeInfo("weather",            weatherType);

    // Values
    InternalValue<int> intValue;
    intValue.setValue(23);
    printValue("int", intValue);
    printType("int", intValue);

    InternalValue<bool> boolValue;
    boolValue.setValue(true);
    printValue("bool", boolValue);
    printType("bool", boolValue);

    InternalValue<Weather> weatherValue;
    weatherValue.fromString("Sunny");
    printValue("weather", weatherValue);
    printType("weather", weatherValue);

    // Managed values
    Test test;
    ExternalValue<int> extValue1(getInt, setInt);
    ExternalValue<int> extValue2(&test, &Test::number, &Test::setNumber);
    ExternalValue<std::array<int, 3>> extValue3(&test, &Test::array, &Test::setArray, &Test::arrayElement, &Test::setArrayElement);

    test.print();
    extValue3.setValue(std::array<int, 3>({{0, 0, 0}}));
    test.print();
    extValue3.setElementValue(0, 100);
    test.print();
    extValue3.setElement(1, "101");
    test.print();
    extValue3.setElementValue(2, 102);
    test.print();

    Variant v1 = 100;
    Variant v2 = 101 - 1;
    Variant v3 = "100";

    if (v1 == v2) std::cout << "v1 == v2" << std::endl;
    if (v1 == v3) std::cout << "v1 == v3" << std::endl;
    if (v2 == v3) std::cout << "v2 == v3" << std::endl;

    Property<int> intProperty("int");

    // Exit
    return 0;
}
