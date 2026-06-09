#include "Templates/GridMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"
#include "Util.hpp"

namespace monoTemplate
{
    GridMonos::GridMonos() : MonoTemplate() {}

    GridMonos::GridMonos(const Vector3& origin) : MonoTemplate(origin) {}

    void GridMonos::init()
    {
        Vector3i pointLength = Vector3i(size.x + 1, size.y + 1, size.z + 1);

        initPrepare(pointLength.x * pointLength.y * pointLength.z);

        auto getDoubleRand = util::getDoubleRandFunc(-noise, noise);

        Vector3 position;
        Vector3i index;

        for (int z = 0; z < pointLength.z; z++)
        {
            position.z = z - (double)size.z / 2.0;
            index.z = z * pointLength.y * pointLength.x;

            bool isEdgeZ = z == 0 || z == size.z;

            for (int y = 0; y < pointLength.y; y++)
            {
                position.y = y - (double)size.y / 2.0;
                index.y = y * pointLength.x;

                bool isEdgeY = y == 0 || y == size.y;

                for (int x = 0; x < pointLength.x; x++)
                {
                    position.x = x - (double)size.x / 2.0;
                    index.x = x;

                    bool isEdgeX = x == 0 || x == size.x;

                    Mono& mono = getMono(index.z + index.y + index.x);

                    mono.fixed = fixEnd && (isEdgeX || isEdgeY || isEdgeZ);

                    if (noise == 0.0)
                    {
                        mono.position = origin + position;
                    }
                    else
                    {
                        mono.position = origin + position +
                                        Vector3(
                                            getDoubleRand(), getDoubleRand(),
                                            getDoubleRand()
                                        );
                    }
                }
            }
        }

        initComplete();
    }
}
