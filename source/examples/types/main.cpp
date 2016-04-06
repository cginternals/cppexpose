
#include <string>
#include <iostream>

#include <cppexpose/typed/DirectValue.h>
#include <cppexpose/typed/DirectArrayValue.h>
#include <cppexpose/typed/StoredValue.h>
#include <cppexpose/typed/StoredArrayValue.h>
#include <cppexpose/variant/Variant.h>


using namespace cppexpose;


// Class containing a value
class MyValue
{
public:
    MyValue()
    : m_value(500)
    {
    }

    ~MyValue()
    {
    }

    int value() const
    {
        return m_value;
    }

    void setValue(int value)
    {
        m_value = value;
    }

protected:
    int m_value;
};


// Static value with accessors
int g_value = 100;

int getValue()
{
    return g_value;
}

void setValue(int v)
{
    g_value = v;
}

std::array<int, 3> three = { {1, 2, 3} };

std::array<int, 3> getArray()
{
    return three;
}

void setArray(const std::array<int, 3> & value)
{
    three = value;
}

int getElement(int index)
{
    return three[index];
}

void setElement(int index, int value)
{
    three[index] = value;
}

enum class Mood : int
{
    Neutral = 0,
    Happy = 1,
    Sad = -1
};

namespace cppexpose
{

template <>
struct EnumDefaultStrings<Mood>
{
    std::map<Mood, std::string> operator()()
    {
        std::map<Mood, std::string> values;
        values[Mood::Neutral] = "Neutral";
        values[Mood::Happy]   = "Happy";
        values[Mood::Sad]     = "Sad";
        return values;
    }
};

}

int main(int, char * [])
{
    using namespace std::placeholders;

    MyValue myValue;

    DirectValue<unsigned int> int1;
    StoredValue<const int> int2(&getValue); //, &setValue);
    StoredValue<int> int3(
        std::bind(&MyValue::value, &myValue),
        std::bind(&MyValue::setValue, &myValue, _1)
    );
//  DirectArrayValue< std::array<int, 3> > ints;
    StoredArrayValue< std::array<int, 3> > ints(&getArray, &setArray, &getElement, &setElement);
    DirectValue<std::string> str1;
    DirectValue<bool> bln1;
    DirectValue<Mood> mood(Mood::Sad);
    DirectValue<float>  flt1;
    DirectValue<double> flt2;
    DirectValue<Variant> var1;

    std::cout << "type(bln1): " << bln1.typeName() << " (" << bln1.type().name() << ")" << std::endl;
    std::cout << "type(str1): " << str1.typeName() << " (" << str1.type().name() << ")" << std::endl;
    std::cout << "type(int1): " << int1.typeName() << " (" << int1.type().name() << ")" << std::endl;
    std::cout << "type(int2): " << int2.typeName() << " (" << int2.type().name() << ")" << std::endl;
    std::cout << "type(int3): " << int3.typeName() << " (" << int3.type().name() << ")" << std::endl;
    std::cout << "type(flt1): " << flt1.typeName() << " (" << flt1.type().name() << ")" << std::endl;
    std::cout << "type(flt2): " << flt2.typeName() << " (" << flt2.type().name() << ")" << std::endl;
    std::cout << "type(ints): " << ints.typeName() << " (" << ints.type().name() << ")" << std::endl;
    std::cout << "Size(ints): " << ints.numElements() << std::endl;
    std::cout << std::endl;

    ints.setValue({{1, 2, 3}});
    std::cout << "int1: " << int1.value() << std::endl;
    std::cout << "int2: " << int2.value() << std::endl;
    std::cout << "int3: " << int3.value() << std::endl;
    std::cout << "ints: " << ints.value()[0] << ", " << ints.value()[1] << ", " << ints.value()[2] << std::endl;
    std::cout << std::endl;

    int1.setValue(10);
    int2.setValue(10);
    int3.setValue(10);
    ints.setElement(0, 10);
    std::cout << "int1: " << int1.value() << std::endl;
    std::cout << "int2: " << int2.value() << std::endl;
    std::cout << "int3: " << int3.value() << std::endl;
    std::cout << "ints: " << ints.value()[0] << ", " << ints.value()[1] << ", " << ints.value()[2] << std::endl;
    std::cout << std::endl;

    int1.setValue(23);
    int2.setValue(23);
    int3.setValue(23);
    ints.setElement(1, 23);
    std::cout << "int1: " << int1.value() << std::endl;
    std::cout << "int2: " << int2.value() << std::endl;
    std::cout << "int3: " << int3.value() << std::endl;
    std::cout << "ints: " << ints.value()[0] << ", " << ints.value()[1] << ", " << ints.value()[2] << std::endl;
    std::cout << std::endl;

    int1.setValue(50);
    int2.setValue(50);
    int3.setValue(50);
    ints.setElement(2, 0);
    std::cout << "int1: " << int1.value() << std::endl;
    std::cout << "int2: " << int2.value() << std::endl;
    std::cout << "int3: " << int3.value() << std::endl;
    std::cout << "ints: " << ints.value()[0] << ", " << ints.value()[1] << ", " << ints.value()[2] << std::endl;
    std::cout << std::endl;

    for (size_t i=0; i<ints.numSubValues(); i++)
    {
        Typed<int> * subValue = static_cast<Typed<int> *>(ints.subValue(i));

        std::cout << "type(ints[" << i << "]): " << subValue->type().name() << std::endl;
        std::cout << "type(ints[" << i << "]): " << subValue->typeName() << std::endl;
        std::cout << "ints[" << i << "]:       " << subValue->value() << std::endl;

        subValue->setValue(42);
    }

    std::cout << std::endl;
    std::cout << "ints: " << ints.value()[0] << ", " << ints.value()[1] << ", " << ints.value()[2] << std::endl;
    std::cout << std::endl;

    std::cout << "bln1.toString(): " << bln1.toString() << std::endl;
    std::cout << "int2.toString(): " << int2.toString() << std::endl;
    std::cout << "ints[1].toString(): " << ints.subValue(1)->toString() << std::endl;
    std::cout << "ints.toString(): " << ints.toString() << std::endl;
    std::cout << std::endl;

    if (ints.fromString("(101, 102, 103)"))
    {
        std::cout << "ints.toString(): " << ints.toString() << std::endl;
        std::cout << std::endl;
    }

    std::cout << "mood.toString(): " << mood.toString() << std::endl;
    std::cout << std::endl;

    mood.fromString("Happy");
    std::cout << "mood.toString(): " << mood.toString() << std::endl;
    std::cout << std::endl;

    Variant v = 3.14f;
    std::cout << "v: " << v.value<float>() << std::endl;
    *v.ptr<float>() = 1.23f;
    std::cout << "v: " << v.value<float>() << std::endl;
    std::cout << std::endl;

    std::cout << "int1:        " << int1.value() << std::endl;
    if (int1.canConvert<int>()) {
        std::cout << "(int)int1:   " << int1.convert<int>() << std::endl;
    }
    if (int1.canConvert<float>()) {
        std::cout << "(float)int1: " << int1.convert<float>() << std::endl;
    }
    if (int1.canConvert<std::string>()) {
        std::cout << "(string)int1: " << int1.convert<std::string>() << std::endl;
    }
    if (!int1.canConvert<MyValue>()) {
        std::cout << "(MyValue)int1: UNSUPPORTED" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
