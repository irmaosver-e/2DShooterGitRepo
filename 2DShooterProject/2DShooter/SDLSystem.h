#ifndef __SDLSystem__
#define __SDLSystem__

#include <SDL.h>

#include "Singleton.h"
class SDLSystem : public Singleton<SDLSystem>
{
public:
	SDLSystem(token);

	bool init(const char* title, const char* iconPath, int windowXpos, int windowYpos, int screenWidth, int screenHeight, int fps, bool fullScreen,
				int drawColour_R, int drawColour_G, int drawColour_B, int drawColour_A);

	void quit();

	void clearScreen() { SDL_RenderClear(m_pRenderer); }
	void drawScreen() { SDL_RenderPresent(m_pRenderer); }

	int getScreenWidth() const { return SDL_GetWindowSurface(m_pWindow)->w; }
	int getScreenHeight() const { return SDL_GetWindowSurface(m_pWindow)->h; }

	float getFrameTime() { return 1000.f / m_fps; }
	const int& getFrameCount() { return m_frameCount; }
	
	bool capFrameRate();

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

private:
	void countFrame();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_fps;
	float m_frameTime;
	int m_frameCount;

	float m_cronometer;
};

typedef SDLSystem TheSDLSystem;

#endif /* defined( __SDLSystem__ )*/
