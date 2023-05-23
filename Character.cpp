#include "Character.h"
using namespace std;

//constructor
Character::Character(string pName, int pHp, int pSwordBlow)
	: Entity(pName, pHp) {

	swordBlow = pSwordBlow;
}

//getters
int Character::getSwordBlow() {
	return swordBlow;
}

//setters
int Character::setSwordBlow(int pSwordBlow) {
	swordBlow = pSwordBlow;
	return swordBlow;
}

