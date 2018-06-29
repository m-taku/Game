#pragma once
class kanren 
{
public:

	kanren();
	~kanren();
	std::vector<CVector3> m_position;
	std::vector<int> No;
	
	void kanrenz(std::vector<int> &a, std::vector<CVector3> &b);
	//親のノードを設定する。
	void SetParentNode(kanren* node)
	{
		m_parentNode = node;
	}
	kanren* GetParentNode()
	{
		return m_parentNode;
	}
	std::vector<float> moveCosts;		//隣接ノードに移動するコスト。
private:
	
	float costFromStart = 0;			//スタート地点からの移動コスト。A*アルゴリズムが実行されたときに設定される。					
	kanren* m_parentNode = nullptr;		//親のノード。A*アルゴリズムが実行されたときに設定される。
};

