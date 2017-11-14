#pragma once
#include "headers.h"
#include "Component.h"
#include "SceneManager.h"
#include "BoneHierarchyLoader.h"

namespace CompEngine
{
	typedef struct _KEYFRAMERATE {
		LPD3DXANIMATIONSET AnimationSet;
		UINT Vertex_Index;
		float AnimationSpeed;
		bool IsPlay;
	} KEYFRAMERATE;

	class SkinnedMesh : public Component
	{
	public:
		SkinnedMesh();
		~SkinnedMesh();

		//void LoadContent();

		void Render(GameObject* object);

		void Load(string fileName);

		void UpdateAnimation();

		void SetAnimationLoop(bool loop);
		bool GetAnimationLoop();

		void GetAnimationSets();
		void SetAnimation(std::string name);

		map<string, int> GetAnmimationSet();
		string GetCurrentAnimation();

		D3DXMATRIX* GetBoneMatrix(string name, Bone* bone = NULL, D3DXMATRIX* mat = NULL);

		void ResetTime();
		double GetAnimationRate();


	private:
		void softwareRender(Bone* bone, GameObject* object);
		void updateMatrices(Bone* bone, D3DXMATRIX* parentMatrix);
		void setupBoneMatrixPointers(Bone* bone);

	private:
		LPD3DXANIMATIONCONTROLLER animationController;
		BoneHierarchyLoader boneHierarchy;

		D3DXFRAME* rootBone;

		D3DXMATRIX matWorld;
		D3DXMATRIX transMat;
		D3DXMATRIX scaleMat;
		D3DXMATRIX rotationMat;

		map<string, int> animationSets;
		string curAnimation;

		bool animationLoop;
	};
}