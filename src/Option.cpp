#include <iostream>
#include <string>

#include "Engine/WorldReader.hpp"
#include "GlutTools/GlutDraw.hpp"
#include "GlutTools/GlutEvent.hpp"
#include "NextUnitEngine.hpp"
#include "Utils/String.hpp"

namespace option
{
    void set(int argc, const char** argv)
    {
        worldReader::nueFilePath = "";

        int i = 1;

        try
        {
            while (i < argc)
            {
                std::string args(argv[i]);

                if (args == "-s")
                {
                    glutDraw::updateCycle = std::stoi(argv[++i]);
                }
                else if (args == "-f")
                {
                    glutEvent::cameraFov = std::stod(argv[++i]);
                }
                else if (args == "-fw")
                {
                    frameWidth = std::stoi(argv[++i]);
                }
                else if (args == "-fh")
                {
                    frameHeight = std::stoi(argv[++i]);
                }
                else if (args == "-fx")
                {
                    framePositionX = std::stoi(argv[++i]);
                }
                else if (args == "-fy")
                {
                    framePositionY = std::stoi(argv[++i]);
                }
                else
                {
                    worldReader::nueFilePath = argv[i];
                }

                i++;
            }
        }
        catch (const std::invalid_argument& e)
        {
            util::printErrorLine(
                "The " + std::to_string(i - 1) +
                    "th argument must be a number.",
                1
            );
        }
        catch (const std::logic_error& e)
        {
            util::printErrorLine("Specify a value after the option.", 1);
        }

        if (worldReader::nueFilePath == "")
            util::printErrorLine("NUE file not specified.", 1);
    }
}
