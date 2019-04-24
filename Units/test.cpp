#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	Sniper i(5,5);
	Base b(5,11);
	Unit *unit1 = &i;
	Unit *unit2 = &b;
	pair<int,int> des;
	des = make_pair(4,5);
	int row =20;
	int col =20;
	int visibility = 1;
	bool move;
	vector<vector<char> >grid;
	grid.resize(row);
	for(int i=0; i<grid.size(); i++){
		grid[i].resize(col,'_');
	}
	grid[5][5] = 'S';
	grid[5][6] = 'b';
	move=unit1->attack(visibility, unit2);
	unit1->print();
	unit2->print();
	return 0;
}
