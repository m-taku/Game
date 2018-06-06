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
	std::vector<AI*> Rsimin;
	std::vector<AI*> Lsimin;
	Fade* m_Fade;
	Geizi* gaizi;
	Player* player;
	Stage* stge;
	camera* camera1;
	Level m_level[10];
	Pasu  pasu[10];
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
	int Gatpasusaiz(int i) const
	{
		return  pasu2[i].size();
	}
	void SatRSaizon(int No)
	{
		RAIseizon[No] = 0;
	}
	void SatLSaizon(int No)
	{
		LAIseizon[No] = 0;
	}
	void SetLeft()
	{
		Leftfrag = 1;
	}
	int GetLeft()
	{
		return Leftfrag;
	}
	int gatsiz(int No)
	{
		return da[No].size();
	}
	int gatLsiz(int No)
	{
		return da2[No].size();
	}
	std::vector<int>::iterator getDate(int i) {
		return pasu2[i].begin();
	}
	int Getsize(int No)
	{
		return da[No].size();
	}
	std::vector<int>::iterator getAIDate(int i) {
		return da[i].begin();
	}
	std::vector<int>::iterator getLAIDate(int i) {
		return da2[i].begin();
	}
private:
	void InitSceneLight();
	int No = 0;
	int Leftfrag = 0;
	std::vector<int> RAIseizon;
	std::vector<int> LAIseizon;
	std::vector<car*> carv;
	std::vector<int> movepasu1 = { 17,12,6,5,13,16,33,36,44,43,42,41,39,30,28,27 };
	std::vector<int> movepasu2 = { 11,18,22,21,29,40,48,47,46,45,35,34,15,14,4,3 };
	std::vector<int> movepasu3 = { 8,7,11,18,22,21,29,40,48,47,37,32,22,21,19,10 };
	std::vector<int> movepasu4 = { 4,3,11,18,31,38,42,41,39,30,28,27,26,25,15,14 };
	std::vector<int> movepasu5 = { 13,16,24,23,31,38,42,41,39,30,28,27,17,12,6,5 };
	std::vector<int> movepasu6 = { 35,34,24,23,22,21,19,10,8,7,6,5,13,16,24,23,22,21,29,40,48,47,46,45 };
	std::vector<int> movepasu7 = { 44,43,42,41,39,30,19,10,8,7,11,18,26,25,33,36 };
	std::vector<int> movepasu8 = { 28,27,26,25,15,14,4,3,11,18,31,38,46,45,35,34,24,23,22,21,29,40,48,47,37,32,17,12,2,1,9,20 };
	std::vector<int> movepasu9 = { 39,30,19,10,8,7,11,18,26,25,33,36,44,43,42,41 };
	std::vector<int> movepasu10 = { 48,47,37,32,22,21,19,10,8,7,6,5,13,16,24,23,22,21,29,40 };
	std::vector<int> movepasu11 = { 29,40,48,47,46,45,35,34,24,23,31,38,42,41,39,30,28,27,17,12,2,1,9,20 };
	std::vector<int> movepasu12 = { 9,20,29,40,48,47,46,45,35,34,24,23,21,19,10,8,7,6,5,13,16,33,36,44,43,37,32,17,12,2,1 };
	std::vector<int> movepasu13 = { 18,31,38,42,41,39,30,28,27,26,25,33,36,44,43,37,32,17,12,6,5,13,16,33,36,44,43,37,32,26,25,15,14,4,3,11 };
	std::vector<int> movepasu14 = { 24,23,22,21,19,10,8,7,11,18,31,38,42,41,39,30,28,27,26,25,33,36,44,43,42,41,39,30,19,10,8,7,6,5,13,16 };
	std::vector<int> movepasu15 = { 22,21,19,10,8,7,6,5,13,16,33,36,44,43,42,41,39,30,19,10,8,7,11,18 };
	std::vector<int> movepasu16 = { 31,38,46,45,35,34,15,14,4,3,2,1,9,20,29,40,48,47,46,45,35,34,15,14,4,3,11,18 };
	std::vector<int> movepasu17 = { 26,25,33,36,44,43,42,41,39,30,28,27,26,25,15,14,4,3,2,1,9,20,28,27 };
	std::vector<int> movepasu18 = { 37,32,26,25,15,14,4,3,2,1,9,20,28,27,17,12,6,5,13,16,33,36,44,43 };
	std::vector<int> movepasu19 = { 20,29,40,48,47,37,32,26,25,33,36,44,43,37,32,17,12,2,1,9 };
	std::vector<int> movepasu20 = { 27,26,25,15,14,4,3,2,1,9,20,28 };
	std::vector<int> movepasu21 = { 46,45,35,34,24,23,22,21,19,10,8,7,6,5,13,16,24,23,31,38};
	std::vector<int> movepasu22 = { 19,10,8,7,6,5,13,16,24,23,22,21,29,40,48,47,37,32,22,21 };
	std::vector<int> movepasu23 = { 33,36,44,43,37,32,26,25,15,14,4,3,2,1,9,20,29,40,48,47,37,32,17,12,6,5,13,16 };

	std::vector<int> AIR1 = { 26,25,17,16,15,14,19,18,24,28,27 };
	std::vector<int> AIR2 = { 22, 29, 28, 31, 36, 35, 32, 27, 26, 25, 23 };
	std::vector<int> AIR3 = { 14, 15, 16, 17, 18, 19, 20, 23, 24, 18, 19 };
	std::vector<int> AIR4 = { 6, 20, 18, 19, 14, 13, 11, 10, 9, 8, 7 };
	std::vector<int> AIR5 = { 1,2,3,4,5,21,22,29,30,37,38,39,40,41,34,33,26,25,17,16,11,10 };
	std::vector<int> AIR6 = { 2,9,8,7,6,20,18,17,16,11,10,1 };
	std::vector<int> AIR7 = { 3,6,20,21,22,23,24,18,19,20,21,5,4 };
	std::vector<int> AIR8 = { 4,5,21,20,19,14,12,11,10,9,8,7,3 };
	std::vector<int> AIR9 = { 20,23,22,29,28,27,26,25,24,18,19 };
	std::vector<int> AIR10 = { 8,7,6,20,18,17,16,11,10,9};
	std::vector<int> AIR11 = { 12,13,14,15 };
	std::vector<int> AIR12 = { 18,24,23,20,19 };
	std::vector<int> AIR13 = { 29,30,31,36,35,40,41,34,33,26,27,28 };
	std::vector<int> AIR14 = { 37,36,35,32,33,26,27,28,29,30 };
	std::vector<int> AIR15 = { 33,26,27,28,29,30,37,36,31,32 };
	std::vector<int> AIR16 = { 30,37,36,39,40,35,34,33,32,27,28,31 };
	std::vector<int> AIR17 = { 32,33,26,25,17,16,15,14,19,18,24,23,22,29,28,31 };
	std::vector<int> AIR18 = { 38,39,40,35,32,33,26,27,28,31,30,37};
	std::vector<int> AIR19 = { 39,36,31,28,27,32,35,40 };
	std::vector<int> AIR20 = { 7,8,13,14,19,20,23,24,18,19,20,6 };

	std::vector<int> AIL1 = { 48,57,56,52 };
	std::vector<int> AIL2 = { 1,10,11,14,28,29,41,40,39,37,35,36,33,32,25,24,23,6,5,4,3,2 };
	std::vector<int> AIL3 = { 2,3,4,7,20,17,16,15,13,12,12,12,11,10,1 };
	std::vector<int> AIL4 = { 3,22,7,6,5,4};
	std::vector<int> AIL5 = { 4,7,22,3,2,1,10,9,22,3 };
	std::vector<int> AIL6 = { 5,6,7,16,23,6,7,22,8,2,3,4 };
	std::vector<int> AIL7 = { 8,9 };
	std::vector<int> AIL8 = { 10,11,12,12,13,15,24,25,32,31,30,29,28,14,13,15,16,7,22,3,2,1 };
	std::vector<int> AIL9 = { 11,14,28,29,41,40,39,37,35,34,31,26,25,24,15,13,12 };
	std::vector<int> AIL10 = { 13,15,24,25,32,33,34,56,55,48,42,30,29,28,14 };
	std::vector<int> AIL11 = { 14,28,29,41,42,30,31,34,33,32,25,24,15,13};
	std::vector<int> AIL12 = { 15,16,17,19,21,22,3,4,5,6,23,24};
	std::vector<int> AIL13 = { 16,7,6,23 };
	std::vector<int> AIL14= { 17,22,7,7,4,3,2,1,10,11,14,13,15,24,23,16 };
	std::vector<int> AIL15 = { 18,19,20,21,22,9,10,11,12,13,15,16,17 };
	std::vector<int> AIL16 = { 23,24,15,13,14,28,27,30,31,32,33,36,35,37,39,42,41,29,28,27,26,25,24,15,16 };
	std::vector<int> AIL17= { 24,25,32,31,26,27,30,29,28,14,13,16,23 };
	std::vector<int> AIL18 = { 25,32,33,36,35,37,40,41,29,28,27,26 };
	std::vector<int> AIL19 = { 26,31,30,42,41,29,28,27 };


	std::vector<std::vector<int>> da2;
	std::vector<std::vector<int>> da;
	std::vector<std::vector<int>> pasu2;

	std::vector<prefab::CPointLight*> point;
	//{ 18, 11, 7, 8, 10, 19, 30, 39, 41, 42, 43, 44, 36, 33, 25, 26 }
	float g = 0.0f, f = 0.0;
	prefab::CDirectionLight* m_sunLig = nullptr;	//	太陽ライト。
	prefab::CPointLight*     m_point;
	int i = 0;
};
extern Game* game1;