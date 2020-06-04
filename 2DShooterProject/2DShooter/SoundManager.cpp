#include "SoundManager.h"

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::init(int frequency, int format, int channnels, int chunksize)
{
	Uint16 sdlAudioFormat = AUDIO_S16;
	
	if (format <= 8)
	{
		sdlAudioFormat = AUDIO_S8;
	}

	std::cout << sdlAudioFormat;

	if (Mix_OpenAudio(frequency, sdlAudioFormat, channnels, chunksize) == -1)
	{
		std::cout << "Mix_OpenAudio: " << Mix_GetError() << "\n";
		return false;
	}

	return true;
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
