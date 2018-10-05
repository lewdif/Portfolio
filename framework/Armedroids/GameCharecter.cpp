#include "GameCharecter.h"
#include "InputManager.h"
#include "Transform3D.h"
#include "RigidBody.h"
#include "SceneManager.h"


namespace CompEngine
{
	void GameCharecter::Init()
	{
		gameObject->AddTag("Player");
		zeroMovement = 1.f;
		mass = 10;

		//playerMesh = new SkinnedMesh();
		boatMesh = new StaticMesh();
		rigidBody = new RigidBody();
		playerTrans3D = new Transform3D();

		gameObject->AddComponent(dynamic_cast<Component*>(playerTrans3D));

		bowgun = new GameObject;
		bowgunScript = new Bowgun;

		this->gameObject->AttachChild(bowgun);
		//bowgun->AttachParent(this->gameObject);

		dynamic_cast<Script*>(bowgunScript)->SetInfo(bowgun, "bowgunScrpt");
		bowgun->AddComponent(dynamic_cast<Component*>(bowgunScript));

		SceneMgr->CurrentScene()->AddComponent(bowgun, "Bowgun");
	}

	void GameCharecter::Reference()
	{
		playerTrans3D->SetPosition(0, 0, 0);

		colShape = new btBoxShape(btVector3(50 * playerTrans3D->GetScale().x,
			100 * playerTrans3D->GetScale().y, 65 * playerTrans3D->GetScale().z));

		//playerMesh->LoadMeshFromX(".\\Resources\\Lucy.x");
		//gameObject->AddComponent(dynamic_cast<Component*>(playerMesh));

		boatMesh->SetFilePath(".\\Resources\\boat.x");
		gameObject->AddComponent(dynamic_cast<Component*>(boatMesh));

		rigidBody->SetRigidBody(gameObject, mass, colShape);
		rigidBody->SetLinearVelocity(zeroMovement, 0, 0);
		rigidBody->LockRotation(true, false, true);
		gameObject->AddComponent(dynamic_cast<Component*>(rigidBody));
	}

	void GameCharecter::Update()
	{
		//Vec3 rightTop =  Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//Vec3 leftBottom =  -Vec3(colShape->getHalfExtentsWithoutMargin().getX(), colShape->getHalfExtentsWithoutMargin().getY(), colShape->getHalfExtentsWithoutMargin().getZ());
		//DeviceMgr->DrawBox(playerTrans3D->GetTransform(), leftBottom/10, rightTop/10, COLOR::GREEN);

		bool Input = false;

		static bool I_Key = false;
		static bool K_Key = false;
		static bool J_Key = false;
		static bool L_Key = false;

		if (InputMgr->KeyDown(VK_UP, false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Forward *= 50000;

			rigidBody->SetLinearVelocity(Forward.x, Forward.y, -Forward.z);

			I_Key = true;
		}
		else if (I_Key)
		{
			rigidBody->SetLinearVelocity(zeroMovement, 0, 0);
			I_Key = false;

			cout << "char pos : (" 
				<< playerTrans3D->GetPosition().x << ", "
				<< playerTrans3D->GetPosition().y << ", "
				<< playerTrans3D->GetPosition().z << ")" << endl;
		}

		if (InputMgr->KeyDown(VK_DOWN, false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Backword = -GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Backword *= 50000;


			rigidBody->SetLinearVelocity(Backword.x, Backword.y, -Backword.z);

			K_Key = true;
		}
		else if (K_Key)
		{
			rigidBody->SetLinearVelocity(0, 0, zeroMovement);
			K_Key = false;

			cout << "char pos : (" << playerTrans3D->GetPosition().x << ", "
				<< playerTrans3D->GetPosition().y << ", "
				<< playerTrans3D->GetPosition().z << ")" << endl;
		}

		if (InputMgr->KeyDown(VK_LEFT, false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody->SetAngularVelocity(0, -5.8f, 0);

			J_Key = true;
		}
		else if (J_Key)
		{
			rigidBody->SetAngularVelocity(0, 0, 0);
			J_Key = false;
		}

		if (InputMgr->KeyDown(VK_RIGHT, false))
		{
			Input = true;
			//playerMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody->SetAngularVelocity(0, 5.8f, 0);

			L_Key = true;
		}
		else if (L_Key)
		{
			rigidBody->SetAngularVelocity(0, 0, 0);
			L_Key = false;
		}

		if (Input == false)
		{
			//playerMesh->SetAnimation("Idle");
		}
	}

	void GameCharecter::LateUpdate()
	{
	}
}