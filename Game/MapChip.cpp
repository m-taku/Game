#include "stdafx.h"
#include "MapChip.h"
#include "LevelRender.h"

void MapChip::OnDestroy()
{
}
void MapChip::Init(
	CVector3 pos,
	CQuaternion rotation,
	CVector3 scale
) {
	m_position = pos;
	m_rotation = rotation;
	m_scale = scale;
}
void MapChip::PostInitAfterInitLevelRender(LevelRender* render)
{
	m_levelRender = render;
	m_physicsStaticObject.CreateMeshObject(m_levelRender->GetSkinModel(), m_position, m_rotation);
}
void MapChip::Update()
{
	m_levelRender->UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

