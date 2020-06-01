#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "ShooterObject.h"

class AnimatedGraphic : public ShooterObject
{
public:
	AnimatedGraphic() : ShooterObject() {}
	virtual ~AnimatedGraphic() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
	int m_frameCount;
};

#endif /* defined ( __AnimatedGraphic__ ) */