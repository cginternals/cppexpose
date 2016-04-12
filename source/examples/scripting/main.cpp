
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
        using namespace std::placeholders;

        addProperty<std::string>("string", std::bind(&MyObject::getString, this), std::bind(&MyObject::setString, this, _1));
        addProperty<int>        ("int",    this, &MyObject::getInt, &MyObject::setInt);
        addProperty<float>      ("float",  std::bind(&MyObject::getFloat,  this), std::bind(&MyObject::setFloat, this, _1));

        addFunction("testFunction", this, &MyObject::testFunction);
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

    void setInt(int value)
    {
        m_int = value;
    }

    float getFloat() const
    {
        return m_float;
    }

    void setFloat(float value)
    {
        m_float = value;
    }


protected:
    void testFunction(int a, float b)
    {
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
    }


protected:
    std::string m_string;
    int         m_int;
    float       m_float;
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
