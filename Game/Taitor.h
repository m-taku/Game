#pragma once
#include"Fade.h"
#include"Player.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	float siya();
	void PostRender(CRenderContext& rc) override;
	void Update();
private:
	enum kaiten {
		steat,
		push,
		suii,
		tyoku
	};
	enum kaiten furag;
	Fade * fase;
	CSprite n_sprite;				//スプライト（中身）。
	CShaderResourceView n_texture;	//テクスチャ。*/
	CQuaternion Quaternion = CQuaternion::Identity; //回転
	CSprite y_sprite;				//スプライト（矢印）。
	CShaderResourceView y_texture;	//テクスチャ。*/
	CVector3 n_position = { 0.0f ,180.0f,0.0f };

	Player* player = nullptr;
	CVector3 target = CVector3::Zero;

	CVector3 nowkmtarget = CVector3::Zero;
	CVector3 Ppos = CVector3::Zero;
	float d = 0.0f;
	CVector3 player_Foeward= CVector3::Zero;
	CVector3 UP = CVector3::AxisY;
	CQuaternion Crot = CQuaternion::Identity;
	CVector3 BasisVector = CVector3::Zero;
	CVector3 nowkmVector = CVector3::Zero;
	int Triggeer = 0;
	float kakudo = 10.0f;
	int speed = 200.0f;
	int kaunto = 0;
	CVector3 ka = CVector3::Zero;
	int hyouji = 11;
	int taim = 11;
	int Target = 3;
};

