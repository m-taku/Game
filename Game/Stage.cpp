#include "stdafx.h"
#include "Stage.h"
#include"Game.h"


Stage::Stage()
{
}


Stage::~Stage()
{
}
void Stage::OnDestroy()
{
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
}
bool Stage::Start()
{
	No = FindGO<Game>("Game")->stag;
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath,L"modelData/stage%d.cmo", No);
	m_skinModelData.Load(moveFilePath);
	m_skinModel.Init(m_skinModelData);
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero;
	rbInfo.rot = CQuaternion::Identity;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//質量を0にすると動かない剛体になる。
												//背景などの動かないオブジェクトは0を設定するとよい。
	m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
	PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
	return true;
}
void Stage::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
}
void Stage::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}