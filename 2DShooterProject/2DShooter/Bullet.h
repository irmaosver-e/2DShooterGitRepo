#ifndef __Bullet__
#define __Bullet__

#include "SDLGameObject.h"

class PlayerBullet : public SDLGameObject
{
public:
	PlayerBullet();
	virtual ~PlayerBullet() {}

    virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading);
    virtual void draw() { SDLGameObject::draw(); }
    virtual void update();
    virtual void clean() { SDLGameObject::clean(); }

    virtual void collision();

    virtual std::string objType() { return "PlayerBullet "; }

private:

    Vector2D m_heading;
};

class EnemyBullet : public PlayerBullet
{
public:
    EnemyBullet() : PlayerBullet(){}
    virtual ~EnemyBullet() {}

    virtual std::string objType() { return "EnemyBullet"; }
};

#endif /* defined ( __Bullet__ ) */

