#include "stdafx.h"
#include "keiroK.h"
#include"AI.h"
#include"Game.h"
#include"math.h"
#include "kanren.h"
keiroK::keiroK()
{
}
keiroK::~keiroK()
{
}
ando *Satando(ando* n, CVector3 m_p, CVector3 s_p,int a,int t, std::vector<int> k , int ka)
{
	n->m_position = m_p;
	n->s_position = s_p;
	n->ime = a;
	n->tunagi = t;
	n->No = k;
	n->cost = ka;
	return n;
}
int keiroK::BackTrace(int x)
{

	if (x == f) {
		return 1;
	}
	std::vector<ando>::iterator tmp = close.begin();
	for (; tmp < close.end(); tmp++) {
		if (tmp->ime == x) {
			x = tmp->tunagi;
			break;
		}
	}
	if (tmp == close.end())
		return 0;

	return BackTrace(tmp->tunagi) + 1;
}
int keiroK::Kans(int count)
{
	if (open.empty())return -10000;
	ando nodes[8];
	resuto1;
	std::vector<ando>::iterator it;
	std::vector<ando>::iterator itmix;
	ando n;
	int costmix = 99999;
	int goulkost = 0;
	int fhuj = 0,kesu =0;
	it = open.begin();
	while (it != open.end()) {
		if (costmix > GetDistance(it->m_position, stuyt.s_position)) {
			costmix = GetDistance(it->m_position, stuyt.s_position);
			itmix = it;
			kesu = fhuj;
		}
		it++;
		fhuj++;
	}
	Satando(
		&n,
		itmix->m_position,
		itmix->s_position,
		itmix->ime,
		itmix->tunagi,
		itmix->No,
		itmix->cost
	);
	close.insert(close.begin() + sumd++, n);
	open.erase(open.begin() + kesu);
	sum--;
	goulkost = BackTrace(n.tunagi);
	kanren* ka = &resuto1[n.ime-1];
	for (int i = 0; i < ka->No.size(); i++) {
		Satando(
			&nodes[i],
			ka->m_position[i],
			n.m_position,
			ka->No[i],
			n.ime,		
			resuto1[ka->No[i]-1].No,
			goulkost + GetDistance(ka->m_position[i], ga) + 1
		);
		std::vector<ando>::iterator tmp = open.begin();
		for (int d = 0; d < open.size(); d++) {
			if (nodes[i].ime == tmp->tunagi) {
				fghjkl = d;
				break;
			}
			tmp++;
		}
		if (tmp != open.end()) {
			if (nodes[i].cost < open[fghjkl].cost) {
				open[fghjkl].m_position = n.m_position;
				open[fghjkl].ime = n.ime;
				open[fghjkl].cost = nodes[i].cost;
			}
			continue;
		}
		std::vector<ando>::iterator tmp1 = close.begin();
		for (int d=0; d<close.size(); d++) {
			if (nodes[i].ime == tmp1->tunagi) {
				fghjkl = d;
				break;
			}
			tmp1++;
		}
		if (tmp1 != close.end()) {
			if (nodes[i].cost < close[fghjkl].cost) {
				ando tmp5;
				Satando(
					&tmp5,
					nodes[i].m_position,
					nodes[i].s_position,
					nodes[i].ime,
					nodes[i].tunagi,
					nodes[i].No,
					nodes[i].cost
				);

				open.insert(open.begin() + sum++, tmp5);
				close.erase(close.begin() + fghjkl);
				--sumd;
			}
			continue;
		}
		// 見つからなければ新規としてOpenリストへ追加
		open.insert(open.begin() + sum++ , nodes[i]);
	}


	//見つかったら探索終了
	if (n.m_position.x== ga.x&&n.m_position.y==ga.y&&n.m_position.z==ga.z) return -1;

	return Kans(count + 1);

}
int keiroK::GetDistance(CVector3 iP ,CVector3 GP)
{
	float  sa_X = iP.x-GP.x;
	float  sa_Y = iP.z - GP.z;
	if (sa_X < 0)sa_X *= -1;
	if (sa_Y < 0)sa_Y *= -1;
	if (sa_X < sa_Y) {
		return (sa_X + (sa_Y - sa_X));
	}
	else {
		return (sa_Y + (sa_X - sa_Y));
	}
}
void keiroK::tansa(CVector3 i, CVector3 Ta, std::vector<int> *a)
{
	Game *game = FindGO<Game>("Game");
	for (int l = 0; l < game->pasu.Pasuresuto.size(); l++) {
		resuto1.push_back(game->pasu.Pasuresuto[l]);
	}
	CVector3 ko = game->pasu.m_pointList[0] - i;
	float sa = ko.Length();

	CVector3 koj = game->pasu.m_pointList[0] - Ta;
	float saj = koj.Length();
	int l = resuto1.size();
	for (int h = 1; h < l; h++) {
		CVector3 k = game->pasu.m_pointList[h] - i;
		float saa = k.Length();
		CVector3 kf = game->pasu.m_pointList[h] - Ta;
		float san = kf.Length();
		if (sa > saa) {
			sa = saa;
			f = h;
		}
		if (saj > san) {
			saj = san;
			N = h;
		}
	}
	fa = game->pasu.m_pointList[f++];
	ga = game->pasu.m_pointList[N++];
	Satando(
		&stuyt,
		fa,
		ga,
		f,
		-1,
		resuto1[f - 1].No,
		0
	);
	open.insert(open.begin() + sum++, stuyt);
	if (Kans(0) == -1) {
		auto han = close.begin();
		int hairetu = f;
		jyunban.push_back(hairetu);
		for (; han < close.end(); han++) {
			if (han->tunagi == hairetu) {
				hairetu = han->ime;
				jyunban.push_back(hairetu);
				han = close.begin();
			}
		}
	}
	for (int goulo = 0; goulo < jyunban.size(); goulo++) {
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
