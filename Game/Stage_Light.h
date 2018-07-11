#pragma once
class Stage_Light : public IGameObject
{
public:
	Stage_Light();
	~Stage_Light();
	bool Start();
	void Update();
private:
	std::vector<prefab::CPointLight*> point;
	//prefab::CVolumeLight* m_volumeLight;
	//prefab::CPointLight*     m_point;
	prefab::CDirectionLight* m_sunLig = nullptr;	//	‘¾—zƒ‰ƒCƒgB
};

