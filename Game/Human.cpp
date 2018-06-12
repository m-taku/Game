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
	auto ka= std::find(Humans.begin(), Humans.end(), this);
	Humans.erase(ka);

}
bool Human::Start()
{
	return true;
}
void Human::Update() {

}