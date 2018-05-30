#pragma once
class carRender:public IGameObject
{
public:
	carRender();
	~carRender();
	bool Start();
	void PreUpdate();
	void PostUpdate();
	void UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale);
	void Render(CRenderContext& rc);
	void Satcarkosuu(int suu)
	{
		carkosuu = suu;
	}
private:
	int carkosuu=0;
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
};

