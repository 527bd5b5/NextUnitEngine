#include "Templates/GridMonos.hpp"
#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Util.hpp"

namespace templateGridMonos
{
    int init(
        int indexShift, int sizeX, int sizeY, int sizeZ, bool fixEnd = false,
        double noise = 0.0
    )
    {
        namespace mem = monoEffectManager;

        auto getDoubleRand = util::getDoubleRandFunc(-noise, noise);

        int pointLengthX = sizeX + 1;
        int pointLengthY = sizeY + 1;
        int pointLengthZ = sizeZ + 1;
        int addMonoNum = pointLengthX * pointLengthY * pointLengthZ;

        mem::set(addMonoNum);

        for (int z = 0; z < pointLengthZ; z++)
        {
            double posZ = z - (double)sizeZ / 2.0;
            bool isEdgeZ = z == 0 || z == sizeZ;
            int indexShiftZ = z * pointLengthY * pointLengthX;

            for (int y = 0; y < pointLengthY; y++)
            {
                double posY = y - (double)sizeY / 2.0;
                bool isEdgeY = y == 0 || y == sizeY;
                int indexShiftY = y * pointLengthX;

                for (int x = 0; x < pointLengthX; x++)
                {
                    double posX = x - (double)sizeX / 2.0;
                    bool isEdgeX = x == 0 || x == sizeX;

                    Mono& mono = mem::getEditableMono(
                        indexShift + indexShiftZ + indexShiftY + x
                    );

                    mono.fixed = fixEnd && (isEdgeX || isEdgeY || isEdgeZ);

                    if (noise == 0.0)
                    {
                        mono.position = Vector3(posX, posY, posZ);
                    }
                    else
                    {
                        mono.position = Vector3(
                            posX + getDoubleRand(), posY + getDoubleRand(),
                            posZ + getDoubleRand()
                        );
                    }
                }
            }
        }

        return indexShift + addMonoNum;
    }
}
