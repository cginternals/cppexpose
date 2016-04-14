
#include <string>
#include <iostream>

#include <cppexpose/reflection/Object.h>
#include <cppexpose/reflection/Property.h>
#include <cppexpose/typed/DirectValue.h>
#include <cppexpose/scripting/ScriptContext.h>


using namespace cppexpose;


class MyObject : public Object
{
public:
    MyObject(const std::string & name = "obj")
    : Object(name)
    , m_string("Hallo")
    , m_int(100)
    , m_float(23.42)
    {
        addProperty<std::string>("string", this, &MyObject::getString, &MyObject::setString);
        addProperty<int>        ("int",    this, &MyObject::getInt, &MyObject::setInt);
        addProperty<float>      ("float",  this, &MyObject::getFloat,  &MyObject::setFloat);

        addFunction("print",        this, &MyObject::print);
        addFunction("test",         this, &MyObject::test);
        addFunction("setFunction",  this, &MyObject::setFunction);
        addFunction("callFunction", this, &MyObject::callFunction);
    }

    virtual ~MyObject()
    {
    }

    std::string getString() const
    {
        return m_string;
    }

    void setString(const std::string & value)
    {
        m_string = value;
    }

    int getInt() const
    {
        return m_int;
    }

    void setInt(const int & value)
    {
        m_int = value;
    }

    float getFloat() const
    {
        return m_float;
    }

    void setFloat(const float & value)
    {
        m_float = value;
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
        m_func.call(std::vector<Variant>());
    }


protected:
    std::string m_string;
    int         m_int;
    float       m_float;
    Function    m_func;
};

int main(int, char * [])
{
    ScriptContext scriptContext;

    MyObject      obj;
    scriptContext.registerObject(&obj);

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
