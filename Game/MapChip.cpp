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


#ifndef instansingu_katto
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
#else

	m_skinModel.Init(m_skinModelData);
	m_physicsStaticObject.CreateMeshObject(m_skinModel, m_position, m_rotation);
}

void MapChip::Update() {
	m_skinModel.Update(m_position, m_rotation, m_scale);
}
void MapChip::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
#endif

