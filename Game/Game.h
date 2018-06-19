#pragma once
#include "Level.h"
#include"keiroK.h"
#include"Geizi.h"
#include"Player.h"
#include"Stage.h"
#include"camera.h"
#include"item.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class Fade;
class AI;
class car;
class AImove;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void OnDestroy();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CAnimationClip m_animClip[1];							//アニメーションクリップ。
	CAnimation m_animation;
	CVector3 m_pos = CVector3::Zero;
	Fade* m_Fade;
	Geizi* gaizi;
	Player* player;
	camera* camera1;
	keiroK* keiro;
	int a = 2;
	int stag = 0;					//レベル。
	int incNo()
	{
		return No++;
	}
	int GatNo()
	{
		return No;
	}
	void risetteNo()
	{
		No = 0;
	}
	
	
private:
	void InitSceneLight();

	int No = 0;
	//{ 18, 11, 7, 8, 10, 19, 30, 39, 41, 42, 43, 44, 36, 33, 25, 26 }
	float g = 0.0f, f = 0.0;
	int i = 0;
};