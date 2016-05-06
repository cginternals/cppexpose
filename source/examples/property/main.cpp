
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>

#include <cppexpose/reflection/AbstractProperty.h>

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
        std::cout << "- " << property->name() << " (" << property->asTyped()->typeName() << ")" << std::endl;
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
    property->asTyped()->fromLongLong(-10);
    property->asTyped()->fromDouble(2.5);
    property->asTyped()->fromULongLong(10);
    property->asTyped()->fromBool(1);
    property->asTyped()->fromString("Hallo");
    property->asTyped()->fromString("123");
    property->asTyped()->fromVariant(Variant(2));
    std::cout << std::endl;

    // Set enum values
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.asTyped()->toString() << ")" << std::endl;
    obj.MyMood.setValue(Mood::Neutral);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.asTyped()->toString() << ")" << std::endl;
    obj.MyMood.asTyped()->fromString("Happy");
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.asTyped()->toString() << ")" << std::endl;
    obj.MyMood.asTyped()->fromVariant(Variant(-1));
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.asTyped()->toString() << ")" << std::endl;
    obj.MyMood.asTyped()->fromULongLong(0);
    std::cout << "mood = "  << (int)obj.getMood() << " (" << obj.MyMood.asTyped()->toString() << ")" << std::endl;
    std::cout << std::endl;

    // Serialize object properties
    Variant values = obj.toVariant();
    std::cout << values.toJSON(SerializerJSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Create object with sub-objects and dynamic properties
    Object * root = new Object;

    for (int i=1; i<=4; i++)
    {
        std::string name = "sub" + toString<int>(i);
        Object * sub = new Object(name, root);
        root->addProperty(sub);

        for (int j=1; j<=4; j++)
        {
            std::string name = "value" + toString<int>(j);
            sub->addProperty(new DynamicProperty<int>(sub, name, i * 10 + j));
        }
    }

    values = root->toVariant();
    std::cout << values.toJSON(SerializerJSON::Beautify) << std::endl;
    std::cout << std::endl;

    delete root;

    // Exit
    return 0;
}
