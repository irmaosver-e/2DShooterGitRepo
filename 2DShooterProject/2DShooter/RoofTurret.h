#ifndef __RoofTurret__
#define __RoofTurret__

#include "Turret.h"

class RoofTurret : 	public Turret
{
public:
    virtual ~RoofTurret() {}

    virtual void draw();
    virtual void update();

};

#endif /* defined ( __RoofTurret__ ) */

