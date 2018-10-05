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
		
		mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
			DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, -250, D3DX_PI * 0.6f);
	}

	void FirstTestCam::Reference()
	{
		cameraTrans = GET_TRANSFORM_3D(gameObject);
		TargetTrans = GET_TRANSFORM_3D(SceneMgr->CurrentScene()->FindObjectByName("Player"));

		gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));

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
		cameraTrans->SetPosition(TargetTrans->GetPosition() + Vec3(300, 300, 0));
		// Target
		mainCamera->SetTargetPosition(TargetTrans->GetPosition());

		mainCamera->FixedUpdate(gameObject);
	}
}