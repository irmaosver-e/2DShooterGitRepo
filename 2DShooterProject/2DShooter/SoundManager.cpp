#include "SoundManager.h"

bool SoundManager::init(int frequency, int format, int channnels, int chunksize)
{
	Uint16 sdlAudioFormat = AUDIO_S16;
	
	if (format <= 8)
	{
		sdlAudioFormat = AUDIO_S8;
	}

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
		//only add the music to the map once
		if (m_music.find(id) == m_music.end())
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
	}
	else if (soundType == SOUND_SFX)
	{
		//only add the fx to the map once
		if (m_sfxs.find(id) == m_sfxs.end())
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
	}
	else
	{
		std::cout << "unknown sound Type in SoundManager::load \n";
	}

	return false;
}

void SoundManager::quit()
{
	clearSoundSnippets();
	Mix_CloseAudio();
}

void SoundManager::clearSoundSnippets()
{
	for (std::map<std::string, Mix_Chunk*>::iterator itFX = m_sfxs.begin(); itFX != m_sfxs.end(); itFX++)
	{
		Mix_FreeChunk(itFX->second);
		itFX->second = nullptr;
	}

	for (std::map<std::string, Mix_Music*>::iterator itMusic = m_music.begin(); itMusic != m_music.end(); itMusic++)
	{
		Mix_FreeMusic(itMusic->second);
		itMusic->second = nullptr;
	}

	m_sfxs.clear();
	m_music.clear();
}

bool SoundManager::playSoundOnce(std::string sfxID, int sourceID)
{
	bool playingSound = true;

	//first check new request / new client / new sfx same client
	if (m_sfxChecker.empty() || 
		m_sfxChecker.find(sourceID) == m_sfxChecker.end() ||
		m_sfxChecker[sourceID].find(sfxID) == m_sfxChecker[sourceID].end())
	{
		//logs the sourceID to sfxID to channel 
		m_sfxChecker[sourceID][sfxID] = Mix_PlayChannel(-1, m_sfxs[sfxID], 0);
	}
	else
	{
		if (!Mix_Playing(m_sfxChecker[sourceID][sfxID]))
		{
			m_sfxChecker[sourceID].erase(sfxID);

			if (m_sfxChecker[sourceID].empty())
			{
				m_sfxChecker.erase(sourceID);
			}
			
			playingSound = false;
		}
	}

	return playingSound;
}

void SoundManager::playSound(std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::playMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}
