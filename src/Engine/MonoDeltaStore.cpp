#include <vector>

#include "Engine/MonoDeltaStore.hpp"

namespace monoDeltaStore
{
    //     00 01 02 03 04 j
    //    +--+--+--+--+--+
    // 00 |><|00|01|02|03|
    //    +--+--+--+--+--+
    // 01 |><|><|04|05|06|
    //    +--+--+--+--+--+
    // 02 |><|><|><|07|08| -> monoDeltas[*]
    //    +--+--+--+--+--+
    // 03 |><|><|><|><|09|
    //    +--+--+--+--+--+
    // 04 |><|><|><|><|><|
    //    +--+--+--+--+--+
    //  i

    int monoNum;
    std::vector<MonoDelta> monoDeltas;
    std::vector<int> stepIndexDict;

    int calcStepIndex(int i)
    {
        int stepIndex = 0;
        int step = monoNum - 1;

        while (i-- > 0)
        {
            stepIndex += step;
            step--;
        }

        return stepIndex;
    }

    void init(int num)
    {
        monoNum = num;
        monoDeltas = std::vector<MonoDelta>(num * (num - 1) / 2);
        stepIndexDict = std::vector<int>(num - 1);

        for (int i = 0; i < num - 1; i++)
            stepIndexDict[i] = calcStepIndex(i);
    }

    void set(int i, int j, MonoDelta& monoDelta)
    {
        monoDeltas[stepIndexDict[i] + j - i - 1] = monoDelta;
    }

    MonoDelta& get(int i, int j)
    {
        return monoDeltas[stepIndexDict[i] + j - i - 1];
    }
}
