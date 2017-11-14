#pragma once
#include "ISingleton.h"
#include "headers.h"

namespace CompEngine
{
	class DeviceManager : public ISingleton <DeviceManager>
	{
	public:
		bool					InitMembers(HWND hWnd);
		IDirect3DDevice9*		GetDevice();
		int						GetHeight();
		int						GetWidth();

	public:
		DeviceManager();
		virtual ~DeviceManager();
		virtual void ReleaseMembers();
		D3DXMATRIXA16 GetWorldMat();

	private:
		HWND					hWnd;
		IDirect3D9*				d3d9;
		D3DCAPS9				caps;
		D3DPRESENT_PARAMETERS	d3dpp;
		IDirect3DDevice9*		D3D_DEVICE;
		ID3DXLine*				line;
		ID3DXFont*				font;
		int						width, height;
		bool					isInit;
		D3DXMATRIXA16			matWorld;
	};
}
