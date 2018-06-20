#include "stdafx.h"
#include "Taitor.h"
#include"Player.h"
#include"Game.h"
#define kaku 15.0f

#define seconds 5
Taitor::Taitor()
{
}
Taitor::~Taitor()
{
}
bool Taitor::Start()
{
	n_texture.CreateFromDDSTextureFromFile(L"sprite/Game_Title2.dds");
	n_sprite.Init(n_texture, 1280, 600);
	n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
	fase = FindGO<Fade>("Fade");
	player= FindGO<Player>("Player");
	//y_texture.CreateFromDDSTextureFromFile(L"sprite/yaji.dds");
	//y_sprite.Init(y_texture, 100, 50);
	//y_sprite.Update(n_position, Quaternion, { 1.0f,1.0f,1.0f });
	BasisVector = { 0.0f,5000.0f,5000.0f };
	fase->StartFadeIn();
	furag = steat;
	return true;
}
void Taitor::Update()
{
	/*if (fase->toumeiodo >= 1.0f) {
		if (Triggeer >= 1) {
			if (Triggeer >= 2) {

			}
			else {
				n_texture.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
				n_sprite.Init(n_texture, 1500, 1000);
				Quaternion.SetRotation(CVector3::AxisZ, 90);
				fase->StartFadeIn();
			}

		}
		else {
			n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
			n_sprite.Init(n_texture, 1280, 720);
			fase->StartFadeIn();
		}
	}
	if (fase->toumeiodo <= 0.0f&&Triggeer >= 1) {
		if (Pad(0).GetLStickXF() < 0.0&&Target < 1) {
			n_position.x -= 100.00f;
			Target = 3;
			hyouji = 1;
			taim = 0;
		}if (Pad(0).GetLStickXF() > 0.0&&Target > 0) {
			n_position.x += 100.00f;
			Target = 0;
			hyouji = 0;
			taim = 0;
		}
	}*/

	//if (Pad(0).IsTrigger(enButtonB) && fase->toumeiodo <= 0.0f) {
	//	if(Triggeer>=1)
	//	fase->StartFadeOut();
	//	Triggeer=0;
	//}

//	y_sprite.Update(n_position, Quaternion,{ 1.0f,1.0f,1.0f });
	//Crot.SetRotationDeg(UP, 2.0f);
	//Crot.Multiply(BasisVector);
	switch (furag) {
	case steat:
		Crot.SetRotationDeg(UP, kaku*GameTime().GetFrameDeltaTime());
		Crot.Multiply(BasisVector);
		if (Pad(0).IsTrigger(enButtonA)) {
			//	fase->StartFadeOut();
			furag = push;
		}
		break;
	case push:
		BasisVector /= 1 - (1 / (seconds / GameTime().GetFrameDeltaTime()));
		target = player->Getbonepos();
		player_Foeward = player->GetFoeward();
		player_Foeward.y = 0.0f;
		player_Foeward.Normalize();
		player_Foeward *= -1;
		kakudo = siya();
		kakudo /= seconds;
		ka = nowkmVector - target;
		ka.y = 0.0f;
		ka.Normalize();
		UP.Cross(ka, player_Foeward);
		UP.Normalize();
		Crot.SetRotationDeg(UP, kakudo*GameTime().GetFrameDeltaTime());
		Crot.Multiply(BasisVector);
		kaunto = seconds / GameTime().GetFrameDeltaTime();
		//	UP = player->Getboneup();
		furag = suii;
		break;
	case suii:
		nowkmtarget += target / kaunto;
		Crot.SetRotationDeg(UP, kakudo*GameTime().GetFrameDeltaTime());
		Crot.Multiply(BasisVector);
		BasisVector *=1-(1/(seconds /GameTime().GetFrameDeltaTime()));

		if (taime++ > kaunto)
		{
			nowkmtarget = target;
			ka = nowkmVector - target;

			ka.Normalize();

			ka.y = 1.2f;
			ka *= (speed * GameTime().GetFrameDeltaTime());
			speed--;
			furag = tyoku;
		}
		break;
	case tyoku:
		ka = nowkmVector - target;
		if (0.0f >= nowkmVector.y - target.y) {
			ka.y = 0.0f;
			nowkmtarget.y = target.y;
			BasisVector.y = 0.0f;
		}
		ka.Normalize();
		if (ka.y > 0) {
			ka.y = 1.2f;
		}

		if (BasisVector.Length() <= 500.0f)
		{
			ka *= 600 * GameTime().GetFrameDeltaTime();
		}
		else {
			ka *= speed * GameTime().GetFrameDeltaTime();
			speed--;
		}
		if (BasisVector.Length() <= 40.0f)
		{
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
		break;
	default:
		break;

	}

	nowkmVector = (BasisVector - ka) + nowkmtarget;
	BasisVector -= ka;
	MainCamera().SetTarget(nowkmtarget);
	MainCamera().SetNear(1.0f);
	MainCamera().SetUp(CVector3::AxisY);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(nowkmVector);
	MainCamera().Update();
}

float Taitor::siya()
{
	CVector3 muki = BasisVector;
	muki.y = 0.0f;
	muki.Normalize();//向きVectorにする。
	float kok = acosf(muki.Dot(player_Foeward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree = CMath::RadToDeg(kok);
	return degree;
}

void  Taitor::PostRender(CRenderContext& rc)
{
	if (furag == steat) {
		n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
	}
}