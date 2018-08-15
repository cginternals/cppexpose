
#include <string>
#include <iostream>

#include <cppexpose/Object.h>
#include <cppexpose/Var.h>

#include <cppexpose-script/example/TreeNode.h>

#include <cppexpose-js/Engine.h>


using namespace cppexpose;
using namespace cppexpose_script;


class MyObject : public cppexpose::Object
{
public:
    Var<std::string> String;
    Var<int>         Int;
    Var<float>       Float;


public:
    MyObject()
    : String(this, "string", "Hallo")
    , Int   (this, "int", 100)
    , Float (this, "float", 23.42f)
    {
        addFunction("print",        this, &MyObject::print);
        addFunction("test",         this, &MyObject::test);
        addFunction("setFunction",  this, &MyObject::setFunction);
        addFunction("callFunction", this, &MyObject::callFunction);
    }

    virtual ~MyObject()
    {
    }


protected:
    void print(const Variant & value)
    {
        std::cout << ":: " << value.toString() << std::endl;
    }

    void test(int a, float b)
    {
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
    }

    void setFunction(const Variant & func)
    {
        if (func.hasType<Function>()) {
            std::cout << "Setting function." << std::endl;
            m_func = func.value<Function>();
        } else {
            std::cout << "Parameter is not a function." << std::endl;
        }
    }

    void callFunction()
    {
        m_func.call({Variant::fromValue<cppexpose::Object *>(this)});
    }


protected:
    Function m_func;
};


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
