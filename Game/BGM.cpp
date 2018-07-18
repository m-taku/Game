#include "stdafx.h"
#include "BGM.h"


BGM::BGM()
{
}


BGM::~BGM()
{
	m_bdm_Title->Stop();
	m_bdm_Sneak1->Stop();
	m_bdm_Sneak2->Stop();
	ZombieNPC_Number = 0;
}

bool BGM::Start()
{
	m_bdm_Title = NewGO<prefab::CSoundSource>(0);
	m_bdm_Title->Init("sound/Zombie_Title_Theme.wav");
	m_bdm_Title->SetVolume(bgm_volume);
	m_bdm_Sneak1 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak1->Init("sound/horror_zone1.wav");
	m_bdm_Sneak1->SetVolume(bgm_volume);
	m_bdm_Sneak2 = NewGO<prefab::CSoundSource>(0);
	m_bdm_Sneak2->Init("sound/n80.wav");
	m_bdm_Sneak2->SetVolume(0.3f);
	Scene = Title;
	ai_manager = FindGO<AI_manager>("AI_manager");//AI_managerのインスタンスを取得。
	NPC_Goukei = ai_manager->Get_NPC_Number();//生成したNPCの合計人数を代入。
	
	return true;
}

void BGM::Play_Title() //タイトルのBGMを流しているときに動く関数。
{
	if (Startbutton_push_Flag == false ) {
		m_bdm_Title->Play(true);//タイトル時のBGMを流す。
	}
	else {//スタートボタンが押されたら
		 //BGMのフェードアウト
		if (bgm_volume > 0.01f) {
			bgm_volume = bgm_volume - 0.01f;
			m_bdm_Title->SetVolume(bgm_volume);
		}
		else {
			m_bdm_Title->Stop();
		}
	}
	
	Gauge = FindGO<Geizi>("Geizi");//インスタンスが生成されていたら入れる。
	if (Gauge != nullptr) {
		Scene = Sneak_First;//ゲージが出た(＝タイトル画面から次ぎへ移行した)ので流すBGMをスニークファーストに変える。
		Startbutton_push_Flag = false;
		bgm_volume = 1.0f;
		//m_bdm_Title->Stop();//次へ切り替わるので今流れているBGMを止める。
	}
}

void BGM::Play_Sneak_First()//スニーク時の最初に処理される。
{
	game = FindGO<Game>("Game");//タイム計測に使う。
	Scene = Sneak_Fewer_people;//処理が終わったので次の状態へ移行する。
}
void BGM::Play_Sneak_Fewer_people()//スニーク時(ゾンビ化NPCが1/2未満の時)のBGMを流しているときに動く関数。
{
	m_bdm_Sneak1->Play(true);//スニーク時のBGMを流す。
	
	if (game->Gettimer_m()<=0)//ゾンビ化NPCがNPCの合計人数の半分以上を占めたら
	{
		//BGMのフェードアウト
		if (bgm_volume > 0.01f) {
			bgm_volume = bgm_volume - 0.01f;
			m_bdm_Sneak1->SetVolume(bgm_volume);
		}
		else {
			m_bdm_Sneak1->Stop();
			Scene = Sneak_Many_persons;//ゾンビ化NPCが半分以上を占めた場合の処理に変える。
			bgm_volume = 1.0f;
		}
	}
}

void BGM::Play_Sneak_Many_persons()//スニーク時(ゾンビ化NPCが1/2以上の時)のBGMを流しているときに動く関数。
{
	m_bdm_Sneak2->Play(true);//スニーク時のBGM2を流す。
	m_bdm_Sneak2->SetVolume(0.5f);
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
	default:
		break;
	}
}

void BGM::Set_Startbutton_push()
{
	Startbutton_push_SE();//効果音。
	Startbutton_push_Flag = true;
}

void BGM::Startbutton_push_SE()
{
	prefab::CSoundSource*m_SE_Startbutton=nullptr;
	m_SE_Startbutton = NewGO<prefab::CSoundSource>(0);
	m_SE_Startbutton->Init("sound/StartbuttonSE.wav", false);
	m_SE_Startbutton->SetVolume(0.7f);
	m_SE_Startbutton->Play(false);//一回だけ再生されて破棄される。
}