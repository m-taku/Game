#pragma once
#include"Pasu.h"

class Dog;
class Osu;
class AI_manager : public IGameObject
{
public:
	AI_manager();
	~AI_manager();

	Pasu pasu[10];
	bool Start(); 
	void SatRSaizon(int No)
	{
		RAIseizon[No] = 0;
	}
	void SatLSaizon(int No)
	{
		LAIseizon[No] = 0;
	}
	void SetLeft()
	{
		Leftfrag = 1;
	}
	int GetLeft()
	{
		return Leftfrag;
	}
	int gatsiz(int No)
	{
		return da[No].size();
	}
	int gatLsiz(int No)
	{
		return da2[No].size();
	}

	int Getsize(int No)
	{
		return da[No].size();
	}
	std::vector<int>::iterator getAIDate(int i) {
		return da[i].begin();
	}
	std::vector<int>::iterator getLAIDate(int i) {
		return da2[i].begin();
	}
	int incNo()
	{
		return No++;
	}
private:
	int No = 0;
	int Leftfrag = 0;
	std::vector<Osu*> Rsimin;
	std::vector<Dog*> Lsimin;
	std::vector<int> RAIseizon;
	std::vector<int> LAIseizon;

	std::vector<int> AIR1 = { 26,25,17,16,15,14,19,18,24,28,27 };
	std::vector<int> AIR2 = { 22, 29, 28, 31, 36, 35, 32, 27, 26, 25, 23 };
	std::vector<int> AIR3 = { 14, 15, 16, 17, 18, 19, 20, 23, 24, 18, 19 };
	std::vector<int> AIR4 = { 6, 20, 18, 19, 14, 13, 11, 10, 9, 8, 7 };
	std::vector<int> AIR5 = { 1,2,3,4,5,21,22,29,30,37,38,39,40,41,34,33,26,25,17,16,11,10 };
	std::vector<int> AIR6 = { 2,9,8,7,6,20,18,17,16,11,10,1 };
	std::vector<int> AIR7 = { 3,6,20,21,22,23,24,18,19,20,21,5,4 };
	std::vector<int> AIR8 = { 4,5,21,20,19,14,12,11,10,9,8,7,3 };
	std::vector<int> AIR9 = { 20,23,22,29,28,27,26,25,24,18,19 };
	std::vector<int> AIR10 = { 8,7,6,20,18,17,16,11,10,9 };
	std::vector<int> AIR11 = { 12,13,14,15 };
	std::vector<int> AIR12 = { 18,24,23,20,19 };
	std::vector<int> AIR13 = { 29,30,31,36,35,40,41,34,33,26,27,28 };
	std::vector<int> AIR14 = { 37,36,35,32,33,26,27,28,29,30 };
	std::vector<int> AIR15 = { 33,26,27,28,29,30,37,36,31,32 };
	std::vector<int> AIR16 = { 30,37,36,39,40,35,34,33,32,27,28,31 };
	std::vector<int> AIR17 = { 32,33,26,25,17,16,15,14,19,18,24,23,22,29,28,31 };
	std::vector<int> AIR18 = { 38,39,40,35,32,33,26,27,28,31,30,37 };
	std::vector<int> AIR19 = { 39,36,31,28,27,32,35,40 };
	std::vector<int> AIR20 = { 7,8,13,14,19,20,23,24,18,19,20,6 };
	std::vector<int> AIR21 = { 34,41,40,39,38,37,30,29,22,21,20,19,14,15,12,13,8,9,10,11,16,17,25,26,33 };
	std::vector<int> AIR22 = { 35,36,31,32 };
	std::vector<int> AIR23 = { 36,37,30,29,28,27,26,25,17,16,15,14,13,12,15,14,19,20,21,22,29,28,31 };
	std::vector<int> AIR24 = { 31,28,27,26,25,24,18,20,6,5,21,22,29,30 };
	std::vector<int> AIR25 = { 40,39,36,35,32,31,28,27,32,31,36,35 };
	std::vector<int> AIR26 = { 41,40,39,38,37,36,35,34,33,26,25,17,16,11,10,9,8,7,3,2,1,10,1,16,17,25,26,33,34 };

	std::vector<int> AIL1 = { 48,57,56,52 };
	std::vector<int> AIL2 = { 1,10,11,14,28,29,41,40,39,37,35,36,33,32,25,24,23,6,5,4,3,2 };
	std::vector<int> AIL3 = { 2,3,4,7,20,17,16,15,13,12,12,12,11,10,1 };
	std::vector<int> AIL4 = { 3,22,7,6,5,4 };
	std::vector<int> AIL5 = { 4,7,22,3,2,1,10,9,22,3 };
	std::vector<int> AIL6 = { 5,6,7,16,23,6,7,22,8,2,3,4 };
	std::vector<int> AIL7 = { 8,9 };
	std::vector<int> AIL8 = { 10,11,12,12,13,15,24,25,32,31,30,29,28,14,13,15,16,7,22,3,2,1 };
	std::vector<int> AIL9 = { 11,14,28,29,41,40,39,37,35,34,31,26,25,24,15,13,12 };
	std::vector<int> AIL10 = { 13,15,24,25,32,33,34,56,55,48,42,30,29,28,14 };
	std::vector<int> AIL11 = { 14,28,29,41,42,30,31,34,33,32,25,24,15,13 };
	std::vector<int> AIL12 = { 15,16,17,19,21,22,3,4,5,6,23,24 };
	std::vector<int> AIL13 = { 16,7,6,23 };
	std::vector<int> AIL14 = { 17,22,7,7,4,3,2,1,10,11,14,13,15,24,23,16 };
	std::vector<int> AIL15 = { 18,19,20,21,22,9,10,11,12,13,15,16,17 };
	std::vector<int> AIL16 = { 23,24,15,13,14,28,27,30,31,32,33,36,35,37,39,42,41,29,28,27,26,25,24,15,16 };
	std::vector<int> AIL17 = { 24,25,32,31,26,27,30,29,28,14,13,16,23 };
	std::vector<int> AIL18 = { 25,32,33,36,35,37,40,41,29,28,27,26 };
	std::vector<int> AIL19 = { 26,31,30,42,41,29,28,27 };
	std::vector<int> AIL20 = { 27,30,29,41,42,39,37,35,34,33,32,31,26 };
	std::vector<int> AIL21 = { 28,29,41,42,30,31,32,33,36,35,34,31,26,27 };
	std::vector<int> AIL22 = { 29,30,31,32,33,34,55,48,42,41,40,39,37,35,36,33,34,31,30,27,28 };
	std::vector<int> AIL23 = { 30,27,26,25,24,23,16,17,18,19,20,21,22,3,2,1,10,11,14,28,29,41,42 };
	std::vector<int> AIL24 = { 31,34,35,37,39,42,30 };
	std::vector<int> AIL25 = { 32,33,34,31,26,25,24,15,16,7,6,23,24,25 };
	std::vector<std::vector<int>> da2;
	std::vector<std::vector<int>> da;

};

extern AI_manager* AI_ado;