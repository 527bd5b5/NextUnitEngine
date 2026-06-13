#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/MonoCluster.hpp"
#include "Classes/MonoTemplate.hpp"
#include "Classes/Vector3.hpp"
#include "Engine/MonoDeltaStore.hpp"
#include "Engine/MonoEffectManager.hpp"
#include "Utils/Math.hpp"

namespace monoEffectManager
{
    std::vector<Mono> monos;
    std::vector<Mono> nextStepMonos;
    std::vector<MonoCluster> clusters;

    void clear()
    {
        monoDeltaStore::clear();
        MonoTemplate::initIndexShift();

        monos.clear();
        nextStepMonos.clear();
        clusters.clear();
    }

    void init(int num)
    {
        monoDeltaStore::init(num);

        monos = std::vector<Mono>(num);
        nextStepMonos = std::vector<Mono>(num);
        clusters.clear();

        for (int i = 0; i < num; i++)
            nextStepMonos[i] = monos[i] = Mono(i);
    }

    void insert(int addNum)
    {
        monoDeltaStore::insert(addNum);

        int currentMonoNum = monos.size();
        int newMonoNum = currentMonoNum + addNum;

        for (int i = currentMonoNum; i < newMonoNum; i++)
        {
            Mono mono = Mono(i);

            monos.push_back(mono);
            nextStepMonos.push_back(mono);
        }

        clusters.clear();
    }

    void set(int num)
    {
        if (monos.size() == 0)
        {
            init(num);
        }
        else
        {
            insert(num);
        }
    }

    Mono& getEditableMono(int index)
    {
        return nextStepMonos[index];
    }

    void setCluster(const Mono& mono1, const Mono& mono2)
    {
        for (MonoCluster& cluster : clusters)
            if (cluster.join(mono1, mono2))
                return;

        clusters.push_back(MonoCluster(mono1, mono2));
    }

    double calcEffectPower(double x)
    {
        return util::untitledFunc(x);
    }

    void calcNextState(double deltaTimes, double clusterThreshold)
    {
        namespace mds = monoDeltaStore;

        int monoNum = monos.size();

        clusters.clear();

        for (int i = 0; i < monoNum; i++)
            monos[i] = Mono(nextStepMonos[i]);

        for (int i = 0; i < monoNum; i++)
        {
            Vector3 positionDeltaSum;

            for (int j = 0; j < monoNum; j++)
            {
                if (i == j)
                    continue;

                if (j > i)
                {
                    Vector3 positionDelta =
                        monos[i].position - monos[j].position;
                    double magnitude = positionDelta.magnitude();
                    double power = calcEffectPower(magnitude);

                    mds::MonoDelta monoDelta = {
                        positionDelta, magnitude, power
                    };

                    mds::set(i, j, monoDelta);

                    positionDeltaSum += positionDelta * power;

                    if (magnitude <= clusterThreshold)
                        setCluster(monos[i], monos[j]);
                }
                else
                {
                    mds::MonoDelta& monoDelta = mds::get(j, i);

                    positionDeltaSum -=
                        monoDelta.positionDelta * monoDelta.power;
                }
            }

            if (nextStepMonos[i].fixed)
                continue;

            nextStepMonos[i].positionDelta += positionDeltaSum * deltaTimes;
            nextStepMonos[i].position += nextStepMonos[i].positionDelta;
        }
    }
}
