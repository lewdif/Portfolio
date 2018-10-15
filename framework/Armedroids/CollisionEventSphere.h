#pragma once
#include "Component.h"
#include "headers.h"
#include "GameObject.h"

namespace CompEngine
{
	class CollisionEventSphere : public Component
	{
	public:
		CollisionEventSphere();
		virtual ~CollisionEventSphere();
	
	private:
		Vec3 shapePos;
		float shapeRadius;
		LPD3DXMESH shapeMesh;

	public:
		void Init(Vec3 pos, float radius);
		void Update(Vec3 pos);
		void Render(Matrix trans, D3DXCOLOR color);
		bool Collide(CollisionEventSphere* colShape);
		Vec3 GetShapePos();
		float GetShapeRadius();
		void SetToZero();
	};
}
