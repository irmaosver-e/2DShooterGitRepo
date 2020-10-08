#ifndef __Bullet__
#define __Bullet__

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
	Bullet();
	virtual ~Bullet() {}

    virtual void load(std::unique_ptr<LoaderParams> pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() { SDLGameObject::clean(); }

    virtual void collision();

    virtual std::string objType() { return "Bullet "; }

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

