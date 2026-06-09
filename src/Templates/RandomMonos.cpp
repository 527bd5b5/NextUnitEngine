#include "Templates/RandomMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Util.hpp"

namespace monoTemplate
{
    RandomMonos::RandomMonos() : MonoTemplate() {}

    RandomMonos::RandomMonos(const Vector3& origin) : MonoTemplate(origin) {}

    void RandomMonos::init(int monoNum)
    {
        initPrepare(monoNum);

        auto getDoubleRandX = util::getDoubleRandFunc(-size.x, size.x);
        auto getDoubleRandY = util::getDoubleRandFunc(-size.y, size.y);
        auto getDoubleRandZ = util::getDoubleRandFunc(-size.z, size.z);

        for (int i = 0; i < monoNum; i++)
            setMono(i, getDoubleRandX(), getDoubleRandY(), getDoubleRandZ());

        initComplete();
    }
}
