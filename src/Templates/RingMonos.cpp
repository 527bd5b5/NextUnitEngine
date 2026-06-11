#include <cmath>

#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Templates/RingMonos.hpp"
#include "Util.hpp"

#define PI_15 3.141592653589793

namespace monoTemplate
{
    RingMonos::RingMonos() : MonoTemplate()
    {
        radius = 1.0;
    }

    RingMonos::RingMonos(const Vector3& origin) : MonoTemplate(origin)
    {
        radius = 1.0;
    }

    void RingMonos::init(int monoNum)
    {
        initPrepare(monoNum);

        auto getPositionNoise =
            util::getDoubleRandFunc(-positionNoise, positionNoise);
        auto getPositionDeltaNoise =
            util::getDoubleRandFunc(-positionDeltaNoise, positionDeltaNoise);

        Vector3 position;
        Vector3 positionDelta;

        for (int i = 0; i < monoNum; i++)
        {
            Mono& mono = getMono(i);
            double angle = 2.0 * PI_15 * (double)i / monoNum;

            position.x = std::cos(angle) * radius;
            position.z = std::sin(angle) * radius;

            if (positionNoise == 0.0)
            {
                mono.position = origin + position;
            }
            else
            {
                mono.position = origin + position +
                                Vector3(
                                    getPositionNoise(), getPositionNoise(),
                                    getPositionNoise()
                                );
            }

            angle += 0.5 * PI_15;

            positionDelta.x = std::cos(angle) * velocity;
            positionDelta.z = std::sin(angle) * velocity;

            if (positionDeltaNoise == 0.0)
            {
                mono.positionDelta = positionDelta;
            }
            else
            {
                mono.positionDelta =
                    positionDelta + Vector3(
                                        getPositionDeltaNoise(),
                                        getPositionDeltaNoise(),
                                        getPositionDeltaNoise()
                                    );
            }
        }

        initComplete();
    }
}
