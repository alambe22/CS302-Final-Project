#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	Biker i(10,3);
	Unit *unit1 = &i;

	pair<int,int> des;
	des = make_pair(18,11);
	int row =20;
	int col =20;
	bool move;
	move=unit1->move(des, row, col);
	unit1->print();
	return 0;
}
