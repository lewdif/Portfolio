#pragma once
#include "Script.h"
#include "Transform3D.h"
#include "StaticMesh.h"
#include "SceneManager.h"

#include "GameManager.h"
#include "Bullet.h"

namespace CompEngine
{
	class Machinegun : public Script
	{
	private:
		Transform3D trans;
		StaticMesh machinegunMesh;

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

		int bulletCount;
		double cooltimeCount;
		bool bulletLoaded;
		double time;

		bool mouseClicker;

		GameManager* GameMgr;

		GameObject* bullet;
		Bullet* bulletScript;
		Transform3D* bulletTrans;

	private:
		void lookAtMouseCoord();
		void fire();

	public:
		bool GetMachineGunStatus();
		void SetMachineGunStatus(bool value);

	public:
		virtual void Init();
		virtual void Reference();
		virtual void Update();
		virtual void LateUpdate();
	};
}
