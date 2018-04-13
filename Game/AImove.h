#pragma once
#define KOSUU 2
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start() override;
	void Update() override;
	void Render(CRenderContext& rc);
	void kyorikeisan(int bangou);
	CSkinModel m_skinModel[KOSUU];					//スキンモデル。
	CSkinModelData m_skinModelData[KOSUU];			//スキンモデルデータ。
	CVector3 iin[KOSUU];
	float in[KOSUU];
	int Size[KOSUU];
	int j = 0;
	CVector3 bekutor[KOSUU];
	float K[KOSUU];
	int Fream[KOSUU];
	int Flag[KOSUU];
	int No[10000];
	int hugo = 1;
	int ima= 0;
	int kosuu[KOSUU] = {};
	Game* game;
};

