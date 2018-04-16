#include "headers.h"
#include "DeviceManager.h"

namespace CompEngine
{
	struct lineVertex
	{
		float x, y, z;
		DWORD color;
	};


	void DeviceManager::DrawLine(D3DXMATRIX matrix, D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR color)
	{
		D3D_DEVICE->SetTransform(D3DTS_WORLD, &matrix);

		lineVertex lineVertices[2];

		const DWORD line_fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		lineVertices[0].x = start.x;
		lineVertices[0].y = start.y;
		lineVertices[0].z = start.z;
		lineVertices[0].color = color;

		lineVertices[1].x = end.x;
		lineVertices[1].y = end.y;
		lineVertices[1].z = end.z;
		lineVertices[1].color = color;

		D3D_DEVICE->SetFVF(line_fvf);
		D3D_DEVICE->SetRenderState(D3DRS_LIGHTING, false);
		D3D_DEVICE->SetTexture(0, NULL);

		D3D_DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 1, lineVertices, sizeof(lineVertex));
	}

	void DeviceManager::DrawLine(D3DXVECTOR3 start, D3DXVECTOR3 end, D3DXCOLOR color)
	{
		Matrix Transform;
		D3DXMatrixIdentity(&Transform);
		D3D_DEVICE->SetTransform(D3DTS_WORLD, &Transform);

		lineVertex lineVertices[2];

		const DWORD line_fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		lineVertices[0].x = start.x;
		lineVertices[0].y = start.y;
		lineVertices[0].z = start.z;
		lineVertices[0].color = color;

		lineVertices[1].x = end.x;
		lineVertices[1].y = end.y;
		lineVertices[1].z = end.z;
		lineVertices[1].color = color;

		D3D_DEVICE->SetFVF(line_fvf);

		D3D_DEVICE->SetTexture(0, NULL);

		D3D_DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, 1, lineVertices, sizeof(lineVertex));
	}

	void DeviceManager::DrawBox(D3DXMATRIX transform, D3DXVECTOR3 leftBottom, D3DXVECTOR3 rightTop, D3DXCOLOR color)
	{
		D3DXVECTOR3 Vertex[8];

		Vertex[0].x = leftBottom.x;
		Vertex[0].y = leftBottom.y;
		Vertex[0].z = leftBottom.z;

		Vertex[1].x = rightTop.x;
		Vertex[1].y = leftBottom.y;
		Vertex[1].z = leftBottom.z;

		Vertex[2].x = leftBottom.x;
		Vertex[2].y = rightTop.y;
		Vertex[2].z = leftBottom.z;

		Vertex[3].x = leftBottom.x;
		Vertex[3].y = leftBottom.y;
		Vertex[3].z = rightTop.z;

		Vertex[4].x = rightTop.x;
		Vertex[4].y = rightTop.y;
		Vertex[4].z = leftBottom.z;

		Vertex[5].x = rightTop.x;
		Vertex[5].y = leftBottom.y;
		Vertex[5].z = rightTop.z;

		Vertex[6].x = leftBottom.x;
		Vertex[6].y = rightTop.y;
		Vertex[6].z = rightTop.z;

		Vertex[7].x = rightTop.x;
		Vertex[7].y = rightTop.y;
		Vertex[7].z = rightTop.z;

		this->DrawLine(transform, Vertex[0], Vertex[1], color);
		this->DrawLine(transform, Vertex[0], Vertex[2], color);
		this->DrawLine(transform, Vertex[0], Vertex[3], color);

		this->DrawLine(transform, Vertex[7], Vertex[4], color);
		this->DrawLine(transform, Vertex[7], Vertex[5], color);
		this->DrawLine(transform, Vertex[7], Vertex[6], color);

		this->DrawLine(transform, Vertex[2], Vertex[4], color);
		this->DrawLine(transform, Vertex[2], Vertex[6], color);

		this->DrawLine(transform, Vertex[5], Vertex[1], color);
		this->DrawLine(transform, Vertex[5], Vertex[3], color);

		this->DrawLine(transform, Vertex[1], Vertex[4], color);
		this->DrawLine(transform, Vertex[3], Vertex[6], color);
	}
}