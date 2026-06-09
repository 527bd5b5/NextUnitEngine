#include "Classes/MonoTemplate.hpp"
#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/MonoEffectManager.hpp"

int MonoTemplate::indexShift = 0;

MonoTemplate::MonoTemplate() {}

MonoTemplate::MonoTemplate(const Vector3& origin)
{
    this->origin = origin;
}

Mono& MonoTemplate::getMono(int index) const
{
    return monoEffectManager::getEditableMono(indexShift + index);
}

void MonoTemplate::setMono(int index, const Vector3& position)
{
    getMono(index).position = origin + position;
}

void MonoTemplate::setMono(int index, double x, double y, double z)
{
    setMono(index, Vector3(x, y, z));
}

void MonoTemplate::initIndexShift()
{
    indexShift = 0;
}

void MonoTemplate::initPrepare(int monoNum)
{
    this->monoNum = monoNum;

    monoEffectManager::set(monoNum);
}

void MonoTemplate::initComplete()
{
    indexShift += monoNum;
}

void MonoTemplate::init(int monoNum)
{
    initPrepare(monoNum);
    initComplete();
}
