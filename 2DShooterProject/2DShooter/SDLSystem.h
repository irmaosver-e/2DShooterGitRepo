#ifndef __SDLSystem__
#define __SDLSystem__

#include <SDL.h>

#include "Singleton.h"
class SDLSystem : public Singleton<SDLSystem>
{
public:
	SDLSystem(token);
	~SDLSystem();

	bool init(const char* title, int windowXpos, int windowYpos, int screenWidth, int screenHeight, int fps, bool fullScreen,
				int drawColour_R, int drawColour_G, int drawColour_B, int drawColour_A);

	void quit();

	void clearScreen() { SDL_RenderClear(m_pRenderer); }
	void drawScreen() { SDL_RenderPresent(m_pRenderer); }

	int getScreenWidth() const { return SDL_GetWindowSurface(m_pWindow)->w; }
	int getScreenHeight() const { return SDL_GetWindowSurface(m_pWindow)->h; }

	float getDTSecs(){ return m_frameTime; }
	bool capFrameRate();

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_fps;
	float m_frameTime;
};

typedef SDLSystem TheSDLSystem;

#endif /* defined( __SDLSystem__ )*/
