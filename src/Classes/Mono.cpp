#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"

Mono::Mono()
{
    index = -1;
}

Mono::Mono(int index)
{
    this->index = index;
}

Mono::Mono(const Mono& mono)
{
    index = mono.index;
    position = Vector3(mono.position);
    positionDelta = Vector3(mono.positionDelta);
    fixed = mono.fixed;
}
