#include "stdafx.h"
#include "Stage.h"
#include"Game.h"
#include"carRender.h"
#include"car.h"
Stage::Stage()
{
}


Stage::~Stage()
{

}
void Stage::OnDestroy()
{
	PhysicsWorld().RemoveRigidBody(m_rigidBody);
	for (int i = 0; i < carv.size(); i++) {
		DeleteGO(carv[i]);
	}
}
bool Stage::Start()
{


	Stege_No = 3;
	//FindGO<Game>("Game")->stag;
	wchar_t moveFilePath[256];//ファイルパス。
	swprintf_s(moveFilePath, L"modelData/stage%d.cmo", Stege_No);//ステージ。
	m_skinModelData.Load(moveFilePath);
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowReceiverFlag(true);
	s_skinModelData.Load(L"modelData/sora.cmo");//空。背景。
	s_skinModel.Init(s_skinModelData);
	////メッシュコライダーを作成。
	m_physicsStaticObject.CreateMeshObject( m_skinModel,CVector3::Zero,CQuaternion::Identity);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 0, 2);
	m_level[0].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 1, 1);
	m_level[1].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 2, 1);
	m_level[2].Build(moveFilePath);
	//carを増やした時のの変更点
	pasu2.push_back(movepasu1);
	pasu2.push_back(movepasu2);
	pasu2.push_back(movepasu3);
	pasu2.push_back(movepasu4);
	pasu2.push_back(movepasu5);
	pasu2.push_back(movepasu6);
	pasu2.push_back(movepasu7);
	pasu2.push_back(movepasu8);
	pasu2.push_back(movepasu9);
	pasu2.push_back(movepasu10);
	pasu2.push_back(movepasu11);
	pasu2.push_back(movepasu12);
	pasu2.push_back(movepasu13);
	pasu2.push_back(movepasu14);
	pasu2.push_back(movepasu15);
	pasu2.push_back(movepasu16);
	pasu2.push_back(movepasu17);
	pasu2.push_back(movepasu18);
	pasu2.push_back(movepasu19);
	pasu2.push_back(movepasu20);
	pasu2.push_back(movepasu21);
	pasu2.push_back(movepasu22);
	pasu2.push_back(movepasu23);
	Car_create();
	return true;
}
void Stage::Update()
{
	m_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);
	s_skinModel.Update(CVector3::Zero, CQuaternion::Identity, CVector3::One);

	SoundEngine().SetListenerPosition(MainCamera().GetPosition());
	CVector3 frontXZ = MainCamera().GetForward();
	frontXZ.y = 0.0f;
	frontXZ.Normalize();
	SoundEngine().SetListenerFront(frontXZ);
}
void Stage::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	s_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
void Stage::Car_create()
{
#ifndef instansingu_katto
	kar = NewGO<carRender>(0, nullptr);
	kar->Satcarkosuu(pasu2.size());
#endif
	for (int i = 0; i < pasu2.size(); i++) {
		carv.push_back(NewGO<car>(0, "car"));
#ifndef  instansingu_katto
		carv[i]->gatcarRender(*kar);
#endif
	}
}
void Stage::Car_delete()
{
	for (int i = 0; i < carv.size(); i++) {
		DeleteGO(carv[i]);
	}
	carv.clear();
	DeleteGO(kar);
}
