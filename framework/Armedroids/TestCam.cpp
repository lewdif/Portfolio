#include "TestCam.h"
#include "InputManager.h"

namespace CompEngine
{
	void TestCam::Init()
	{
		gameObject->AddTag("TestCam");
		mainCamUpVec = Vec3(0.0f, 1.0f, 0.0f);

		//mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_PERSPACTIVE,
		//	Vec3(0, 1, 0), DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 2000, 0.1f, D3DX_PI * 0.6f);

		mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
			DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, 10, D3DX_PI * 0.6f);
	}

	void TestCam::Reference()
	{
		cameraTrans = GET_TRANSFORM_3D(gameObject);

		gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));

		if ((Camera*)SceneMgr->CurrentScene()->GetCurrentCamera() != mainCamera)
		{
			SceneMgr->CurrentScene()->SetCameraIndex(0);
			cout << "Camera setting completed." << endl;
		}
	}

	void TestCam::Update()
	{
		//cout << mainCamera->GetProjectionType() << endl;
	}

	void TestCam::LateUpdate()
	{
		// Eye
		cameraTrans->SetPosition(Vec3(1, 600, 0));
		// Target
		mainCamera->SetTargetPosition(Vec3(0, 0, 0));

		mainCamera->FixedUpdate(gameObject);
	}
}