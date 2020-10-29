#ifndef __Cursor__
#define __Cursor__

#include "SDLGameObject.h"

class Cursor : public SDLGameObject
{
public:
	Cursor() {}
	virtual ~Cursor() {}

	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision();

	virtual std::string objType() { return "Cursor"; }

private:

	void handleInput();
	//void handleAnimation();
};

#endif /*defined(__Cursor__)*/
