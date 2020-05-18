#ifndef __Turret__
#define __Turret__

#include "Enemy.h"
#include "BaseCreator.h"

class Turret :	public Enemy
{
public:
    Turret();
    virtual ~Turret() {}

    virtual void collision();
    virtual void update();

};

class TurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Turret();
    }
};

#endif /* defined ( __Turret__ ) */

