#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	Base i(5,0);
	Unit *unit1 = &i;

	pair<int,int> des;
	des = make_pair(8,4);
	int row =20;
	int col =20;

	unit1->move(unit1->getPosition(), des, row, col);
	unit1->print();
	return 0;
}
