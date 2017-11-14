#include "TimeManager.h"


namespace CompEngine
{
	TimeManager::TimeManager()
		:deltaTime(0)
	{
	}

	TimeManager::~TimeManager()
	{
	}

	void TimeManager::SetTime(double timeDelta)
	{
		deltaTime = timeDelta;
	}

	double TimeManager::GetTime()
	{
		return deltaTime;
	}

	void TimeManager::ReleaseMembers()
	{
	}
}