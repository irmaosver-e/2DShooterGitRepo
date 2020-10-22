#ifndef __HUD__
#define __HUD__

#include "SDLGameObject.h"
#include "Player.h"

#include "AnimatedGraphic.h"

class HUD : public SDLGameObject
{
public:
	HUD() : SDLGameObject() {}
	virtual ~HUD() {}

	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual std::string objType() { return "HUD"; }

private:
	Player* m_pPlayer;

	AnimatedGraphic m_animGraphic;

};

#endif /* defined ( __HUD__ ) */