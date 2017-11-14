#include "Lucy.h"

namespace CompEngine
{
	Lucy::Lucy()
	{
		Info.position = new D3DXVECTOR3(0, 0, 0);
		Info.skinnedMesh = new SkinnedMesh;
		Info.xFilePath = ".\\Resources\\Lucy.X ";
		Info.skinnedMesh->Load(Info.xFilePath);
	}

	Lucy::~Lucy()
	{
	}

	void Lucy::InitMembers()
	{
	}

	void Lucy::Render()
	{
		//cout << "deltaTime in main.cpp / Render() / lucy->Render() : " << TimeMgr->GetTime() << endl;	// 로그 출력
		DeviceMgr->GetDevice()->SetTransform(D3DTS_WORLD, &Info.localMat);
		Info.skinnedMesh->SetAnimation("Idle");
		Info.skinnedMesh->UpdateAnimation();
		Info.skinnedMesh->Render(NULL);
	}

	void Lucy::Release()
	{
		DeviceMgr->ReleaseMembers();
		delete &Info;
	}
}