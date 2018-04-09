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

	void SkinnedMesh::SetAnimation(std::string name)
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

	D3DXMATRIX* SkinnedMesh::GetBoneMatrix(std::string name, Bone* bone, D3DXMATRIX* mat)
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

		//cout << "result : " << deltaTime << endl;

		if (result >= 0.99f && animationLoop == false)
		{
			result = 1.0f;
			animationController->SetTrackPosition(0, pAnim->GetPeriod());
		}

		return result;
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

		// 동일한 계산을 형제 본에 대해 수행한다.
		if (bone->pFrameSibling)
		{
			updateMatrices((Bone *)bone->pFrameSibling, parentMatrix);
		}

		// 동일한 계산을 자식 본에 대해 수행한다.
		if (bone->pFrameFirstChild)
		{
			// 형제 본에 전달한 부모 행렬과 다른 행렬을 전달하는 것에 주의!
			updateMatrices((Bone *)bone->pFrameFirstChild, &bone->CombinedTransformationMatrix);
		}
	}

	void SkinnedMesh::softwareRender(Bone* bone, GameObject* object)
	{
		if (bone == nullptr)
			bone = (Bone *)rootBone;

		// 렌더링할 메시가 존재한다면
		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh *)bone->pMeshContainer;

			if (boneMesh->pSkinInfo != nullptr)
			{
				// 링크된 본들의 변환 행렬을 설정한다. 
				// 즉, 본의 결합된 변환 행렬과 오프셋 행렬을 결합하여 최종 변환 행렬을 만든다.
				int numBones = boneMesh->pSkinInfo->GetNumBones();

				for (int i = 0; i < numBones; i++)
					D3DXMatrixMultiply(&boneMesh->currentBoneMatrices[i], &boneMesh->boneOffsetMatrices[i], boneMesh->boneMatrixPtrs[i]);

				// 스킨드 메시를 갱신한다.
				void *src = nullptr, *dest = nullptr;
				boneMesh->OriginalMesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&src);
				boneMesh->MeshData.pMesh->LockVertexBuffer(0, (VOID**)&dest);

				boneMesh->pSkinInfo->UpdateSkinnedMesh(boneMesh->currentBoneMatrices, nullptr, src, dest);

				boneMesh->MeshData.pMesh->UnlockVertexBuffer();
				boneMesh->OriginalMesh->UnlockVertexBuffer();

				// scale rotation translation
				Matrix matWorld, matWorldIT;
				matWorld = GET_TRANSFORM_3D(object)->GetTransform();

				D3DXMatrixInverse(&matWorldIT, NULL, &matWorld);
				D3DXMatrixTranspose(&matWorldIT, &matWorldIT);
				DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

				// 메시를 렌더링한다.
				for (int i = 0; i < boneMesh->NumAttributeGroups; i++)
				{
					int mtrl = boneMesh->attributeTable[i].AttribId;
					DeviceMgr->GetDevice()->SetMaterial(&(boneMesh->materials[mtrl]));
					DeviceMgr->GetDevice()->SetTexture(0, boneMesh->textures[mtrl]);
					//cout << "mesh loading" << endl;
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