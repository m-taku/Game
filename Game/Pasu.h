#pragma once
#include"kanren.h"
class PathEdge {
public:
	CVector3 startPos;		//!<始点。
	CVector3 endPos;		//!<終点。
	CVector3 direction;		//!<方向。
	CVector3 directionXZ;	//!<XZ平面での方向。
	int no;
	///*!
	//*@brief	エッジまでの最短ベクトルを計算。
	//*/
	//CVector3 CalcVectorToEdge(const CVector3& point) const;
};
class Pasu
{
public:
	Pasu();
	~Pasu();
	void Load(const wchar_t* filePath);
	int GetNumPoint() const
	{
		return static_cast<int>(m_pointList.size());
	}
	/*!
	*@brief	最近棒のエッジを検索。
	*/
	//const PathEdge* GetNearEdge(const CVector3& pos)const;
	///*!
	//*@brief	エッジの数を取得。
	//*/
	//int GetNumEdge() const
	//{
	//	return m_edgeList.size();
	//}
	///*!
	//*@brief	エッジを取得。
	//*/
	//const PathEdge* GetEdge(const int no) const
	//{
	//	return &m_edgeList[no];
	//}
	std::vector<CVector3> m_pointList;	//!<座標のリスト。
	kanren kan;
	std::vector<kanren> Pasuresuto;
private:
	std::vector<int> No2;

	std::vector<std::vector<int>> No12;
	//std::vector<PathEdge> m_edgeList;		//!<エッジのリスト。
};




