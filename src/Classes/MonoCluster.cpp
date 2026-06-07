#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Classes/Vector3.hpp"

MonoCluster::MonoCluster() {}

MonoCluster::MonoCluster(const Mono& mono1, const Mono& mono2)
{
    monos.push_back(mono1);
    monos.push_back(mono2);
}

bool MonoCluster::contains(const Mono& targetMono) const
{
    for (const Mono& mono : monos)
        if (mono.index == targetMono.index)
            return true;

    return false;
}

int MonoCluster::size() const
{
    return monos.size();
}

bool MonoCluster::join(const Mono& mono1, const Mono& mono2)
{
    if (contains(mono1))
    {
        if (!contains(mono2))
            monos.push_back(mono2);

        return true;
    }

    if (contains(mono2))
    {
        if (!contains(mono1))
            monos.push_back(mono1);

        return true;
    }

    return false;
}

Vector3 MonoCluster::getCenterPosition() const
{
    Vector3 position;

    for (const Mono& mono : monos)
        position += mono.position;

    return position / monos.size();
}
