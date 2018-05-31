#include "stdafx.h"
#include "carRender.h"


carRender::carRender()
{
}


carRender::~carRender()
{
}

bool carRender::Start()
{
	m_skinModelData.Load(L"modelData/Vehicle_SUV1.cmo");//ÉvÉåÉCÉÑÅ[ÇèëÇØ
	m_skinModel.Init(m_skinModelData,carkosuu);
	m_skinModel.SetShadowCasterFlag(true);
	m_skinModel.SetShadowReceiverFlag(true);
	return true;
}

void carRender::PreUpdate()
{
	m_skinModel.BeginUpdateInstancingData();
}
void carRender::PostUpdate()
{
	m_skinModel.EndUpdateInstancingData();
}

void carRender::UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
{
	m_skinModel.UpdateInstancingData(trans, rot, scale);
}
void carRender::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}