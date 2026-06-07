#include "Templates/RandomMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Util.hpp"

namespace templateRandomMonos
{
    void init(int num, double spread)
    {
        namespace mem = monoEffectManager;

        mem::init(num);

        auto getDoubleRand = util::getDoubleRandFunc(-spread, spread);

        for (int i = 0; i < mem::monos.size(); i++)
            mem::getEditableMono(i).position =
                Vector3(getDoubleRand(), getDoubleRand(), getDoubleRand());
    }
}
