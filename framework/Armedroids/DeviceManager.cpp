#include "DeviceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"


namespace CompEngine
{
	_RAY::_RAY()
		:origin(Vec3(0, 0, 0)), direction(Vec3(0, 0, 0))
	{
	}

	DeviceManager::DeviceManager()
	{
		isInit = false;
		D3DXMatrixIdentity(&matWorld);
	}

	DeviceManager::~DeviceManager()
	{
	}

	bool DeviceManager::InitMembers(HWND hWnd)
	{
		this->hWnd = hWnd;

		d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
		d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

		int vp = 0;

		if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
			vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
		else
			vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

		RECT ClientRect;
		GetClientRect(this->hWnd, &ClientRect);

		width = ClientRect.right;
		height = ClientRect.bottom;

		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		vp = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			this->hWnd,
			vp,
			&d3dpp,
			&D3D_DEVICE);

		font = nullptr;
		line = nullptr;

		if (vp != D3D_OK)
		{
			isInit = false;
			return 0;
		}

		/// 기본컬링, CCW
		D3D_DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		/// Z버퍼기능을 켠다.
		D3D_DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);

		/// 정점에 색깔값이 있으므로, 광원기능을 끈다.
		D3D_DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);

		isInit = true;

		return isInit;
	}

	IDirect3DDevice9* DeviceManager::GetDevice()
	{
		if (isInit)
			return D3D_DEVICE;
		else
		{
			cout << "Device doesn't exists" << endl;
			return nullptr;
		}
	}

	int DeviceManager::GetHeight()
	{
		RECT rt;
		GetClientRect(hWnd, &rt);
		height = rt.bottom;

		return height;
	}

	int DeviceManager::GetWidth()
	{
		RECT rt;
		GetClientRect(hWnd, &rt);
		width = rt.right;

		return width;
	}

	void DeviceManager::ReleaseMembers()
	{
		if (line) { line->Release(); }
		if (font) { font->Release(); }
		if (D3D_DEVICE) { D3D_DEVICE->Release(); }
		if (d3d9) { d3d9->Release(); }
	}

	D3DXMATRIXA16 DeviceManager::GetWorldMat()
	{
		return matWorld;
	}

	RAY	DeviceManager::GetPickRayToView()
	{
		POINT cursor;
		D3DVIEWPORT9 view;
		Matrix projMat;
		Camera* currentCam = (Camera*)SceneMgr->CurrentScene()->GetCurrentCamera();

		GetCursorPos(&cursor);
		ScreenToClient(hWnd, &cursor);

		D3D_DEVICE->GetViewport(&view);
		D3D_DEVICE->GetTransform(D3DTS_PROJECTION, &projMat);
		
		float vx = (+2.0f * cursor.x / view.Width - 1.0f) / projMat._11;
		float vy = (-2.0f * cursor.y / view.Height + 1.0f) / projMat._22;

		Vec3 Origin(vx, vy, 0.0f);
		Vec3 Direction(vx, vy, 1.0f);

		Matrix viewMat;
		Matrix inverseViewMat;

		D3D_DEVICE->GetTransform(D3DTS_VIEW, &viewMat);

		D3DXMatrixInverse(&inverseViewMat, 0, &viewMat);
		D3DXVec3TransformCoord(&Origin, &Origin, &inverseViewMat);
		D3DXVec3TransformNormal(&Direction, &Direction, &inverseViewMat);

		RAY ray;

		ray.origin = Origin;
		ray.direction = Direction;
		
		//DeviceMgr->DrawLine(ray.origin, ray.direction, COLOR::CYAN);

		return ray;
	}
	
	RAY DeviceManager::GetPickRayToViewOrtho()
	{
		POINT cursor;

		GetCursorPos(&cursor);
		ScreenToClient(hWnd, &cursor);

		D3DVIEWPORT9 view;
		D3D_DEVICE->GetViewport(&view);

		Matrix projMat;
		D3D_DEVICE->GetTransform(D3DTS_PROJECTION, &projMat);

		float vx = (+2.0f * cursor.x / view.Width - 1.0f) / projMat._11;
		float vy = (-2.0f * cursor.y / view.Height + 1.0f) / projMat._22;

		D3DXVECTOR3 Origin(cursor.x, cursor.y, 0.0f);
		D3DXVECTOR3 Direction(cursor.x, cursor.y, 1.0f);

		Matrix viewMat;
		D3D_DEVICE->GetTransform(D3DTS_VIEW, &viewMat);

		D3DXVECTOR3 vtemp;
		D3DXVec3Unproject(&vOrg, &Origin, &view, &projMat, &viewMat, &matWorld);
		D3DXVec3Unproject(&vtemp, &Direction, &view, &projMat, &viewMat, &matWorld);

		vDir = vtemp - vOrg;
		D3DXVec3Normalize(&vDir, &vDir);

		RAY ray;
		ray.origin = vOrg;
		ray.direction = vDir;

		//cout << vDir.x << ", " << vDir.y << ", " << vDir.z << endl;

		//DeviceMgr->DrawLine(ray.origin, ray.direction, COLOR::CYAN);
		return ray;
	}

	bool DeviceManager::IsRayInMesh(const D3DXMATRIX& matWorld, LPD3DXMESH mesh, float* dist)
	{
		POINT cursor;

		GetCursorPos(&cursor);
		ScreenToClient(hWnd, &cursor);

		D3DVIEWPORT9 view;
		D3D_DEVICE->GetViewport(&view);

		Matrix projMat;
		D3D_DEVICE->GetTransform(D3DTS_PROJECTION, &projMat);

		float vx = (+2.0f * cursor.x / view.Width - 1.0f) / projMat._11;
		float vy = (-2.0f * cursor.y / view.Height + 1.0f) / projMat._22;

		D3DXVECTOR3 Origin(vx, vy, 0.0f);
		D3DXVECTOR3 Direction(vx, vy, 1.0f);
		
		Matrix viewMat;
		D3D_DEVICE->GetTransform(D3DTS_VIEW, &viewMat);

		Matrix inverseViewMat;
		D3DXMatrixInverse(&inverseViewMat, 0, &viewMat);
		D3DXVec3TransformCoord(&Origin, &Origin, &inverseViewMat);
		D3DXVec3TransformNormal(&Direction, &Direction, &inverseViewMat);
		
		Matrix inverseMat;
		D3DXMatrixInverse(&inverseMat, nullptr, &matWorld);

		D3DXVec3TransformCoord(&vOrg, &Origin, &inverseMat);
		D3DXVec3TransformNormal(&vDir, &Direction, &inverseMat);
		
		BOOL isHit = FALSE;

		D3DXIntersect(mesh, &vOrg, &vDir, &isHit, nullptr, nullptr, nullptr, dist, nullptr, nullptr);

		return isHit;
	}

	bool DeviceManager::IsRayInMeshOrtho(const D3DXMATRIX& matWorld, LPD3DXMESH mesh, float* dist)
	{
		POINT cursor;

		GetCursorPos(&cursor);
		ScreenToClient(hWnd, &cursor);

		D3DVIEWPORT9 view;
		D3D_DEVICE->GetViewport(&view);

		Matrix projMat;
		D3D_DEVICE->GetTransform(D3DTS_PROJECTION, &projMat);

		/*float vx = (+2.0f * cursor.x / view.Width - 1.0f) / projMat._11;
		float vy = (-2.0f * cursor.y / view.Height + 1.0f) / projMat._22;*/

		D3DXVECTOR3 Origin(cursor.x, cursor.y, 0.0f);
		D3DXVECTOR3 Direction(cursor.x, cursor.y, 1.0f);
		
		Matrix viewMat;
		D3D_DEVICE->GetTransform(D3DTS_VIEW, &viewMat);

		D3DXVECTOR3 vtemp;
		D3DXVec3Unproject(&vOrg, &Origin, &view, &projMat, &viewMat, &matWorld);
		D3DXVec3Unproject(&vtemp, &Direction, &view, &projMat, &viewMat, &matWorld);

		vDir = vtemp - vOrg;
		D3DXVec3Normalize(&vDir, &vDir);

		BOOL isHit = FALSE;

		D3DXIntersect(mesh, &vOrg, &vDir, &isHit, nullptr, nullptr, nullptr, dist, nullptr, nullptr);

		return isHit;
	}

	bool DeviceManager::RayTo(const D3DXMATRIX& matWorld, LPD3DXMESH mesh, float* dist, Vec3 curPos)
	{
		POINT cursor;

		GetCursorPos(&cursor);
		ScreenToClient(hWnd, &cursor);

		D3DVIEWPORT9 view;
		D3D_DEVICE->GetViewport(&view);

		Matrix projMat;
		D3D_DEVICE->GetTransform(D3DTS_PROJECTION, &projMat);

		/*float vx = (+2.0f * cursor.x / view.Width - 1.0f) / projMat._11;
		float vy = (-2.0f * cursor.y / view.Height + 1.0f) / projMat._22;*/

		D3DXVECTOR3 Origin(curPos.x, curPos.y, curPos.z);
		D3DXVECTOR3 Direction(cursor.x, cursor.y, 1.0f);


		Matrix viewMat;
		D3D_DEVICE->GetTransform(D3DTS_VIEW, &viewMat);

		D3DXVECTOR3 vtemp;
		//D3DXVec3Unproject(&vOrg, &Origin, &view, &projMat, &viewMat, &matWorld);
		//D3DXVec3Unproject(&vtemp, &Direction, &view, &projMat, &viewMat, &matWorld);

		vDir = vtemp - vOrg;
		D3DXVec3Normalize(&vDir, &vDir);

		BOOL isHit = FALSE;
		//DrawLine(Origin, vDir, COLOR::RED);

		//cout << vDir.x << ", " << vDir.y << ", " << vDir.z << endl;

		D3DXIntersect(mesh, &Origin, &vDir, &isHit, nullptr, nullptr, nullptr, dist, nullptr, nullptr);

		return isHit;
	}

	bool DeviceManager::IsRayInTriangle(RAY* ray, const D3DXMATRIX& matWorld, D3DXVECTOR3 Vec3_1, D3DXVECTOR3 Vec3_2, D3DXVECTOR3 Vec3_3, float* u, float* v, float* dist)
	{
		D3DXMATRIX inverseMat;

		D3DXMatrixInverse(&inverseMat, nullptr, &matWorld);
		D3DXVec3TransformCoord(&vOrg, &ray->origin, &inverseMat);
		D3DXVec3TransformNormal(&vDir, &ray->direction, &inverseMat);

		bool isHit;
		isHit = D3DXIntersectTri(&Vec3_1, &Vec3_2, &Vec3_3, &vOrg, &vDir, u, v, dist);

		return isHit;
	}

	void DeviceManager::SetHitPos(Vec3 pos)
	{
		hitPos = pos;
	}

	Vec3 DeviceManager::GetHitPos()
	{
		return hitPos;
	}
}