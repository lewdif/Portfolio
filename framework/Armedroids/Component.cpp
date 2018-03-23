#include "Component.h"

namespace CompEngine
{
	Component::Component()
	{
	}

	void Component::SetComponentName(std::string ComponentName)
	{
		this->componentName = ComponentName;
	}

	string Component::GetComponentName()
	{
		return componentName;
	}

	bool Component::IsScript()
	{
		return isScript;
	}
}