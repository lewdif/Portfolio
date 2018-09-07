#include "SoundManager.h"


namespace CompEngine
{
	SoundManager::SoundManager()
	{
		position = vec3df(0, 0, 0);
		lookDirection = vec3df(0, 0, 0);
		velPerSecond = vec3df(0, 0, 0);
		up = vec3df(0, 0, 0);
	}

	SoundManager::~SoundManager()
	{
		if (soundEngine != nullptr)
		{
			soundEngine->drop();
		}
	}

	void SoundManager::InitMembers()
	{
		soundEngine = createIrrKlangDevice();
	}

	void SoundManager::ReleaseMembers()
	{
		RemoveAllSounds();

		if (soundEngine != nullptr)
		{
			soundEngine->drop();
		}
	}

	ISoundSource* SoundManager::AddSoundSource(string name)
	{
		return soundEngine->addSoundSourceFromFile(name.c_str());
	}

	ISoundEngine* SoundManager::GetSoundEngine()
	{
		return soundEngine;
	}

	void SoundManager::ListenerUpdate(Vec3 pos, Vec3 lookDir, Vec3 upVector)
	{
		position = vec3df(pos.x, pos.y, pos.z);
		lookDirection = vec3df(lookDir.x, lookDir.y, lookDir.z);
		up = vec3df(upVector.x, upVector.y, upVector.z);

		soundEngine->setListenerPosition(position, lookDirection, velPerSecond, up);
	}

	void SoundManager::StopAllSounds()
	{
		soundEngine->stopAllSounds();
	}

	void SoundManager::Play2D(string file, float volume, bool loop)
	{
		if (soundContainer.find(file) == soundContainer.end())
		{
			ISound* sound = soundEngine->play2D(file.c_str(), loop, false, true);
			sound->setVolume(volume);

			soundContainer.insert(pair<string, ISound*>(file, sound));
		}
		else
		{
			if (soundContainer[file] != nullptr)
			{
				soundContainer[file]->drop();
			}

			soundContainer[file] = soundEngine->play2D(file.c_str(), loop, false, true);
			soundContainer[file]->setVolume(volume);

			soundContainer[file]->setIsLooped(loop);
			soundContainer[file]->setVolume(volume);
		}
	}

	void SoundManager::Stop2D(string file)
	{
		if (soundContainer.find(file) == soundContainer.end()) { return; }

		if (soundContainer[file] != nullptr)
		{
			soundContainer[file]->stop();
		}
	}

	bool SoundManager::IsPlaying2D(string file)
	{
		if (soundContainer.find(file) == soundContainer.end())
			return false;

		if (soundContainer[file] == nullptr)
			return false;

		if (soundContainer[file]->isFinished())
			return false;

		return true;
	}

	void SoundManager::RemoveSound(ISoundSource* source)
	{
		soundEngine->removeSoundSource(source);
	}

	void SoundManager::RemoveAllSounds()
	{
		for (auto iter = soundContainer.begin(); iter != soundContainer.end(); )
		{
			if ((*iter).second != nullptr)
				(*iter).second->drop();

			iter = soundContainer.erase(iter);
		}

		soundEngine->removeAllSoundSources();
	}

}
