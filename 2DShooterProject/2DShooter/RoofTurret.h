#ifndef __RoofTurret__
#define __RoofTurret__

#include "Turret.h"
#include "BaseCreator.h"
#include "TextureManager.h" 

class RoofTurret : 	public Turret
{
public:
    virtual ~RoofTurret() {}

    virtual void draw();
    virtual void update();

};

class RoofTurretCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new RoofTurret();
    }
};

#endif /* defined ( __RoofTurret__ ) */

