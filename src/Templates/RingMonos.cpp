#include <cmath>

#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Templates/RingMonos.hpp"
#include "Utils/Math.hpp"

namespace monoTemplate
{
    RingMonos::RingMonos() : MonoTemplate() {}

    void RingMonos::init()
    {
        initPrepare(monoNum);

        Vector3 position, positionDelta;

        for (int i = 0; i < monoNum; i++)
        {
            double angle = 2.0 * util::PI_15 * (double)i / monoNum;

            position.x = std::cos(angle) * radius;
            position.z = std::sin(angle) * radius;

            setMonoPosition(i, position);

            angle += 0.5 * util::PI_15;

            positionDelta.x = std::cos(angle) * velocity;
            positionDelta.z = std::sin(angle) * velocity;

            setMonoPositionDelta(i, positionDelta);
        }

        initComplete();
    }

    void RingMonos::setFromScript()
    {
        MonoTemplate::setFromScript();

        monoNum = getScriptInt("mono-num", 8);
        radius = getScriptDouble("radius", 1.0 / 8);
        velocity = getScriptDouble("velocity", 1.0 / 256);
    }
}
