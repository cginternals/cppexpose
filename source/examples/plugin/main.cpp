
#include <string>
#include <iostream>

#include <cppexpose/plugin/ComponentManager.h>
#include <cppexpose/plugin/TypedComponent.h>
#include <cppexpose/plugin/Example.h>

#include "BottlesOfBeer.h"


using namespace cppexpose;


int main(int, char * [])
{
    // Create a component manager
    ComponentManager componentManager;

    // Add local components
    componentManager.addComponent(&BottlesOfBeer::Component);

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
        std::cout << "description: " << component->description() << std::endl;
        std::cout << "type:        " << component->type() << std::endl;
        std::cout << "tags:        " << component->tags() << std::endl;
        std::cout << "annotations: " << component->annotations() << std::endl;
        std::cout << "vendor:      " << component->vendor() << std::endl;
        std::cout << "version:     " << component->version() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    // Run all examples
    for (AbstractComponent * component : componentManager.components())
    {
        std::string name = component->name();
        std::string type = component->type();

        // Check if type is "cppexpose::Example"
        if (type != "cppexpose::Example")
            continue;

        // Instanciate example
        TypedComponent<Example> * exampleComponent = 
            static_cast< TypedComponent<Example> * >(component);
        Example * example = exampleComponent->createInstance();

        // Run example
        std::cout << name << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        example->run();
        std::cout << "----------------------------------------" << std::endl;
        std::cout << std::endl;
    }

    // Exit application
    return 0;
}
