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
int keiroK::Kans(int currentCost)
{
	return -1000;
}
void keiroK::tansa(CVector3 i, CVector3 Ta, std::vector<int> *a,int Leftfrag)
{
	//開始
	auto& kanrenList = AI_ado->pasu[Leftfrag].Pasuresuto;
	//開始ノードを検索する。
	auto minDist = FLT_MAX;
	kanren* startNode = nullptr;
	for (auto& kanren : kanrenList) {
		auto vDist = i - kanren.m_position[0];
		if (minDist > vDist.Length()) {
			//こっちが近い。
			minDist = vDist.Length();
			startNode = &kanren;
		}
	}
	//終了ノードを検索する。
	minDist = FLT_MAX;
	kanren* endNode = nullptr;
	for (auto& kanren : kanrenList) {
		auto vDist = Ta - kanren.m_position[0];
		if (minDist > vDist.Length()) {
			//こっちが近い。
			minDist = vDist.Length();
			endNode = &kanren;
		}
	}

	auto currentNode = startNode;
	//終端ノードに到達するまでループする。
	std::vector<int> openNodeNos;
	std::vector<int> closeNodeNos;
	kanren* parentNode = nullptr;
	//開始ノードをオープンリストに積む。
	openNodeNos.push_back(currentNode->No[0]-1);
	float moveCost = 0.0f;
	while (currentNode != endNode && openNodeNos.empty() == false) {
		//オープンされているリストへの移動コストを計算する。
		//次に開くノードを選ぶ。
		minDist = FLT_MAX;
		auto nextNodeNo = -1;
		for (auto nodeNo : openNodeNos) {
			//終了地点までの距離を計算する。
			//ここは要改善。
			auto vDist = kanrenList[nodeNo].m_position[0] - Ta;
			if (minDist > vDist.Length()) {
				//こちらのほうが近い。
				minDist = vDist.Length();
				nextNodeNo = nodeNo;
			}
		}
		//カレントノードを見つかったノードにする。
		currentNode = &kanrenList[nextNodeNo];
		currentNode->SetParentNode(parentNode);
		parentNode = currentNode;
		//次のノードをクローズ。
		closeNodeNos.push_back(nextNodeNo);
		//オープンリストから削除。
		auto itFind = std::find(openNodeNos.begin(), openNodeNos.end(), nextNodeNo);
		openNodeNos.erase(itFind);
		//オープンリストを作成。
		for (int i = 1; i < currentNode->No.size(); i++) {
			//クローズされていないか調べる。
			itFind = std::find(closeNodeNos.begin(), closeNodeNos.end(), currentNode->No[i]);
			if (itFind == closeNodeNos.end()) {
				//クローズされていない。
				openNodeNos.push_back(currentNode->No[i]-1);
			}
		}
	}
	
	while (currentNode != startNode) {
		a->push_back(currentNode->No[0]);
		currentNode = currentNode->GetParentNode();
	}
	//目標地点からの逆順になっているのでリバース。
	std::reverse(a->begin(), a->end());
}