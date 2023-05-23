#include "Ocktopus.h"
using namespace std;

//constructor
Ocktopus::Ocktopus(string pName, int pHp, int pThrowRock)
	: Entity(pName, pHp) {
	throwRock = pThrowRock;
}

//getters
int Ocktopus::getThrowRock() {
	return throwRock;
}

//setters
int Ocktopus::setThrowRock(int pThrowRock) {
	throwRock = pThrowRock;
	return throwRock;
}
