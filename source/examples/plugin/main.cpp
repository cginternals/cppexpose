
#include <string>
#include <iostream>
#include <vector>

#include <cppexpose/plugin/ComponentManager.h>
#include <cppexpose/plugin/AbstractComponent.h>

#include "BottlesOfBeer.h"
#include "Addition.h"
#include "Multiplication.h"


using namespace cppexpose;


int main(int, char * [])
{
    // Create a component manager
    ComponentManager componentManager;

    // Add local components
    componentManager.addComponent(&BottlesOfBeer::Component);
    componentManager.addComponent(&Addition::Component);
    componentManager.addComponent(&Multiplication::Component);

    // Search for plugins in the current working directory
    componentManager.addPluginPath(".");
    componentManager.scanPlugins();

    // List available components
    std::cout << "Components:" << std::endl;
    std::cout << std::endl;
    for (AbstractComponent * component : componentManager.components())
    {
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "name:        " << component->name() << std::endl;
        std::cout << "type:        " << component->type() << std::endl;
        std::cout << "description: " << component->description() << std::endl;
        std::cout << "tags:        " << component->tags() << std::endl;
        std::cout << "annotations: " << component->annotations() << std::endl;
        std::cout << "vendor:      " << component->vendor() << std::endl;
        std::cout << "version:     " << component->version() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    // Get all examples
    for (auto * component : componentManager.components<cppexpose::Example>())
    {
        std::string name = component->name();
        std::string type = component->type();

        // Check if type is "cppexpose::Example"
        if (type != "cppexpose::Example")
            continue;

        // Instanciate example
        auto example = component->createInstance();

        // Evaluate operator
        std::cout << name << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        example->run();
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    // Get all operators
    for (auto * component : componentManager.components<BinaryOperator>())
    {
        std::string name = component->name();
        std::string type = component->type();

        // Check if type is "BinaryOperator"
        if (type != "BinaryOperator")
            continue;

        // Instanciate operator
        auto op = component->createInstance(2, 3);

        // Evaluate operator
        std::cout << name << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << op->compute() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    // Exit application
    return 0;
}
