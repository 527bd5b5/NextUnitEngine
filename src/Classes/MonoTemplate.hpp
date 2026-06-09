#pragma once

#include "Classes/Mono.hpp"
#include "Classes/Vector3.hpp"

class MonoTemplate
{
  private:
    static int indexShift;

  protected:
    Mono& getMono(int index) const;
    void setMono(int index, const Vector3& position);
    void setMono(int index, double x, double y, double z);

  public:
    int monoNum;
    Vector3 origin;

    MonoTemplate();
    MonoTemplate(const Vector3& origin);
    static void initIndexShift();
    void initPrepare(int monoNum);
    void initComplete();
    virtual void init(int monoNum);
};
