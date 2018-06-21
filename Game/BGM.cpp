#include "stdafx.h"
#include "BGM.h"


BGM::BGM()
{
}


BGM::~BGM()
{
}

bool BGM::Start()
{
	/*m_bdm_Title = NewGO<prefab::CSoundSource>(0);
	m_bdm_Title->Init("sound/horror_zone1.wav", false);*/
	m_bdm_Sneak = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak->Init("sound/horror_zone1.wav");
	m_bdm_Sneak->Play(true);
	Scene = Title;
	/*m_bdm_Assault = NewGO<prefab::CSoundSource>(0);
	m_bdm_Assault->Init("sound/horror_zone1.wav", false);*/

	return true;
}

void BGM::Play_Title() //タイトルのBGMを流しているときに動く関数。
{
	//m_bdm_Title->Play(true);//	タイトル時時のBGMを流す。
	Gauge = FindGO<Geizi>("Geizi");//インスタンスが生成されていたら入れる。
	if (Gauge != nullptr) {
		Scene = Sneak;//ゲージが出た(＝タイトル画面から次ぎへ移行した)ので流すBGMをスニークに変える。
		//m_bdm_Title->Stop();//次へ切り替わるので今流れているBGMを止める。
	}
}

void BGM::Play_Sneak()//スニーク時のBGMを流しているときに動く関数。
{
	m_bdm_Sneak->Play(true);//スニーク時のBGMを流す。
	if (Gauge->Get_keifou_saiz()>=0.95) {//ゲージが敵兵が出てくるラインを超えたら
		Scene = Assault;//ゲージがラインを超えた(＝敵兵とのバトルに移行する)ので流すBGMをアサルトに変える。
		m_bdm_Sneak->Stop();//次へ切り替わるので今流れているBGMを止める。
	}
}

void BGM::Play_Assault()//アサルト(敵兵と戦う)時のBGMを流しているときに動く関数。
{
	//m_bdm_Assault->Play(true);//敵兵と戦う時のBGMを流す。
}

void BGM::Update()
{

	m_bdm_Sneak->Play(true);

	switch (Scene)//今、どのBGMを流すかを判断する。
	{
	case Title://タイトル
		Play_Title();
		break;
	case Sneak://スニーク
		Play_Sneak();
		break;
	case Assault://アサルト(敵兵と戦う)
		Play_Assault();
		break;
		Play_Title();
	default:
		break;
	}
}
