#pragma once
class LevelRender:public IGameObject
{
public:
	LevelRender();
	~LevelRender();
	void Init(const wchar_t* objName,int numInstance);
	void PreUpdate() override;
	void PostUpdate() override;
	void Render(CRenderContext& rc);
	void UpdateWorldMatrix(
		const CVector3& trans,
		const CQuaternion& rot,
		const CVector3& scale
	);
	CSkinModel& GetSkinModel ()
	{
		return m_skinModel;
	}
private:
	int m_numInstance = 0;

	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
};


