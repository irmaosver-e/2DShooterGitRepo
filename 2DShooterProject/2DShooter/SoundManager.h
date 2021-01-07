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
	SoundManager(token) 
	{
		m_musicStartTime = 0;
		m_musicPauseTime = 0;
		m_currentMusicID = "";
		m_pausedMusicID = "";
		m_loops = 0;
	}

	bool init(int frequency, int format, int channnels, int chunksize);
	bool load(std::string fileName, std::string id, sound_type soundType);
	void update();
	void quit();

	bool playSoundOnce(std::string sfxID, int sourceID);
	void playSound(std::string id, int loop);
	void playMusic(std::string id, int loop);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();

private:
	void clearSoundSnippets();
	
	std::map<std::string, Mix_Chunk*> m_sfxs;
	std::map<std::string, Mix_Music*> m_music;

	std::map<int, std::map<std::string, int>> m_sfxChecker;

	float m_musicStartTime;
	float m_musicPauseTime;
	std::string m_pausedMusicID;
	std::string m_currentMusicID;
	int m_loops;
};

typedef SoundManager TheSoundManager;

#endif /* defined ( __SoundManager__ ) */

