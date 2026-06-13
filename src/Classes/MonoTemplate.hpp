#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Classes/Mono.hpp"
#include "Classes/Vector2.hpp"
#include "Classes/Vector2i.hpp"
#include "Classes/Vector3.hpp"
#include "Classes/Vector3i.hpp"

class MonoTemplate
{
  private:
    static int indexShift;
    std::function<double(void)> getOriginNoise;
    std::function<double(void)> getForceNoise;
    void addMonoOriginNoise(int index);
    void addMonoForceNoise(int index);

  protected:
    Mono& getMono(int index) const;
    void setMonoPosition(int index);
    void setMonoPosition(int index, const Vector3& position);
    void setMonoPosition(int index, double x, double y, double z);
    void setMonoPositionDelta(int index);
    void setMonoPositionDelta(int index, const Vector3& positionDelta);
    void setMonoPositionDelta(int index, double x, double y, double z);
    void initPrepare(int monoNum);
    void initComplete();
    int getScriptInt(const std::string& key, int defaultValue);
    double getScriptDouble(const std::string& key, double defaultValue);
    bool getScriptBoolean(const std::string& key, bool defaultValue);
    Vector2
    getScriptVector2(const std::string& key, const Vector2& defaultValue);
    Vector2i
    getScriptVector2i(const std::string& key, const Vector2i& defaultValue);
    Vector3
    getScriptVector3(const std::string& key, const Vector3& defaultValue);
    Vector3i
    getScriptVector3i(const std::string& key, const Vector3i& defaultValue);

  public:
    int monoNum;
    Vector3 origin; // initial position
    Vector3 force; // initial position delta
    double originNoise;
    double forceNoise;
    std::map<std::string, std::vector<std::string>> script;

    MonoTemplate();
    MonoTemplate(const Vector3& origin);
    static void initIndexShift();
    virtual void init();
    virtual void setFromScript();
};
