
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <cppexpose/type/Type.h>
#include <cppexpose/type/Value.h>


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

    int number() const
    {
        return m_number;
    }

    void setNumber(int number)
    {
        m_number = number;
    }

protected:
    int m_number;
};


void printTypeInfo(const std::string & name, AbstractType & type)
{
    std::cout << "typeof(" << name << "): " << type.typeName() << std::endl;
    std::cout << name << " is const:    " << (type.isConst() ? "true" : "false") << std::endl;
    std::cout << name << " is boolean:  " << (type.isBoolean() ? "true" : "false") << std::endl;
    std::cout << name << " is number:   " << (type.isNumber() ? "true" : "false") << std::endl;
    std::cout << name << " is integral: " << (type.isIntegral() ? "true" : "false") << std::endl;
    std::cout << name << " is unsigned: " << (type.isUnsigned() ? "true" : "false") << std::endl;
    std::cout << name << " is float:    " << (type.isFloatingPoint() ? "true" : "false") << std::endl;
    std::cout << name << " is string:   " << (type.isString() ? "true" : "false") << std::endl;
    std::cout << name << " is array:    " << (type.isArray() ? "true" : "false") << std::endl;
    if (type.isArray()) {
        std::cout << "- dynamic: " << (type.isDynamicArray() ? "true" : "false") << std::endl;
        std::cout << "- elementType: " << type.elementType().typeName() << std::endl;
    }
    std::cout << name << " is map:      " << (type.isMap() ? "true" : "false") << std::endl;

    std::cout << std::endl;
}

void printValue(const std::string & name, AbstractValue & value)
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
    Type<bool> boolType;
    Type<int> intType;
    Type<unsigned int> uintType;
    Type<long> longType;
    Type<unsigned long> ulongType;
    Type<float> floatType;
    Type<double> doubleType;
    Type<std::string> stringType;
    Type<int[3]> arrayType1;
    Type<std::array<bool, 3>> arrayType2;
    Type<std::vector<float>> arrayType3;
    Type<std::map<std::string, float>> mapType;
    Type<Test> testType;

    printTypeInfo("bool",               boolType);
    printTypeInfo("int",                intType);
    printTypeInfo("uint",               uintType);
    printTypeInfo("long",               longType);
    printTypeInfo("ulong",              ulongType);
    printTypeInfo("float",              floatType);
    printTypeInfo("double",             doubleType);
    printTypeInfo("string",             stringType);
    printTypeInfo("int_array[3]",       arrayType1);
    printTypeInfo("array<bool, 3>",     arrayType2);
    printTypeInfo("vector<float>",      arrayType3);
    printTypeInfo("map<string, float>", mapType);
    printTypeInfo("test",               testType);

    // Values
    Value<int> intValue;
    intValue.setValue(23);
    printValue("int", intValue);

    // Exit
    return 0;
}
