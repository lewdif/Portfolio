#include "Pirate.h"
#include "Transform3D.h"
#include "RigidBody.h"

#include "InputManager.h"
#include "GameCharecter.h"

#include "PirateAttackState.h"
#include "PirateChaseState.h"
#include "PirateHoldState.h"

namespace CompEngine
{
	void Pirate::dameged(int weaponType)
	{
		int damege = 0;

		if (weaponType == WEAPON_TYPE::BOWGUN)
		{
			damege = playerScript->GetPlayerInfo().BGUN_ATK - stat.DEF;
		}
		else if (weaponType == WEAPON_TYPE::MACHINEGUN)
		{
			damege = playerScript->GetPlayerInfo().MGUN_ATK - stat.DEF;
		}

		if (damege <= 0)
		{
			damege = 1;
		}
		cout << "Damege : " << damege << endl;

		stat.REM_HP -= damege;

		if (stat.REM_HP <= 0)
		{
			cout << "DEAD" << endl;
			gameObject->SetIsActive(false);
		}
	}

	void Pirate::ChangeStateTo(int state)
	{
		switch (state)
		{
		case ENEMY_STATUS::PATROL:
			pirateState = hldState;
			break;

		case ENEMY_STATUS::CHASE:
			pirateState = chsState;
			break;

		case ENEMY_STATUS::ATTACK:
			pirateState = atkState;
			//PirateMesh.SetAnimation("normal");
			break;

		default:
			break;
		}
	}

	void Pirate::Attack()
	{
		atkTimer += SceneMgr->GetTimeDelta();

		if (atkTimer > 4.5f && !((GameCharecter*)SceneMgr->CurrentScene()->
			FindObjectByTag("Player")->GetComponent("playerScript"))->GetIsDead())
		{
			isAtk = true;
			cout << "attack!!" << endl;
			atkTimer = 0;
		}
		else
		{
		}

		/*if (PirateMesh.GetAnimationRate() >= 0.95f && isAtk
			&& PirateMesh.GetCurrentAnimation() == "attack")
		{
			((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")
				->GetComponent("playerScript"))->Dameged(stat.ATK);
			cout << "Attack!" << endl;
			cout << PirateMesh.GetCurrentAnimation() << " - anim rate : "
				<< PirateMesh.GetAnimationRate() << endl;
			isAtk = false;
		}*/

		rigidBody->SetLinearVelocity(zeroMovement, 0, 0);

		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));
	}

	void Pirate::Chase()
	{
		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));

		trans.GetWorldPosition(); // ?? 왜 이 함수를 호출하지 않으면 동작하지 않는지 확인 필요.

		Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();
		Forward *= 6000;
		rigidBody->SetLinearVelocity(Forward.x, Forward.y, Forward.z);
	}

	void Pirate::Hold()
	{
		if ((int)trans.GetWorldPosition().x != (int)originPoint.x ||
			(int)trans.GetWorldPosition().z != (int)originPoint.z)
		{
			//trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), originPoint));

			//trans.GetWorldPosition(); // ?? 왜 이 함수를 호출하지 않으면 동작하지 않는지 확인 필요.

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();
			Forward *= 2000;
			rigidBody->SetLinearVelocity(Forward.x, Forward.y, Forward.z);
		}
	}

	float Pirate::GetDistToPlayer()
	{
		return D3DXVec3Length(&(playerTrans->GetWorldPosition() - trans.GetWorldPosition()));
	}

	void Pirate::SetPirateInfo(int lv, int spd, Vec3 location)
	{
		if (lv < 0)
		{
			cout << "level can't be set below zero : " << lv << endl;
			return;
		}

		originPoint = location;

		stat.LV = lv;
		stat.SPD = spd;

		trans.SetPosition(location);
		trans.SetRotation(0, 0, 0);
		rigidBody->SetTransform(trans.GetWorldPosition(), trans.GetRotationAngle());


		stat.ATK = lv + (int)sqrt((double)(lv));
		stat.HP = lv * 2 + 15;
		stat.REM_HP = stat.HP;
		stat.DEF = (int)sqrt((double)(lv));

		cout << stat.LV << ". hp : " << stat.REM_HP << " / " << stat.HP << endl;
	}

	void Pirate::Init()
	{
		//gameObject->AddTag("Pirate");

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		zeroMovement = 1;
		mass = 10;
		atkTimer = 0;
		stat = { 3, 1, 1, 3, 1 };
		isAtk = false;

		colShape = new btBoxShape(btVector3(40 * trans.GetScale().x,
			100 * trans.GetScale().y, 60 * trans.GetScale().z));

		if (!gameObject->GetComponent("RigidBody"))
		{
			rigidBody = new RigidBody;
			rigidBody->SetRigidBody(gameObject, mass, colShape);
			rigidBody->LockRotation(true, false, true);
			gameObject->AddComponent(dynamic_cast<Component*>(rigidBody));
		}

		if (!gameObject->GetComponent("CollisionEventSphere"))
		{
			evntSphere = new CollisionEventSphere;
			gameObject->AddComponent(dynamic_cast<Component*>(evntSphere));
		}

		if (!gameObject->GetIsActive())
		{
			gameObject->SetIsActive(true);
		}

		if (atkState == nullptr || chsState == nullptr || hldState == nullptr)
		{
			atkState = new PirateAttackState(this);
			chsState = new PirateChaseState(this);
			hldState = new PirateHoldState(this);
		}
	}

	void Pirate::Reference()
	{
		//trans.SetPosition(400, 0, -400);
		//trans.SetRotation(0, 0, 0);

		evntSphere->Init(trans.GetWorldPosition(), 50.0f);

		if (!gameObject->GetComponent("StaticMesh"))
		{
			pirateMesh.SetFilePath(".\\Resources\\PirateShip.x");
			gameObject->AddComponent(dynamic_cast<Component*>(&pirateMesh));
		}

		playerTrans = GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByTag("Player"));
		arrowCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
			FindObjectByName("ProjectileArrow")->GetComponent("CollisionEventSphere"));
		bulletCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
			FindObjectByName("Bullet")->GetComponent("CollisionEventSphere"));

		pirateState = dynamic_cast<IEnemyState*>(hldState);

		projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		playerScript = (GameCharecter*)(SceneMgr->CurrentScene()->FindObjectByName("Player")->GetComponent("playerScript"));
	}

	void Pirate::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		//evntSphere->Render(trans.GetTransform(), COLOR::RED);

		pirateState->UpdateState();

		if (evntSphere->Collide(arrowCollider) && projArrow->GetIsActive())
		{
			// 플레이어로부터 작살 공격력 받아와서 방어력과 차이 계산및 적용
			// REM_HP <= 0 일때 죽음값 반환
			//cout << "collide" << endl;

			dameged(WEAPON_TYPE::BOWGUN);

			if (projArrow->GetIsActive())
			{
				projArrow->SetIsActive(false);
			}
		}
		else if (evntSphere->Collide(bulletCollider))
		{
			dameged(WEAPON_TYPE::MACHINEGUN);
			//GET_TRANSFORM_3D(bullet)->SetPosition(0, 0, 0);
			cout << "bullet hit" << endl;
		}
	}

	void Pirate::LateUpdate()
	{
	}
}