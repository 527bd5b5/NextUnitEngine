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
    std::string nueFilePath;

    void throwInvalidFormat(int lineNum)
    {
        util::printErrorLine(
            "Invalid formatting on line " + std::to_string(lineNum) + ".", 3
        );
    }

    void throwInvalidFormat(int lineNum, const std::runtime_error& e)
    {
        util::printErrorLine(
            "Invalid formatting on line " + std::to_string(lineNum) + ": " +
                e.what(),
            3
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

    void setWorldConfig(
        const std::string& key, const std::string& value, int currentLineNum
    )
    {
        namespace wr = worldRunner;

        try
        {
            if (key == "mono-graphic-scale")
            {
                wr::monoGraphicScale = std::stod(value);
            }
            else if (key == "mono-graphic-size")
            {
                wr::monoGraphicSize = std::stod(value);
            }
            else if (key == "delta-times")
            {
                wr::deltaTimes = std::stod(value);
            }
            else if (key == "cluster-threshold")
            {
                wr::clusterThreshold = std::stod(value);
            }
            else if (key == "show-mono-index-label")
            {
                wr::showMonoIndexLabel = value == "true";
            }
            else
            {
                throw std::runtime_error("Unregistered config name.");
            }
        }
        catch (const std::runtime_error& e)
        {
            throwInvalidFormat(currentLineNum, e);
        }
        catch (const std::exception& e)
        {
            throwInvalidFormat(currentLineNum);
        }
    }

    void setMonoTemplate(
        const std::string& alias,
        std::map<std::string, std::vector<std::string>>& properties,
        int sectionLineNum
    )
    {
        namespace mt = monoTemplate;

        try
        {
            MonoTemplate* monoTemplatePoint;

            if (alias == "mono")
            {
                monoTemplatePoint = new MonoTemplate;
            }
            else if (alias == "ring")
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

            worldRunner::addMonoTemplate(monoTemplatePoint, properties);
        }
        catch (const std::runtime_error& e)
        {
            throwInvalidFormat(alias, sectionLineNum, e);
        }
    }

    std::pair<std::string, std::vector<std::string>>
    readProperty(const std::string& line, int currentLineNum)
    {
        std::vector<std::string> property = util::splitString(line, ':');

        if (property.size() != 2)
            throwInvalidFormat(currentLineNum);

        util::trimSpace(property);

        std::vector<std::string> values = util::splitString(property[1], ',');

        if (values.size() < 1)
            throwInvalidFormat(currentLineNum);

        util::trimSpace(values);

        return std::make_pair(property[0], values);
    }

    void readNueFile(const std::string& filePath)
    {
        nueFilePath = filePath;

        readNueFile();
    }

    void readNueFile()
    {
        std::ifstream file(nueFilePath);

        if (!file)
            util::printErrorLine("A non-existent file was specified.", 2);

        worldRunner::deleteMonoTemplates();

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
            else if (line[0] == '$')
            {
                auto property = readProperty(line, currentLineNum);

                if (property.second.size() != 1)
                    throwInvalidFormat(currentLineNum);

                setWorldConfig(
                    property.first.substr(1), property.second[0], currentLineNum
                );
            }
            else
            {
                auto property = readProperty(line, currentLineNum);

                properties[property.first] = property.second;
            }

            currentLineNum++;
        }

        if (!alias.empty())
            setMonoTemplate(alias, properties, sectionLineNum);
    }
}
