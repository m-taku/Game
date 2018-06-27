#include "stdafx.h"
#include "keiroK.h"
#include"AI.h"
#include"Game.h"
#include"math.h"
#include <map>
#include <tchar.h>
#include "AI_manager.h"
#include "kanren.h"
keiroK::keiroK()
{
}
keiroK::~keiroK()
{
}
ando *Satando(ando* n, CVector3 m_p, CVector3 s_p,int a,int t, std::vector<int> k , int ka,int before)
{
	n->m_position = m_p;
	n->s_position = s_p;
	n->ime = a;
	n->tunagi = t;
	n->No = k;
	n->cost = ka;
	n->beforeNo = before;
	return n;
}
int keiroK::BackTrace(int x)
{
	if (x%100 == f) {
		return 1;
	}
	std::map<int ,ando>::iterator tmp = close.find(x);
	if (tmp == close.end())
		return 0;
	return BackTrace(tmp->second.beforeNo) + GetDistance(tmp->second.m_position, tmp->second.s_position);
}
int keiroK::Kans(int count)
{
	if (open.empty())return -10000;
	ando nodes[8];
	resuto1;
	std::map<int,ando>::iterator it;
	std::map<int,ando>::iterator itmix;

	int costmix = 99999;
	int goulkost = 0;
	int fhuj = 0,kesu =0;
	it = open.begin();
	while (it != open.end()) {
		if (costmix > (it->second.cost + GetDistance(it->second.s_position, ga))) {
			costmix = (it->second.cost + GetDistance(it->second.s_position, ga));
			itmix = it;
			kesu = it->first;
		}
		it++;
	}
	Satando(
		&n,
		itmix->second.m_position,
		itmix->second.s_position,
		itmix->second.ime,
		itmix->second.tunagi,
		itmix->second.No,
		itmix->second.cost,
		itmix->second.beforeNo
	);
	close.insert(std::pair<int, ando>(kesu,n));
	open.erase(kesu);
	goulkost = BackTrace(n.ime*100+n.tunagi);
	for (No = 0; No < resuto1.size(); No++) {
		if (resuto1[No].No[0]== n.tunagi)
		{
			break;
		}
	}
	kanren* ka = &resuto1[No];
	for (int i = 0; i < ka->No.size()-1; i++) {
		bool findfrag = false;
		Satando(
			&nodes[i],
			ka->m_position[0],
			ka->m_position[i + 1],
			n.tunagi,
			ka->No[i + 1],
			resuto1[No].No,
			goulkost + GetDistance(ka->m_position[i + 1], n.s_position),
			n.ime * 100 + n.tunagi
		);
		//std::map<int,ando>::iterator tmp = open.begin();
		for (auto& ka : open) {
			if (ka.second.tunagi == nodes[i].ime && ka.second.ime==nodes[i].tunagi)
			{
				//if (nodes[i].cost < ka.second.cost) {
				//	ka.second.m_position = nodes[i].m_position;
				//	ka.second.ime = nodes[i].ime;

				//	ka.second.cost = nodes[i].cost;
				//	ka.second.beforeNo = nodes[i].beforeNo;
				//}
				findfrag = true;
				break;
			}
		}
	//	std::map<int ,ando>::iterator tmp1 = close.begin();
		if (findfrag == false) {
			for (auto ka : close) {
				if (ka.second.tunagi == nodes[i].ime && ka.second.ime == nodes[i].tunagi)
				{
					if (nodes[i].cost < ka.second.cost) {
						ando tmp5;
						Satando(
							&tmp5,
							nodes[i].m_position,
							nodes[i].s_position,
							nodes[i].ime,
							nodes[i].tunagi,
							nodes[i].No,
							nodes[i].cost,
							nodes[i].beforeNo
						);
						open.insert(std::pair<int, ando>((tmp5.ime * 100 + tmp5.tunagi), tmp5));
						close.erase(tmp5.tunagi * 100 + tmp5.ime);
					}
					findfrag = true;
					break;
				}
			}
		}
		if (findfrag == false) {
			// 見つからなければ新規としてOpenリストへ追加
			open.insert(std::pair<int, ando>((nodes[i].ime * 100 + nodes[i].tunagi), nodes[i]));
		}
	}


	//見つかったら探索終了
	if (n.s_position.x== ga.x&&n.s_position.y==ga.y&&n.s_position.z==ga.z) return -1;

	return Kans(count + 1);

}
int keiroK::GetDistance(CVector3 iP ,CVector3 GP)
{
	return (iP - GP).Length();
}
void keiroK::tansa(CVector3 i, CVector3 Ta, std::vector<int> *a,int Leftfrag)
{

	AI_manager *game = FindGO<AI_manager>("AI_manager");
	for (int l = 0; l < game->pasu[Leftfrag].Pasuresuto.size(); l++) {
		if(game->pasu[Leftfrag].Pasuresuto[l].No.size()>1)
		resuto1.push_back(game->pasu[Leftfrag].Pasuresuto[l]);
	}
	CVector3 ko = game->pasu[Leftfrag].m_pointList[resuto1[0].No[0]-1] - i;
	float sa = ko.Length();

	CVector3 koj = game->pasu[Leftfrag].m_pointList[resuto1[0].No[0]-1] - Ta;
	float saj = koj.Length();
	int l = resuto1.size();
	for (int h = 1; h < l; h++) {
		CVector3 k = game->pasu[Leftfrag].m_pointList[resuto1[h].No[0]-1] - i;
		float saa = k.Length();
		CVector3 kf = game->pasu[Leftfrag].m_pointList[resuto1[h].No[0]-1] - Ta;
		float san = kf.Length();
		if (sa > saa) {
			sa = saa;
			f = resuto1[h].No[0];
			No = h;
		}
		if (saj > san) {
			saj = san;
			N = resuto1[h].No[0];
		}
	}
	ga = game->pasu[Leftfrag].m_pointList[N-1];
	fa = game->pasu[Leftfrag].m_pointList[f-1];
	Satando(
		&stuyt,
		fa,
		CVector3::Zero,
		f,
		f,
		resuto1[No].No,
		0,
		f * 100 + 0
	); 
	open.insert(std::pair<int, ando>((f *100+ N),stuyt));
	if (Kans(0) == -1) {
		auto han = close.begin();
		float hairetu= N;
		jyunban.push_back(hairetu);
		while (han != close.end())
		{
			if (hairetu == han->second.tunagi) {
				hairetu = han->second.ime;
				jyunban.push_back(hairetu);
				han = close.begin();
				if (hairetu == f)
				{
					break;
				}
			}
			han++;
		}
	}
	for (int goulo = jyunban.size()-1; goulo >=0; goulo--) {
		a->push_back(jyunban[goulo]);
	}
	open.clear();
	close.clear();
	resuto1.clear();
	jyunban.clear();
	f = 1;
	N = 1;
	sum = 0;
	sumd = 0;
	fghjkl = 0;
}