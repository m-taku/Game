#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"

#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CMeshCollider m_meshCollider;	//メッシュコライダー。
	CRigidBody m_rigidBody;			//剛体
	int No = 0;
private:
	CPhysicsStaticObject m_physicsStaticObject;
	CSkinModel s_skinModel;					//スキンモデル。
	CSkinModelData s_skinModelData;			//スキンモデルデータ。
};

