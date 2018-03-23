#pragma once


#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 

#include <strsafe.h>
#pragma warning( default : 4996 )

#include <d3dx9.h>

#pragma warning(disable:4786)	// to reduce STL warning

#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;

// Bullet Physics
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

//static double deltaTime;

#define Mesh LPD3DXMESH
#define Color D3DCOLOR
#define Matrix D3DXMATRIX
#define Vec2 D3DXVECTOR2
#define Vec3 D3DXVECTOR3
#define Quater D3DXQUATERNION

#define S_DEL(p) { if(p) delete p; p = NULL; }
#define S_DELS(p) { if(p) delete[] p; }
#define S_DEL_ARR(p) {if(p) {delete[](p); (p)=NULL;}}
#define S_REL(p) { if ( (p) ) { (p)->Release(); (p) = 0; } }
#define MAX_STR_LEN 128

#define DeviceMgr DeviceManager::GetInstance()
#define SceneMgr SceneManager::GetInstance()
#define InputMgr InputManager::GetInstance()

#define GET_TRANSFORM_3D(Object) ((Transform3D*)Object->transform3D)
//#define GET_COLLISION(Object)    ((CompEngine::Collision*)Object->GetComponent("Collision"))
//#define GET_RIGIDBODY(Object)    ((RigidBody*)Object->GetComponent("RigidBody"))
//#define GET_SKINNED_MESH(Object) ((SkinnedMesh*)Object->GetComponent("SkinnedMesh"))