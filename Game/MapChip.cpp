#include "stdafx.h"
#include "MapChip.h"




void MapChip::OnDestroy()
{
	DeleteGO(m_skinModelRender);
}
void MapChip::Init(
	const wchar_t* modelFilePath,
	CVector3 pos,
	CVector3 scale,
	CQuaternion rotation
) {
	m_position = pos;
	m_rotation = rotation;
#if BUILD_LEVEL != BUILD_LEVEL_MASTER

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(modelFilePath);
	
	//静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateMeshObject(m_skinModelRender, m_position, m_rotation);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
#endif
}

