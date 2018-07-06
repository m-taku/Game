#pragma once
#include "tkEngine/Light/tkLightBase.h"

namespace tkEngine
{
	namespace prefab
	{
		class CVolumeLight : public IGameObject
		{
		public:
			bool Start()override;

			void Init(CVector3* pos);

			void Update()override;

			void VolumeLightRender(CRenderContext& rc)override;
		private:
			CSkinModelData	m_skinModelData;
			CSkinModel		m_skinModel;
			CVector3*		m_position;
		};
	}
}