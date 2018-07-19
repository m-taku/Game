#pragma once
class tekihei;
class Player;
#define flash 0.4f
class Geizi : public IGameObject
{
public:
	Geizi();
	~Geizi();
	bool Start();
	void Update();
//	void Render(CRenderContext& rc);

	void PostRender(CRenderContext& rc);
	void satHP(float a)
	{
		HP -= a;
		HP_saiz = HP+ flash;
		Dame = UP; 
		time = 30;
	}
	void Satpoint(float a)
	{
		point += a;
	}
	float GatHP() 
	{
		return HP;
	}
	float GatFragu()
	{
		return furag;
	}
	void SatFragu()
	{
		furag++;
	}
	int GatHPfurag()
	{
		return HPfurag;
	}

	float Get_keifou_saiz()
	{
		return keifou_saiz;//これが0.95以上になると敵兵が出てくる。
	}
private:
	int time = 0;
	CSprite hy_sprite;				//スプライト(照準)。
	CShaderResourceView hy_texture;	//テクスチャ。
	enum Damage
	{
		UP,
		Down,
		idor
	};
	Player* player;
	Damage Dame;
	CShaderResourceView HP_texture;	//テクスチャ。
	CSprite hm_sprite;				//スプライトh(枠)。
	tekihei* haus;
	float point = 0.0f;
	float HP = 0.95f;
	float  furag = 0.0f; //特殊部隊が出たら1になる。
	int HPfurag = 0;
	float keifou_saiz = 0.0f, HP_saiz = 1.0f;
};

