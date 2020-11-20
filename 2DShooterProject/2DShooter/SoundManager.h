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
	SoundManager(token) {}

	bool init(int frequency, int format, int channnels, int chunksize);
	bool load(std::string fileName, std::string id, sound_type soundType);
	void quit();

	bool playSoundOnce(std::string sfxID, int sourceID);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);

private:
	void clearSoundSnippets();
	
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	std::map<int, std::map<std::string, int>> m_sfxChecker;
};

typedef SoundManager TheSoundManager;

#endif /* defined ( __SoundManager__ ) */

