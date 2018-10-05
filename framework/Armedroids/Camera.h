#pragma once

#include "Component.h"
#include "headers.h"
#include "GameObject.h"
#include "DeviceManager.h"

namespace CompEngine
{
	enum PROJECTION_TYPE { PROJECTION_PERSPACTIVE, PROJECTION_ORTHOGONAL };

	class Camera : public Component
	{
	private:
		int ID;

		Vec3 targetPosition;
		Vec3 cameraUp;
		Vec3 viewVector;
		Vec3 crossVector;
		Matrix viewMatrix;
		Matrix projectionMatrix;

		float nearDistance;
		float farDistance;
		float fov;

		PROJECTION_TYPE type;

		GameObject* owner;

		int width;
		int height;

	public:
		Camera(int ID, PROJECTION_TYPE type, Vec3 cameraUp, int width, int height, float farDist, float nearDist, float fov);

		void SetFov(float fov);
		void SetNearDistance(float nearDist);
		void SetFarDistance(float farDist);
		void SetTargetPosition(Vec3 targetPosition);
		void SetTargetPosition(float x, float y, float z);

		int GetID();
		int GetScreenWidth();
		int GetScreenHeight();
		PROJECTION_TYPE GetProjectionType();
		float GetFov();
		float GetNearDistance();
		float GetFarDistance();
		Vec3 GetCameraUp();
		Vec3 GetTargetPosition();
		Matrix GetViewMatrix(GameObject* owner);
		Matrix GetProjectionMatrix();

		void RotateLocalX(float angle);
		void RotateLocalY(float angle);

		Vec3 GetViewVector();
		Vec3 GetCrossVector();

		//Vec3 GetPickRay(float mouseX, float mouseY);

		void FixedUpdate(GameObject* owner, Vec3 tagert);
		virtual void FixedUpdate(GameObject* owner);
	};
}