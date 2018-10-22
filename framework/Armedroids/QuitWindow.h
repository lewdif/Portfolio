#pragma once
#include "Script.h"
#include "Transform2D.h"
#include "SceneManager.h"
#include "Image.h"


namespace CompEngine
{
	class QuitWindow : public Script
	{
	private:
		Transform2D trans;
		Image img;

		Rect imgRect;

	private:

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
