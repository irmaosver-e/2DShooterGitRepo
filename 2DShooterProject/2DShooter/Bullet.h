#ifndef __Bullet__
#define __Bullet__

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
	Bullet();
	virtual ~Bullet() {}

    virtual void update();
    
    
    virtual void outOfView();

    virtual void collision();
    virtual void collisionPassive();
    virtual void collisionWithLayer();

    virtual std::string objType() { return "Bullet"; }

private:
    //void turnBulletOff();
};

class PlayerBullet : public Bullet
{
public:
    PlayerBullet() : Bullet() {}
    virtual ~PlayerBullet() {}

    virtual std::string objType() { return "PlayerBullet"; }
};

class EnemyBullet : public Bullet
{
public:
    EnemyBullet() : Bullet(){}
    virtual ~EnemyBullet() {}

    virtual std::string objType() { return "EnemyBullet"; }
};

#endif /* defined ( __Bullet__ ) */

