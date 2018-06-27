#include "tkEngine/tkEnginePreCompile.h"
#include "tkVolumeLight.h"

namespace tkEngine
{
	namespace prefab
	{
		bool CVolumeLight::Start()
		{
			m_skinModelData.Load(L"modelData/VolumeLight.cmo");
			m_skinModel.Init(m_skinModelData);
			m_skinModel.SetShadowCasterFlag(false);
			m_skinModel.SetShadowReceiverFlag(false);
			m_skinModel.SetIsZPrePass(false);
			m_skinModel.SetIsGBuffer(false);
			return true;
		}

		void CVolumeLight::Init(CVector3* pos)
		{
			m_position = pos;
		}

		void CVolumeLight::Update()
		{
			CVector3 pos = *m_position;
			pos.z += 100.0f;
			pos.y += 150.0f;
			CQuaternion rot = CQuaternion::Identity;
			m_skinModel.Update(pos, rot, CVector3::One, tkEngine::CSkinModel::enFbxUpAxisZ);
		}

		void CVolumeLight::VolumeLightRender(CRenderContext & rc)
		{
			m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}
	}
}

