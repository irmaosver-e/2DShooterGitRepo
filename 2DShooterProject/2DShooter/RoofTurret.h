#ifndef __RoofTurret__
#define __RoofTurret__

#include "Turret.h"
#include "BaseCreator.h"
#include "TextureManager.h" 

class RoofTurret : 	public Turret
{
public:
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

/* possible template implementation

ObjCreator<RoofTurret> RoofTurretCreator;

*/

#endif /* defined ( __RoofTurret__ ) */

