#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

bool item::Start()
{
	tp = FindGO<tekihei>("tekihei");
	itemModelData.Load(L"modelData/item.cmo");
	for (int i = 0;i < tekikazu;i++)
	{
		itemf[i] = 0;
		itemModel[i].Init(itemModelData);
	}
	
	
	return true;
}

void item::Update()
{

	//for (int i = 0;i < tekikazu;i++)
	//{
	//	if (tp != NULL)
	//	{
	//		if (tp->tekiheiflag[i] == 0)
	//		{
	//			itemf[i] = 1;
	//			itempos[i] = tp->tekipos[i];
	//		}
	//	}
	//	if(itemf[i]==1)
	//	itemModel[i].Update(itempos[i], itemrot[i], CVector3::One);
	//}
	//
}

void item::Render(CRenderContext& rc)
{
	for (int i = 0;i < tekikazu;i++)
	{
		if(itemf[i]==1)
		itemModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
		
}