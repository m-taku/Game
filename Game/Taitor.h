#pragma once
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);

};

