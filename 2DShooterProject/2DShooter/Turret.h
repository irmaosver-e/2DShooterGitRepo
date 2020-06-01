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

#endif /* defined ( __Turret__ ) */

