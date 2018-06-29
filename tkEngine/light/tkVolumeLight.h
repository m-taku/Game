#pragma once
#include "tkEngine/Light/tkLightBase.h"

namespace tkEngine
{
	struct SVolumeLightInfo
	{
		CVector3 s_position;
	};
	namespace prefab
	{
		class CVolumeLight : public IGameObject
		{
		public:
			bool Start()override;

			void Init();

			void Update()override;

			void VolumeLightRender(CRenderContext& rc)override;

			void AddVolumeLight(SVolumeLightInfo& info);
		private:
			std::vector<SVolumeLightInfo> m_volumeLightList;
			CSkinModelData	m_skinModelData;
			CSkinModel		m_skinModel;
			CVector3*		m_position;
		};
	}
}