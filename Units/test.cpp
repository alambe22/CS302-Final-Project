#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	Sniper i(5,5);
	Base g(3,5);
	Unit *unit1 = &i;
	Unit *unit2 = &g;
	pair<int,int> des;
	des = make_pair(20,20);
	int row =20;
	int col =20;
	int visibility = 1;
	bool move;
	vector<Unit*> units;
	units.push_back(unit1);
	units.push_back(unit2);

	move=unit1->attack(visibility, unit2);
	unit2->print();
	return 0;
}
