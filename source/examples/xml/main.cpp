
#include <string>
#include <iostream>

#include <cppexpose-xml/XML.h>
#include <cppexpose-xml/Element.h>

#include <cppexpose-js/Engine.h>

#include <linenoise-ng/linenoise.h>


using namespace cppexpose;
using namespace cppexpose_xml;


static std::string xml = R"(
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<bookstore>
    <![CDATA[
        Within this Character Data block I can
        use double dashes as much as I want (along with <, &, ', and ")
        *and* %MyParamEntity; will be expanded to the text
        "Has been expanded" ... however, I can't use
        the CEND sequence. If I need to use CEND I must escape one of the
        brackets or the greater-than sign using concatenated CDATA sections.
    ]]>
    <book ISBN="10-000000-001">
        <title>The Iliad and The Odyssey</title>
        <price>12.95</price>
        <comments>
            <userComment rating="4">
                Best translation I've read.
            </userComment>
            <userComment rating="2">
                I like other versions better.
            </userComment>
        </comments>
    </book>
    <book ISBN="10-000000-999">
        <title>Anthology of World Literature</title>
        <price>24.95</price>
        <comments>
            <userComment rating="3">
                Needs more modern literature.
            </userComment>
            <userComment rating="4">
                Excellent overview of world literature.
            </userComment>
        </comments>
    </book>
    <book ISBN="11-000000-002">
        <title>Computer Dictionary</title>
        <price>24.95</price>
        <comments>
            <userComment rating="3">
               A valuable resource.
            </userComment>
        </comments>
    </book>
    <book ISBN="11-000000-003">
        <title>Cooking on a Budget</title>
        <price>23.95</price>
        <comments>
            <userComment rating="4">Delicious!</userComment>
        </comments>
    </book>
    <book ISBN="11-000000-004">
        <title>Great Works of Art</title>
        <price>29.95</price>
    </book>
</bookstore>
)";


int main(int, char * [])
{
    Element root = XML::parse(xml);

    cppexpose_js::Engine engine;
    engine.addGlobalObject("xml", &root);

    // Load history
    linenoiseHistoryLoad("history.txt");

    // Start interactive command console
    while (char * line = linenoise("> ")) {
        // Get command
        std::string cmd = line;
        free(line);

        // Check command
        if (cmd[0] != '\0') {
            // Process command
            if (cmd == "exit") {
                // Exit command line
                break;
            } else {
                // Execute javascript code
                Variant result = engine.evaluate(cmd);
                std::cout << result.toString() << std::endl;

                // Add line to history
                linenoiseHistoryAdd(cmd.c_str());
            }
        }
    }

    // Save history
    linenoiseHistorySave("history.txt");

    // Exit application
    return 0;
}
