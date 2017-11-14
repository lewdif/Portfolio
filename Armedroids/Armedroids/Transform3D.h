#pragma once
#include "Component.h"
#include "headers.h"
#include "GameObject.h"

namespace CompEngine
{
	class Transform3D : public Component
	{
	private:
		Vec3 position;
		Vec3 forward;
		Vec3 up;
		Vec3 scale;
		Quater rotAngle;

		Matrix transform;
		Matrix scaleTransform;
		Matrix rotationTransform;
		Matrix translationTransform;

		GameObject *parent;
		Matrix* combineMatrix;

	public:
		Transform3D();
		virtual ~Transform3D();

		void SetForward(float x, float y, float z);
		void SetForward(Vec3 forward);

		void SetPosition(float x, float y, float z);
		void SetPosition(Vec3 pos);

		void Scale(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void Scale(Vec3 scale);
		void SetScale(Vec3 scale);

		void Rotate(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void Rotate(Quater rotAngle);
		void SetRotation(Quater rotAngle);

		void Translate(float x, float y, float z);
		void Translate(Vec3 pos);

		Vec3 GetForward();
		Vec3 GetLeft();

		Vec3 GetPosition();
		Vec3 GetWorldPositon();

		Vec3 GetScale();
		Vec3 GetWolrdScale();

		Vec3 GetRotationAngle();
		Vec3 GetWorldRotationAngle();
		Quater GetRotationQuater();
		Quater GetWorldRotationQuater();

		void AttachObject(GameObject* parent);

		Matrix GetTransform();
		void CombineMatrix(Matrix* matrix);
	};
}