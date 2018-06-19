#include "stdafx.h"
#include "car.h"
#include"AImove.h"
#include"AI.h"
#include"Game.h"
#include"Geizi.h"
#include"Human.h"
#include"Stage.h"
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
	Stage* stage =FindGO<Stage>("stage");
	Gaizi = FindGO<Geizi>("Geizi");
	fa = stage->incNo();//車ができた数だけカウントする関数。
	saidaiNo = stage->Gatpasusaiz(fa);
	pasu = stage->getDate(fa);
	ran = NewGO<AImove>(0, "AImove");
	m_position = No[pasu[ima++]-1];
	m_position.y = 10.0f;
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	for (int u = 0; u < Humans.size(); u++) {
		Human* ai = Humans[u];
		HumanLest.push_back(ai);
	}

	
	m_noise = NewGO<prefab::CSoundSource>(0);
	m_noise->Init("sound/car_noise.wav", true);
	m_noise->AddSoundStopCallback([&]() {
		//サウンドが停止したらこの関数が呼ばれる
		
	});
	
	//m_noise->Play(false);//初めて止まったので、クラクションを鳴らす。

	//クラクションの初期化。
	//m_klaxon = NewGO<prefab::CSoundSource>(0);
	//m_klaxon->Init("sound/car-horn1.wav",true);
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
	if (stage->GatNo() >= 23) {//carを増やすときに変える。
		stage->risetteNo();
	}


	m_skinModelData.Load(L"modelData/Vehicle_SUV1.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);

	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	RigidBodyInfo rbInfo;
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass= 10.0f;							//質量を0にすると動かない剛体になる。
												//背景などの動かないオブジェクトは0を設定するとよい。
	m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
	PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
	stopFlag = false;//stopFlagの初期化。

#ifdef instansingu_katto
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
#endif 
	SetTags(20);
	return true;
}

void car::Update()
{
	klaxonFlag = false;//毎回初期化。
	if (Gaizi->GatFragu() < 1.0f) {
		CarSound_SetPosition();//音源の座標を設定。

		m_tekirot.MakeRotationFromQuaternion(m_rotation);
		m_forward.x = m_tekirot.m[2][0];
		m_forward.y = m_tekirot.m[2][1];
		m_forward.z = m_tekirot.m[2][2];
		m_forward.y = 0.0f;
		m_forward.Normalize();
		frag = false;
		Humanfrag = false;
		Stop();
		//こ↑こ↓より下は、停止している限りklaxonFlagがtrueになる。
		//if (frag <= 0) {
		Move();
		//}

		if (move != 0.0f) {//動いていたら
			if(m_noise->Get3DSoundFlag() ==true)
			m_noise->Play(true);//車の走行音を流す。
		}
		else {//止まっていたら
			m_noise->Stop();//車の走行音を止める。
		}
		//クラクションを鳴らすかを判定する。
		if (klaxonFlag == true) {//クラクションを鳴らした。
			SoundklaxonPlay();
		}

		if (klaxonFlag == false) {
			stopFlag = false;
		}
		m_position.y = 0.0f;
		if (Humanfrag != false) {

			ran->Setlen(0.0f);
		}

//	}

	if (move == 0.0f) {
		int i = 0;
	}
	//クラクションを鳴らすかを判定する。
	if (klaxonFlag == true) {//クラクションを鳴らした。
		SoundklaxonPlay();
	}

	if (klaxonFlag == false) {
		stopFlag = false;
	}


	btVector3 m_pos = m_rigidBody.GetBody()->getWorldTransform().getOrigin();
	if (0 >= m_pos.y()) {
		m_pos.setY(0.0f);
	}
	m_pos.setX(m_position.x);
	m_pos.setZ(m_position.z);
	m_rigidBody.GetBody()->getWorldTransform().setOrigin(m_pos);
	m_position.Set(m_pos);


#ifdef instansingu_katto
	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f });
#else
	m_Render->UpdateWorldMatrix(m_position, m_rotation, {1.0f,1.0f,1.0f});
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

			siya = 100.0f;
			//frag = 0;
			move = 1.0;
		}
	}
	m_position += m_forward * ((move*speed)*(GameTime().GetFrameDeltaTime()));

	if (300.0f > ran->Getlen()) {

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
	for (auto& Humanlest : HumanLest) {
		if (Humanfrag != true) {
			CVector3 kyori1 = Humanlest->Getposition() - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if(!Humanlest->GetZonbi()){
				if (f <= 800) { //距離が視野内だったら
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= 30)
					{
						//この一連の処理を続けているときは止まっている。
						move = -0.1;
						Humanfrag = true;
						klaxonFlag = true;//クラクションを鳴らす。止まり続ける限りtrueのままになる。
					}
				}
			}
		}
	}

	int ha = 0;
	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this && ha == 0) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			car* ai = (car*)go;
			CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if (f <= 1000) { //距離が車間距離よりも短くなっていたら
				float kaku1 = acosf(ai->m_forward.Dot(this->m_forward));
				float degree1 = CMath::RadToDeg(kaku1);
				if (degree1 <160) {
					kyori1.Normalize();
					kyori1.y = 0.0f;
					float kaku = acosf(kyori1.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
					float degree = CMath::RadToDeg(kaku);
					if (degree <= siya) {
						if (ai->ran->Getlen() <= this->ran->Getlen())
						{
							if (ai->Humanfrag == true) {
								move = -0.1;

								siya = 10.0f;
								Humanfrag = true;
							}

							else {
								if (move <= 0.2) {
									move = -0.1;
								}
								else {
									move -= 0.31;
								}
								ha++;
							}
						}
					}

				}
			}
		}
	});
}

void car::CarSound_SetPosition()//一連のさうんどの処理をする。
{
	//	//クラクションを鳴らすかを判定する。
	//	SoundklaxonPlay();
	//サウンドのポジションを設定する。
	m_noise->SetPosition(m_position);
}

void car::SoundklaxonPlay()//クラクションのサウンドを鳴らされた時に一回だけ流す。
{
	if (stopFlag == false) {
		prefab::CSoundSource*m_klaxon = nullptr;
		m_klaxon = NewGO<prefab::CSoundSource>(0);
		m_klaxon->Init("sound/klaxon.wav", true);
		m_klaxon->AddSoundStopCallback([&]() {
			//サウンドが停止したらこの関数が呼ばれる
			stopFlag = true;//ストップした。
		});
		//サウンドのポジションを設定する。
		m_klaxon->SetPosition(m_position);
		m_klaxon->Play(false);//初めて止まったので、クラクションを鳴らす。
	//if (Humanfrag == false) {//車が動き出した。
	//	stopFlag = false;//「ストップした」というフラグを元に戻しておく。
	//}
		stopFlag = true;//ストップした。
	}
}
void car::Render(CRenderContext& rc)
{

#ifdef instansingu_katto
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
#endif 
}