#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = nullptr;

SoundManager* SoundManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new SoundManager();
	}
	return s_pInstance;
}

SoundManager::SoundManager()
{
	Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
	std::cout << " HARDCODED values for SoundManager::SoundManager() \n"
				"Mix_OpenAudio(frequency, Uint16 format, int channnels, int chunksize) \n";
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type soundType)
{
	if (soundType == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		
		if (!pMusic)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << "\n";
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	else if (soundType == SOUND_SFX)
	{
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());

		if (!pChunk)
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << "\n";
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	else
	{
		std::cout << "unknown sound Type in SoundManager::load \n";
	}

	return false;
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}
