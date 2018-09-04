#pragma once
#include "ISingleton.h"
#include "headers.h"

using namespace irrklang;

namespace CompEngine
{
	class SoundManager : public ISingleton <SoundManager>
	{
	private:
		ISoundEngine* soundEngine;
		map<string, ISound*> soundContainer;

		irrklang::vec3df position;
		irrklang::vec3df lookDirection;
		irrklang::vec3df velPerSecond;
		irrklang::vec3df up;

	public:
		SoundManager();
		virtual ~SoundManager();

		void InitMembers();

		virtual void ReleaseMembers();

	public:
		ISoundSource* AddSoundSource(string name);
		ISoundEngine* GetSoundEngine();

		void ListenerUpdate(Vec3 pos, Vec3 lookDir, Vec3 upVector);
		void StopAllSounds();

		void Play2D(string file, float volume, bool loop);
		void Stop2D(string file);
		bool IsPlaying2D(string file);

		void RemoveSound(ISoundSource* source);
		void RemoveAllSounds();
	};
}