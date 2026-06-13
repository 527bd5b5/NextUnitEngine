#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "Classes/MonoTemplate.hpp"
#include "Engine/WorldReader.hpp"
#include "Engine/WorldRunner.hpp"
#include "Templates/GridMonos.hpp"
#include "Templates/RandomMonos.hpp"
#include "Templates/RingMonos.hpp"
#include "Utils/String.hpp"

namespace worldReader
{
    void throwInvalidFormat(int lineNum)
    {
        util::printErrorLine(
            "Invalid formatting on line " + std::to_string(lineNum) + ".", 3
        );
    }

    void throwInvalidFormat(const std::string& alias, int lineNum)
    {
        util::printErrorLine(
            "Invalid formatting for template \"" + alias +
                "\" starts on line " + std::to_string(lineNum) + ".",
            3
        );
    }

    void throwInvalidFormat(
        const std::string& alias, int lineNum, const std::runtime_error& e
    )
    {
        util::printErrorLine(
            "Invalid formatting for template \"" + alias +
                "\" starts on line " + std::to_string(lineNum) + ": " +
                e.what(),
            3
        );
    }

    void setMonoTemplate(
        const std::string& alias,
        std::map<std::string, std::vector<std::string>> properties,
        int sectionLineNum
    )
    {
        namespace mt = monoTemplate;

        try
        {
            MonoTemplate* monoTemplatePoint;

            if (alias == "ring")
            {
                monoTemplatePoint = new mt::RingMonos;
            }
            else if (alias == "random")
            {
                monoTemplatePoint = new mt::RandomMonos;
            }
            else if (alias == "grid")
            {
                monoTemplatePoint = new mt::GridMonos;
            }
            else
            {
                throw std::runtime_error("Unregistered template name.");
            }

            monoTemplatePoint->script = properties;

            monoTemplatePoint->setFromScript();

            worldRunner::monoTemplates.push_back(monoTemplatePoint);
        }
        catch (const std::runtime_error& e)
        {
            throwInvalidFormat(alias, sectionLineNum, e);
        }
    }

    void readNueFile(const std::string& filePath)
    {
        std::ifstream file(filePath);

        if (!file)
            util::printErrorLine("A non-existent file was specified.", 2);

        std::string line, alias;
        std::map<std::string, std::vector<std::string>> properties;

        int currentLineNum = 1;
        int sectionLineNum = 1;

        while (std::getline(file, line))
        {
            line = util::trimSpace(line);

            if (line.empty() || line[0] == '#')
            {
                currentLineNum++;

                continue;
            }
            else if (line[0] == '@')
            {
                if (!alias.empty())
                {
                    setMonoTemplate(alias, properties, sectionLineNum);

                    properties.clear();
                }

                alias = line.substr(1);
                sectionLineNum = currentLineNum;
            }
            else
            {
                std::vector<std::string> property =
                    util::splitString(line, ':');

                if (property.size() != 2)
                    throwInvalidFormat(currentLineNum);

                util::trimSpace(property);

                std::vector<std::string> values =
                    util::splitString(property[1], ',');

                if (values.size() < 1)
                    throwInvalidFormat(currentLineNum);

                util::trimSpace(values);

                properties[property[0]] = values;
            }

            currentLineNum++;
        }

        if (!alias.empty())
            setMonoTemplate(alias, properties, sectionLineNum);
    }
}
