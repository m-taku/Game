#include "stdafx.h"
#include "tekihei.h"
#include"Player.h"


tekihei::tekihei()
{
}


tekihei::~tekihei()
{
}

bool tekihei::Start()
{
	
	for (int i = 0;i < teki;i++)
	{
		tekispeed[i] = CVector3::Zero;
		teki_angle[i] = 0.0f;
		trot[i] = CQuaternion::Identity;
		tekirot[i] = CQuaternion::Identity;
		tekipos[i] = CVector3::Zero;
		tekiskinModelData[i].Load(L"modelData/unityChan.cmo");//プレイヤーを書け
		tekiskinModel[i].Init(tekiskinModelData[i]);

		tekipos[i].x += 50.0f;
		tekipos[i].z -= i * 100;
		m_charaCon[i].Init(
			20.0,			//半径。 
			100.0f,			//高さ。
			tekipos[i]		//初期位置。
		);
	}

	Pp = FindGO<Player>("Player");
	return true;
}

void tekihei::Update()
{

	for (int i = 0;i < teki;i++)
	{
		m_tekirot[i].MakeRotationFromQuaternion(tekirot[i]);
		tekiright[i].x = m_tekirot[i].m[0][0];
		tekiright[i].y = m_tekirot[i].m[0][1];
		tekiright[i].z = m_tekirot[i].m[0][2];
		tekiright[i].Normalize();

		ppos = Pp->m_position;
		teki_to_player[i] = ppos - tekipos[i];
		teki_to_player[i].Normalize();
		teki_angle[i] = atanf(tekiright[i].Dot(teki_to_player[i]));
		teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];
		trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);
		tekirot[i].Multiply(trot[i]);



		tekispeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();
		if (m_charaCon[i].IsOnGround()) {
			//地面についた。
			tekispeed[i].y = 0.0f;
		}
		tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
		tekiskinModel[i].Update(tekipos[i], tekirot[i], CVector3::One);
	}
	
}

void tekihei::Render(CRenderContext& rc)
{
	for (int i = 0;i < teki;i++)
	{
		tekiskinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}