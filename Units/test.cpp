#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	Sniper i(10,3);
	Base g(3,3);
	Unit *unit1 = &i;
	Unit *unit2 = &g;
	pair<int,int> des;
	des = make_pair(18,11);
	int row =20;
	int col =20;
	int visibility = 3;
	bool move;
	move=unit1->attack(des, visibility, unit2);
	unit1->print();
	return 0;
}
