#include "Target.h"

#include "InputManager.h"


namespace CompEngine
{
	void Target::dameged(int weaponType)
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

			trans.SetPosition(0, -5000, 0);
			rigidBody->SetTransform(trans.GetWorldPosition(), trans.GetRotationAngle());

			gameObject->SetIsActive(false);
		}
	}

	void Target::SetInfo(int lv, int spd, Vec3 location)
	{
		if (lv < 0)
		{
			cout << "level can't be set below zero : " << lv << endl;
			return;
		}

		stat.LV = lv;
		stat.SPD = spd;

		trans.SetPosition(location);
		rigidBody->SetTransform(trans.GetWorldPosition(), trans.GetRotationAngle());


		stat.ATK = lv + (int)sqrt((double)(lv));
		stat.HP = lv * 2 + 15;
		stat.REM_HP = stat.HP;
		stat.DEF = (int)sqrt((double)(lv));

		cout << stat.LV << ". hp : " << stat.REM_HP << " / " << stat.HP << endl;
	}

	void Target::Init()
	{
		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		zeroMovement = 1;
		mass = 0;
		stat = { 1, 1, 1, 3, 1 };

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
	}

	void Target::Reference()
	{
		trans.SetPosition(400, 0, -400);

		evntSphere->Init(trans.GetWorldPosition(), 50.0f);

		if (!gameObject->GetComponent("StaticMesh"))
		{
			staticMesh.SetFilePath(".\\Resources\\Target.x");
			gameObject->AddComponent(dynamic_cast<Component*>(&staticMesh));
		}

		if (arrowCollider == nullptr || bulletCollider == nullptr)
		{
			arrowCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
				FindObjectByName("ProjectileArrow")->GetComponent("CollisionEventSphere"));
			bulletCollider = (CollisionEventSphere*)(SceneMgr->CurrentScene()->
				FindObjectByName("Bullet")->GetComponent("CollisionEventSphere"));
		}

		if (projArrow == nullptr || playerScript == nullptr)
		{
			projArrow = SceneMgr->CurrentScene()->FindObjectByName("ProjectileArrow");
			playerScript = (GameCharecter*)(SceneMgr->CurrentScene()->FindObjectByName("Player")->GetComponent("playerScript"));
		}
	}

	void Target::Update()
	{
		evntSphere->Update(trans.GetWorldPosition());
		//evntSphere->Render(trans.GetTransform(),COLOR::RED);

		if (evntSphere->Collide(arrowCollider) && projArrow->GetIsActive())
		{
			dameged(WEAPON_TYPE::BOWGUN);

			if (projArrow->GetIsActive())
			{
				projArrow->SetIsActive(false);
			}
		}
		else if (evntSphere->Collide(bulletCollider))
		{
			dameged(WEAPON_TYPE::MACHINEGUN);
			cout << "bullet hit" << endl;
		}
	}
	
	void Target::LateUpdate()
	{
	}
}