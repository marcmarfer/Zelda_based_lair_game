#include "Ganondorf.h"
using namespace std;


//constructor
Ganondorf::Ganondorf(string pName, int pHp, int pOneSwordAttack, int pTwoSwordsAttack)
	: Entity(pName, pHp) {
	oneSwordAttack = pOneSwordAttack;
	twoSwordsAttack = pTwoSwordsAttack;
}

//getters
int Ganondorf::getOneSwordAttack() {
	return oneSwordAttack;
}

int Ganondorf::getTwoSwordsAttack() {
	return twoSwordsAttack;
}

//setters
int Ganondorf::setOneSwordAttack(int pOneSwordAttack) {
	oneSwordAttack = pOneSwordAttack;
	return oneSwordAttack;
}

int Ganondorf::setTwoSwordsAttack(int pTwoSwordsAttack) {
	twoSwordsAttack = pTwoSwordsAttack;
	return twoSwordsAttack;
}
