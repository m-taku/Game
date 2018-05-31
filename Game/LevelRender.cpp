#include "stdafx.h"
#include "LevelRender.h"


LevelRender::LevelRender()
{
}


LevelRender::~LevelRender()
{
}
void LevelRender::Init(const wchar_t* objName, int numInstance)
{
	m_numInstance = numInstance;
	wchar_t modelDataFilePath[256];
	swprintf(modelDataFilePath, L"modelData/%s.cmo", objName);
	m_skinModelData.Load(modelDataFilePath);
	if (numInstance > 1) {
		m_skinModel.Init(m_skinModelData, numInstance);
	}
	else {
		m_skinModel.Init(m_skinModelData);
	}
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);


}
void LevelRender::PreUpdate()
{
	m_skinModel.BeginUpdateInstancingData();
}
void LevelRender::PostUpdate()
{
	m_skinModel.EndUpdateInstancingData();
}
void LevelRender::UpdateWorldMatrix(
	const CVector3& trans,
	const CQuaternion& rot,
	const CVector3& scale
)
{
	if (m_numInstance > 1) {
		m_skinModel.UpdateInstancingData(trans, rot, scale);
	}
	else {
		m_skinModel.Update(trans, rot, scale);
	}
}
void LevelRender::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}