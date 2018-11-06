#include "headers.h"
#include "SoundClip.h"
#include "SoundManager.h"
#include "Transform3D.h"


namespace CompEngine
{
	SoundClip::SoundClip()
	{
		SetComponentName("SoundClip");
	}

	SoundClip::~SoundClip()
	{
	}

	void SoundClip::LoadContent()
	{
	}

	void SoundClip::AttachObject(GameObject* owner)
	{
		this->owner = owner;
	}

	void SoundClip::AddSoundClip(string file, float volume, float minDist, float maxDist, bool loop, bool isPaused)
	{
		Sound clip;

		clip.volume = volume;
		clip.minDist = minDist;
		clip.maxDist = maxDist;
		clip.loop = loop;
		clip.isPaused = isPaused;

		soundClips.insert(pair<string, Sound>(file, clip));
	}

	void SoundClip::ChangeInfo(string file, float volume, float minDist, float maxDist, bool loop, bool isPaused)
	{
		auto item = soundClips.find(file);

		if (item == soundClips.end())
			return;

		item->second.volume = volume;
		item->second.minDist = minDist;
		item->second.maxDist = maxDist;
		item->second.loop = loop;
		item->second.isPaused = isPaused;

		if (item->second.sound != nullptr)
		{
			item->second.sound->setVolume(item->second.volume);
			item->second.sound->setMinDistance(item->second.minDist);
			item->second.sound->setMaxDistance(item->second.maxDist);
			item->second.sound->setIsLooped(item->second.loop);
		}
	}


	void SoundClip::RemoveSoundClip(string clip)
	{
		auto item = soundClips.find(clip);

		if (item == soundClips.end())
			return;

		if (item->second.sound != nullptr)
		{
			item->second.sound->drop();
		}

		item->second.sound = nullptr;

		soundClips.erase(item);
	}

	bool SoundClip::IsPlaying(string clip)
	{
		auto item = soundClips.find(clip);

		if (item == soundClips.end())
			return false;

		if (item->second.sound == nullptr)
			return false;

		if (item->second.sound->isFinished())
			return false;

		return true;
	}

	void SoundClip::Play(string clip)
	{
		auto item = soundClips.find(clip);

		if (item == soundClips.end())
		{
			cout << "Sound : " + clip + "doesn't exist." << endl;
			return;
		}

		Vec3 pos = GET_TRANSFORM_3D(owner)->GetPosition();

		if (item->second.sound != nullptr)
			item->second.sound->drop();

		item->second.sound = SoundMgr->GetSoundEngine()->play3D(clip.c_str(),
			vec3df(pos.x, pos.y, pos.z), item->second.loop, false, true );

		if (item->second.sound != nullptr)
		{
			item->second.sound->setVolume(item->second.volume);
			item->second.sound->setMinDistance(item->second.minDist);
			item->second.sound->setMaxDistance(item->second.maxDist);
		}
	}

	void SoundClip::Stop(string clip)
	{
		auto item = soundClips.find(clip);

		if (item == soundClips.end())
			return;

		if (item->second.sound != nullptr)
			item->second.sound->stop();
	}

	void SoundClip::Update()
	{
		for each(auto item in soundClips)
		{
			if (item.second.sound != nullptr)
			{
				Vec3 pos = GET_TRANSFORM_3D(owner)->GetPosition();

				item.second.sound->setPosition(vec3df(pos.x, pos.y, pos.z));
			}
		}
	}

}
