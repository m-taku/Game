#pragma once
#include "Level.h"
#include"Pasu.h"
#include"keiroK.h"
#include"Geizi.h"
#include"Player.h"
#include"Stage.h"
#include"camera.h"
#include"item.h"
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
	Fade* m_Fade;
	Geizi* gaizi;
	Player* player;
	Stage* stge;
	camera* camera1;
	Level m_level[10];
	Pasu  pasu;
	keiroK* keiro;
	int a = 2;
	int stag = 0;					//レベル。

	int da[4][11] = { { 26,25,17,16,15,14,19,18,24,28,27 }
		,{ 22,29,28,31,36,35,32,27,26,25,23 },
	{ 14,15,16,17,18,19,20,23,24,18,19 },
	{ 6,20,18,19,14,13,11,10,9,8,7 } };
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
	int Gatpasusaiz(int i) const
	{
		return  pasu2[i].size();
	}
	std::vector<int>::iterator getDate(int i) {
		return pasu2[i].begin();
	}
private:
	void InitSceneLight();
	int No = 0;
	std::vector<int> movepasu1 = { 17,12,6,5,13,16,33,36,44,43,42,41,39,30,28,27 };
	std::vector<int> movepasu2 = { 11,18,22,21,29,40,48,47,46,45,35,34,15,14,4,3 };
	std::vector<int> movepasu3 = {5,6,11,18,23,24,15,14};
	std::vector<std::vector<int>> pasu2;
	//{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }

	//{ 18, 11, 7, 8, 10, 19, 30, 39, 41, 42, 43, 44, 36, 33, 25, 26 }
	float g = 0.0f, f = 0.0;
	prefab::CDirectionLight* m_sunLig = nullptr;	//	太陽ライト。
	prefab::CPointLight*     m_point;
	int i = 0;
};

