#ifndef __Level1Boss__
#define __Level1Boss__

#include "Enemy.h"
#include "Game.h"
#include "BaseCreator.h"

class Level1Boss : public Enemy
{
public:
    Level1Boss();
    virtual ~Level1Boss() {}

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void collision();
    virtual void update();


private:

    bool m_entered;
};

class Level1BossCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Level1Boss();
    }
};
#endif /* defined ( __Level1Boss__ ) */

