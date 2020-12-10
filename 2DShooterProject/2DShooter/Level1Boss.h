#ifndef __Level1Boss__
#define __Level1Boss__

#include "Enemy.h"

class Level1Boss : public Enemy
{
public:
    Level1Boss();
    virtual ~Level1Boss() {}

    virtual void load(const LoaderParams& rParams);
    virtual void reset(const LoaderParams& rParams, Vector2Df* position);

    virtual void collision();
    virtual void update();
    virtual void scroll(float scrollSpeed);

    virtual std::string objType() { return "Level1Boss"; }

private:
    bool m_entered;
};

#endif /* defined ( __Level1Boss__ ) */

