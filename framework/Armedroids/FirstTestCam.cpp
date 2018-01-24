#include "FirstTestCam.h"
#include "InputManager.h"

namespace CompEngine
{
	void FirstTestCam::Init()
	{
		gameObject->AddTag("MainCam");
		mouseX = 0;
		mouseY = 0;
		//curTarPos = Vec3(0, 0, 0);
	}


	void FirstTestCam::Reference()
	{
		mainCamObj = new GameObject();
		Vec3 mainCamUpVec(0.0f, 1.0f, 0.0f);

		Transform3D* tr = new Transform3D();
		tr->SetPosition(0.0f, 200.0f, -500.0f);
		mainCamObj->AddComponent(tr);
		cameraTrans = tr;

		Camera *camera = new Camera(0, PROJECTION_TYPE::PROJECTION_ORTHOGONAL, mainCamUpVec,
		DeviceMgr->GetWidth(), DeviceMgr->GetHeight(), 3000, -250, D3DX_PI * 0.6f);

		//camera->SetTargetPosition(((Transform3D*)gameObject->transform3D)->GetPosition());
		mainCamObj->AddComponent(camera);
		//mainCamObj->AddComponent(cameraTrans);
		mainCamera = camera;
		
		SceneMgr->CurrentScene()->AddComponent(mainCamObj, "MainCamera");
		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(cameraTrans->GetPosition());
		gameObject->AddComponent(dynamic_cast<Component*>(mainCamera));
	}

	void FirstTestCam::Update()
	{
		/*bool Input = false;

		static bool W_Key = false;
		static bool S_Key = false;
		static bool A_Key = false;
		static bool D_Key = false;

		if (InputMgr->KeyDown('W', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() - Vec3(0, 0, 10));

			curTarPos -= Vec3(0, 0, 10);
			Vec3 Forward = GetTransform3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
			<< temp.y << ", " << temp.z << endl;

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

			curTarPos += Vec3(0, 0, 10);
			Vec3 Forward = GetTransform3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;

			S_Key = true;
		}
		else if (S_Key)
		{
			S_Key = false;
		}

		if (InputMgr->KeyDown('A', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() + Vec3(10, 0, 0));

			curTarPos += Vec3(10, 0, 0);
			Vec3 Forward = GetTransform3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;

			A_Key = true;
		}
		else if (A_Key)
		{
			A_Key = false;
		}

		if (InputMgr->KeyDown('D', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() - Vec3(10, 0, 0));

			curTarPos -= Vec3(10, 0, 0);
			Vec3 Forward = GetTransform3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;

			D_Key = true;
		}
		else if (D_Key)
		{
			D_Key = false;
		}

		if (Input == false)
		{
		}*/

		//mainCamera->SetTargetPosition(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
		mainCamera->SetTargetPosition(curTarPos);
		Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
		//cout << "cur cam pos : " << curTarPos.x << ", " << curTarPos.y << ", " << curTarPos.z << endl;
		//((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(cameraTrans->GetPosition());
		/*cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
			<< temp.y << ", " << temp.z << endl;*/
		//cout << curTarPos.x << ", " << curTarPos.y << ", " << curTarPos.z << endl;
	}

	void FirstTestCam::LateUpdate()
	{
		/*POINT pt;
		float fDelta = 0.001f; // 마우스의 민감도, 이 값이 커질수록 많이 움직인다.

		GetCursorPos(&pt);
		int dx = pt.x - mouseX;
		int dy = pt.y - mouseY;*/
		/*
		Vec3 Target = GetTransform3D(gameObject)->GetPosition() + Vec3(0, 25, 0);
		Vec3 Eye = GetTransform3D(mainCamObj)->GetPosition();

		Vec3 Dir = Eye - Target;

		Vec3 YRotatePos = Target;

		Matrix YMat;
		D3DXMatrixRotationY(&YMat, dx * fDelta);
		D3DXVec3TransformCoord(&YRotatePos, &Dir, &YMat);

		Vec3 Cross;
		D3DXVec3Normalize(&Dir, &Dir);
		D3DXVec3Cross(&Cross, &Dir, &Vec3(0, 1, 0));
		D3DXVec3Normalize(&Cross, &Cross);

		Vec3 FinalPos;

		Matrix CrossMat;
		D3DXMatrixRotationAxis(&CrossMat, &Cross, dy * fDelta);
		D3DXVec3TransformCoord(&FinalPos, &YRotatePos, &CrossMat);
		D3DXVec3Normalize(&FinalPos, &FinalPos);
		FinalPos *= 15;

		pt.x = (DeviceMgr->GetWidth()) / 2;
		pt.y = (DeviceMgr->GetHeight()) / 2;

		SetCursorPos(pt.x, pt.y);
		mouseX = pt.x;
		mouseY = pt.y;*/
		
		//mainCamera->SetTargetPosition(Target);
		//cameraTrans->SetPosition(FinalPos + Target);
		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(cameraTrans->GetPosition());

		//mainCamera->SetTargetPosition(curTarPos + Vec3(0, 10, 0));
		Vec3 temp = mainCamera->GetTargetPosition();
		//cout << temp.x << ", " << temp.y << ", " << temp.z << endl;

		mainCamera->FixedUpdate(mainCamObj);
	}
}