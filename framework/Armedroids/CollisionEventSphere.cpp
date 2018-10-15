#include "CollisionEventSphere.h"
#include "DeviceManager.h"

namespace CompEngine
{
	CollisionEventSphere::CollisionEventSphere()
	{
		SetComponentName("CollisionEventSphere");
	}


	CollisionEventSphere::~CollisionEventSphere()
	{
	}

	void CollisionEventSphere::Init(Vec3 pos, float radius)
	{
		shapePos = pos;
		shapeRadius = radius;
	}

	void CollisionEventSphere::Update(Vec3 pos)
	{
		shapePos = pos;
	}

	void CollisionEventSphere::Render(Matrix trans, D3DXCOLOR color)
	{
		DeviceMgr->DrawSphere(trans, shapeRadius, color);
	}

	bool CollisionEventSphere::Collide(CollisionEventSphere* colShape)
	{
		float length = D3DXVec3Length(&(shapePos - (colShape->GetShapePos())));
		
		if (length < shapeRadius + colShape->GetShapeRadius())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Vec3 CollisionEventSphere::GetShapePos()
	{
		return shapePos;
	}

	float CollisionEventSphere::GetShapeRadius()
	{
		return shapeRadius;
	}

	void CollisionEventSphere::SetToZero()
	{
		shapePos = Vec3(0, 0, 0);
	}
}