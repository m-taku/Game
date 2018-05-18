#pragma once
#include"Fade.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	Fade* fase;
	CSprite n_sprite;				//スプライト（中身）。
	CShaderResourceView n_texture;	//テクスチャ。*/
	CQuaternion Quaternion = CQuaternion::Identity; //回転
	CSprite y_sprite;				//スプライト（矢印）。
	CShaderResourceView y_texture;	//テクスチャ。*/
	CVector3 n_position = CVector3::Zero;
private:
	int Triggeer = 0;
	int hyouji = 11;
	int taim = 11;
	int Target = 3;
};

