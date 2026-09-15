#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Classes/MonoOrbit.hpp"

namespace monoEffectManager
{
    extern std::vector<Mono> monos;
    extern std::vector<MonoCluster> clusters;
    extern std::vector<MonoOrbit> orbits;

    void clear();
    void set(int num);
    Mono& getEditableMono(int index);
    void calcNextState(
        double deltaTimes, double clusterThreshold, int orbitRemaining
    );
}
