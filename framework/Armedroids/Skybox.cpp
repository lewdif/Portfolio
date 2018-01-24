#include "Skybox.h"
#include"DeviceManager.h"
#include "Transform3D.h"
#include "Vertex.h"


namespace CompEngine
{
	Skybox::Skybox()
		:isInit(false), filePath(""), fileName("")
	{
	}

	void Skybox::SetFilePath(string path, string name)
	{
		filePath = path;
		fileName = name;
	}

	bool Skybox::SetSkybox(string path, string name, string fileType)
	{
		char TextureAddress[6][100] = { {} };

		for (int i = 0; i < 6; i++)
		{
			strcpy_s(TextureAddress[i], path.c_str());
			strcat_s(TextureAddress[i], "\\");
			strcat_s(TextureAddress[i], name.c_str());
		}

		strcat_s(TextureAddress[0], "_up.");
		strcat_s(TextureAddress[0], fileType.c_str());

		strcat_s(TextureAddress[1], "_down.");
		strcat_s(TextureAddress[1], fileType.c_str());

		strcat_s(TextureAddress[2], "_right.");
		strcat_s(TextureAddress[2], fileType.c_str());

		strcat_s(TextureAddress[3], "_left.");
		strcat_s(TextureAddress[3], fileType.c_str());

		strcat_s(TextureAddress[4], "_front.");
		strcat_s(TextureAddress[4], fileType.c_str());

		strcat_s(TextureAddress[5], "_back.");
		strcat_s(TextureAddress[5], fileType.c_str());

		// - texture UV���� �����غ��� ���� 24���� �ʿ��ϴ�.
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[0], &meshTextures[0])))
			meshTextures[0] = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[1], &meshTextures[1])))
			meshTextures[1] = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[2], &meshTextures[2])))
			meshTextures[2] = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[3], &meshTextures[3])))
			meshTextures[3] = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[4], &meshTextures[4])))
			meshTextures[4] = nullptr;
		if (FAILED(D3DXCreateTextureFromFile(DeviceMgr->GetDevice(), TextureAddress[5], &meshTextures[5])))
			meshTextures[5] = nullptr;

		VERTEX* pv;

		for (int i = 0; i<6; i++)
			if (FAILED(DeviceMgr->GetDevice()->CreateVertexBuffer(sizeof(VERTEX) * 4, 0,
				VERTEX::FVF, D3DPOOL_DEFAULT, &VtxBufr[i], nullptr))) return false;

		//top
		if (FAILED(VtxBufr[0]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		Set3DTexture(pv[1], D3DXVECTOR3(-1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[2], D3DXVECTOR3(1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		Set3DTexture(pv[3], D3DXVECTOR3(-1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		VtxBufr[0]->Unlock();
		
		//bottom
		if (FAILED(VtxBufr[1]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		Set3DTexture(pv[1], D3DXVECTOR3(-1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		Set3DTexture(pv[2], D3DXVECTOR3(1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[3], D3DXVECTOR3(-1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		VtxBufr[1]->Unlock();

		//left
		if (FAILED(VtxBufr[2]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(-1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[1], D3DXVECTOR3(-1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		Set3DTexture(pv[2], D3DXVECTOR3(-1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		Set3DTexture(pv[3], D3DXVECTOR3(-1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		VtxBufr[2]->Unlock();

		//right
		if (FAILED(VtxBufr[3]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[1], D3DXVECTOR3(1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		Set3DTexture(pv[2], D3DXVECTOR3(1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		Set3DTexture(pv[3], D3DXVECTOR3(1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		VtxBufr[3]->Unlock();

		//front
		if (FAILED(VtxBufr[4]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[1], D3DXVECTOR3(-1100.f, 1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		Set3DTexture(pv[2], D3DXVECTOR3(1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		Set3DTexture(pv[3], D3DXVECTOR3(-1100.f, -1100.f, 1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		VtxBufr[4]->Unlock();

		//back
		if (FAILED(VtxBufr[5]->Lock(0, 0, (void**)&pv, 0))) return false;
		Set3DTexture(pv[0], D3DXVECTOR3(-1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 0);
		Set3DTexture(pv[1], D3DXVECTOR3(1100.f, 1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 1, 0);
		Set3DTexture(pv[2], D3DXVECTOR3(-1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 0, 1);
		Set3DTexture(pv[3], D3DXVECTOR3(1100.f, -1100.f, -1100.f), D3DXVECTOR3(1, 1, 1), 1, 1);
		VtxBufr[5]->Unlock();

		for (int i = 0; i<6; i++)
			if (FAILED(DeviceMgr->GetDevice()->CreateIndexBuffer(sizeof(VERTEX_INDEX) * 12, 0,
				D3DFMT_INDEX16, D3DPOOL_DEFAULT, &IdxBufr[i], nullptr))) return false;

		//�ε��� ���� �ʱ�ȭ
		VERTEX_INDEX* iv;
		for (int i = 0; i<6; i++)
		{
			if (FAILED(IdxBufr[i]->Lock(0, 0, (void**)&iv, 0))) return false;
			SetIndex(iv[0], 0, 1, 2);
			SetIndex(iv[1], 2, 1, 3);
			IdxBufr[i]->Unlock();
		}

		for (int i = 0; i < 6; i++)
			if (!meshTextures[i])
				return false;

		isInit = true;

		return isInit;
	}

	void Skybox::Render(GameObject* cameraObject)
	{
		if (isInit)
		{
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0x08);
			DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
			DeviceMgr->GetDevice()->SetSamplerState(7, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			DeviceMgr->GetDevice()->SetSamplerState(7, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);

			// ������ ���̾������� ���
			//DeviceMgr->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			if (VtxBufr != nullptr && IdxBufr != nullptr)
			{
				//��ī�� �ڽ��� �׸��� ���� ����� �ٽ� �ʱ�ȭ ��Ŵ.
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//�ø��� ���
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z���� ����
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			//���� ����

				//��ī�� �ڽ� �̵�.
				D3DXVECTOR3 vPos = ((Transform3D*)cameraObject->GetComponent("Transform3D"))->GetPosition();
				//cout << "vPos : " << vPos.x << ", " << vPos.y << ", " << vPos.z << endl;
				//cout << cameraObject->GetName() << endl;

				D3DXMatrixIdentity(&matWrd);
				D3DXMatrixTranslation(&matWrd, vPos.x, vPos.y, vPos.z);
				DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &matWrd);
				
				//�ؽ��� UV Address�� ����.
				DeviceMgr->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
				DeviceMgr->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

				//��ī�̹ڽ� ��ο�.
				for (int i = 0; i < 6; i++)
				{
					DeviceMgr->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
					DeviceMgr->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

					DeviceMgr->GetDevice()->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
					DeviceMgr->GetDevice()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
					DeviceMgr->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, 0);
					DeviceMgr->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, 0);

					DeviceMgr->GetDevice()->SetTexture(0, (meshTextures[i]) ? meshTextures[i] : nullptr);
					DeviceMgr->GetDevice()->SetStreamSource(0, VtxBufr[i], 0, sizeof(VERTEX));
					DeviceMgr->GetDevice()->SetFVF(VERTEX::FVF);
					DeviceMgr->GetDevice()->SetIndices(IdxBufr[i]);
					DeviceMgr->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
				}

				//��� �ʱ�ȭ.
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);			//Z���� �ѱ�
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);			//���� �ѱ�
				DeviceMgr->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//�ø� �ݽð����

			}

			//DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE); // disable alpha blend
			//DeviceMgr->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); // i am not sure maybie this one needs to be disabled also
		}
	}

	void Skybox::Release()
	{
		for (int i = 0; i<6; i++)
		{
			if (meshTextures[i] != nullptr)
				meshTextures[i]->Release();

			if (VtxBufr[i] != nullptr)
				VtxBufr[i]->Release();

			if (IdxBufr[i] != nullptr)
				IdxBufr[i]->Release();
		}
	}
}