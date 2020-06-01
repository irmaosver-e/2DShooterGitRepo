#ifndef __Eskeletor__
#define __Eskeletor__


#include "Enemy.h"
#include "BaseCreator.h"
#include "SoundManager.h"
#include "BulletHandler.h"
#include "Game.h"

class Eskeletor : public Enemy
{
public:

    Eskeletor();
    virtual ~Eskeletor() {}

    virtual void collision();
    virtual void update();
};

#endif /* defined ( __Eskeletor__ ) */

