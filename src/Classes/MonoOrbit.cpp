#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoOrbit.hpp"

MonoOrbit::MonoOrbit() {}

MonoOrbit::MonoOrbit(const Mono& mono)
{
    positions.insert(positions.begin(), Vector3(mono.position));
}

void MonoOrbit::insertPosition(const Mono& mono, int remaining)
{
    int deleteNum = positions.size() - remaining + 1;

    for (int i = 0; i < deleteNum; i++)
        positions.erase(positions.end() - 1);

    positions.insert(positions.begin(), Vector3(mono.position));
}
