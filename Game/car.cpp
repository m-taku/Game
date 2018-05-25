#include "stdafx.h"
#include "car.h"
#include"AImove.h"
#include"Game.h"
car::car()
{
}


car::~car()
{
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
	fa = game->incNo();
	saidaiNo = game->Gatpasusaiz(fa);
	pasu = game->getDate(fa);
	ran = NewGO<AImove>(0, "AImove");
	m_position = No[pasu[ima++]-1];
	m_position.y = 0.0f;
	m_skinModelData.Load(L"modelData/Vehicle_SUV1.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);
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
	ran->Satkakudo(0.1f);
	ran->Sathaba(1.0f);
	m_skinModel.Update(m_position, m_rotation, { 0.5f,0.5f,0.5f });
	if (game->GatNo() >= 5) {
		game->risetteNo();
	}
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
//	frag = 0;
	Stop();
//	if (frag <= 0) {
	Move();
//	}
	m_position.y = 0.0f;
	m_skinModel.Update(m_position,m_rotation, { 0.5f,0.5f,0.5f });
}
void car::Move()
{
	ran->kyorikeisan(pasu[ima] - 1, m_position, m_forward, No);

	if (ran->Gatkaiten() != 0.0f) {
		m_rotation.Multiply(ran->Gatkaku());//回転させる
		if (move > 0.5) {
			move -= 0.05;
		}
		else {
			ran->Satkakudo(1.8f);
			ran->Sathaba(1.0f);
		}

	}
	else {
		if (move < 1.0) {
			if (frag == 0)
				move += 0.05;
		}
		else {
			ran->Satkakudo(0.1f);
			ran->Sathaba(1.0f);
		}
	}
	m_position += m_forward * ((move*speed)*(GameTime().GetFrameDeltaTime()));

	if (200.0f > ran->Gatlen()) {

		if (ima >= saidaiNo-1) {//今のポジションが6なら
						//0にリセットする。0,1,2,3,4,5の順番。
			ima = 0;
		}
		else {
			ima++;
		}
	}
}
void car::Stop()
{
	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			car* ai = (car*)go;
			CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if (f <= 1100) { //距離が攻撃範囲以内だったら
				kyori1.Normalize();
				kyori1.y = 0.0f;
				float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
				float degree = CMath::RadToDeg(kaku);
				if (degree <= 80) {
					if (ai->ran->Gatlen() < this->ran->Gatlen())
					{
						if (move > 0.5)
							move -= 0.11;
						if (move < 0.5)
							move = 0.5;

					}
				}
			}
		}
	});
}
void car::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
