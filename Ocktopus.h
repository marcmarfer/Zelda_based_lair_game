#pragma once
#include <iostream>
#include "Entity.h"

using namespace std;

class Ocktopus : public Entity {

private:
	//global vars
	int throwRock;

public:
	//getters
	int getThrowRock();

	//setters
	int setThrowRock(int pThrowRock);

	//constructor
	Ocktopus(string pName, int pHp, int pThrowRock);
};