#pragma once
#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "Level.h"
#include"carRender.h"
class Level;
class car;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	bool Start();
	void Update();
	void Car_create();
	void Car_delete();
	void Render(CRenderContext& rc);
	void OnDestroy();
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CMeshCollider m_meshCollider;	//メッシュコライダー。
	CRigidBody m_rigidBody;			//剛体
	
	int incNo()
	{
		return No++;
	}
	int GatNo()
	{
		return No;
	}
	void risetteNo()
	{
		No = 0;
	}

	int Gatpasusaiz(int i) const
	{
	return  pasu2[i].size();
	}
	std::vector<int>::iterator getDate(int i) {
		return pasu2[i].begin();
	}

	std::vector<car*> getcarv(){
		return carv;
	}
private:
	Level m_level[10];
	CPhysicsStaticObject m_physicsStaticObject;
	CSkinModel s_skinModel;					//スキンモデル。
	CSkinModelData s_skinModelData;			//スキンモデルデータ。
	carRender* kar;
	int No = 0;
	int Stege_No = 0;
	std::vector<car*> carv;
	std::vector<int> movepasu1 = { 17,12,6,5,13,16,33,36,44,43,42,41,39,30,28,27 };
	std::vector<int> movepasu2 = { 11,18,22,21,29,40,48,47,46,45,35,34,15,14,4,3 };
	std::vector<int> movepasu3 = { 8,7,11,18,22,21,29,40,48,47,37,32,22,21,19,10 };
	std::vector<int> movepasu4 = { 4,3,11,18,31,38,42,41,39,30,28,27,26,25,15,14 };
	std::vector<int> movepasu5 = { 13,16,24,23,31,38,42,41,39,30,28,27,17,12,6,5 };
	std::vector<int> movepasu6 = { 35,34,24,23,22,21,19,10,8,7,6,5,13,16,24,23,22,21,29,40,48,47,46,45 };
	std::vector<int> movepasu7 = { 44,43,42,41,39,30,19,10,8,7,11,18,26,25,33,36 };
	std::vector<int> movepasu8 = { 28,27,26,25,15,14,4,3,11,18,31,38,46,45,35,34,24,23,22,21,29,40,48,47,37,32,17,12,2,1,9,20 };
	std::vector<int> movepasu9 = { 39,30,19,10,8,7,11,18,26,25,33,36,44,43,42,41 };
	std::vector<int> movepasu10 = { 48,47,37,32,22,21,19,10,8,7,6,5,13,16,24,23,22,21,29,40 };
	std::vector<int> movepasu11 = { 29,40,48,47,46,45,35,34,24,23,31,38,42,41,39,30,28,27,17,12,2,1,9,20 };
	std::vector<int> movepasu12 = { 9,20,29,40,48,47,46,45,35,34,24,23,21,19,10,8,7,6,5,13,16,33,36,44,43,37,32,17,12,2,1 };
	std::vector<int> movepasu13 = { 18,31,38,42,41,39,30,28,27,26,25,33,36,44,43,37,32,17,12,6,5,13,16,33,36,44,43,37,32,26,25,15,14,4,3,11 };
	std::vector<int> movepasu14 = { 24,23,22,21,19,10,8,7,11,18,31,38,42,41,39,30,28,27,26,25,33,36,44,43,42,41,39,30,19,10,8,7,6,5,13,16 };
	std::vector<int> movepasu15 = { 22,21,19,10,8,7,6,5,13,16,33,36,44,43,42,41,39,30,19,10,8,7,11,18 };
	std::vector<int> movepasu16 = { 31,38,46,45,35,34,15,14,4,3,2,1,9,20,29,40,48,47,46,45,35,34,15,14,4,3,11,18 };
	std::vector<int> movepasu17 = { 26,25,33,36,44,43,42,41,39,30,28,27,26,25,15,14,4,3,2,1,9,20,28,27 };
	std::vector<int> movepasu18 = { 37,32,26,25,15,14,4,3,2,1,9,20,28,27,17,12,6,5,13,16,33,36,44,43 };
	std::vector<int> movepasu19 = { 20,29,40,48,47,37,32,26,25,33,36,44,43,37,32,17,12,2,1,9 };
	std::vector<int> movepasu20 = { 27,26,25,15,14,4,3,2,1,9,20,28 };
	std::vector<int> movepasu21 = { 46,45,35,34,24,23,22,21,19,10,8,7,6,5,13,16,24,23,31,38 };
	std::vector<int> movepasu22 = { 19,10,8,7,6,5,13,16,24,23,22,21,29,40,48,47,37,32,22,21 };
	std::vector<int> movepasu23 = { 33,36,44,43,37,32,26,25,15,14,4,3,2,1,9,20,29,40,48,47,37,32,17,12,6,5,13,16 };
	std::vector<std::vector<int>> pasu2;
};

