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
	game = FindGO<Game>("Game");
}


AImove::~AImove()
{
}
bool AImove::Start()
{
	return true;
}
int AImove::kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward)
{

	//game = FindGO<Game>("Game");
	qBias1 = CQuaternion::Identity;
	muve = 0;
	m_pos.y = 0.0f;
	len = 0;
	mokuteki = game->pasu.m_pointList[bangou];
	mokuteki.y = 0.0f;
	bekutor = mokuteki - m_pos;
	len = bekutor.Length();//長さ
	if (15.0f <= len) {
		float angle = VectorAngleDeg(bekutor, m_forward);
		if (angle >= 3.0) {
			bekutor.y = 0.0f;
			bekutor.Normalize();
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(m_forward,bekutor);
			rotAxis.Normalize();
			qBias1.SetRotationDeg(rotAxis, 3.0f);
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