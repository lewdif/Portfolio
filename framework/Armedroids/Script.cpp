#include "Script.h"


namespace CompEngine
{
	Script::Script()
	{
	}

	Script::~Script()
	{
	}

	void Script::SetInfo(GameObject* gameObject, string name)
	{
		this->gameObject = gameObject;
		this->SetComponentName(name);

		isScript = true;
	}

	void Script::Awake()
	{

	}

	void Script::Init()
	{

	}

	void Script::Reference()
	{

	}

	void Script::Update()
	{

	}

	void Script::LateUpdate()
	{

	}

	void Script::LateRender()
	{

	}
}