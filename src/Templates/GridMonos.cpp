#include "Templates/GridMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"

namespace monoTemplate
{
    GridMonos::GridMonos() : MonoTemplate() {}

    void GridMonos::init()
    {
        Vector3i pointLength = Vector3i(size.x + 1, size.y + 1, size.z + 1);

        initPrepare(pointLength.x * pointLength.y * pointLength.z);

        Vector3 position;
        Vector3i index;

        for (int z = 0; z < pointLength.z; z++)
        {
            position.z = (z - (double)size.z / 2.0) * scale;
            index.z = z * pointLength.y * pointLength.x;

            bool isEdgeZ = z == 0 || z == size.z;

            for (int y = 0; y < pointLength.y; y++)
            {
                position.y = (y - (double)size.y / 2.0) * scale;
                index.y = y * pointLength.x;

                bool isEdgeY = y == 0 || y == size.y;

                for (int x = 0; x < pointLength.x; x++)
                {
                    position.x = (x - (double)size.x / 2.0) * scale;
                    index.x = x;

                    bool isEdgeX = x == 0 || x == size.x;
                    int i = index.z + index.y + index.x;

                    if (fixEnd)
                        getMono(i).fixed = (isEdgeX || isEdgeY || isEdgeZ);

                    setMonoPosition(i, position);
                    setMonoPositionDelta(i);
                }
            }
        }

        initComplete();
    }

    void GridMonos::setFromScript()
    {
        MonoTemplate::setFromScript();

        size = getScriptVector3i("size", Vector3i(4, 4, 4));
        scale = getScriptDouble("scale", 1.0);
        fixEnd = getScriptBoolean("fix-end", false);
    }
}
