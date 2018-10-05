#include "SkinnedMesh.h"
#include "DeviceManager.h"
#include "SceneManager.h"
#include "BoneHierarchyLoader.h"
#include "Transform3D.h"
#include "GameObject.h"

namespace CompEngine
{
	SkinnedMesh::SkinnedMesh()
	{
		SetComponentName("SkinnedMesh");
		animationLoop = true;
	}

	SkinnedMesh::~SkinnedMesh()
	{
	}

	void SkinnedMesh::LoadMeshFromX(string fileName)
	{
		D3DXLoadMeshHierarchyFromX(fileName.c_str(), D3DXMESH_MANAGED, DeviceMgr->GetDevice(),
			&boneHierarchy, nullptr, &rootBone, &animationController);

		updateMatrices((Bone *)rootBone, nullptr);
		setupBoneMatrixPointers(nullptr);
		GetAnimationSets();

		cout << "Mesh is loaded : " + fileName << endl;
	}

	void SkinnedMesh::Render(GameObject* object)
	{
		updateMatrices((Bone*)rootBone, nullptr);

		// scale rotation translation
		Matrix matWorld;
		//Matrix matWorldIT;
		matWorld = GET_TRANSFORM_3D(object)->GetTransform();

		//D3DXMatrixInverse(&matWorldIT, NULL, &matWorld);
		//D3DXMatrixTranspose(&matWorldIT, &matWorldIT);
		DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

		softwareRender(nullptr, object);
	}

	void SkinnedMesh::UpdateAnimation()
	{
		if (GetAnimationRate() < 0.99f || animationLoop)
		{
			animationController->AdvanceTime(
				SceneMgr->GetTimeDelta(),
				nullptr
			);
		}
	}

	void SkinnedMesh::SetAnimationLoop(bool loop)
	{
		animationLoop = loop;
	}

	bool SkinnedMesh::GetAnimationLoop()
	{
		return animationLoop;
	}

	void SkinnedMesh::GetAnimationSets() {
		ID3DXAnimationSet* pAnim = nullptr;

		for (int i = 0; i < (int)animationController->GetMaxNumAnimationSets(); i++)
		{
			pAnim = nullptr;
			animationController->GetAnimationSet(i, &pAnim);

			//If we found an animation set, add it to the map
			if (pAnim != nullptr)
			{
				string name = pAnim->GetName();
				animationSets[name] = i;//Creates an entry
				pAnim->Release();
			}
		}

		SetAnimation(animationSets.begin()->first);
	}

	void SkinnedMesh::SetAnimation(string name)
	{
		if (name == curAnimation)
			return;

		ID3DXAnimationSet* pAnim = nullptr;
		animationController->GetAnimationSet(animationSets[name], &pAnim);
		//cout << name << endl;
		//cout << pAnim->GetName() << endl;

		if (pAnim != nullptr)
		{
			animationController->ResetTime();
			animationController->SetTrackAnimationSet(0, pAnim);
			curAnimation = pAnim->GetName();
			pAnim->Release();
		}
	}

	map<string, int> SkinnedMesh::GetAnmimationSet()
	{
		return animationSets;
	}

	string SkinnedMesh::GetCurrentAnimation()
	{
		return curAnimation;
	}

	D3DXMATRIX* SkinnedMesh::GetBoneMatrix(string name, Bone* bone, D3DXMATRIX* mat)
	{
		static D3DXMATRIX* result = nullptr;

		if (bone == nullptr)
			bone = (Bone*)rootBone;

		if (mat == nullptr)
			bone->CombinedTransformationMatrix = bone->TransformationMatrix;
		else
		{
			D3DXMatrixMultiply(&bone->CombinedTransformationMatrix,
				&bone->TransformationMatrix,
				mat
			);
		}

		if (name == bone->Name)
		{
			return result = &(bone->CombinedTransformationMatrix);
		}

		if (bone->pFrameSibling != nullptr)
			GetBoneMatrix(name, (Bone*)bone->pFrameSibling, &bone->CombinedTransformationMatrix);

		if (bone->pFrameFirstChild != nullptr)
			GetBoneMatrix(name, (Bone*)bone->pFrameFirstChild, &bone->CombinedTransformationMatrix);

		return result;
	}

	void SkinnedMesh::ResetTime()
	{
		animationController->ResetTime();
	}

	double SkinnedMesh::GetAnimationRate()
	{
		ID3DXAnimationSet* pAnim = nullptr;
		// Get the animation set from the name.
		animationController->GetAnimationSet(animationSets[curAnimation], &pAnim);

		D3DXTRACK_DESC Track;
		animationController->GetTrackDesc(0, &Track);

		double result = Track.Position / pAnim->GetPeriod();

		if (result >= 0.99f && animationLoop == false)
		{
			result = 1.0f;
			animationController->SetTrackPosition(0, pAnim->GetPeriod());
		}

		return result;
	}

	bool SkinnedMesh::IsRayHit(RAY* ray, Bone* bone, float& curDist)
	{
		if (bone == nullptr)
			bone = (Bone*)rootBone;

		static bool exist = false;
		/*
		float Temp = -1;

		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh*)bone->pMeshContainer;

			if (boneMesh->pSkinInfo != nullptr)
			{
				int numBones = boneMesh->pSkinInfo->GetNumBones();

				for (int i = 0; i < numBones; i++)
					D3DXMatrixMultiply(&boneMesh->currentBoneMatrices[i], &boneMesh->boneOffsetMatrices[i], boneMesh->boneMatrixPtrs[i]);

				void* *src = nullptr, *dest = nullptr;

				boneMesh->OriginalMesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&src);
				boneMesh->MeshData.pMesh->LockVertexBuffer(0, (VOID**)&dest);

				boneMesh->pSkinInfo->UpdateSkinnedMesh(boneMesh->currentBoneMatrices, nullptr, src, dest);

				boneMesh->MeshData.pMesh->UnlockVertexBuffer();
				boneMesh->OriginalMesh->UnlockVertexBuffer();

				for (UINT i = 0; i < boneMesh->NumAttributeGroups; i++)
				{
					Matrix matIden;
					D3DXMatrixIdentity(&matIden);
					if (DeviceMgr->IsRayInMesh(matIden, boneMesh->MeshData.pMesh, &Temp))
						if (Temp <= curDist)
						{
							exist = true;
							curDist = Temp;
						}
				}
			}
		}

		if (bone->pFrameSibling != nullptr)
			IsRayHit(ray, (Bone*)bone->pFrameSibling, curDist);

		if (bone->pFrameFirstChild != nullptr)
			IsRayHit(ray, (Bone*)bone->pFrameFirstChild, curDist);
			*/
		return exist;
	}

	void SkinnedMesh::updateMatrices(Bone* bone, D3DXMATRIX *parentMatrix)
	{
		if (bone == nullptr)
			return;

		if (parentMatrix == nullptr)
			bone->CombinedTransformationMatrix = bone->TransformationMatrix;
		else
		{
			D3DXMatrixMultiply(&bone->CombinedTransformationMatrix,
				&bone->TransformationMatrix,
				parentMatrix
			);
		}

		if (bone->pFrameSibling)
		{
			updateMatrices((Bone *)bone->pFrameSibling, parentMatrix);
		}

		if (bone->pFrameFirstChild)
		{
			updateMatrices((Bone *)bone->pFrameFirstChild, &bone->CombinedTransformationMatrix);
		}
	}

	void SkinnedMesh::softwareRender(Bone* bone, GameObject* object)
	{
		if (bone == nullptr)
			bone = (Bone *)rootBone;

		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh *)bone->pMeshContainer;

			if (boneMesh->pSkinInfo != nullptr)
			{
				int numBones = boneMesh->pSkinInfo->GetNumBones();

				for (int i = 0; i < numBones; i++)
					D3DXMatrixMultiply(&boneMesh->currentBoneMatrices[i], &boneMesh->boneOffsetMatrices[i], boneMesh->boneMatrixPtrs[i]);

				void *src = nullptr, *dest = nullptr;
				boneMesh->OriginalMesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&src);
				boneMesh->MeshData.pMesh->LockVertexBuffer(0, (VOID**)&dest);

				boneMesh->pSkinInfo->UpdateSkinnedMesh(boneMesh->currentBoneMatrices, nullptr, src, dest);

				boneMesh->MeshData.pMesh->UnlockVertexBuffer();
				boneMesh->OriginalMesh->UnlockVertexBuffer();

				for (int i = 0; i < boneMesh->NumAttributeGroups; i++)
				{
					int mtrl = boneMesh->attributeTable[i].AttribId;
					DeviceMgr->GetDevice()->SetMaterial(&(boneMesh->materials[mtrl]));
					DeviceMgr->GetDevice()->SetTexture(0, boneMesh->textures[mtrl]);
					boneMesh->MeshData.pMesh->DrawSubset(mtrl);
				}
			}
		}

		// 디버깅용 : 와이어프레임 렌더모드
		// DeviceMgr->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		if (bone->pFrameSibling != nullptr)
			softwareRender((Bone *)bone->pFrameSibling, object);

		if (bone->pFrameFirstChild != nullptr)
			softwareRender((Bone *)bone->pFrameFirstChild, object);
	}
	
	void SkinnedMesh::setupBoneMatrixPointers(Bone *bone)
	{
		if (bone == nullptr) { bone = (Bone*)rootBone; }

		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh *)bone->pMeshContainer;

			if (boneMesh->pSkinInfo != nullptr)
			{
				int NumBones = boneMesh->pSkinInfo->GetNumBones();

				boneMesh->boneMatrixPtrs = new D3DXMATRIX*[NumBones];

				for (int i = 0; i < NumBones; i++)
				{
					Bone *b = (Bone *)D3DXFrameFind(rootBone, boneMesh->pSkinInfo->GetBoneName(i));
					
					if (b != nullptr)
					{
						boneMesh->boneMatrixPtrs[i] = &b->CombinedTransformationMatrix;
					}
					else
					{
						boneMesh->boneMatrixPtrs[i] = nullptr;
					}
				}
			}
		}

		if (bone->pFrameSibling != nullptr)
			setupBoneMatrixPointers((Bone *)bone->pFrameSibling);

		if (bone->pFrameFirstChild != nullptr)
			setupBoneMatrixPointers((Bone *)bone->pFrameFirstChild);
	}
}