
#include <iostream>
#include <fstream>

#include <cppexpose/cppexpose-version.h>

#include <cppexpose/cppexpose.h>


namespace cppexpose
{


void printInfo()
{
    std::string dataPath = "data";

    // Library name
    std::cout << "Library cppexpose::cppexpose" << std::endl;
    std::cout << "========================================" << std::endl;

    // Library version
    std::cout << "Version: " << CPPEXPOSE_VERSION << std::endl;
    std::cout << std::endl;

    // Library type (static or dynamic)
    #ifdef CPPEXPOSE_STATIC_DEFINE
        std::cout << "Library type: STATIC" << std::endl;
    #else
        std::cout << "Library type: SHARED" << std::endl;
    #endif

    // Data directory
    std::cout << "Data path:    " << dataPath << std::endl;
    std::cout << std::endl;

    // Read file
    std::cout << "Data directory access" << std::endl;
    std::cout << "========================================" << std::endl;

    std::string fileName = dataPath + "/DATA_FOLDER.txt";
    std::cout << "Reading from '" << fileName << "': " << std::endl;
    std::cout << std::endl;

    std::ifstream f(fileName);
    if (f.is_open()) {
        std::string line;
        while (getline(f, line)) {
            std::cout << line << '\n';
        }
        f.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}


} // namespace cppexpose
