#ifndef __TextBox__
#define __TextBox__

#include "SDLGameObject.h"
#include "SDL_Font.h"

class TextBox : public SDLGameObject
{
public:
	TextBox() : SDLGameObject() { m_watchedValue = nullptr; }
	virtual ~TextBox() {}

	virtual void load(const LoaderParams& rParams);

	virtual void draw();
	//virtual void update() {}
	//virtual void clean() {}



private:
	std::string textAndValueMessage();

	std::string m_text;
	std::string m_fontType;
	Colour m_textColour;
	int m_fontSize;

	int* m_watchedValue;
};

#endif /* defined ( __TextBox__ ) */
