#include "tkEngine/tkEnginePreCompile.h"
#include "tkVolumeLight.h"

namespace tkEngine
{
	namespace prefab
	{
		bool CVolumeLight::Start()
		{

			return true;
		}

		void CVolumeLight::Init()
		{
			m_skinModelData.Load(L"modelData/VolumeLight.cmo");
			m_skinModel.Init(m_skinModelData, m_volumeLightList.size());
			m_skinModel.SetShadowCasterFlag(false);
			m_skinModel.SetShadowReceiverFlag(false);
			m_skinModel.SetIsZPrePass(false);
			m_skinModel.SetIsGBuffer(false);
		}

		void CVolumeLight::Update()
		{
			m_skinModel.BeginUpdateInstancingData();
			for (auto& volumeLight : m_volumeLightList)
			{
				m_skinModel.UpdateInstancingData(volumeLight.s_position, CQuaternion::Identity, CVector3::One, CSkinModel::enFbxUpAxisZ);
			}
			m_skinModel.EndUpdateInstancingData();
		}

		void CVolumeLight::VolumeLightRender(CRenderContext & rc)
		{
			m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}
		void CVolumeLight::AddVolumeLight(SVolumeLightInfo & info)
		{
			m_volumeLightList.push_back(info);
		}
	}
}

