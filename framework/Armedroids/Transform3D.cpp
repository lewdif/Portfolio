#include "Transform3D.h"


namespace CompEngine
{
	Transform3D::Transform3D()
		:position(Vec3(0, 0, 0)), rotAngle(Quater(0, 0, 0, 1)), scale(Vec3(1, 1, 1)),
		forward(Vec3(0, 0, -1)), up(Vec3(0, 1, 0)), parent(nullptr), combineMatrix(nullptr)
	{
		D3DXMatrixIdentity(&transform);
		D3DXMatrixIdentity(&scaleTransform);
		D3DXMatrixIdentity(&rotationTransform);
		D3DXMatrixIdentity(&translationTransform);

		SetComponentName("Transform3D");
	}

	Transform3D::~Transform3D()
	{
	}

	void Transform3D::SetForward(float x, float y, float z)
	{
		if (forward == nullptr)
		{
			cout << "forward equals nullptr!" << endl << "Initialized by (0, 0, -1)" << endl;
			forward = Vec3(0, 0, -1);
		}

		forward.x = x;
		forward.y = y;
		forward.z = z;

		D3DXVec3Normalize(&forward, &forward);
	}

	void Transform3D::SetForward(Vec3 forward)
	{
		this->forward = forward;
		D3DXVec3Normalize(&this->forward, &this->forward);
	}

	void Transform3D::SetPosition(float x, float y, float z)
	{
		if (position == nullptr)
		{
			cout << "position equals nullptr!" << endl << "Initialized by (0, 0, 0)" << endl;
			position = Vec3(0, 0, 0);
		}

		position.x = x;
		position.y = y;
		position.z = z;
	}

	void Transform3D::SetPosition(Vec3 pos)
	{
		this->position = pos;
	}

	void Transform3D::Scale(float x, float y, float z)
	{
		scale.x += x;
		scale.y += y;
		scale.z += z;
	}

	void Transform3D::SetScale(float x, float y, float z)
	{
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}

	void Transform3D::Scale(Vec3 scale)
	{
		this->scale.x += scale.x;
		this->scale.y += scale.y;
		this->scale.z += scale.z;
	}

	void Transform3D::SetScale(Vec3 scale)
	{
		this->scale = scale;
	}

	void Transform3D::Rotate(float x, float y, float z)
	{
		Quater quater;
		D3DXQuaternionRotationYawPitchRoll(&quater, y, x, z);

		D3DXQuaternionMultiply(&rotAngle, &rotAngle, &quater);
	}

	void Transform3D::SetRotation(float x, float y, float z)
	{
		Quater quater;
		D3DXQuaternionRotationYawPitchRoll(&quater, y, x, z);

		rotAngle = quater;
	}

	void Transform3D::Rotate(Quater rotAngle)
	{
		D3DXQuaternionMultiply(&this->rotAngle, &this->rotAngle, &rotAngle);
	}

	void Transform3D::SetRotation(Quater rotAngle)
	{
		this->rotAngle = rotAngle;
	}

	void Transform3D::Translate(float x, float y, float z)
	{
		position.x += x;
		position.y += y;
		position.z += z;
	}

	void Transform3D::Translate(Vec3 pos)
	{
		position += pos;
	}

	Vec3 Transform3D::GetForward()
	{
		Vec3 thisForward = forward;

		D3DXVec3TransformNormal(&thisForward, &thisForward, &transform);
		D3DXVec3Normalize(&thisForward, &thisForward);

		return thisForward;
	}

	Vec3 Transform3D::GetLeft()
	{
		Vec3 left;
		Vec3 thisForward = forward;
		Vec3 thisUp = up;

		D3DXVec3TransformNormal(&thisUp, &thisUp, &transform);
		D3DXVec3Normalize(&thisUp, &thisUp);

		D3DXVec3TransformNormal(&thisForward, &thisForward, &transform);
		D3DXVec3Normalize(&thisForward, &thisForward);

		D3DXVec3Cross(&left, &thisForward, &thisUp);	// 벡터의 외적을 계산하여 Left에 넣어줌
		D3DXVec3Normalize(&left, &left);

		return left;
	}

	Vec3 Transform3D::GetPosition()
	{
		Vec3 resultPos = position;

		if (combineMatrix != nullptr)
		{
			// combineMatrix 행렬의 (4, 1), (4, 2), (4, 3) => x, y, z
			resultPos.x += ((*combineMatrix)._41);
			resultPos.y += ((*combineMatrix)._42);
			resultPos.z += ((*combineMatrix)._43);
		}

		return resultPos;
	}

	Vec3 Transform3D::GetWorldPosition()
	{
		GameObject* parentPtr = parent;

		Vec3 thisPos(0, 0, 0);

		if (combineMatrix != nullptr)
		{
			thisPos.x += ((*combineMatrix)._41);
			thisPos.y += ((*combineMatrix)._42);
			thisPos.z += ((*combineMatrix)._43);
		}

		D3DXVec3TransformCoord(&thisPos, &thisPos, &GetTransform());

		return thisPos;
	}

	Vec3 Transform3D::GetScale()
	{
		return scale;
	}

	Vec3 Transform3D::GetWolrdScale()
	{
		GameObject* parentPtr = parent;

		Vec3 thisScale = scale;

		while (parentPtr != nullptr)
		{
			thisScale.x *= ((Transform3D*)parentPtr->GetComponent("Transform3D"))->GetScale().x;
			thisScale.y *= ((Transform3D*)parentPtr->GetComponent("Transform3D"))->GetScale().y;
			thisScale.z *= ((Transform3D*)parentPtr->GetComponent("Transform3D"))->GetScale().z;

			parentPtr = parentPtr->GetParent();
		}

		D3DXMatrixScaling(&scaleTransform, thisScale.x, thisScale.y, thisScale.z);

		return thisScale;
	}

	Vec3 Transform3D::GetRotationAngle()
	{
		float sqw = rotAngle.w * rotAngle.w;
		float sqx = rotAngle.x * rotAngle.x;
		float sqy = rotAngle.y * rotAngle.y;
		float sqz = rotAngle.z * rotAngle.z;

		float pitch = asinf(2.0f * (rotAngle.w * rotAngle.x - rotAngle.y * rotAngle.z));
		float yaw = atan2f(2.0f * (rotAngle.x * rotAngle.z + rotAngle.w * rotAngle.y), (-sqx - sqy + sqz + sqw));
		float roll = atan2f(2.0f * (rotAngle.x * rotAngle.y + rotAngle.w * rotAngle.z), (-sqx + sqy - sqz + sqw));

		return Vec3(pitch, yaw, roll);
	}

	Vec3 Transform3D::GetWorldRotationAngle()
	{
		GameObject* parentPtr = parent;

		Quater result = rotAngle;

		while (parentPtr != nullptr)
		{
			result *= ((Transform3D*)parentPtr->GetComponent("Transform3D"))->GetRotationQuater();

			parentPtr = parentPtr->GetParent();
		}

		float sqw = result.w * result.w;
		float sqx = result.x * result.x;
		float sqy = result.y * result.y;
		float sqz = result.z * result.z;

		float pitch = asinf(2.0f * (result.w * result.x - result.y * result.z));
		float yaw = atan2f(2.0f * (result.x * result.z + result.w * result.y), (-sqx - sqy + sqz + sqw));
		float roll = atan2f(2.0f * (result.x * result.y + result.w * result.z), (-sqx + sqy - sqz + sqw));

		return Vec3(pitch, yaw, roll);
	}

	Quater Transform3D::GetRotationQuater()
	{
		return rotAngle;
	}

	Quater Transform3D::GetWorldRotationQuater()
	{
		GameObject* parentPtr = parent;

		Quater result = rotAngle;

		while (parentPtr != nullptr)
		{
			result *= ((Transform3D*)parentPtr->GetComponent("Transform3D"))->GetRotationQuater();

			parentPtr = parentPtr->GetParent();
		}

		return result;
	}

	void Transform3D::AttachObject(GameObject* parent)
	{
		this->parent = parent;
	}

	Matrix Transform3D::GetTransform()
	{
		GameObject* parentPtr = parent;

		Vec3 Scale = scale;
		Vec3 Posit = position;
		Quater RotAngle = rotAngle;

		D3DXMatrixRotationQuaternion(&rotationTransform, &RotAngle);
		D3DXMatrixTranslation(&translationTransform, Posit.x, Posit.y, Posit.z);
		D3DXMatrixScaling(&scaleTransform, Scale.x, Scale.y, Scale.z);

		transform = scaleTransform * rotationTransform * translationTransform;

		if (combineMatrix != nullptr)
		{
			Matrix mat;

			transform *= *combineMatrix;
		}

		while (parentPtr != nullptr)
		{
			transform *= ((Transform3D*)parentPtr->transform3D)->GetTransform();

			parentPtr = parentPtr->GetParent();
		}

		return transform;
	}

	void Transform3D::CombineMatrix(Matrix* matrix)
	{
		combineMatrix = matrix;
	}
}