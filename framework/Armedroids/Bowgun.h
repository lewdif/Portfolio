#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SoundClip.h"

#include "Arrow.h"
#include "ProjectileArrow.h"

namespace CompEngine
{
	class Bowgun : public Script
	{
	private:
		Transform3D trans;
		StaticMesh bowgunMesh;
		
		Vec3 parentPos;
		
		RAY ray;
		float rayDist;
		StaticMesh* waterMesh;
		Transform3D* waterTrans3D;
		
		Vec3 curPos;
		Vec3 targetPos;
		Quater curRot;
		Quater destRot;
		Quater resRot;
		float rotSpeed;
		float maximumRange;

		//SoundClip sound;

		GameObject* arrow;
		Arrow* arrowScript;
		double cooltimeCount;
		bool arrowLoaded;

		bool mouseClicker;

		GameManager* GameMgr;
		GameObject* projArrow;
		Transform3D* projArrowTrans;
		ProjectileArrow* projArrowScript;

	private:
		void lookAtMouseCoord();
		void fire();

	public:
		bool GetArrowStatus();
		void SetArrowStatus(bool value);
		float GetMaxiumunRange();

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
