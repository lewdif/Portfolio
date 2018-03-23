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
		curPos = Vec3(0, 30, 50);
		curTargetPos = Vec3(0, 0, 0);

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

		cout << "gameObj name : " << gameObject->GetName() << endl;
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

			cameraTrans->SetPosition(cameraTrans->GetPosition() - Vec3(0, 10, 0));

			//curPos -= Vec3(0, 10, 0);
			//curTargetPos -= Vec3(0, 10, 0);

			//Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			/*cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
			<< temp.y << ", " << temp.z << endl;*/

			W_Key = true;
		}
		else if (W_Key)
		{
			W_Key = false;
		}

		if (InputMgr->KeyDown('S', false))
		{
			Input = true;

			cameraTrans->SetPosition(cameraTrans->GetPosition() + Vec3(0, 10, 0));

			//curPos += Vec3(0, 10, 0);
			//curTargetPos += Vec3(0, 10, 0);
			//Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			/*cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;*/

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

			//curPos -= Vec3(10, 0, 0);
			//curTargetPos -= Vec3(10, 0, 0);
			//Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			/*cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;*/

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
			//curTargetPos += Vec3(10, 0, 0);
			//Vec3 Forward = GET_TRANSFORM_3D(gameObject)->GetForward();

			//Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
			Vec3 temp = mainCamera->GetTargetPosition();

			/*cout << "((Transform3D*)gameObject->GetPosition() : " << temp.x << ", "
				<< temp.y << ", " << temp.z << endl;*/

			D_Key = true;
		}
		else if (D_Key)
		{
			D_Key = false;
		}

		if (Input == false)
		{
		}

		SetTargetPos();
		//mainCamera->SetTargetPosition(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());
		//mainCamera->SetTargetPosition(curTarPos);
		Vec3 temp(((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition());

		//((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(cameraTrans->GetPosition());
		cout << "Camera position : " << temp.x << ", "
			<< temp.y << ", " << temp.z << endl;
	}

	void FirstTestCam::LateUpdate()
	{
		POINT pt;
		float fDelta = 0.001f; // 마우스의 민감도, 이 값이 커질수록 많이 움직인다.

		GetCursorPos(&pt);
		int dx = 1;
		int dy = 1;


		/*cout << ((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().x << ", " <<
			((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().y << ", " <<
			((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().z << ", " << endl;*/
		//cout << "-" << gameObject->GetName() << endl;

		Vec3 Target = curTargetPos;
		// Vec3 Target = GET_TRANSFORM_3D(gameObject)->GetPosition() + Vec3(0, 25, 0);
		Vec3 Eye = GET_TRANSFORM_3D(mainCamObj)->GetPosition();
		/*cout << "Camera pos : (" << Eye.x << ", " << Eye.y << ", " << Eye.z << ")" << ", "
			<< "Camera target pos : (" << curTargetPos.x << ", " << curTargetPos.y << ", " << curTargetPos.z << ")"
			<< endl;*/
		/*
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
		*/
		//pt.x = (DeviceMgr->GetWidth()) / 2;
		//pt.y = (DeviceMgr->GetHeight()) / 2;

		//SetCursorPos(pt.x, pt.y);
		//mouseX = pt.x;
		//mouseY = pt.y;
		//cout << FinalPos.x << ", " << FinalPos.y << ", " << FinalPos.z << endl;
		
		mainCamera->SetTargetPosition(Target);
		((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(Eye);

		/*GameObject* tempCam = SceneMgr->CurrentScene()->GetCurrentCamera();
		((Transform3D*)tempCam->GetComponent("Transform3D"))->SetPosition(Target);
		*/
		/*cout << "SceneMgr cam pos : (" << ((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().x << ", "
			<< ((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().y << ", "
			<< ((Transform3D*)gameObject->GetComponent("Transform3D"))->GetPosition().z << ") "
			<< endl;*/
		//((Transform3D*)gameObject->GetComponent("Transform3D"))->SetPosition(cameraTrans->GetPosition());

		//mainCamera->SetTargetPosition(curTarPos + Vec3(0, 10, 0));
		//Vec3 temp = mainCamera->GetTargetPosition();
		//cout << temp.x << ", " << temp.y << ", " << temp.z << endl;

		mainCamera->FixedUpdate(mainCamObj);
	}

	void FirstTestCam::SetTargetPos()
	{
		GameObject* lucy = SceneMgr->CurrentScene()->FindObjectByName("Lucy");
		curTargetPos = ((Transform3D*)lucy->GetComponent("Transform3D"))->GetPosition();

		cout << "curTargetPos : (" << curTargetPos.x << ", " << curTargetPos.y 
			<< ", " << curTargetPos.z << ")" << endl;
	}
}