#include "GameCharecter.h"
#include "InputManager.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "SceneManager.h"


namespace CompEngine
{
	void GameCharecter::controll()
	{
		bool Input = false;

		static bool W_Key = false;
		static bool S_Key = false;
		static bool A_Key = false;
		static bool D_Key = false;

		if (InputMgr->KeyDown('W', false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Forward *= 10000;

			rigidBody.SetLinearVelocity(Forward.x, Forward.y, -Forward.z);

			W_Key = true;
		}
		else if (W_Key)
		{
			rigidBody.SetLinearVelocity(zeroMovement, 0, 0);
			W_Key = false;
		}

		if (InputMgr->KeyDown('S', false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Backword = -GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Backword *= 10000;


			rigidBody.SetLinearVelocity(Backword.x, Backword.y, -Backword.z);

			S_Key = true;
		}
		else if (S_Key)
		{
			rigidBody.SetLinearVelocity(0, 0, zeroMovement);
			S_Key = false;
		}

		if (InputMgr->KeyDown('A', false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody.SetAngularVelocity(0, -2.5f, 0);

			A_Key = true;
		}
		else if (A_Key)
		{
			rigidBody.SetAngularVelocity(0, 0, 0);
			A_Key = false;
		}

		if (InputMgr->KeyDown('D', false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody.SetAngularVelocity(0, 2.5f, 0);

			D_Key = true;
		}
		else if (D_Key)
		{
			rigidBody.SetAngularVelocity(0, 0, 0);
			D_Key = false;
		}

		if (Input == false)
		{
			//playerMesh->SetAnimation("Idle");
		}
	}

	void GameCharecter::GainEXP(int amount)
	{
		stat.CUR_EXP += amount;

		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		cout << "Gained EXP : " << amount << endl;

		if (stat.CUR_EXP >= stat.EXP)
		{
			for (int i = stat.CUR_EXP; i < stat.EXP; )
			{
				stat.LV++;
				stat.CUR_EXP -= stat.EXP;
				stat.EXP = (stat.LV + 1) * (stat.LV + 1)*(stat.LV + 1);
				stat.SKL_PNT += 2;
				cout << "Level up!" << endl;
			}
		}

		cout << " ( " << stat.CUR_EXP << " / " << stat.EXP << " ) " << endl;
		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
	}

	void GameCharecter::SetSkill(int num)
	{
		switch (num)
		{
		case ABLE_SKILLS::HP:
			stat.HP += 5;
			stat.REM_HP += 5;
			stat.SKL_PNT--;
			break;

		case ABLE_SKILLS::BGUN:
			stat.BGUN_ATK += 2;
			stat.SKL_PNT--;
			break;

		case ABLE_SKILLS::MGUN:
			stat.MGUN_ATK++;
			stat.SKL_PNT--;
			break;

		case ABLE_SKILLS::CANON:
			stat.CANON_ATK += 3;
			stat.SKL_PNT--;
			break;

		case ABLE_SKILLS::DEF:
			stat.DEF++;
			stat.SKL_PNT--;
			break;

		case ABLE_SKILLS::SPD:
			stat.SPD++;
			stat.SKL_PNT--;
			break;

		default:
			break;
		}
	}

	void GameCharecter::Dameged(int damege)
	{
		if (stat.REM_HP <= damege)
		{
			isDead = true;
			return;
		}

		stat.REM_HP = stat.REM_HP - (damege - (stat.DEF * 0.5f));
		cout << stat.REM_HP << " / " << stat.HP << endl;
	}

	void GameCharecter::Respawn(Vec3 location)
	{
		gameObject->SetIsActive(true);
		bowgun->SetIsActive(true);
		SceneMgr->CurrentScene()->FindObjectByName("Arrow")->SetIsActive(true);

		isDead = false;

		stat.REM_HP = stat.HP;

		playerTrans3D.SetPosition(location);	// 리스폰 위치 설정 필요
		playerTrans3D.SetRotation(0, playerTrans3D.GetRotationAngle().y, 0);
		rigidBody.SetLinearVelocity(zeroMovement, 0, 0);

		rigidBody.SetTransform(playerTrans3D.GetWorldPosition(), playerTrans3D.GetRotationAngle());
	}

	int GameCharecter::GetRespawnTime()
	{
		return stat.LV + 5;
	}

	bool GameCharecter::GetIsDead()
	{
		return isDead;
	}

	void GameCharecter::SetPlayerActive(bool value)
	{
		gameObject->SetIsActive(value);
	}

	CHARECTER_STATUS GameCharecter::GetPlayerInfo()
	{
		return stat;
	}

	int GameCharecter::GetWeaponType()
	{
		return weaponType;
	}

	void GameCharecter::Init()
	{
		gameObject->AddTag("Player");
		zeroMovement = 1.f;
		mass = 5000;

		isDead = false;
		respawnCounter = 0;

		//playerMesh = new SkinnedMesh();
		stat = { 1, 15, 15, 4, 1, 8, 1, 8, 8, 0, 0 };

		gameObject->AddComponent(dynamic_cast<Component*>(&playerTrans3D));

		bowgun = new GameObject;
		bowgunScript = new Bowgun;

		weaponType = WEAPON_TYPE::BOWGUN;

		this->gameObject->AttachChild(bowgun);

		dynamic_cast<Script*>(bowgunScript)->SetInfo(bowgun, "bowgunScrpt");
		bowgun->AddComponent(dynamic_cast<Component*>(bowgunScript));

		SceneMgr->CurrentScene()->AddObject(bowgun, "Bowgun");
	}

	void GameCharecter::Reference()
	{
		playerTrans3D.SetPosition(0, 0, 0);

		colShape = new btBoxShape(btVector3(50 * playerTrans3D.GetScale().x,
			50 * playerTrans3D.GetScale().y, 65 * playerTrans3D.GetScale().z));

		//playerMesh->LoadMeshFromX(".\\Resources\\Lucy.x");
		//gameObject->AddComponent(dynamic_cast<Component*>(playerMesh));

		boatMesh.SetFilePath(".\\Resources\\boat.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&boatMesh));

		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.SetLinearVelocity(zeroMovement, 0, 0);
		rigidBody.LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));
	}

	void GameCharecter::Update()
	{
		/*sec += SceneMgr->GetTimeDelta();
		if (sec > 2)
		{
			cout << playerTrans3D.GetPosition().x << ", "
				<< playerTrans3D.GetPosition().y << ", "
				<< playerTrans3D.GetPosition().z << endl;

			sec = 0;
		}*/

		if (isDead)
		{
			gameObject->SetIsActive(false);
			bowgun->SetIsActive(false);
			SceneMgr->CurrentScene()->FindObjectByName("Arrow")->SetIsActive(false);
			return;
		}

		/*if (playerTrans3D.GetPosition().y != 0)
		{
			playerTrans3D.SetRotation(0, playerTrans3D.GetRotationAngle().y, 0);
			playerTrans3D.SetPosition(playerTrans3D.GetPosition().x, 0, playerTrans3D.GetPosition().z);
			//rigidBody.SetTransform(playerTrans3D.GetWorldPosition(), playerTrans3D.GetRotationAngle());
		}*/

		//Vec3 rightTop =  Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//Vec3 leftBottom =  -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//DeviceMgr->DrawBox(playerTrans3D->GetTransform(), leftBottom/10, rightTop/10, COLOR::GREEN);
		controll();

	}

	void GameCharecter::LateUpdate()
	{
		
	}
}