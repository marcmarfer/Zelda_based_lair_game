#pragma once
#include <iostream>
#include "Entity.h"

using namespace std;

class SpearMoblin : public Entity {

private:
	//global vars
	int spearHit;

public:
	//getters
	int getSpearHit();

	//setters
	int setSpearHit(int pSpearHit);

	//constructor
	SpearMoblin(string pName, int pHp, int pSpearHit);
};