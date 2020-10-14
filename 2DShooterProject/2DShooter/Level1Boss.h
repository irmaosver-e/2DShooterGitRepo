#ifndef __Level1Boss__
#define __Level1Boss__

#include "Enemy.h"

class Level1Boss : public Enemy
{
public:
    Level1Boss();
    virtual ~Level1Boss() {}

    virtual void load(const LoaderParams& rParams);
    virtual void collision();
    virtual void update();


private:
    bool m_entered;
};

#endif /* defined ( __Level1Boss__ ) */

