#pragma once

#include <vector>

#include "Classes/MonoTemplate.hpp"

namespace worldRunner
{
    extern double monoGraphicScale;
    extern double monoGraphicSize;
    extern double deltaTimes;
    extern double clusterThreshold;
    extern bool showMonoIndexLabel;
    extern std::vector<MonoTemplate*> monoTemplates;

    void addMonoTemplate(
        MonoTemplate* mt,
        std::map<std::string, std::vector<std::string>>& properties
    );
    void deleteMonoTemplates();
    void reset();
    void reload();
    void update();
    void draw();
}
