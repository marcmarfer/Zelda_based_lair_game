#pragma once
#include <iostream>
#include "Entity.h"

using namespace std;

class Character : public Entity {

private:
	//global vars --- I'm not gonna do setters / getters for sf classes cause they already come with the library
	int swordBlow;

public:
	//getters
	int getSwordBlow();

	//setters
	int setSwordBlow(int pSwordBlow);

	//constructor
	Character(string pName, int pHp, int pSwordBlow);
};

