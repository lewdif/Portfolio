#include "TutorialMap.h"
#include "SoundManager.h"

namespace CompEngine
{
	void TutorialMap::Init()
	{
		gameObject->AddTag("TutorialMap");

		if (!gameObject->GetComponent("Transform3D"))
		{
			gameObject->AddComponent(dynamic_cast<Component*>(&trans));
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall01"))
		{
			wall01 = new GameObject;
			wallTrans01 = new Transform3D;
			wallTrans01->SetPosition(-1950, 0, 800);
			wallShape01 = new btBoxShape(btVector3(1100 * wallTrans01->GetScale().x,
				500 * wallTrans01->GetScale().y, 50 * wallTrans01->GetScale().z));
			wallScript01 = new Wall(wallTrans01, wallShape01);

			dynamic_cast<Script*>(wallScript01)->SetInfo(wall01, "wallScript01");
			wall01->AddComponent(dynamic_cast<Component*>(wallScript01));
			SceneMgr->CurrentScene()->AddObject(wall01, "Wall01");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall02"))
		{
			wall02 = new GameObject;
			wallTrans02 = new Transform3D;
			wallTrans02->SetPosition(-2450, 0, 700);
			wallShape02 = new btBoxShape(btVector3(300 * wallTrans02->GetScale().x,
				500 * wallTrans02->GetScale().y, 50 * wallTrans02->GetScale().z));
			wallScript02 = new Wall(wallTrans02, wallShape02);

			dynamic_cast<Script*>(wallScript02)->SetInfo(wall02, "wallScript02");
			wall02->AddComponent(dynamic_cast<Component*>(wallScript02));
			SceneMgr->CurrentScene()->AddObject(wall02, "Wall02");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall03"))
		{
			wall03 = new GameObject;
			wallTrans03 = new Transform3D;
			wallTrans03->SetPosition(-3000, 0, 350);
			wallShape03 = new btBoxShape(btVector3(50 * wallTrans03->GetScale().x,
				500 * wallTrans03->GetScale().y, 400 * wallTrans03->GetScale().z));
			wallScript03 = new Wall(wallTrans03, wallShape03);

			dynamic_cast<Script*>(wallScript03)->SetInfo(wall03, "wallScript03");
			wall03->AddComponent(dynamic_cast<Component*>(wallScript03));
			SceneMgr->CurrentScene()->AddObject(wall03, "Wall03");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall04"))
		{
			wall04 = new GameObject;
			wallTrans04 = new Transform3D;
			wallTrans04->SetPosition(-2900, 0, -350);
			wallShape04 = new btBoxShape(btVector3(50 * wallTrans04->GetScale().x,
				500 * wallTrans04->GetScale().y, 400 * wallTrans04->GetScale().z));
			wallScript04 = new Wall(wallTrans04, wallShape04);

			dynamic_cast<Script*>(wallScript04)->SetInfo(wall04, "wallScript04");
			wall04->AddComponent(dynamic_cast<Component*>(wallScript04));
			SceneMgr->CurrentScene()->AddObject(wall04, "Wall04");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall05"))
		{
			wall05 = new GameObject;
			wallTrans05 = new Transform3D;
			wallTrans05->SetPosition(-1500, 0, -700);
			wallShape05 = new btBoxShape(btVector3(1450 * wallTrans05->GetScale().x,
				500 * wallTrans05->GetScale().y, 50 * wallTrans05->GetScale().z));
			wallScript05 = new Wall(wallTrans05, wallShape05);

			dynamic_cast<Script*>(wallScript05)->SetInfo(wall05, "wallScript05");
			wall05->AddComponent(dynamic_cast<Component*>(wallScript05));
			SceneMgr->CurrentScene()->AddObject(wall05, "Wall05");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall06"))
		{
			wall06 = new GameObject;
			wallTrans06 = new Transform3D;
			wallTrans06->SetPosition(-2350, 0, 100);
			wallShape06 = new btBoxShape(btVector3(300 * wallTrans06->GetScale().x,
				500 * wallTrans06->GetScale().y, 50 * wallTrans06->GetScale().z));
			wallScript06 = new Wall(wallTrans06, wallShape06);

			dynamic_cast<Script*>(wallScript06)->SetInfo(wall06, "wallScript06");
			wall06->AddComponent(dynamic_cast<Component*>(wallScript06));
			SceneMgr->CurrentScene()->AddObject(wall06, "Wall06");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall07"))
		{
			wall07 = new GameObject;
			wallTrans07 = new Transform3D;
			wallTrans07->SetPosition(-2100, 0, 0);
			wallShape07 = new btBoxShape(btVector3(350 * wallTrans07->GetScale().x,
				500 * wallTrans07->GetScale().y, 50 * wallTrans07->GetScale().z));
			wallScript07 = new Wall(wallTrans07, wallShape07);

			dynamic_cast<Script*>(wallScript07)->SetInfo(wall07, "wallScript07");
			wall07->AddComponent(dynamic_cast<Component*>(wallScript07));
			SceneMgr->CurrentScene()->AddObject(wall07, "Wall07");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall08"))
		{
			wall08 = new GameObject;
			wallTrans08 = new Transform3D;
			wallTrans08->SetPosition(-1500, 0, -100);
			wallShape08 = new btBoxShape(btVector3(350 * wallTrans08->GetScale().x,
				500 * wallTrans08->GetScale().y, 50 * wallTrans08->GetScale().z));
			wallScript08 = new Wall(wallTrans08, wallShape08);

			dynamic_cast<Script*>(wallScript08)->SetInfo(wall08, "wallScript08");
			wall08->AddComponent(dynamic_cast<Component*>(wallScript08));
			SceneMgr->CurrentScene()->AddObject(wall08, "Wall08");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall09"))
		{
			wall09 = new GameObject;
			wallTrans09 = new Transform3D;
			wallTrans09->SetPosition(-1550, 0, -600);
			wallShape09 = new btBoxShape(btVector3(300 * wallTrans09->GetScale().x,
				500 * wallTrans09->GetScale().y, 50 * wallTrans09->GetScale().z));
			wallScript09 = new Wall(wallTrans09, wallShape09);

			dynamic_cast<Script*>(wallScript09)->SetInfo(wall09, "wallScript09");
			wall09->AddComponent(dynamic_cast<Component*>(wallScript09));
			SceneMgr->CurrentScene()->AddObject(wall09, "Wall09");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall10"))
		{
			wall10 = new GameObject;
			wallTrans10 = new Transform3D;
			wallTrans10->SetPosition(-850, 0, 700);
			wallShape10 = new btBoxShape(btVector3(100 * wallTrans10->GetScale().x,
				500 * wallTrans10->GetScale().y, 50 * wallTrans10->GetScale().z));
			wallScript10 = new Wall(wallTrans10, wallShape10);

			dynamic_cast<Script*>(wallScript10)->SetInfo(wall10, "wallScript10");
			wall10->AddComponent(dynamic_cast<Component*>(wallScript10));
			SceneMgr->CurrentScene()->AddObject(wall10, "Wall10");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall11"))
		{
			wall11 = new GameObject;
			wallTrans11 = new Transform3D;
			wallTrans11->SetPosition(-800, 0, 550);
			wallShape11 = new btBoxShape(btVector3(50 * wallTrans11->GetScale().x,
				500 * wallTrans11->GetScale().y, 100 * wallTrans11->GetScale().z));
			wallScript11 = new Wall(wallTrans11, wallShape11);

			dynamic_cast<Script*>(wallScript11)->SetInfo(wall11, "wallScript11");
			wall11->AddComponent(dynamic_cast<Component*>(wallScript11));
			SceneMgr->CurrentScene()->AddObject(wall11, "Wall11");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall12"))
		{
			wall12 = new GameObject;
			wallTrans12 = new Transform3D;
			wallTrans12->SetPosition(-850, 0, 350);
			wallShape12 = new btBoxShape(btVector3(100 * wallTrans12->GetScale().x,
				500 * wallTrans12->GetScale().y, 100 * wallTrans12->GetScale().z));
			wallScript12 = new Wall(wallTrans12, wallShape12);

			dynamic_cast<Script*>(wallScript12)->SetInfo(wall12, "wallScript12");
			wall12->AddComponent(dynamic_cast<Component*>(wallScript12));
			SceneMgr->CurrentScene()->AddObject(wall12, "Wall12");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall13"))
		{
			wall13 = new GameObject;
			wallTrans13 = new Transform3D;
			wallTrans13->SetPosition(-1000, 0, 200);
			wallShape13 = new btBoxShape(btVector3(150 * wallTrans13->GetScale().x,
				500 * wallTrans13->GetScale().y, 50 * wallTrans13->GetScale().z));
			wallScript13 = new Wall(wallTrans13, wallShape13);

			dynamic_cast<Script*>(wallScript13)->SetInfo(wall13, "wallScript13");
			wall13->AddComponent(dynamic_cast<Component*>(wallScript13));
			SceneMgr->CurrentScene()->AddObject(wall13, "Wall13");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall14"))
		{
			wall14 = new GameObject;
			wallTrans14 = new Transform3D;
			wallTrans14->SetPosition(-1150, 0, 50);
			wallShape14 = new btBoxShape(btVector3(100 * wallTrans14->GetScale().x,
				500 * wallTrans14->GetScale().y, 100 * wallTrans14->GetScale().z));
			wallScript14 = new Wall(wallTrans14, wallShape14);

			dynamic_cast<Script*>(wallScript14)->SetInfo(wall14, "wallScript14");
			wall14->AddComponent(dynamic_cast<Component*>(wallScript14));
			SceneMgr->CurrentScene()->AddObject(wall14, "Wall14");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall15"))
		{
			wall15 = new GameObject;
			wallTrans15 = new Transform3D;
			wallTrans15->SetPosition(-650, 0, -200);
			wallShape15 = new btBoxShape(btVector3(600 * wallTrans15->GetScale().x,
				500 * wallTrans15->GetScale().y, 50 * wallTrans15->GetScale().z));
			wallScript15 = new Wall(wallTrans15, wallShape15);

			dynamic_cast<Script*>(wallScript15)->SetInfo(wall15, "wallScript15");
			wall15->AddComponent(dynamic_cast<Component*>(wallScript15));
			SceneMgr->CurrentScene()->AddObject(wall15, "Wall15");
		}

		if (!SceneMgr->CurrentScene()->FindObjectByName("Wall16"))
		{
			wall16 = new GameObject;
			wallTrans16 = new Transform3D;
			wallTrans16->SetPosition(0, 0, -400);
			wallShape16 = new btBoxShape(btVector3(50 * wallTrans16->GetScale().x,
				500 * wallTrans16->GetScale().y, 250 * wallTrans16->GetScale().z));
			wallScript16 = new Wall(wallTrans16, wallShape16);

			dynamic_cast<Script*>(wallScript16)->SetInfo(wall16, "wallScript16");
			wall16->AddComponent(dynamic_cast<Component*>(wallScript16));
			SceneMgr->CurrentScene()->AddObject(wall16, "Wall16");
		}
	}

	void TutorialMap::Reference()
	{
		trans.SetPosition(0, 0, 0);

		if (!gameObject->GetComponent("StaticMesh"))
		{
			mapMesh.SetFilePath(".\\Resources\\Tutorial.x");
			gameObject->AddComponent(dynamic_cast<Component*>(&mapMesh));
		}
	}

	void TutorialMap::Update()
	{
		if (SceneMgr->CurrentScene()->GetName() == "inGameScene" &&
			!SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3"))
		{
			SoundMgr->Play2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3", .5f, true);
		}
	}

	void TutorialMap::LateUpdate()
	{
	}
}