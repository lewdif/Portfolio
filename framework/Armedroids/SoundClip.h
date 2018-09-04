#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

using namespace irrklang;

namespace CompEngine
{
	struct Sound {
		ISound* sound;

		float volume;

		bool loop;
		bool isPaused;

		float minDist;
		float maxDist;

		Sound() : sound(nullptr)
		{
		}
	};

	class SoundClip : public Component
	{
	protected:
		GameObject* owner;
		map<string, Sound> soundClips;

	public:
		SoundClip();
		~SoundClip();

		void LoadContent();

		void AttachObject(GameObject* owner);

		void AddSoundClip(string file, float volume, float minDist, float maxDist, bool loop, bool isPaused);
		void ChangeInfo(string file, float volume, float minDist, float maxDist, bool loop, bool isPaused);
		void RemoveSoundClip(string file);

		bool IsPlaying(string clip);

		void Play(string clip);
		void Stop(string clip);

		void Update();
	};
}
