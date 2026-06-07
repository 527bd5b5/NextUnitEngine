#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"

namespace monoEffectManager
{
    extern std::vector<Mono> monos;
    extern std::vector<MonoCluster> clusters;

    void init(int num);
    Mono& getEditableMono(int index);
    void calcNextState(double deltaTimes, double clusterThreshold);
}
