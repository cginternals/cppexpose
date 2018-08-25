
#include <string>
#include <iostream>

#include <cppassist/string/conversion.h>
#include <cppassist/memory/make_unique.h>

#include <cppexpose/AbstractVar.h>
#include <cppexpose/JSON.h>

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
        std::string   name     = it.first;
        AbstractVar * property = it.second;
        std::cout << "- " << name << " (" << property->typeName() << ")" << std::endl;
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
    AbstractVar * property = obj.property("int");

    // Set property value from different data types
    property->fromVar(Var<int>(-10));
    property->fromVar(Var<double>(2.5));
    property->fromVar(Var<unsigned long long>(10));
    property->fromVar(Var<bool>(1));
    property->fromVar(Var<std::string>("Hallo"));
    property->fromVar(Var<std::string>("123"));
    property->fromVar(Variant(2));
    std::cout << std::endl;

    // Set enum values
    std::cout << "mood = "  << obj.MyMood.convert<int>() << " (" << obj.MyMood.convert<std::string>() << ")" << std::endl;

    obj.MyMood = Mood::Neutral;
    std::cout << "mood = "  << obj.MyMood.convert<int>() << " (" << obj.MyMood.convert<std::string>() << ")" << std::endl;

    obj.MyMood = Variant("Happy");
    std::cout << "mood = "  << obj.MyMood.convert<int>() << " (" << obj.MyMood.convert<std::string>() << ")" << std::endl;

    obj.MyMood = Variant(-1);
    std::cout << "mood = "  << obj.MyMood.convert<int>() << " (" << obj.MyMood.convert<std::string>() << ")" << std::endl;

    obj.MyMood = Variant(0);
    std::cout << "mood = "  << obj.MyMood.convert<int>() << " (" << obj.MyMood.convert<std::string>() << ")" << std::endl;

    std::cout << std::endl;

    // Serialize object properties
    std::cout << JSON::stringify(obj, JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Create object with sub-objects and dynamic properties
    auto root = cppassist::make_unique<Object>();

    for (int i=1; i<=4; i++)
    {
        std::string name = "sub" + cppassist::string::toString<int>(i);
        auto sub = cppassist::make_unique<Object>();

        for (int j=1; j<=4; j++)
        {
            std::string name = "value" + cppassist::string::toString<int>(j);
            sub->createProperty<int>(name, i * 10 + j);
        }

        sub->removeProperty(sub->property("value2"));
        sub->removeProperty(sub->property("value3"));

        root->addProperty(name, std::move(sub));
    }

    std::cout << JSON::stringify(obj, JSON::Beautify) << std::endl;
    std::cout << std::endl;

    // Exit
    return 0;
}
