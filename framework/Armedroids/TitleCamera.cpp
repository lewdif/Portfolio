#include "TitleCamera.h"
#include "InputManager.h"


namespace CompEngine
{
	void TitleCamera::Init()
	{
		gameObject->AddTag("TitleCam");
		mainCamUpVec = Vec3(0.0f, 1.0f, 0.0f);

		cameraTrans = new Transform3D;
		gameObject->AddComponent(dynamic_cast<Component*>(cameraTrans));

		mainCamera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
			DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, -1000, D3DX_PI * 0.6f);
	}

	void TitleCamera::Reference()
	{
		gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));

		if ((Camera*)SceneMgr->CurrentScene()->GetCurrentCamera() != mainCamera)
		{
			SceneMgr->CurrentScene()->SetCameraIndex(0);
			cout << "Camera setting completed." << endl;
		}
	}

	void TitleCamera::Update()
	{
	}

	void TitleCamera::LateUpdate()
	{
		// Eye
		cameraTrans->SetPosition(1000, 1000, -1000);
		// Target
		mainCamera->SetTargetPosition(0, 0, 0);

		mainCamera->FixedUpdate(gameObject);
	}
}