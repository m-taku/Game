#pragma once
#include"Fade.h"
#include"Player.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	void Update();
private:
	enum kaiten {
		steat,
		push,
		suii
	};
	enum kaiten furag;
	Fade * fase;
	CSprite n_sprite;				//スプライト（中身）。
	CShaderResourceView n_texture;	//テクスチャ。*/
	CQuaternion Quaternion = CQuaternion::Identity; //回転
	CSprite y_sprite;				//スプライト（矢印）。
	CShaderResourceView y_texture;	//テクスチャ。*/
	CVector3 n_position = CVector3::Zero;

	Player* player = nullptr;
	CVector3 target = CVector3::Zero;
	CVector3 Ppos = CVector3::Zero;
	float d = 0.0f;
	CVector3 position_of_player;
	CVector3 UP = CVector3::AxisY;
	CQuaternion Crot = CQuaternion::Identity;
	CVector3 Pboneforward = CVector3::Zero;
	int Triggeer = 0;
	int hyouji = 11;
	int taim = 11;
	int Target = 3;
};

