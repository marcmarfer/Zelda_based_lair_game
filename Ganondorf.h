#pragma once
#include <iostream>
#include "Entity.h"

using namespace std;

class Ganondorf : public Entity {
private:
	//global vars
	int oneSwordAttack;
	int twoSwordsAttack;

public:
	//getters
	int getOneSwordAttack();
	int getTwoSwordsAttack();

	//setters
	int setOneSwordAttack(int pOneSwordAttack);
	int setTwoSwordsAttack(int pTwoSwordsAttack);

	//constructor
	Ganondorf(string pName, int pHp, int pOneSwordAttack, int pTwoSwordsAttack);
};