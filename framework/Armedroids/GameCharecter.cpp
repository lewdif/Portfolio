#include "GameCharecter.h"
#include "InputManager.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "SceneManager.h"

#include "Bullet.h"
#include "G_Val.h"

namespace CompEngine
{
	void GameCharecter::controll()
	{
		bool Input = false;

		static bool W_Key = false;
		static bool S_Key = false;
		static bool A_Key = false;
		static bool D_Key = false;

		static bool num1_Key = false;
		static bool num2_Key = false;
		static bool num3_Key = false;

		if (InputMgr->KeyDown('W', false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Forward *= 10000;

			rigidBody.SetLinearVelocity(Forward.x, Forward.y, Forward.z);

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


			rigidBody.SetLinearVelocity(Backword.x, Backword.y, Backword.z);

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

		if (InputMgr->KeyDown('1', false))
		{
			Input = true;

			weaponType = WEAPON_TYPE::BOWGUN;

			num1_Key = true;
		}
		else if (num1_Key)
		{
			num1_Key = false;
		}

		if (InputMgr->KeyDown('2', false))
		{
			Input = true;

			weaponType = WEAPON_TYPE::MACHINEGUN;

			num2_Key = true;
		}
		else if (num2_Key)
		{
			num2_Key = false;
		}

		if (InputMgr->KeyDown('3', false))
		{
			Input = true;

			weaponType = WEAPON_TYPE::CANONGUN;

			num3_Key = true;
		}
		else if (num3_Key)
		{
			num3_Key = false;
		}

		if (Input == false)
		{
			//playerMesh->SetAnimation("Idle");
		}
	}

	void GameCharecter::setWeapon()
	{
		if (weaponType == WEAPON_TYPE::BOWGUN)
		{
			if (!bowgun->GetIsActive())
			{
				bowgun->SetIsActive(true);

				if (bowgunScript->GetArrowStatus())
				{
					bowgun->FindChildByTag("Arrow")->SetIsActive(true);
				}
			}
			machinegun->SetIsActive(false);
			bullet->SetIsActive(false);
		}
		else if (weaponType == WEAPON_TYPE::MACHINEGUN)
		{
			if (!machinegun->GetIsActive())
			{
				machinegun->SetIsActive(true);
				bullet->SetIsActive(true);
			}

			bowgun->SetIsActive(false);
			bowgun->FindChildByTag("Arrow")->SetIsActive(false);
		}
		else if (weaponType == WEAPON_TYPE::CANONGUN)
		{
			bowgun->SetIsActive(false);
			bowgun->FindChildByTag("Arrow")->SetIsActive(false);

			machinegun->SetIsActive(false);
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
			SceneMgr->CurrentScene()->FindObjectByName("GameOverWnd")->SetIsActive(true);
			SceneMgr->CurrentScene()->FindObjectByName("RestartBtn")->SetIsActive(true);
			SceneMgr->CurrentScene()->FindObjectByName("ToTitleBtn")->SetIsActive(true);
			SceneMgr->CurrentScene()->FindObjectByName("ToMapBtn")->SetIsActive(true);
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

		rigidBody.SetTransform(playerTrans3D.GetWorldPosition(), Vec3(0,0,0));
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
		stat = { 1, 150, 1, 50, 5, 8, 1, 8, 8, 0, 0 };

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&playerTrans3D));
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Bowgun"))
		{
			bowgun = new GameObject;
			bowgunScript = new Bowgun;

			dynamic_cast<Script*>(bowgunScript)->SetInfo(bowgun, "bowgunScript");
			bowgun->AddComponent(dynamic_cast<Component*>(bowgunScript));

			SceneMgr->CurrentScene()->AddObject(bowgun, "Bowgun");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Machinegun"))
		{
			machinegun = new GameObject;
			machinegunScript = new Machinegun;

			dynamic_cast<Script*>(machinegunScript)->SetInfo(machinegun, "machinegunScript");
			machinegun->AddComponent(dynamic_cast<Component*>(machinegunScript));

			SceneMgr->CurrentScene()->AddObject(machinegun, "Machinegun");
		}
		
		weaponType = WEAPON_TYPE::BOWGUN;

		if (!gameObject->GetIsActive())
		{
			gameObject->SetIsActive(true);
		}
	}

	void GameCharecter::Reference()
	{
		playerTrans3D.SetPosition(-300, 0, -400);
		playerTrans3D.SetRotation(0, 0, 0);

		colShape = new btBoxShape(btVector3(50 * playerTrans3D.GetScale().x,
			50 * playerTrans3D.GetScale().y, 65 * playerTrans3D.GetScale().z));

		bullet = SceneMgr->CurrentScene()->FindObjectByName("Bullet");

		boatMesh.SetFilePath(".\\Resources\\boat.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&boatMesh));

		rigidBody.SetRigidBody(gameObject, mass, colShape);
		rigidBody.SetLinearVelocity(zeroMovement, 0, 0);
		rigidBody.LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(&rigidBody));
	}

	void GameCharecter::Update()
	{
		setWeapon();

		if (isDead)
		{
			gameObject->SetIsActive(false);

			if (weaponType == WEAPON_TYPE::BOWGUN)
			{
				bowgun->SetIsActive(false);
				SceneMgr->CurrentScene()->FindObjectByName("Arrow")->SetIsActive(false);
			}
			else if (weaponType == WEAPON_TYPE::MACHINEGUN)
			{
				machinegun->SetIsActive(false);
				SceneMgr->CurrentScene()->FindObjectByName("Bullet")->SetIsActive(false);
			}

			return;
		}

		if (TUTORIAL_OVER)
		{
			controll();
		}
	}

	void GameCharecter::LateUpdate()
	{
		
	}
}