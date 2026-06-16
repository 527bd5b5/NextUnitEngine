#pragma once

#include <vector>

#include "Classes/MonoTemplate.hpp"

namespace worldRunner
{
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
