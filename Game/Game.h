#pragma once
#include "Level.h"
#include"Pasu.h"
#include"keiroK.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class Fade;
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
	Level m_level[3];
	Pasu pasu[3];
	keiroK keiro;
	int a=2;							//レベル。
private:
	void InitSceneLight();
	float g = 0.0f, f = 0.0;
};

