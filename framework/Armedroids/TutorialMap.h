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
	class TutorialMap : public Script
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

		GameObject* wall07;
		Wall* wallScript07;
		Transform3D* wallTrans07;
		btBoxShape* wallShape07;

		GameObject* wall08;
		Wall* wallScript08;
		Transform3D* wallTrans08;
		btBoxShape* wallShape08;

		GameObject* wall09;
		Wall* wallScript09;
		Transform3D* wallTrans09;
		btBoxShape* wallShape09;

		GameObject* wall10;
		Wall* wallScript10;
		Transform3D* wallTrans10;
		btBoxShape* wallShape10;

		GameObject* wall11;
		Wall* wallScript11;
		Transform3D* wallTrans11;
		btBoxShape* wallShape11;

		GameObject* wall12;
		Wall* wallScript12;
		Transform3D* wallTrans12;
		btBoxShape* wallShape12;

		GameObject* wall13;
		Wall* wallScript13;
		Transform3D* wallTrans13;
		btBoxShape* wallShape13;

		GameObject* wall14;
		Wall* wallScript14;
		Transform3D* wallTrans14;
		btBoxShape* wallShape14;

		GameObject* wall15;
		Wall* wallScript15;
		Transform3D* wallTrans15;
		btBoxShape* wallShape15;

		GameObject* wall16;
		Wall* wallScript16;
		Transform3D* wallTrans16;
		btBoxShape* wallShape16;

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
