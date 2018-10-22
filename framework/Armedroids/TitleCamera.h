#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SceneManager.h"

namespace CompEngine
{
	class TitleCamera : public Script
	{
	private:
		Camera* mainCamera;
		Transform3D* cameraTrans;

		Vec3 mainCamUpVec;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
