#pragma once
#include"AImove.h"
#include"tkEngine/sound/tkSoundSource.h"
#include"carRender.h"
class car : public IGameObject
{
public:
	car();
	~car();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void gatcarRender(carRender& ka)
	{
		m_Render = &ka;
	}
	void CarSound();//Carクラスのサウンドを扱う関数。
	void SoundklaxonPlay();//クラクションを鳴らす処理。
	CVector3 Getposition()
	{
		return m_position;//現在の座標
	}
	CVector3 Getforward()
	{
		return m_forward;
	}
	void GetGeizi(Geizi* naka)
	{
		Gaizi = naka;
	}
private:

	//CMeshCollider m_meshCollider;	//メッシュコライダー。
	//CRigidBody m_rigidBody;			//剛体
	//CPhysicsStaticObject m_physicsStaticObject;
	void Move();
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	AImove* ran;
	std::vector<Human*> HumanLest;
	Geizi* Gaizi= nullptr;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CVector3 m_position = CVector3::Zero;				//現在の座標
	CMatrix m_tekirot;									//行列
	CVector3 m_forward;									//キャラの前方。
	float  move = 1.0f;									//移動速度（倍率、1.0が普通）
	std::vector<CVector3> No;
	float speed = 1000;									//常に走るスピード
	std::vector<int>::iterator pasu;
	int saidaiNo = 0;
	int ima = 0;
	void Stop();
	int fa = 0;
	bool frag = false;
	float siya = 100.0f;
	bool Humanfrag = false;
	carRender* m_Render;
	
	bool stopFlag = false;//今止まっているかを示すフラグこのフラグがtrueのときは、前のフレームで既に止まっている。
	bool loodflag = false;//ロードしたかを示すフラグ。
	bool klaxonFlag = false;//クラクションを鳴らすことを示すフラグ。
};

