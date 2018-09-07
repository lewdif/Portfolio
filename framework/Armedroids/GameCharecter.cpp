#include "GameCharecter.h"
#include "InputManager.h"
#include "Transform3D.h"
#include "RigidBody.h"


namespace CompEngine
{
	void GameCharecter::Init()
	{
		gameObject->AddTag("Player");
		//GET_TRANSFORM_3D(gameObject)->SetScale(0.1f, 0.1f, 0.1f);
		//GET_TRANSFORM_3D(gameObject)->SetPosition(0, 0, 0);
		zeroMovement = 1.0f;
	}

	void GameCharecter::Reference()
	{
		skinnedMesh = GET_SKINNED_MESH(gameObject);
		rigidBody = GET_RIGIDBODY(gameObject);
		trans = GET_TRANSFORM_3D(gameObject);
		//gameObject->DebugOut();
		//rigidBody->set

		rigidBody->SetLinearVelocity(zeroMovement, 0, 0);
	}

	void GameCharecter::Update()
	{
		bool Input = false;

		Vec3 curPos = trans->GetPosition();

		static bool I_Key = false;
		static bool K_Key = false;
		static bool J_Key = false;
		static bool L_Key = false;

		if (InputMgr->KeyDown('I', false))
		{
			Input = true;
			skinnedMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Forward *= 5000;

			rigidBody->SetLinearVelocity(Forward.x, Forward.y, -Forward.z);

			I_Key = true;
		}
		else if (I_Key)
		{
			rigidBody->SetLinearVelocity(zeroMovement, 0, 0);
			I_Key = false;

			cout << "char pos : (" 
				<< trans->GetPosition().x << ", "
				<< trans->GetPosition().y << ", "
				<< trans->GetPosition().z << ")" << endl;
		}

		if (InputMgr->KeyDown('K', false))
		{
			Input = true;
			skinnedMesh->SetAnimation("Walk");

			Vec3 Backword = -GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			Backword *= 5000;


			rigidBody->SetLinearVelocity(Backword.x, Backword.y, -Backword.z);

			K_Key = true;
		}
		else if (K_Key)
		{
			rigidBody->SetLinearVelocity(0, 0, zeroMovement);
			K_Key = false;

			cout << "char pos : (" << trans->GetPosition().x << ", "
				<< trans->GetPosition().y << ", "
				<< trans->GetPosition().z << ")" << endl;
		}

		if (InputMgr->KeyDown('J', false))
		{
			Input = true;
			skinnedMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody->SetAngularVelocity(0, -1.0f, 0);

			J_Key = true;
		}
		else if (J_Key)
		{
			rigidBody->SetAngularVelocity(0, 0, 0);
			J_Key = false;
		}

		if (InputMgr->KeyDown('L', false))
		{
			Input = true;
			skinnedMesh->SetAnimation("Walk");

			Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			rigidBody->SetAngularVelocity(0, 1.0f, 0);

			L_Key = true;
		}
		else if (L_Key)
		{
			rigidBody->SetAngularVelocity(0, 0, 0);
			L_Key = false;
		}

		if (Input == false)
		{
			skinnedMesh->SetAnimation("Idle");
		}

		//GET_TRANSFORM_3D(gameObject)->SetPosition(trans->GetPosition());
	}

	void GameCharecter::LateUpdate()
	{
	}
}