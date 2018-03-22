
#pragma once

#include "MapChip.h"

	//レベル。
class Level
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
	std::vector<MapChip*> m_mapChipList;		//マップチップのリスト。
};