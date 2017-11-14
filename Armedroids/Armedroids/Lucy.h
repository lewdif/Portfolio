#pragma once
//#include "headers.h"
//#include "MeshManager.h"
#include "DeviceManager.h"
#include "TimeManager.h"
#include "SkinnedMesh.h"
#include "Character.h"
#include "LucyState.h"
#include "StateMachine.h"

namespace CompEngine
{

	template <class entityType> class State;

	enum STATES
	{
		IDLE, MOVE, ATTACK, DAMAGED
	};

	class Lucy : public Character
	{
	public:
		Lucy();
		virtual ~Lucy();

	public:
		virtual void Release();
		virtual void Render();
		virtual void InitMembers();

		void SetAnim();

	private:
		CharInfo Info;

	private:
	};

}