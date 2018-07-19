#include "stdafx.h"
#include "Taitor.h"
#include"Player.h"
#include"Game.h"
#define kaku 15.0f
#define fream 30
#define seconds 5
Taitor::Taitor()
{
}
Taitor::~Taitor()
{
}
bool Taitor::Start()
{
	kakudu = kaiton;
	n_texture.CreateFromDDSTextureFromFile(L"sprite/Game_Title2.dds");
	n_sprite.Init(n_texture, 1280.0f, 720.0f);
	n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
	fase = FindGO<Fade>("Fade");
	player= FindGO<Player>("Player");
	bgm = FindGO<BGM>("BGM"); 
	Abotan_texture.CreateFromDDSTextureFromFile(L"sprite/A_botan.dds");
	Abotan_sprite.Init(Abotan_texture, 163.3333f,233.3333f);
	n_position.y -= 360.0f; 
	Abotan_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, {0.5f,0.5f});
	Pusu_texture.CreateFromDDSTextureFromFile(L"sprite/Press_Button.dds");
	Pusu_sprite.Init(Pusu_texture, 800.0f, 400.0f);
	n_position.x -= 150.0f;
	n_position.y += 5.0f;
	Pusu_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	start_texture.CreateFromDDSTextureFromFile(L"sprite/Start_Button.dds");
	start_sprite.Init(start_texture, 800.0f, 400.0f);
	n_position.x += 280.0f;
	n_position.y -= 10.0f;
	start_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	BasisVector = { 0.0f,5000.0f,5000.0f };
	fase->StartFadeIn();
	furag = steat;
	Crot = CQuaternion::Identity;
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
			bgm->Set_Startbutton_push();
			furag = push;
		}
		break;
	case push:
		BasisVector /= 1 - (1 / (seconds / GameTime().GetFrameDeltaTime()));
		target = player->Getbonepos();
		player_Foeward = CVector3::Zero;
		player_Foeward.z = -1.0f;
		ka = nowkmVector- nowkmtarget;
		ka.y = 0.0f;
		ka.Normalize();
		kakudo = siya();
		kakudo /= seconds;
		UP.Cross(ka,player_Foeward);
		UP.Normalize();
		Crot.SetRotationDeg(UP, kakudo*GameTime().GetFrameDeltaTime());
		Crot.Multiply(BasisVector);
		kaunto = seconds /GameTime().GetFrameDeltaTime();
		//UP = player->Getboneup();
		furag = suii;
		break;
	case suii:
		//kakudo = siya();
		//kakudo /= seconds;
		kaunto = seconds / GameTime().GetFrameDeltaTime();
		nowkmtarget += target / kaunto;
		kaiten();
		BasisVector *= 1 - (1 / (seconds  / GameTime().GetFrameDeltaTime()));
		kakakakak = target - nowkmtarget;
		if ((target - nowkmtarget).Length() <= 50.0f)
		{
			float Player_back = siya();
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
		kaiten();
		ka = nowkmVector - target;
		if (0.0f >= nowkmVector.y - target.y) {
			ka.y = 0.0f;
			nowkmtarget.y = target.y;
			BasisVector.y = 0.0f;
		}
		ka.Normalize();
		if (ka.y > 0) {
			ka.y = 0.8f;
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
	camera_to_player_vector = player->GetPosition() - nowkmVector;
	camera_to_player_dist = camera_to_player_vector.Length();
	float t = max( min(1.0f, nowkmVector.y / 5000.0f ), 0.0f);
	t = pow(t, 30);
	cm_near = 1.0 * (1.0f - t) + 2000.0f * t;

	nowkmVector = (BasisVector - ka) + nowkmtarget;
	BasisVector -= ka;
	MainCamera().SetTarget(nowkmtarget);
	MainCamera().SetNear(cm_near);
	MainCamera().SetUp(CVector3::AxisY);
	MainCamera().SetFar(25000.0f);
	MainCamera().SetPosition(nowkmVector);
	MainCamera().Update();
}
void  Taitor::PostRender(CRenderContext& rc)
{
	if (furag == steat) {
		n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
		Transparency();
		Abotan_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
		Pusu_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
		start_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
	}
}
void Taitor::Transparency()
{
	switch (FADE)
	{
	case Up:
		if (toumei >= 0)
		{
			toumei -= GameTime().GetFrameDeltaTime();
			if (toumei <= 0)
			{
				toumei = 0;
				FADE = Down;
			}
		}
		break;
	case Down:
		if (toumei <= 1.0f)
		{
			toumei += GameTime().GetFrameDeltaTime();
			if (toumei >= 1)
			{
				toumei = 1;
				FADE = Up;
			}
		}
		break;
	case Idor:
		break;
	default:
		break;
	}
	Pusu_sprite.SetMulColor({ 1.0f,1.0f,1.0f,toumei });
	start_sprite.SetMulColor({ 1.0f,1.0f,1.0f,toumei });
	Abotan_sprite.SetMulColor({ 1.0f,1.0f,1.0f,toumei });
}
void Taitor::kaiten()
{
	float Player_back = siya();
	switch (kakudu)
	{
	case kaiton:
		if (Player_back >= 2.0f)
		{
			Crot.SetRotationDeg(UP, kakudo*GameTime().GetFrameDeltaTime());
			Crot.Multiply(BasisVector);
		}
		else {
			Crot.SetRotationDeg(UP, Player_back);
			Crot.Multiply(BasisVector);
			kakudu = idor;
		}
		break;
	case idor:
		break;
	default:
		break;
	}
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
