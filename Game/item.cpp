#include "stdafx.h"
#include "item.h"
#include"AI.h"
#include <math.h>
item::item()
{
}


item::~item()
{
}

bool item::Start()
{
	Pp = FindGO<Player>("Player");
	itemModelData.Load(L"modelData/item.cmo");
	itemModel.Init(itemModelData);
	
	
	return true;
}

float item::item_to_player_dist(CVector3 playerpos, CVector3 itemposition)
{
	CVector3 item_to_player_vector = itemposition - playerpos;
	float item_to_player_distance = sqrt(item_to_player_vector.x*item_to_player_vector.x + item_to_player_vector.y*item_to_player_vector.y + item_to_player_vector.z*item_to_player_vector.z);
	return item_to_player_distance;
}
void item::Update()
{
	if (item_to_player_dist(Pp->GetPosition(), itempos)<50.0f)
	{
		Pp->set_itemcounter();
		DeleteGO(this);
	}
	itemQrot.SetRotationDeg(CVector3::AxisY, 100.0f*GameTime().GetFrameDeltaTime());
	itemrot.Multiply(itemQrot);

	itemModel.Update(itempos, itemrot, CVector3::One);
}

void item::Render(CRenderContext& rc)
{
	itemModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		
}