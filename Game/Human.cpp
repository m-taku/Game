#include "stdafx.h"
#include "Human.h"

std::vector<Human*> Humans;
Human::Human()
{
	Humans.push_back(this);
	SetTags(1);
}


Human::~Human()
{
	
}
bool Human::Start()
{
	return true;
}
void Human::Update() {

}