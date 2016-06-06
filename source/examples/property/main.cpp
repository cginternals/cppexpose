
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>

#include <cppexpose/reflection/DynamicProperty.h>

#include "MyObject.h"


using namespace cppexpose;
using namespace cppassist;


int main(int, char * [])
{
    // Create object and print its initial contents
    MyObject obj;
    obj.print();

    // Enumerate properties
    std::cout << "Properties:" << std::endl;
    for (auto it : obj.properties())
    {
        AbstractProperty * property = it.second;
        std::cout << "- " << property->name() << " (" << property->typeName() << ")" << std::endl;
    }
    std::cout << std::endl;

    // Set properties directly
    obj.String.setValue("Modified");
    obj.Int.setValue(111);
    obj.Float.setValue(23.42);
    obj.print();

    // Register callback on property changes
    obj.Int.valueChanged.connect([] (const int & value)
    {
        std::cout << "CALLBACK: int set to " << value << std::endl;
    });

    // Get property by name
    AbstractProperty * property = obj.property("int");

    // Set property value from different data types
    property->fromLongLong(-10);
    property->fromDouble(2.5);
    property->fromULongLong(10);
    property->fromBool(1);
    property->fromString("Hallo");
    property->fromString("123");
    property->fromVariant(Variant(2));
    std::cout << std::endl;

    // Set enum values
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.setValue(Mood::Neutral);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromString("Happy");
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromVariant(Variant(-1));
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromULongLong(0);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    std::cout << std::endl;

    // Serialize object properties
    Variant values = obj.toVariant();
    std::cout << values.toJSON(SerializerJSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Create object with sub-objects and dynamic properties
    PropertyGroup * root = new PropertyGroup;

    for (int i=1; i<=4; i++)
    {
        std::string name = "sub" + toString<int>(i);
        PropertyGroup * sub = new PropertyGroup(name);
        root->addProperty(sub, PropertyOwnership::Parent);

        for (int j=1; j<=4; j++)
        {
            std::string name = "value" + toString<int>(j);
            sub->createDynamicProperty<int>(name, i * 10 + j);
        }

        sub->destroyProperty(sub->property("value2"));
        sub->destroyProperty(sub->property("value3"));
    }

    values = root->toVariant();
    std::cout << values.toJSON(SerializerJSON::Beautify) << std::endl;
    std::cout << std::endl;

    delete root;

    // Exit
    return 0;
}
