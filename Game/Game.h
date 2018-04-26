#pragma once
#include "Level.h"
#include"Pasu.h"
#include"keiroK.h"
#include"Geizi.h"
#include"Player.h"
#include"Stage.h"
#include"camera.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class Fade;
class AI;
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
	std::vector<AI*> simin;
	std::vector<AImove*> siminUI;
	Fade* m_Fade;
	Geizi* gaizi;
	Player* player;
	Stage* stge;
	camera* camera1;
	Level m_level[3];
	Pasu  pasu;
	keiroK* keiro;
	int No = 0;
	int da[2][6] = { { 1,4,5,7,10,9}, { 3, 4, 13,15,10,11} };
	int a=2;							//レベル。
private:
	void InitSceneLight();
	float g = 0.0f, f = 0.0;
};

