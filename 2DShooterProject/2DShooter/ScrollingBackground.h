#ifndef __ScrollingBackground__
#define __ScrollingBackground__

#include "ShooterObject.h"
#include "BaseCreator.h"
#include "Game.h"
#include "TextureManager.h"

class ScrollingBackground : public ShooterObject
{
public:
	ScrollingBackground();
	virtual ~ScrollingBackground() {}

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void collision() {}

private:

    int m_scrollSpeed;

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

class ScrollingBackgroundCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};

#endif /* defined ( __ScrollingBackground__ ) */
