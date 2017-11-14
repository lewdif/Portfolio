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
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&transMat);
		D3DXMatrixIdentity(&scaleMat);
		D3DXMatrixIdentity(&rotationMat);

		SetComponentName("SkinnedMesh");
		animationLoop = true;
	}

	SkinnedMesh::~SkinnedMesh()
	{
	}

	void SkinnedMesh::Render(GameObject* object)
	{
		updateMatrices((Bone*)rootBone, nullptr);

		softwareRender(nullptr, object);
	}

	void SkinnedMesh::Load(string fileName)
	{
		// .x ���Ϸκ��� �� ���� ������ �ε��Ѵ�.
		D3DXLoadMeshHierarchyFromX(fileName.c_str(), D3DXMESH_MANAGED, DeviceMgr->GetDevice(),
			&boneHierarchy, nullptr, &rootBone, &animationController);
		// ��� ���� ��ȯ ��ĵ��� ������Ʈ �Ѵ�.
		updateMatrices((Bone *)rootBone, nullptr);
		setupBoneMatrixPointers(nullptr);
		GetAnimationSets();
	}

	void SkinnedMesh::softwareRender(Bone* bone, GameObject* object)
	{
		if (bone == nullptr)
			bone = (Bone *)rootBone;

		// �������� �޽ð� �����Ѵٸ�
		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh *)bone->pMeshContainer;

			if (boneMesh->pSkinInfo != nullptr)
			{
				// ��ũ�� ������ ��ȯ ����� �����Ѵ�. 
				// ��, ���� ���յ� ��ȯ ��İ� ������ ����� �����Ͽ� ���� ��ȯ ����� �����.
				int numBones = boneMesh->pSkinInfo->GetNumBones();

				for (int i = 0; i < numBones; i++)
					D3DXMatrixMultiply(&boneMesh->currentBoneMatrices[i], &boneMesh->boneOffsetMatrices[i], boneMesh->boneMatrixPtrs[i]);

				// ��Ų�� �޽ø� �����Ѵ�.
				void *src = nullptr, *dest = nullptr;
				boneMesh->OriginalMesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&src);
				boneMesh->MeshData.pMesh->LockVertexBuffer(0, (VOID**)&dest);

				boneMesh->pSkinInfo->UpdateSkinnedMesh(boneMesh->currentBoneMatrices, nullptr, src, dest);

				boneMesh->MeshData.pMesh->UnlockVertexBuffer();
				boneMesh->OriginalMesh->UnlockVertexBuffer();

				// scale rotation translation
				Matrix matWorld, matWorldIT;
				matWorld = ((Transform3D*)object->transform3D)->GetTransform();
				D3DXMatrixInverse(&matWorldIT, NULL, &matWorld);
				D3DXMatrixTranspose(&matWorldIT, &matWorldIT);

				// �޽ø� �������Ѵ�.
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
		
		// ������ : ���̾������� �������
		// DeviceMgr->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		// ����, �ڽ� ���鿡 ���ؼ��� �������Ѵ�.
		if (bone->pFrameSibling != nullptr)
			softwareRender((Bone *)bone->pFrameSibling, object);

		if (bone->pFrameFirstChild != nullptr)
			softwareRender((Bone *)bone->pFrameFirstChild, object);
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

		// ������ ����� ���� ���� ���� �����Ѵ�.
		if (bone->pFrameSibling)
		{
			updateMatrices((Bone *)bone->pFrameSibling, parentMatrix);
		}

		// ������ ����� �ڽ� ���� ���� �����Ѵ�.
		if (bone->pFrameFirstChild)
		{
			// ���� ���� ������ �θ� ��İ� �ٸ� ����� �����ϴ� �Ϳ� ����!
			updateMatrices((Bone *)bone->pFrameFirstChild, &bone->CombinedTransformationMatrix);
		}
	}

	void SkinnedMesh::setupBoneMatrixPointers(Bone *bone)
	{
		if (bone == nullptr)
			bone = (Bone*)rootBone;

		// �޽ø� �����ϰ� �ִ� ��� ������ ã�´�.
		if (bone->pMeshContainer != nullptr)
		{
			BoneMesh *boneMesh = (BoneMesh *)bone->pMeshContainer;

			// ��Ų�� �޽ø� ���� ���鿡 ����, ��� �����͸� �����Ѵ�.
			if (boneMesh->pSkinInfo != nullptr)
			{
				// �� �޽ÿ� ��ũ�� ������ ���� ��´�.
				int NumBones = boneMesh->pSkinInfo->GetNumBones();

				// ���� ����ŭ�� ������ �迭�� �����.
				boneMesh->boneMatrixPtrs = new D3DXMATRIX*[NumBones];

				// �迭�� ä���.
				for (int i = 0; i < NumBones; i++)
				{
					// ��ũ�� ���� �̸����� ã�´�.
					Bone *b = (Bone *)D3DXFrameFind(rootBone,
						boneMesh->pSkinInfo->GetBoneName(i));
					// �׸��� �� ���� ���յ� ��ȯ ����� �����͸� �迭�� �����Ѵ�.
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

		// ���� ������ �������� �ȴ´�.
		if (bone->pFrameSibling != nullptr)
			setupBoneMatrixPointers((Bone *)bone->pFrameSibling);

		if (bone->pFrameFirstChild != nullptr)
			setupBoneMatrixPointers((Bone *)bone->pFrameFirstChild);
	}
}