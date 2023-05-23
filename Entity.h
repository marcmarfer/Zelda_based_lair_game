#pragma once
#include <iostream>
using namespace std;

class Entity {

private:
	//global vars
	string name;
	int hp;

public:
	//getters
	string getName();
	int getHp();

	//setters
	void setName(string pName);
	int setHp(int pHp);

	//constructor
	Entity(string pName, int pHp);
};