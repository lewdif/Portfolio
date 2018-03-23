#pragma once
#include "headers.h"

namespace CompEngine
{
	struct VCol
	{
		VCol(const D3DXVECTOR3& v, D3DCOLOR c) :pos(v), col(c) {}

		D3DXVECTOR3 pos;
		D3DCOLOR    col;
	};

	class DebugDraw : public btIDebugDraw
	{
	private:
		IDirect3DDevice9* device;
	public:
		int m_debugMode;
		std::vector< VCol > m_vertices;

		DebugDraw();

		void            present();
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor);
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
		virtual void	drawSphere(const btVector3& p, btScalar radius, const btVector3& color);
		virtual void	drawBox(const btVector3& boxMin, const btVector3& boxMax, const btVector3& color, btScalar alpha);
		virtual void	drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha);
		virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
		virtual void	reportErrorWarning(const char* warningString);
		virtual void	draw3dText(const btVector3& location, const char* textString);
		virtual void	setDebugMode(int debugMode);
		virtual int		getDebugMode() const { return m_debugMode; }
	};
}
