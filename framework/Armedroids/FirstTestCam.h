#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "Camera.h"
#include "SceneManager.h"

namespace CompEngine
{
	class FirstTestCam : public Script
	{
	private:
		Camera* mainCamera;
		GameObject* mainCamObj;
		Transform3D* cameraTrans;
		float mouseX;
		float mouseY;
		Vec3 curPos;
		Vec3 curTargetPos;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();

	public:
		void SetTargetPos();
	};
}
