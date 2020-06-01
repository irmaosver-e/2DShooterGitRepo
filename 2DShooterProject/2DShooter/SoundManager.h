#ifndef __SoundManager__
#define __SoundManager__

#include <iostream>
#include <map>

#include <SDL_mixer.h>
#include "Singleton.h"

enum sound_type {SOUND_MUSIC, SOUND_SFX};

class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager(token);
	~SoundManager();

	bool load(std::string fileName, std::string id, sound_type soundType);

	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);

private:
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;
};

typedef SoundManager TheSoundManager;

#endif /* defined ( __SoundManager__ ) */

