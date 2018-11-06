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
	void Shark::dameged(int weaponType)
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
			//sharkMesh.SetAnimation("normal");
			break;

		default:
			break;
		}
	}

	void Shark::Attack()
	{
		atkTimer += SceneMgr->GetTimeDelta();

		if (sharkMesh.GetCurrentAnimation() == "move")
		{
			sharkMesh.SetAnimation("normal");
		}

		if (sharkMesh.GetAnimationRate() >= 0.99f && sharkMesh.GetCurrentAnimation() == "attack")
		{
			sharkMesh.SetAnimationLoop(true);
			sharkMesh.SetAnimation("normal");
		}


		if (atkTimer > 2.5f && !((GameCharecter*)SceneMgr->CurrentScene()->
			FindObjectByTag("Player")->GetComponent("playerScript"))->GetIsDead())
		{
			sharkMesh.SetAnimationLoop(false);
			sharkMesh.SetAnimation("attack");
			isAtk = true;

			atkTimer = 0;
		}
		else
		{
		}

		if (sharkMesh.GetAnimationRate() >= 0.95f && isAtk
			&& sharkMesh.GetCurrentAnimation() == "attack")
		{
			((GameCharecter*)SceneMgr->CurrentScene()->FindObjectByTag("Player")
				->GetComponent("playerScript"))->Dameged(stat.ATK);
			cout << "Attack!" << endl;
		cout << sharkMesh.GetCurrentAnimation() << " - anim rate : "
			<< sharkMesh.GetAnimationRate() << endl;
			isAtk = false;
		}

		rigidBody->SetLinearVelocity(zeroMovement, 0, 0);

		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));
	}

	void Shark::Chase()
	{
		//cout << "Chase!" << endl;
		sharkMesh.SetAnimationLoop(true);
		sharkMesh.SetAnimation("move");

		trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), playerTrans->GetWorldPosition()));

		trans.GetWorldPosition(); // ?? �� �� �Լ��� ȣ������ ������ �������� �ʴ��� Ȯ�� �ʿ�.
		
		Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();
		Forward *= 11000;
		rigidBody->SetLinearVelocity(Forward.x, Forward.y, Forward.z);
	}

	void Shark::Patrol()
	{
		sharkMesh.SetAnimationLoop(true);
		sharkMesh.SetAnimation("move");

		if ((int)trans.GetWorldPosition().x != (int)destination.x ||
			(int)trans.GetWorldPosition().z != (int)destination.z)
		{
			isReached = false;
		}
		else if ((int)trans.GetWorldPosition().x == (int)destination.x &&
			(int)trans.GetWorldPosition().z == (int)destination.z)
		{
			isReached = true;
		}

		if (isReached && destination == patPoint)
		{
			destination = originPoint;
			isReached = false;
			if (gameObject->GetName() == "SharkA")
			{
				cout << "to origin" << endl;
			}
		}
		else if (isReached && destination == originPoint)
		{
			destination = patPoint;
			isReached = false;
			if (gameObject->GetName() == "SharkA")
			{
				cout << "to path" << endl;
			}
		}

		if (!isReached)
		{
			trans.SetRotation(trans.LookAt(trans.GetWorldPosition(), destination));

			trans.GetWorldPosition(); // ?? �� �� �Լ��� ȣ������ ������ �������� �ʴ��� Ȯ�� �ʿ�.

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();
			Forward *= 2000;
			rigidBody->SetLinearVelocity(Forward.x, Forward.y, Forward.z);
		}
	}

	float Shark::GetDistToPlayer()
	{
		return D3DXVec3Length(&(playerTrans->GetWorldPosition() - trans.GetWorldPosition()));
	}

	void Shark::ChangeDestination()
	{
		if (D3DXVec3Length(&(destination - trans.GetWorldPosition())) < 200)
		{
			if (destination == originPoint)
			{
				destination = patPoint;
			}
			else
			{
				destination = originPoint;
			}
		}
	}

	void Shark::SetSharkInfo(int lv, int spd, Vec3 location, Vec3 patrolPoint)
	{
		if (lv < 0)
		{
			cout << "level can't be set below zero : " << lv << endl;
			return;
		}
		
		patPoint = patrolPoint;
		originPoint = location;
		destination = patPoint;

		stat.LV = lv;
		stat.SPD = spd;

		trans.SetPosition(location);
		trans.SetRotation(0, 0, 0);
		rigidBody->SetTransform(trans.GetWorldPosition(), trans.GetRotationAngle());


		stat.ATK = lv + (int)sqrt((double)(lv));
		stat.HP = lv * 2 + 15 ;
		stat.REM_HP = stat.HP;
		stat.DEF = (int)sqrt((double)(lv));

		cout << stat.LV << ". hp : " << stat.REM_HP << " / " << stat.HP << endl;
	}

	void Shark::Init()
	{
		//gameObject->AddTag("Shark");

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		zeroMovement = 1;
		mass = 10;
		atkTimer = 0;
		stat = { 1, 1, 1, 3, 1 };
		isAtk = false;
		isReached = false;

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

		if (atkState == nullptr || chsState == nullptr || ptlState == nullptr)
		{
			atkState = new SharkAttackState(this);
			chsState = new SharkChaseState(this);
			ptlState = new SharkPatrolState(this);
		}
	}

	void Shark::Reference()
	{
		//trans.SetPosition(400, 0, -400);
		//trans.SetRotation(0, 0, 0);

		evntSphere->Init(trans.GetWorldPosition(), 50.0f);

		if (!gameObject->GetComponent("SkinnedMesh"))
		{
			//sharkMesh.SetFilePath(".\\Resources\\Shark.x");
			sharkMesh.LoadMeshFromX(".\\Resources\\SkinnedShark.X");
			gameObject->AddComponent(dynamic_cast<Component*>(&sharkMesh));
		}

		sharkMesh.SetAnimation("normal");
		playerTrans = GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByTag("Player"));
		arrowCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
			FindObjectByName("ProjectileArrow")->GetComponent("CollisionEventSphere"));
		bulletCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
			FindObjectByName("Bullet")->GetComponent("CollisionEventSphere"));

		sharkState = dynamic_cast<IEnemyState*>(ptlState);

		projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
		playerScript = (GameCharecter*)(SceneMgr->CurrentScene()->FindObjectByName("Player")->GetComponent("playerScript"));
	}

	void Shark::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		//evntSphere->Render(trans.GetTransform(), COLOR::RED);

		sharkState->UpdateState();

		if (evntSphere->Collide(arrowCollider) && projArrow->GetIsActive())
		{
			// �÷��̾�κ��� �ۻ� ���ݷ� �޾ƿͼ� ���°� ���� ���� ����
			// REM_HP <= 0 �϶� ������ ��ȯ
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

	void Shark::LateUpdate()
	{
	}
}
