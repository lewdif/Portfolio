#include "Shark.h"
#include "Transform3D.h"
#include "RigidBody.h"

#include "InputManager.h"
#include "GameCharecter.h"

#include "SharkAttackState.h"
#include "SharkChaseState.h"
#include "SharkPatrolState.h"

namespace CompEngine
{
	void Shark::dameged()
	{
		int damege = 0;

		if (playerScript->GetWeaponType() == WEAPON_TYPE::BOWGUN)
		{
			damege = playerScript->GetPlayerInfo().BGUN_ATK - stat.DEF;
		}


		if (damege <= 0)
		{
			damege = 1;
		}

		stat.REM_HP -= damege;

		if (stat.REM_HP <= 0)
		{
			cout << "DEAD" << endl;
			gameObject->SetIsActive(false);
		}
	}

	void Shark::ChangeStateTo(int state)
	{
		switch (state)
		{
		case ENEMY_STATUS::PATROL:
			sharkState = ptlState;
			break;

		case ENEMY_STATUS::CHASE:
			sharkState = chsState;
			break;

		case ENEMY_STATUS::ATTACK:
			sharkState = atkState;
			break;

		default:
			break;
		}
	}

	void Shark::Attack()
	{
		atkTimer += SceneMgr->GetTimeDelta();

		if (atkTimer > 2.5f && !((GameCharecter*)SceneMgr->CurrentScene()->
			FindObjectByTag("Player")->GetComponent("playerScrpt"))->GetIsDead())
		{
			((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")
				->GetComponent("playerScrpt"))->Dameged(stat.ATK);
			cout << "Attack!" << endl;
			atkTimer = 0;
		}

		rigidBody.SetLinearVelocity(zeroMovement, 0, 0);

		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));
	}

	void Shark::Chase()
	{
		//cout << "Chase!" << endl;
		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));

		trans.GetWorldPosition(); // ?? 왜 이 함수를 호출하지 않으면 동작하지 않는지 확인 필요.
		
		Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();
		Forward *= 11000;
		rigidBody.SetLinearVelocity(Forward.x, Forward.y, -Forward.z);
	}

	void Shark::Patrol()
	{
		//cout << "Patrol!" << endl;
		rigidBody.SetLinearVelocity(zeroMovement, 0, 0);
	}

	float Shark::GetDistToPlayer()
	{
		return D3DXVec3Length(&(playerTrans->GetWorldPosition() - trans.GetWorldPosition()));
	}

	void Shark::SetSharkInfo(int lv, int spd, Vec3 location)
	{
		if (lv < 0)
		{
			cout << "level can't be set below zero : " << lv << endl;
			return;
		}

		stat.LV = lv;
		stat.SPD = spd;

		trans.SetPosition(location);

		stat.ATK = lv + (int)sqrt((double)(lv));
		stat.HP = lv * 2 + 15 ;
		stat.REM_HP = stat.HP;
		stat.DEF = (int)sqrt((double)(lv));
	}

	void Shark::Init()
	{
		//gameObject->AddTag("Shark");

		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		zeroMovement = 1;
		mass = 10;
		atkTimer = 0;
		stat = { 1, 1, 1, 3, 1 };

		evntSphere = new CollisionEventSphere;
		gameObject->AddComponent(dynamic_cast<Component*>(evntSphere));

		atkState = new SharkAttackState(this);
		chsState = new SharkChaseState(this);
		ptlState = new SharkPatrolState(this);

	}

	void Shark::Reference()
	{
		trans.SetPosition(400, 0, -400);

		evntSphere->Init(trans.GetWorldPosition(), 30.0f);

		colShape = new btBoxShape(btVector3(40 * trans.GetScale().x,
			100 * trans.GetScale().y, 60 * trans.GetScale().z));

		sharkMesh.SetFilePath(".\\Resources\\Shark.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&sharkMesh));

		playerTrans = GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByTag("Player"));
		arrowCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
			FindObjectByName("ProjectileArrow")->GetComponent("CollisionEventSphere"));

		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));

		sharkState = dynamic_cast<IEnemyState*>(ptlState);

		projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		projArrowScript = (ProjectileArrow*)(projArrow->GetComponent("projArrowScript"));

		playerScript = (GameCharecter*)(SceneMgr->CurrentScene()->FindObjectByName("Player")->GetComponent("playerScrpt"));
	}

	void Shark::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		evntSphere->Render(trans.GetTransform(), COLOR::RED);

		sharkState->UpdateState();

		if (evntSphere->Collide(arrowCollider))
		{
			// 플레이어로부터 작살 공격력 받아와서 방어력과 차이 계산및 적용
			// REM_HP <= 0 일때 죽음값 반환
			cout << "collide" << endl;

			dameged();

			if (projArrow->GetIsActive())
			{
				projArrow->SetIsActive(false);
			}
		}
	}

	void Shark::LateUpdate()
	{
	}
}
