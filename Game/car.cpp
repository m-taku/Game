#include "stdafx.h"
#include "car.h"
#include"AImove.h"
#include"Game.h"
#include"Human.h"
car::car()
{
}


car::~car()
{
	DeleteGO(ran);
}
bool car::Start()
{
	CLocData loc;
	loc.Load(L"lever/carLv001.tks");
	No.resize(loc.GetNumObject());
	for (int i = 0; i < loc.GetNumObject(); i++) {
		int ka=_wtoll(loc.GetObjectName(i));
		No[ka-1] = loc.GetObjectPosition(i);
	}
	Game* game=FindGO<Game>("Game");
	fa = game->incNo();//車ができた数だけカウントする関数。
	saidaiNo = game->Gatpasusaiz(fa);
	pasu = game->getDate(fa);
	ran = NewGO<AImove>(0, "AImove");
	m_position = No[pasu[ima++]-1];
	m_position.y = 0.0f;
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	CVector3 c = No[pasu[ima] - 1];
	CVector3 bekutor =  c-m_position;
	bekutor.y = 0.0f;
	bekutor.Normalize();
	//回転軸を求める。
	c.y = 0.0f;
	c.Normalize();//向きVectorにする。
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, bekutor);
	CVector3 l = CVector3::Zero;
	if (rotAxis.x==0&& rotAxis.y==0&& rotAxis.z==0) {
		if (bekutor.z > 0) {
			m_rotation.SetRotationDeg(CVector3::AxisY,0.0f);
		}
		else {
			m_rotation.SetRotationDeg(CVector3::AxisY,-180.0);
		}
	}
	else {
		float kaku = acosf(c.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
		float degree = CMath::RadToDeg(kaku);
		rotAxis.Normalize();
		m_rotation.SetRotationDeg(rotAxis, degree);
	}
	//rotation.Multiply(rotation);
	ran->Setkakudo(0.1f);
	ran->Sethaba(1.0f);
	if (game->GatNo() >= 23) {//carを増やすときに変える。
		game->risetteNo();
	}
#ifdef instansingu_katto
	m_skinModelData.Load(L"modelData/Vehicle_SUV1.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
#else

#endif // Mizuki_baka
	SetTags(20);
	return true;
}
void car::Update()
{
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	frag = 0;
	Stop();
	//if (frag <= 0) {
	Move();
	//}
	m_position.y = 0.0f;

#ifdef instansingu_katto
	m_skinModel.Update(m_position, m_rotation, { 0.5f,0.5f,0.5f });
#else
	m_Render->UpdateWorldMatrix(m_position, m_rotation, { 0.5f,0.5f,0.5f });
#endif // Mizuki_baka
}
void car::Move()
{
	ran->kyorikeisan(pasu[ima] - 1, m_position, m_forward, No);

	if (ran->Getkaiten() != 0.0f) {
		m_rotation.Multiply(ran->Getkaku());//回転させる
		if (move > 0.5) {
			move -= 0.05;
		}
		else {
			//if (frag <= 0) {
			//	//	できたらいいなぁ～～
			//	CVector3 k = No[pasu[ima] - 1] - m_position;
			//	k.x = k.x*m_forward.x;
			//	k.y = k.y*m_forward.y;
			//	k.z = k.z*m_forward.z;
			//	float K = 90.0f / ((((k * 2)*3.14159) / 4).Length() / (move*speed*GameTime().GetFrameDeltaTime()));
			ran->Setkakudo(3.0f);
			ran->Sethaba(1.5f);
			//frag++;
			if (move < 0.4) {
				move += 0.3;

			}
		}
	}
	else {
		if (move < 1.0) {
			move += 0.1;
		}else{	
			ran->Setkakudo(0.5f);
			ran->Sethaba(1.0f);
			//frag = 0;
			move = 1.0;
		}
	}
	m_position += m_forward * ((move*speed)*(GameTime().GetFrameDeltaTime()));

	if (400.0f > ran->Getlen()) {

		if (ima >= saidaiNo-1) {//今のポジションが6なら
						//0にリセットする。0,1,2,3,4,5の順番。
			ima = 0;
			//ran->Setkakudo(0.3f);
			//ran->Sethaba(1.0f);
		}
		else {
			ima++;
			//ran->Setkakudo(0.3f);
			//ran->Sethaba(1.0f);
		}
	}
}
void car::Stop()
{
	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this && frag <= 0) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			car* ai = (car*)go;
			CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if (f <= 900) { //距離が車間距離よりも短くなっていたら

				kyori1.Normalize();
				kyori1.y = 0.0f;
				float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
				float degree = CMath::RadToDeg(kaku);
				if (degree <= 60) {
					if (ai->ran->Getlen() < this->ran->Getlen())
					{
						if (move > 0.2)
							move -= 0.21;
						if (move < 0.2) {
							move = -0.1;
						}
						frag++;
					}
				}
			}
		}
	});
	if (frag <= 0) {
		FindGameObjectsWithTag(1, [&](IGameObject* go) {
			if (go != this&&frag<=0) {            //自分からの距離を計測するため、検索結果から自分を除外する。
				Human* ai = (Human*)go;
				CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
				float f = kyori1.Length();
				if (f <= 900) { //距離が視野内だったら
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= 30)
					{
						move = -0.1;
						frag++;
					}
				}
			}
		});
	}
	if (frag <= 0) {
		FindGameObjectsWithTag(10, [&](IGameObject* go) {
			if (go != this && frag <= 0) {            //自分からの距離を計測するため、検索結果から自分を除外する。
				Human* ai = (Human*)go;
				CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
				float f = kyori1.Length();
				if (f <= 900) { //距離が視野内だったら
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= 30)
					{
						move = -0.1;
						frag++;
					}
				}
			}
		});
	}
}

void car::Render(CRenderContext& rc)
{

#ifdef instansingu_katto
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
#endif // Mizuki_baka
}

