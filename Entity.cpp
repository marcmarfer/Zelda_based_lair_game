#include "Entity.h"
using namespace std;

//contructor
Entity::Entity(string pName, int pHp) {
	name = pName;
	hp = pHp;
}

//getters
string Entity::getName() {
	return name;
}

int Entity::getHp() {
	return hp;
}


//setters
void Entity::setName(string pName) {
	name = pName;
}

int Entity::setHp(int pHp) {
	hp = pHp;
	return hp;
}

