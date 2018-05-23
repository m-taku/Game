#include "stdafx.h"
#include "AImove.h"
#include"Level.h"
#include"math.h"
#include"Game.h"
#include"Pasu.h"
#include"keiroK.h"
#include"AI.h"
#define SOKUDO 500.0f;

float VectorAngleDeg(CVector3 c, CVector3 forward);
AImove::AImove()
{
}


AImove::~AImove()
{
}

int AImove::kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward, std::vector<CVector3> pasu)
{

	//game = FindGO<Game>("Game");
	kaku = 0.0f;
	muve = 1.0f;
	qBias1 = CQuaternion::Identity;
	m_pos.y = 0.0f;
	len = 0;
	mokuteki = pasu[bangou];
	mokuteki.y = 0.0f;
	bekutor = mokuteki - m_pos;
	len = bekutor.Length();//長さ
	if (15.0f <= len) {
		float angle = VectorAngleDeg(bekutor, m_forward);
		if (angle >= haba) {
			bekutor.y = 0.0f;
			bekutor.Normalize();
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(m_forward,bekutor);
			rotAxis.Normalize();
			kaku = kakudo;
			qBias1.SetRotationDeg(rotAxis, kaku);
		}
		else {	
			muve = SOKUDO;
		}
	}
	return muve;
}
float VectorAngleDeg(CVector3 c,CVector3 forward)
{
	c.y = 0.0f;
	c.Normalize();//向きVectorにする。
	float kaku = acosf(c.Dot(forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree = CMath::RadToDeg(kaku);

	return degree;
}