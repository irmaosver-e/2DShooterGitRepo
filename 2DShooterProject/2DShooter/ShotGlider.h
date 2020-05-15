#ifndef __ShotGlider__
#define __ShotGlider__

#include "Glider.h"
#include "BaseCreator.h"

//cpp includes
#include "BulletHandler.h"

class ShotGlider : public Glider
{
public:

    ShotGlider();
    virtual ~ShotGlider() {}

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void update();
};

class ShotGliderCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new ShotGlider();
    }
};
#endif /* defined ( __ShotGlider__ )*/

