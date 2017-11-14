#include "InGame.h"
#include "DeviceManager.h"
#include "TimeManager.h"

namespace CompEngine
{
	InGame::InGame()
		:camera(nullptr), player(nullptr)
	{
	}

	InGame::~InGame()
	{
	}

	void InGame::Init()
	{
		initObjects();
		initMatrix();
	}

	void InGame::Update()
	{

	}

	void InGame::Render()
	{
		if (NULL == DeviceMgr->GetDevice()) { return; }

		DeviceMgr->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

		if (SUCCEEDED(DeviceMgr->GetDevice()->BeginScene()))
		{
			lucy->Render();

			DeviceMgr->GetDevice()->EndScene();
		}

		// Present the backbuffer contents to the display
		DeviceMgr->GetDevice()->Present(NULL, NULL, NULL, NULL);
	}

	void InGame::Release()
	{
		S_DEL(camera);
		S_DEL(lucy);
		S_DEL(player);
	}

	void InGame::Destroy(GameObject* gameObject)
	{
		for (auto Iter = objectList.begin(); Iter != objectList.end(); Iter++)
		{
			if (gameObject == (*Iter))
			{
				objectList.remove(gameObject);
				break;
			}
		}

		delete gameObject;
	}

	void InGame::initObjects()
	{
		camera = new Camera;
		player = new GameObject;
		lucy = new Lucy;
	}

	void InGame::initMatrix()
	{
		D3DXMATRIXA16	g_matView;
		D3DXMATRIXA16	g_matProj;

		// 월드 행렬 설정
		//D3DXMatrixIdentity(&g_matWorld);
		DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &DeviceMgr->GetWorldMat());

		// 뷰 행렬을 설정
		D3DXVECTOR3 vEyePt(0.0f, 150.0f, -150.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 10.0f, 0.0f);
		D3DXMatrixLookAtLH(&g_matView, &vEyePt, &vLookatPt, &vUpVec);
		DeviceMgr->GetDevice()->SetTransform(D3DTS_VIEW, &g_matView);

		// 실제 프로젝션 행렬
		D3DXMatrixPerspectiveFovLH(&g_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
		DeviceMgr->GetDevice()->SetTransform(D3DTS_PROJECTION, &g_matProj);

		// 카메라 초기화
		camera->SetView(&vEyePt, &vLookatPt, &vUpVec);
	}
}