
#include <string>
#include <iostream>

#include <cppexpose/Object.h>

#include <cppexpose-js/Engine.h>

#include "TreeNode.h"
#include "MyObject.h"


using namespace cppexpose;


int main(int, char * [])
{
    cppexpose_js::Engine engine;

    // Create scripting environment
    Object script;
    engine.addGlobalObject("script", &script);

    MyObject obj;
    script.addProperty("obj", &obj);

    TreeNode tree;
    script.addProperty("tree", &tree);

    // Provide a script console
    bool done = false;
    while (!done && !std::cin.eof())
    {
        // Prompt
        std::cout << "> " << std::flush;

        // Read command
        std::string cmd;
        std::getline(std::cin, cmd);

        // Process command
        if (cmd != "exit") {
            Variant result = engine.evaluate(cmd);
            std::cout << result.toString() << std::endl;
        } else done = true;
    }

    // Exit application
    return 0;
}
