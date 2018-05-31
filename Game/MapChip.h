#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

class LevelRender;

class MapChip : public IGameObject
{
public:
	void OnDestroy() override;
	void Init(
		CVector3 pos,
		CQuaternion rotation,
		CVector3 scale
	);
	//レベルレンダーを初期化した後で呼び出される、遅延初期化。
	void PostInitAfterInitLevelRender(LevelRender* render);
	void Update();
	
	//////////////////////////////////////////////////
	// ここからメンバ変数。
	//////////////////////////////////////////////////

	CPhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。
	CVector3 m_position;				//!<座標。
	CVector3 m_scale;
	CQuaternion m_rotation;				//!<回転。
private:
	LevelRender* m_levelRender = nullptr;	//!<レベルレンダラー。
};

