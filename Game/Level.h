
#pragma once

#include "MapChip.h"

	//レベル。
class Level:IGameObject
{
public:
	Level();
	~Level();
	/*!
	*@brief	レベルの構築。
	*@param[in]	levelDataFilePath	読み込むレベルデータのファイルパス。
	*/

	void Build(const wchar_t* levelDataFilePath);
	float X = 0.0f, Z = 0.0f;
	///////////////////////////////////////////////
	// ここからメンバ変数。
	///////////////////////////////////////////////
private:
	std::vector<int> kaunto;
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。

	std::vector<LevelRender*> render;
	std::wstring name;
	int renderNo = 0;
	std::vector<MapChip*> m_mapChipList;		//マップチップのリスト。
	std::vector<std::wstring> nameNo;
	int hairetuNo = 0;
	int No=0;
};