#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "SceneManager.h"
#include "headers.h"
#include "GameObject.h"
#include "StaticMesh.h"

#include "Wall.h"

namespace CompEngine
{
	class BasinMap : public Script
	{
	private:
		Transform3D trans;
		StaticMesh mapMesh;

		GameObject* wall01;
		Wall* wallScript01;
		Transform3D* wallTrans01;
		btBoxShape* wallShape01;

		GameObject* wall02;
		Wall* wallScript02;
		Transform3D* wallTrans02;
		btBoxShape* wallShape02;

		GameObject* wall03;
		Wall* wallScript03;
		Transform3D* wallTrans03;
		btBoxShape* wallShape03;

		GameObject* wall04;
		Wall* wallScript04;
		Transform3D* wallTrans04;
		btBoxShape* wallShape04;

		GameObject* wall05;
		Wall* wallScript05;
		Transform3D* wallTrans05;
		btBoxShape* wallShape05;

		GameObject* wall06;
		Wall* wallScript06;
		Transform3D* wallTrans06;
		btBoxShape* wallShape06;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
