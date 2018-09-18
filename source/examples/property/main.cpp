
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/memory/make_unique.h>

#include <cppexpose/reflection/DynamicProperty.h>

#include "MyObject.h"


int main(int, char * [])
{
    // Create object and print its initial contents
    MyObject obj;
    obj.print();

    // Enumerate properties
    std::cout << "Properties:" << std::endl;
    for (auto it : obj.properties())
    {
        cppexpose::AbstractProperty * property = it.second;
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
    cppexpose::AbstractProperty * property = obj.property("int");

    // Set property value from different data types
    property->fromLongLong(-10);
    property->fromDouble(2.5);
    property->fromULongLong(10);
    property->fromBool(1);
    property->fromString("Hallo");
    property->fromString("123");
    property->fromVariant(cppexpose::Variant(2));
    std::cout << std::endl;

    // Set enum values
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.setValue(Mood::Neutral);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromString("Happy");
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromVariant(cppexpose::Variant(-1));
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    obj.MyMood.fromULongLong(0);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.toString() << ")" << std::endl;
    std::cout << std::endl;

    // Serialize object properties
    cppexpose::Variant values = obj.toVariant();
    std::cout << values.toJSON(cppexpose::JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Create object with sub-objects and dynamic properties
    auto root = cppassist::make_unique<cppexpose::Object>();

    for (int i=1; i<=4; i++)
    {
        std::string name = "sub" + cppassist::string::toString<int>(i);
        auto sub = cppassist::make_unique<cppexpose::Object>(name);

        for (int j=1; j<=4; j++)
        {
            std::string name = "value" + cppassist::string::toString<int>(j);
            sub->createDynamicProperty<int>(name, i * 10 + j);
        }

        sub->removeProperty(sub->property("value2"));
        sub->removeProperty(sub->property("value3"));

        root->addProperty(std::move(sub));
    }

    values = root->toVariant();
    std::cout << values.toJSON(cppexpose::JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Exit
    return 0;
}
