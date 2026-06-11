#include "Templates/RandomMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Utils/Random.hpp"

namespace monoTemplate
{
    RandomMonos::RandomMonos() : MonoTemplate() {}

    void RandomMonos::init()
    {
        initPrepare(monoNum);

        auto getDoubleRandSizeX =
            util::getDoubleRandFunc(-size.x / 2.0, size.x / 2.0);
        auto getDoubleRandSizeY =
            util::getDoubleRandFunc(-size.y / 2.0, size.y / 2.0);
        auto getDoubleRandSizeZ =
            util::getDoubleRandFunc(-size.z / 2.0, size.z / 2.0);

        for (int i = 0; i < monoNum; i++)
        {
            setMonoPosition(
                i, getDoubleRandSizeX(), getDoubleRandSizeY(),
                getDoubleRandSizeZ()
            );

            setMonoPositionDelta(i);
        }

        initComplete();
    }

    void RandomMonos::setFromScript()
    {
        MonoTemplate::setFromScript();

        monoNum = getScriptInt("mono-num", 256);
        size = getScriptVector3("size", Vector3(4.0, 4.0, 4.0));
    }
}
