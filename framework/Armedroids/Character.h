#pragma once
#include "headers.h"
//#include "MeshManager.h"
#include "DeviceManager.h"
//#include "Vertex.h"
#include "BoneHierarchyLoader.h"
#include "SkinnedMesh.h"

namespace CompEngine
{
	struct CharInfo
	{
		D3DXVECTOR3*		position;

		SkinnedMesh*	skinnedMesh;
		D3DXMATRIXA16	localMat;
		string			xFilePath;
		string			texturePath;

		D3DXMATRIX		objMat;
		D3DXMATRIX		transform;
		D3DXMATRIX		rotateTransform;
		D3DXMATRIX		translateTransform;
		D3DXMATRIX		scaleTransform;
	};

	class Character
	{
	public:
		virtual ~Character() {}

		virtual void Release() PURE;
		virtual void Render() PURE;
		virtual void InitMembers() PURE;
	};
}
