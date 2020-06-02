#ifndef __SDLSystem__
#define __SDLSystem__

#include <SDL.h>

#include "Singleton.h"
class SDLSystem : public Singleton<SDLSystem>
{
public:
	SDLSystem(token);
	~SDLSystem();

	bool init(const char* configFilePath);
	void quit();

	void clearScreen() { SDL_RenderClear(m_pRenderer); }
	void drawScreen() { SDL_RenderPresent(m_pRenderer); }

	int getScreenWidth() const { return m_screenWidth; }
	int getScreenHeight() const { return m_screenHeight; }

	float getDTSecs();
	bool capFrameRate();

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getWindow() const { return m_pWindow; }

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_screenWidth;
	int m_screenHeight;

	int m_fps;

	float m_frameTime;
	bool m_bFullScreen;
};

typedef SDLSystem TheSDLSystem;

#endif /* defined( __SDLSystem__ )*/
