#pragma once
#include "Script.h"
#include "Transform2D.h"
#include "SceneManager.h"
#include "Image.h"
#include "SceneManager.h"

namespace CompEngine
{
	class WeaponSelector : public Script
	{
	private:
		Transform2D trans;
		Image img;

		string fileName;

		Rect imgRect;

	public:
		void SetPosition(float x, float y, float z);

	public:
		WeaponSelector(string fileName);

		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
