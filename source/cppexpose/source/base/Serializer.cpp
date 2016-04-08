
#include <cppexpose/base/Serializer.h>

#include <fstream>
#include <sstream>


namespace cppexpose
{


Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

bool Serializer::load(Variant & obj, const std::string & filename)
{
    // Open file
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (!in) {
        // Could not open file
        return false;
    }

    // Read file content
    std::string content;
    in.seekg(0, std::ios::end);
    content.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();

    // Parse string
    return fromString(obj, content);
}

bool Serializer::save(const Variant & obj, const std::string & filename)
{
    // Open file
    std::ofstream out(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!out) {
        // Could not open file
        return false;
    }

    // Write string representation to file
    out << toString(obj);
    out.close();

    // Success
    return true;
}


} // namespace cppexpose
