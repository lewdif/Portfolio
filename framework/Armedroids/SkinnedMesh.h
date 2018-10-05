#pragma once
#include "headers.h"
#include "Component.h"
#include "SceneManager.h"
#include "BoneHierarchyLoader.h"

namespace CompEngine
{
	typedef struct _KEYFRAMERATE {
		LPD3DXANIMATIONSET AnimationSet;
		UINT VertexIndex;
		float AnimationSpeed;
		bool IsPlay;
	} KEYFRAMERATE;

	class SkinnedMesh : public Component
	{
	public:
		SkinnedMesh();
		~SkinnedMesh();

		void AttachObject(GameObject* owner);

		void LoadMeshFromX(string fileName);
		void Render(GameObject* object);
		void UpdateAnimation();

		void SetAnimationLoop(bool loop);
		bool GetAnimationLoop();

		void GetAnimationSets();
		void SetAnimation(string name);

		map<string, int> GetAnmimationSet();
		string GetCurrentAnimation();

		D3DXMATRIX* GetBoneMatrix(string name, Bone* bone = NULL, D3DXMATRIX* mat = NULL);

		void ResetTime();
		double GetAnimationRate();

		bool IsRayHit(RAY *ray, Bone* bone, float& curDist);

	private:
		void updateMatrices(Bone* bone, D3DXMATRIX* parentMatrix);
		void softwareRender(Bone* bone, GameObject* object);

		void setupBoneMatrixPointers(Bone* bone);

	private:
		D3DXFRAME* rootBone;

		bool animationLoop;

		LPD3DXANIMATIONCONTROLLER animationController;
		BoneHierarchyLoader boneHierarchy;

		map<string, int> animationSets;
		string curAnimation;
	};
}