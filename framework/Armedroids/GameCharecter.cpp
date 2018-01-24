#include "GameCharecter.h"
#include "InputManager.h"


namespace CompEngine
{
	void GameCharecter::Init()
	{
		gameObject->AddTag("Player");
		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetScale(0.1f, 0.1f, 0.1f);
		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(0, 0, 0);
	}

	void GameCharecter::Reference()
	{
		skinnedMesh = ((SkinnedMesh*)gameObject->GetComponent("SkinnedMesh"));
		trans = (Transform3D*)gameObject->GetComponent("Transform3D");
	}

	void GameCharecter::Update()
	{
		bool Input = false;

		static bool W_Key = false;
		if (InputMgr->KeyDown('W', false))
		{
			Input = true;
			skinnedMesh->SetAnimation("Walk");
			Vec3 Forward = GetTransform3D(gameObject)->GetForward() * SceneMgr->GetTimeDelta();

			trans->SetPosition(trans->GetPosition() + Vec3(0, 10, 0));

			Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			cout << temp.x << ", " << temp.y << ", " << temp.z << endl;
			
			W_Key = true;
		}
		else if (W_Key)
		{
			//GET_RIGIDBODY(gameObject)->SetLinearVelocity(0, 0, 0);
			W_Key = false;
		}

		if (Input == false)
		{
			skinnedMesh->SetAnimation("Idle");
		}

		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(trans->GetPosition());
	}

	void GameCharecter::LateUpdate()
	{
	}
}