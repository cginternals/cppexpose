
#include <string>
#include <iostream>

#include <cppexpose/reflection/Object.h>
#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>
#include <cppexpose/scripting/ScriptContext.h>

#include "TreeNode.h"


using namespace cppexpose;


int main(int, char * [])
{
    ScriptContext scriptContext;

    TreeNode root("root");
    scriptContext.registerObject(&root);

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
            Variant result = scriptContext.evaluate(cmd);
            std::cout << result.toString() << std::endl;
        } else done = true;
    }

    // Exit application
    return 0;
}
