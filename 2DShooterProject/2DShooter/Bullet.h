#ifndef __Bullet__
#define __Bullet__

#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
public:
	PlayerBullet();
	virtual ~PlayerBullet() {}

    virtual void load(std::unique_ptr<LoaderParams> pParams, Vector2D heading);
    virtual void draw() { ShooterObject::draw(); }
    virtual void update();
    virtual void clean() { ShooterObject::clean(); }

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

