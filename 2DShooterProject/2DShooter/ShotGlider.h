#ifndef __ShotGlider__
#define __ShotGlider__

#include "Glider.h"

class ShotGlider : public Glider
{
public:

    ShotGlider();
    virtual ~ShotGlider() {}

    virtual void load(const LoaderParams& rParams);

    virtual void update();
};

#endif /* defined ( __ShotGlider__ )*/

