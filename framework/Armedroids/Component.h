#pragma once
#include "headers.h"

namespace CompEngine
{
	class Component
	{
	private:
		string componentName;

	protected:
		void SetComponentName(string componentName);
		bool isScript;

	public:
		Component();
		virtual ~Component() {}

		string GetComponentName();
		bool IsScript();
	};
}
