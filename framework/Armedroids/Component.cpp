#include "Component.h"

namespace CompEngine
{
	Component::Component()
	{
	}

	void Component::SetComponentName(std::string typeName)
	{
		this->componentName = typeName;
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