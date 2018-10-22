#include "BasinMap.h"
#include "SoundManager.h"


namespace CompEngine
{
	void BasinMap::Init()
	{
		gameObject->AddTag("BasinMap");

		gameObject->AddComponent(dynamic_cast<Component*>(&trans));

		wall01 = new GameObject;
		wallTrans01 = new Transform3D;
		wallTrans01->SetPosition(-150, 0, 750);
		wallShape01 = new btBoxShape(btVector3(900 * wallTrans01->GetScale().x,
			500 * wallTrans01->GetScale().y, 100 * wallTrans01->GetScale().z));
		wallScript01 = new Wall(wallTrans01, wallShape01);

		dynamic_cast<Script*>(wallScript01)->SetInfo(wall01, "wallScript01");
		wall01->AddComponent(dynamic_cast<Component*>(wallScript01));
		SceneMgr->CurrentScene()->AddObject(wall01, "Wall01");

		wall02 = new GameObject;
		wallTrans02 = new Transform3D;
		wallTrans02->SetPosition(-150, 0, -650);
		wallShape02 = new btBoxShape(btVector3(900 * wallTrans02->GetScale().x,
			500 * wallTrans02->GetScale().y, 100 * wallTrans02->GetScale().z));
		wallScript02 = new Wall(wallTrans02, wallShape02);

		dynamic_cast<Script*>(wallScript02)->SetInfo(wall02, "wallScript02");
		wall02->AddComponent(dynamic_cast<Component*>(wallScript02));
		SceneMgr->CurrentScene()->AddObject(wall02, "Wall02");

		wall03 = new GameObject;
		wallTrans03 = new Transform3D;
		wallTrans03->SetPosition(-950, 0, 50);
		wallShape03 = new btBoxShape(btVector3(100 * wallTrans03->GetScale().x,
			500 * wallTrans03->GetScale().y, 600 * wallTrans03->GetScale().z));
		wallScript03 = new Wall(wallTrans03, wallShape03);

		dynamic_cast<Script*>(wallScript03)->SetInfo(wall03, "wallScript03");
		wall03->AddComponent(dynamic_cast<Component*>(wallScript03));
		SceneMgr->CurrentScene()->AddObject(wall03, "Wall03");

		wall04 = new GameObject;
		wallTrans04 = new Transform3D;
		wallTrans04->SetPosition(650, 0, 50);
		wallShape04 = new btBoxShape(btVector3(100 * wallTrans04->GetScale().x,
			500 * wallTrans04->GetScale().y, 600 * wallTrans04->GetScale().z));
		wallScript04 = new Wall(wallTrans04, wallShape04);

		dynamic_cast<Script*>(wallScript04)->SetInfo(wall04, "wallScript04");
		wall04->AddComponent(dynamic_cast<Component*>(wallScript04));
		SceneMgr->CurrentScene()->AddObject(wall04, "Wall04");

		wall05 = new GameObject;
		wallTrans05 = new Transform3D;
		wallTrans05->SetPosition(450, 0, 550);
		wallShape05 = new btBoxShape(btVector3(100 * wallTrans05->GetScale().x,
			500 * wallTrans05->GetScale().y, 100 * wallTrans05->GetScale().z));
		wallScript05 = new Wall(wallTrans05, wallShape05);

		dynamic_cast<Script*>(wallScript05)->SetInfo(wall05, "wallScript05");
		wall05->AddComponent(dynamic_cast<Component*>(wallScript05));
		SceneMgr->CurrentScene()->AddObject(wall05, "Wall05");

		wall06 = new GameObject;
		wallTrans06 = new Transform3D;
		wallTrans06->SetPosition(-700, 0, 550);
		wallShape06 = new btBoxShape(btVector3(150 * wallTrans06->GetScale().x,
			500 * wallTrans06->GetScale().y, 100 * wallTrans06->GetScale().z));
		wallScript06 = new Wall(wallTrans06, wallShape06);

		dynamic_cast<Script*>(wallScript06)->SetInfo(wall06, "wallScript06");
		wall06->AddComponent(dynamic_cast<Component*>(wallScript06));
		SceneMgr->CurrentScene()->AddObject(wall06, "Wall06");

	}

	void BasinMap::Reference()
	{
		trans.SetPosition(0, 0, 0);
		mapMesh.SetFilePath(".\\Resources\\Basin.x");
		gameObject->AddComponent(dynamic_cast<Component*>(&mapMesh));
	}

	void BasinMap::Update()
	{
		if (SceneMgr->CurrentScene()->GetName() == "basinScene" &&
			!SoundMgr->IsPlaying2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3"))
		{
			SoundMgr->Play2D(".\\Resources\\Sounds\\bensound-acousticbreeze.mp3", .5f, true);
		}
	}

	void BasinMap::LateUpdate()
	{
	}
}