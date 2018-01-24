#pragma once
#include "headers.h"

namespace CompEngine
{
	struct Bone : public D3DXFRAME
	{
		D3DXMATRIX CombinedTransformationMatrix;
	};

	struct BoneMesh : public D3DXMESHCONTAINER
	{
		ID3DXMesh* OriginalMesh;               // 스키닝 계산에 사용될 참조 메시
		vector<D3DMATERIAL9> materials;        // 재질 목록
		vector<IDirect3DTexture9 *> textures;  // 텍스처 목록

		DWORD NumAttributeGroups;              // 속성 그룹의 수
		D3DXATTRIBUTERANGE* attributeTable;    // 속성 테이블
		D3DXMATRIX** boneMatrixPtrs;           // 본 변환 행렬들의 포인터
		D3DXMATRIX* boneOffsetMatrices;        // 본 오프셋 행렬들
		D3DXMATRIX* currentBoneMatrices;       // 본들의 합산된 변환 행렬들
	};

	class BoneHierarchyLoader : public ID3DXAllocateHierarchy
	{
	public:
		BoneHierarchyLoader();
		~BoneHierarchyLoader();


	public:
		STDMETHOD(CreateFrame)(THIS_ LPCTSTR Name, LPD3DXFRAME *ppNewFrame);
		STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR Name,
			CONST D3DXMESHDATA *pMeshData,
			CONST D3DXMATERIAL *pMaterials,
			CONST D3DXEFFECTINSTANCE *pEffectInstances,
			DWORD NumMaterials,
			CONST DWORD *pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER *ppNewMeshContainer);
		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
	};
}