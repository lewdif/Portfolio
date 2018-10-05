#include "Transform2D.h"
#include "DeviceManager.h"

namespace CompEngine
{
	Transform2D::Transform2D()
		: parent(nullptr), position(Vec3(DeviceMgr->GetWidth() / 2, DeviceMgr->GetHeight() / 2, 0)),
		scale(Vec2(1, 1)), pivot(Vec2(0.5f, 0.5f)), size(Vec2(10, 10)), rotation(0)
	{
		D3DXMatrixIdentity(&transformMat);
		SetComponentName("Transform2D");
	}

	Transform2D::~Transform2D()
	{
	}

	void Transform2D::SetScale(Vec2 _scale)
	{
		scale = _scale;
	}

	void Transform2D::SetScale(float _x, float _y)
	{
		scale.x = _x;
		scale.y = _y;
	}

	void Transform2D::SetRotate(float _rotation)
	{
		rotation = _rotation;
	}

	void Transform2D::SetPosition(Vec3 pos)
	{
		position = pos;
	}

	void Transform2D::SetPosition(float _x, float _y, float _z)
	{
		position.x = _x;
		position.y = _y;
		position.z = _z;
	}

	void Transform2D::SetPivot(Vec2 _pivot)
	{
		this->pivot = _pivot;
	}

	void Transform2D::SetPivot(float _x, float _y)
	{
		pivot.x = _x;
		pivot.y = _y;
	}

	void Transform2D::SetSize(float width, float height)
	{
		size.x = width;
		size.y = height;
	}

	void Transform2D::Scale(Vec2 _scale)
	{
		scale += _scale;
	}

	void Transform2D::Scale(float _x, float _y)
	{
		scale.x += _x;
		scale.y += _y;
	}

	void Transform2D::Rotate(float _rotation)
	{
		rotation += _rotation;
	}

	void Transform2D::Translate(Vec3 _position)
	{
		position += _position;
	}

	void Transform2D::Translate(float _x, float _y, float _z)
	{
		position.x += _x;
		position.y += _y;
		position.z += _z;
	}

	Vec3 Transform2D::GetPosition()
	{
		return position;
	}

	Vec2 Transform2D::GetScale()
	{
		return scale;
	}

	float Transform2D::GetRotateAngle()
	{
		return rotation;
	}

	Vec2 Transform2D::GetPivot()
	{
		return pivot;
	}

	Vec2 Transform2D::GetSize()
	{
		return size;
	}

	Matrix Transform2D::GetTransformMatrix()
	{
		D3DXMatrixIdentity(&transformMat);
		D3DXMatrixTransformation2D(&transformMat, &pivot, 0, &scale, &pivot, rotation, &Vec2(position.x, position.y));

		return transformMat;
	}

	void Transform2D::AddParent(GameObject* parent)
	{
		this->parent = parent;
	}
}