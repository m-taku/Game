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
	m_bdm_Sneak1 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak1->Init("sound/horror_zone1.wav");
	m_bdm_Sneak2 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak2->Init("sound/n80.wav");
	Scene = Title;
	ai_manager = FindGO<AI_manager>("AI_manager");//AI_managerのインスタンスを取得。
	/*m_bdm_Assault = NewGO<prefab::CSoundSource>(0);
	m_bdm_Assault->Init("sound/horror_zone1.wav", false);*/
	NPC_Goukei = ai_manager->Get_NPC_Number();//生成したNPCの合計人数を代入。
	return true;
}

void BGM::Play_Title() //タイトルのBGMを流しているときに動く関数。
{
	//m_bdm_Title->Play(true);//	タイトル時時のBGMを流す。
	Gauge = FindGO<Geizi>("Geizi");//インスタンスが生成されていたら入れる。
	if (Gauge != nullptr) {
		Scene = Sneak_First;//ゲージが出た(＝タイトル画面から次ぎへ移行した)ので流すBGMをスニークファーストに変える。
		//m_bdm_Title->Stop();//次へ切り替わるので今流れているBGMを止める。
	}
}

void BGM::Play_Sneak_First()//スニーク時の最初に処理される。
{
	Scene = Sneak_Fewer_people;//処理が終わったので次の状態へ移行する。
}
void BGM::Play_Sneak_Fewer_people()//スニーク時(ゾンビ化NPCが1/2未満の時)のBGMを流しているときに動く関数。
{
	m_bdm_Sneak1->Play(true);//スニーク時のBGMを流す。
	if (ZombieNPC_Number>=(NPC_Goukei/2))//ゾンビ化NPCがNPCの合計人数の半分以上を占めたら
	{
		Scene = Sneak_Many_persons;//ゾンビ化NPCが半分以上を占めた場合の処理に変える。
	}
	if (Gauge->Get_keifou_saiz()>=0.95) //ゲージが敵兵が出てくるラインを超えたら
	{
		Scene = Assault;//ゲージがラインを超えた(＝敵兵とのバトルに移行する)ので流すBGMをアサルトに変える。
		m_bdm_Sneak1->Stop();//次へ切り替わるので今流れているBGMを止める。
	}
}

void BGM::Play_Sneak_Many_persons()//スニーク時(ゾンビ化NPCが1/2以上の時)のBGMを流しているときに動く関数。
{
	m_bdm_Sneak1->Play(true);//スニーク時のBGM1を流す。
	m_bdm_Sneak2->Play(true);//スニーク時のBGM2を流す。
	if (Gauge->Get_keifou_saiz() >= 0.95) //ゲージが敵兵が出てくるラインを超えたら
	{
		Scene = Assault;//ゲージがラインを超えた(＝敵兵とのバトルに移行する)ので流すBGMをアサルトに変える。
		m_bdm_Sneak1->Stop();//次へ切り替わるので今流れているBGM1を止める。
		m_bdm_Sneak2->Stop();//次へ切り替わるので今流れているBGM2を止める。
	}
}

void BGM::Play_Assault()//アサルト(敵兵と戦う)時のBGMを流しているときに動く関数。
{
	//m_bdm_Assault->Play(true);//敵兵と戦う時のBGMを流す。
}

void BGM::Update()
{

	switch (Scene)//今、どのBGMを流すかを判断する。
	{
	case Title://タイトル
		Play_Title();
		break;
	case Sneak_First://スニークの最初の処理。
		Play_Sneak_First();
		break;
	case Sneak_Fewer_people://スニークかつゾンビが1/2未満。
		Play_Sneak_Fewer_people();
		break;
	case Sneak_Many_persons://スニークかつゾンビが1/2以上。
		Play_Sneak_Many_persons();
		break;
	case Assault://アサルト(敵兵と戦う)
		Play_Assault();
		break;
		Play_Title();
	default:
		break;
	}
}
