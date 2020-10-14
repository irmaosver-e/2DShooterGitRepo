#ifndef __ScrollingBackground__
#define __ScrollingBackground__

#include "SDLGameObject.h"
#include "SDL_rect.h"

class ScrollingBackground : public SDLGameObject
{
public:
	ScrollingBackground() : SDLGameObject(), m_count(0), m_maxcount(10) {}
	virtual ~ScrollingBackground() {}

    virtual void load(const LoaderParams& rParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    float m_scrollSpeed;

    int m_count;
    int m_maxcount;

    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;

    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;

    int m_srcRect1Width;
    int m_srcRect2Width;

    int m_destRect1Width;
    int m_destRect2Width;
};

#endif /* defined ( __ScrollingBackground__ ) */
