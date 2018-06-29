#include "stdafx.h"
#include "Stage_Light.h"

#include "tkEngine\light\tkDirectionLight.h"
#include"tkEngine/graphics/tkLight.h"
#include "tkEngine\light\tkPointLight.h"

Stage_Light::Stage_Light()
{
	m_volumeLight = nullptr;
}


Stage_Light::~Stage_Light()
{
	for (int i = 0; i < point.size(); i++) {
		DeleteGO(point[i]);
	}
	DeleteGO(m_sunLig);
	if (m_volumeLight != nullptr)
	{
		DeleteGO(m_volumeLight);
		m_volumeLight = nullptr;
	}
}

bool Stage_Light::Start() 
{
	m_volumeLight = NewGO<prefab::CVolumeLight>(0);
	CLocData loc;
	loc.Load(L"lever/laitLv001.tks");
	for (int i = 0; i < loc.GetNumObject(); i++) {
		point.push_back(NewGO<prefab::CPointLight>(0));
		CVector3 f = loc.GetObjectPosition(i);
		f.y = 500.0f;
		point[i]->SetPosition(f);
		point[i]->SetColor({ 180.0f,255.0f, 0.0f,0.0f });
		point[i]->SetAttn({ 700.0f,4.0f ,0.0f });
		//SVolumeLightInfo volumeInfo;
		//volumeInfo.s_position = f;
		//m_volumeLight->AddVolumeLight(volumeInfo);
	}
	//m_volumeLight->Init();
	m_sunLig = NewGO<prefab::CDirectionLight>(0);
	CVector3 lightDir = { 0.707f, -0.707f, 0.0f };
	m_sunLig->SetDirection(lightDir);
	m_sunLig->SetColor({ 1.0f, 0.05f, 0.8f, 1.0f });
	LightManager().SetAmbientLight({ 1.0f, 1.0f, 1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);
	return true;
}
void Stage_Light::Update()
{
	
}
