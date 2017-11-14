#include "DeviceManager.h"


namespace CompEngine
{
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
		D3D_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

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
}