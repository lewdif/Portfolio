#pragma once
#include "ISingleton.h"
#include "headers.h"

namespace CompEngine
{
	class TimeManager : public ISingleton <TimeManager>
	{
	private:
		double deltaTime;

	public:
		TimeManager();
		virtual ~TimeManager();
		virtual void ReleaseMembers();

	public:
		void SetTime(double timeDelta);
		double GetTime();
	};
}
