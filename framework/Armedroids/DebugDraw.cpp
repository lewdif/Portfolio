#include "DebugDraw.h"
#include "DeviceManager.h"

namespace CompEngine
{
	DebugDraw::DebugDraw()
		: m_debugMode(0)
	{
		device = DeviceMgr->GetDevice();
	}

	void DebugDraw::present()
	{
		if (!m_vertices.size()) return;

		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		device->SetTransform(D3DTS_WORLD, &world);
		device->SetVertexShader(NULL);
		device->SetPixelShader(NULL);
		device->SetRenderState(D3DRS_LIGHTING, FALSE);
		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->DrawPrimitiveUP(D3DPT_LINELIST, m_vertices.size() / 2, &m_vertices[0], sizeof(VCol));

		m_vertices.clear();
	}

	void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
	{
		D3DXVECTOR3 vFrom, vTo, vCFrom, vCTo;

		memcpy(&vFrom, &from, sizeof(D3DXVECTOR3));
		memcpy(&vTo, &to, sizeof(D3DXVECTOR3));
		memcpy(&vCFrom, &fromColor, sizeof(D3DXVECTOR3));
		memcpy(&vCTo, &toColor, sizeof(D3DXVECTOR3));

		D3DCOLOR cFrom, cTo;
		cFrom = D3DCOLOR_ARGB(0xFF, (DWORD)(vCFrom.x * 255), (DWORD)(vCFrom.y * 255), (DWORD)(vCFrom.z * 255));
		cTo = D3DCOLOR_ARGB(0xFF, (DWORD)(vCTo.x * 255), (DWORD)(vCTo.y * 255), (DWORD)(vCTo.z * 255));

		VCol vert[] = { VCol(vFrom, cFrom), VCol(vTo, cTo) };

		if (m_vertices.size() < 50000)
		{
			m_vertices.push_back(vert[0]);
			m_vertices.push_back(vert[1]);
		}
	}

	void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		drawLine(from, to, color, color);
	}

	void DebugDraw::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
	{
	}

	void DebugDraw::drawBox(const btVector3& boxMin, const btVector3& boxMax, const btVector3& color, btScalar alpha)
	{
	}

	void DebugDraw::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
	{
	}

	void DebugDraw::setDebugMode(int debugMode)
	{
		m_debugMode = debugMode;
	}

	void DebugDraw::draw3dText(const btVector3& location, const char* textString)
	{
	}

	void DebugDraw::reportErrorWarning(const char* warningString)
	{
		OutputDebugStringA(warningString);
		OutputDebugStringA("\n");
	}

	void DebugDraw::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
	}
}