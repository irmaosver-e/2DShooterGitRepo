#ifndef __TextBox__
#define __TextBox__

#include "SDLGameObject.h"
#include "SDL_Font.h"

class TextBox : public SDLGameObject
{
public:
	TextBox() : SDLGameObject() {}
	virtual ~TextBox() {}

	virtual void load(const LoaderParams& rParams);

	virtual void draw();
	//virtual void update() {}
	//virtual void clean() {}

private:
	std::string m_text;
	std::string m_fontType;
	Colour m_textColour;
};

#endif /* defined ( __TextBox__ ) */
