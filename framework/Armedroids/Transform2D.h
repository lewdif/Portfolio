#pragma once
#include "headers.h"
#include "Component.h"
#include "GameObject.h"

namespace CompEngine
{
	class Transform2D : public Component
	{
	private:
		GameObject * parent;

		Vec3 position;
		Vec2 scale;
		float rotation;

		Vec2 pivot;

		Vec2 size;

		Matrix transformMat;

	public:
		Transform2D();
		~Transform2D();

		void SetScale(Vec2 scale);
		void SetScale(float x, float y);
		void SetRotate(float rotAngle);
		void SetPosition(Vec3 pos);
		void SetPosition(float x, float y, float z);
		void SetPivot(Vec2 pivot);
		void SetPivot(float x, float y);
		void SetSize(float width, float height);

		void Scale(Vec2 scale);
		void Scale(float x, float y);
		void Rotate(float rotAngle);
		void Translate(Vec3 pos);
		void Translate(float x, float y, float z);

		Vec3 GetPosition();
		Vec2 GetScale();
		float GetRotateAngle();
		Vec2 GetPivot();
		Vec2 GetSize();
		Matrix GetTransformMatrix();

		void AttachObject(GameObject* parent);
	};
}
