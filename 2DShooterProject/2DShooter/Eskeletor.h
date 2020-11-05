#ifndef __Eskeletor__
#define __Eskeletor__


#include "Enemy.h"

class Eskeletor : public Enemy
{
public:

    Eskeletor();
    virtual ~Eskeletor() {}
    virtual void reset(const LoaderParams& rParams);

    virtual void collision();
    virtual void collisionWithLayer();

    virtual void update();

    virtual std::string objType() { return "Eskeletor"; }

private:
    enum eskeletor_state { ALIVE, DEAD };
};

#endif /* defined ( __Eskeletor__ ) */

