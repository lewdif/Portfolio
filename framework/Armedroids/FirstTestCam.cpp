#include "FirstTestCam.h"
#include "InputManager.h"

namespace CompEngine
{
	void FirstTestCam::Init()
	{
		gameObject->AddTag("MainCam");
		mouseX = 0;
		mouseY = 0;
	}


	void FirstTestCam::Reference()
	{
		mainCamObj = new GameObject();
		Vec3 mainCamUpVec(0.0f, 1.0f, 0.0f);
		curPos = Vec3(0, 3000, 500);
		curTargetPos = Vec3(0, 0, 0);

		Transform3D* tr = new Transform3D();
		tr->SetPosition(0.0f, 200.0f, -500.0f);
		mainCamObj->AddComponent(tr);
		cameraTrans = tr;

		Camera *camera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
		DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, -250, D3DX_PI * 0.6f);
		/*
		Camera *camera = new Camera(0, PROJECTION_TYPE::PROJECTION_PERSPACTIVE,
		Vec3(200, 1000, 0), DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 2000, 0.1f, D3DX_PI * 0.6f);
		*/
		//camera->SetTargetPosition(((Transform3D*)gameObject->transform3D)->GetPosition());

		mainCamObj->AddComponent(camera);
		//mainCamObj->AddComponent(cameraTrans);
		mainCamera = camera;
		
		SceneMgr->CurrentScene()->AddComponent(mainCamObj, "MainCamera");
		GET_TRANSFORM_3D(gameObject)->SetPosition(cameraTrans->GetPosition());
		gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));

		gameObject->DebugOut();
	}

	void FirstTestCam::Update()
	{
		bool Input = false;

		static bool W_Key = false;
		static bool S_Key = false;
		static bool A_Key = false;
		static bool D_Key = false;

		if (InputMgr->KeyDown('W', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() - Vec3(0, 0, 10));
			//cameraTrans->SetPosition(Vec3(0, 1000, 0));
			
			W_Key = true;
		}
		else if (W_Key)
		{
			W_Key = false;
		}

		if (InputMgr->KeyDown('S', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() + Vec3(0, 0, 10));

			S_Key = true;
		}
		else if (S_Key)
		{
			S_Key = false;
		}

		if (InputMgr->KeyDown('A', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() - Vec3(10, 0, 0));

			A_Key = true;
		}
		else if (A_Key)
		{
			A_Key = false;
		}

		if (InputMgr->KeyDown('D', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() + Vec3(10, 0, 0));

			curPos += Vec3(10, 0, 0);

			D_Key = true;
		}
		else if (D_Key)
		{
			D_Key = false;
		}

		if (Input == false)
		{
		}

	}

	void FirstTestCam::LateUpdate()
	{
		SetTargetPos();

		Vec3 Target = curTargetPos;
		
		Vec3 Eye = GET_TRANSFORM_3D(mainCamObj)->GetPosition();

		mainCamera->SetTargetPosition(Target);
		GET_TRANSFORM_3D(gameObject)->SetPosition(Eye);

		mainCamera->FixedUpdate(mainCamObj);
	}

	void FirstTestCam::SetTargetPos()
	{
		GameObject* lucy = SceneMgr->CurrentScene()->FindObjectByName("Lucy");
		curTargetPos = ((Transform3D*)lucy->GetComponent("Transform3D"))->GetPosition();

		//curTargetPos = GET_TRANSFORM_3D(mainCamObj)->GetPosition() - Vec3(10, 50, 50);
	}
}