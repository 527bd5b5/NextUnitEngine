#include "Templates/RandomMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Util.hpp"

namespace templateRandomMonos
{
    int init(int indexShift, int num, double spread)
    {
        namespace mem = monoEffectManager;

        auto getDoubleRand = util::getDoubleRandFunc(-spread, spread);

        mem::set(num);

        for (int i = 0; i < num; i++)
            mem::getEditableMono(indexShift + i).position =
                Vector3(getDoubleRand(), getDoubleRand(), getDoubleRand());

        return indexShift + num;
    }
}
