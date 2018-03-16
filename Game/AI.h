#pragma once
#include"Human.h"
class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
};

