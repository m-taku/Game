#include "stdafx.h"
#include "Level.h"
#include "MapChip.h"
#include"LevelRender.h"
Level::Level()
{
}


Level::~Level()
{
	for (auto& mapChip : m_mapChipList) {
		DeleteGO(mapChip);
	}
}

/*!
*@brief	レベルの作成。
*@param[in]	levelDataFilePath	読み込むレベルデータのファイルパス。
*/
void Level::Build(const wchar_t* levelDataFilePath)
{
	//今回は配置データとしてスケルトンを利用する。
	CLocData locData;
	locData.Load(levelDataFilePath);
	std::map<std::wstring, std::list<MapChip*>> objListDataMap;
	for (int i = 0; i < locData.GetNumObject(); i++) {
		//マップチップを構築。
		CVector3 position, scale;
		CQuaternion rotation;
		scale = CVector3::One;
		position = locData.GetObjectPosition(i);
		rotation = locData.GetObjectRotation(i);
		CQuaternion qRotation;
		qRotation.SetRotationDeg(CVector3::AxisX, -90.0f);
		rotation.Multiply(rotation, qRotation);
		//ボーン名からモデルデータのファイルパスを作成する。
		const wchar_t* boneName = locData.GetObjectName(i);
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		MapChip* mapChip = NewGO<MapChip>(0);

#ifdef instansingu_katto
		mapChip->Getmama(modelDataFilePath);
#endif
		mapChip->Init(position, rotation, CVector3::One);

		m_mapChipList.push_back(mapChip);
#ifndef instansingu_katto
		//マップにオブジェクトが存在しているか検索する。
		auto itObjData = objListDataMap.find(boneName);
		if (itObjData == objListDataMap.end()) {
			//マップに存在しないオブジェクトなので、新規の
			//オブジェクトデータリストを追加。
			itObjData = objListDataMap.insert({ boneName , std::list<MapChip*>() }).first;
		}
		auto& mapChipList = itObjData->second;
		mapChipList.push_back(mapChip);
	}
	for (auto& objDataList : objListDataMap) {
		LevelRender* render = NewGO<LevelRender>(0, nullptr);
		render->Init(objDataList.first.c_str(), objDataList.second.size());
		for (auto& mapChip : objDataList.second) {
			mapChip->PostInitAfterInitLevelRender(render);
		}
	}
}

#else
		m_skinModelData.Load(modelDataFilePath);
		m_skinModel.Init(m_skinModelData);
		m_skinModel.SetShadowCasterFlag(true);
		m_skinModel.SetShadowReceiverFlag(true);
	}
}

#endif // Mizuki_baka
	
	/*kaunto.push_back(0);
	L_pos.push_back(CVector3::Zero);
	L_scale.push_back(CVector3::Zero);
	L_AI4.push_back(CQuaternion::Identity);
	for (int i = 0; i < locData.GetNumObject(); i++) {
		i_pos = L_pos.begin();
		i_scale = L_scale.begin();
		i_AI4 = L_AI4.begin();
		//平行移動、回転を取得する。
		CVector3 position, scale;
		CQuaternion rotation;
		scale = CVector3::One;
		position = locData.GetObjectPosition(i);
		rotation = locData.GetObjectRotation(i);
		CQuaternion qRotation;
		qRotation.SetRotationDeg(CVector3::AxisX, -90.0f);
		rotation.Multiply(rotation, qRotation);
		//ボーン名からモデルデータのファイルパスを作成する。
		const wchar_t* boneName = locData.GetObjectName(i);
		wchar_t modelDataFilePath[256];
		swprintf(modelDataFilePath, L"modelData/%s.cmo", boneName);
		if (i < 1) {
			name = modelDataFilePath;
			nameNo.push_back(name);
			hairetuNo++;
		}
		MapChip* mapChip = NewGO<MapChip>(0);
		mapChip->Init(modelDataFilePath, position, CVector3::One, rotation);
		m_mapChipList.push_back(mapChip);
		for (No = 0; No < nameNo.size(); No++) {
			std::wstring DataFilePath = nameNo[No];
			
			int h = wcscmp(modelDataFilePath, DataFilePath.c_str());
			if (h == 0) {
				kaunto[No]++;
				for (int k = 0; k < No; k++) {
					for (int l = 0; l < kaunto[k]; l++) {
						i_pos++;
						i_AI4++;
						i_scale++;
					}
				}
				L_pos.insert(i_pos, position);
				L_scale.insert(i_scale, scale);
				L_AI4.insert(i_AI4, rotation);
				break;
			}

		}
		if (No == nameNo.size()) {
			name = modelDataFilePath;
			nameNo.push_back(name);
			hairetuNo++;
			kaunto.push_back(1);
			for (int k = 0; k < kaunto.size(); k++) {
				for (int l = 0; l < kaunto[k]; l++) {
					i_pos++;
					i_AI4++;
					i_scale++;
				}
			}
			L_pos.insert(i_pos, position);
			L_scale.insert(i_scale, scale);
			L_AI4.insert(i_AI4, rotation);
		}
	}
	i_pos = L_pos.begin();
	i_scale = L_scale.begin();
	i_AI4 = L_AI4.begin();
	for (int No = 0; No < nameNo.size(); No++) {
		LevelRender* lao = NewGO<LevelRender>(0, nullptr);
		lao->Satcarkosuu(kaunto[No]);
		std::wstring kau = nameNo[No];
		
		lao->Init(kau.c_str(), i_pos, i_AI4, i_scale);
		for (int k = 0; k < kaunto[No]; k++) {
			L_pos.pop_front();
			L_AI4.pop_front();
			L_scale.pop_front();
		}
		i_pos = L_pos.begin();
		i_AI4 = L_AI4.begin();
		i_scale = L_scale.begin();
	}*/

