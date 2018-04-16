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

		void DrawLine(D3DXMATRIX matrix, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR color);
		void DrawLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR color);

		void DrawBox(D3DXMATRIX transform, D3DXVECTOR3 leftBottom, D3DXVECTOR3 rightTop, D3DXCOLOR color);

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
