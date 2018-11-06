#include "FirstTestCam.h"
#include "InputManager.h"

namespace CompEngine
{
	void FirstTestCam::Init()
	{
		gameObject->AddTag("MainCam");
		mainCamUpVec = Vec3(0.0f, 1.0f, 0.0f);

		//mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_PERSPACTIVE,
		//	Vec3(0, 1, 0), DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 2000, 0.1f, D3DX_PI * 0.6f);

		if (!gameObject->GetComponent("Transform3D"))
		{
			cameraTrans = new Transform3D;
			gameObject->AddComponent(dynamic_cast<Component*>(cameraTrans));
		}

		if (mainCamera == nullptr)
		{
			mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
				DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, -1000, D3DX_PI * 0.6f);
		}
	}

	void FirstTestCam::Reference()
	{
		TargetTrans = GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByName("Player"));

		if (!gameObject->GetComponent("Camera"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));
		}

		if ((Camera*)SceneMgr->CurrentScene()->GetCurrentCamera() != mainCamera)
		{
			SceneMgr->CurrentScene()->SetCameraIndex(0);
			cout << "Camera setting completed." << endl;
		}
	}

	void FirstTestCam::Update() 
	{
	}

	void FirstTestCam::LateUpdate()
	{
		// Eye
		cameraTrans->SetPosition(TargetTrans->GetPosition() + Vec3(1000, 1000, -1000));
		// Target
		//mainCamera->SetTargetPosition(Vec3(0,0,0));
		mainCamera->SetTargetPosition(TargetTrans->GetPosition());

		mainCamera->FixedUpdate(gameObject);
	}
}