#include <iostream>
#include <string>
#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector2.hpp"
#include "Classes/Vector2i.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Utils/Random.hpp"

int MonoTemplate::indexShift = 0;

MonoTemplate::MonoTemplate() {}

void MonoTemplate::addMonoOriginNoise(int index)
{
    if (originNoise != 0.0)
        getMono(index).position +=
            Vector3(getOriginNoise(), getOriginNoise(), getOriginNoise());
}

void MonoTemplate::addMonoForceNoise(int index)
{
    if (forceNoise != 0.0)
        getMono(index).positionDelta +=
            Vector3(getForceNoise(), getForceNoise(), getForceNoise());
}

Mono& MonoTemplate::getMono(int index) const
{
    return monoEffectManager::getEditableMono(indexShift + index);
}

void MonoTemplate::setMonoPosition(int index)
{
    getMono(index).position = origin;

    addMonoOriginNoise(index);
}

void MonoTemplate::setMonoPosition(int index, const Vector3& position)
{
    getMono(index).position = origin + position;

    addMonoOriginNoise(index);
}

void MonoTemplate::setMonoPosition(int index, double x, double y, double z)
{
    setMonoPosition(index, Vector3(x, y, z));
}

void MonoTemplate::setMonoPositionDelta(int index)
{
    getMono(index).positionDelta = force;

    addMonoForceNoise(index);
}

void MonoTemplate::setMonoPositionDelta(int index, const Vector3& positionDelta)
{
    getMono(index).positionDelta = force + positionDelta;

    addMonoForceNoise(index);
}

void MonoTemplate::setMonoPositionDelta(int index, double x, double y, double z)
{
    setMonoPositionDelta(index, Vector3(x, y, z));
}

void MonoTemplate::initPrepare(int monoNum)
{
    this->monoNum = monoNum;

    monoEffectManager::set(monoNum);

    getOriginNoise = util::getDoubleRandFunc(-originNoise, originNoise);
    getForceNoise = util::getDoubleRandFunc(-forceNoise, forceNoise);
}

void MonoTemplate::initComplete()
{
    indexShift += monoNum;
}

int MonoTemplate::getScriptInt(const std::string& key, int defaultValue)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 1)
        throw std::runtime_error("Number of invalid integer type arguments.");

    return std::stoi(values[0]);
}

double
MonoTemplate::getScriptDouble(const std::string& key, double defaultValue)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 1)
        throw std::runtime_error("Number of invalid double type arguments.");

    return std::stod(values[0]);
}

bool MonoTemplate::getScriptBoolean(const std::string& key, bool defaultValue)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 1)
        throw std::runtime_error("Number of invalid boolean type arguments.");

    return values[0] == "true";
}

Vector2 MonoTemplate::getScriptVector2(
    const std::string& key, const Vector2& defaultValue
)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 2)
        throw std::runtime_error("Number of invalid vector-2 type arguments.");

    return Vector2(std::stod(values[0]), std::stod(values[1]));
}

Vector2i MonoTemplate::getScriptVector2i(
    const std::string& key, const Vector2i& defaultValue
)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 2)
        throw std::runtime_error("Number of invalid vector-2i type arguments.");

    return Vector2i(std::stoi(values[0]), std::stoi(values[1]));
}

Vector3 MonoTemplate::getScriptVector3(
    const std::string& key, const Vector3& defaultValue
)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 3)
        throw std::runtime_error("Number of invalid vector-3 type arguments.");

    return Vector3(
        std::stod(values[0]), std::stod(values[1]), std::stod(values[2])
    );
}

Vector3i MonoTemplate::getScriptVector3i(
    const std::string& key, const Vector3i& defaultValue
)
{
    if (script.count(key) == 0)
        return defaultValue;

    std::vector<std::string>& values = script[key];

    if (values.size() != 3)
        throw std::runtime_error("Number of invalid vector-3i type arguments.");

    return Vector3i(
        std::stoi(values[0]), std::stoi(values[1]), std::stoi(values[2])
    );
}

void MonoTemplate::initIndexShift()
{
    indexShift = 0;
}

void MonoTemplate::init()
{
    throw std::logic_error("Function not overridden.");
}

void MonoTemplate::setFromScript()
{
    origin = getScriptVector3("origin", Vector3(0.0, 0.0, 0.0));
    force = getScriptVector3("force", Vector3(0.0, 0.0, 0.0));
    originNoise = getScriptDouble("origin-noise", 0.0);
    forceNoise = getScriptDouble("force-noise", 0.0);
}
