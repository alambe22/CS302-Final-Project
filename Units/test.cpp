#include "Units.h"
#include <iostream>
using namespace std;


int main(){

	//testing the print function for each unit which will give the range, health, and damage but just health for base
	Biker i;
	Unit *unit1 = &i;
//	unit1->print();
//	cout<<endl;
	pair<int,int> pos;
	pair<int,int> des;
	pos= make_pair(10,10);
	des= make_pair(2,10);
	int numtiles =1;
	int row= 20;
	int col=20;
	unit1->move(pos, des,row, col);
/*	Artillery a;
	Infantry i;
	Cavalry c(35);
	Biker bi;
	Base b;

	Unit *unit1 = &s;
	Unit *unit2 = &a;
	Unit *unit3 = &i;
	Unit *unit4 = &c;
	Unit *unit5 = &bi;
	Unit *unit6 = &b;

	unit1->print();
	cout<<endl;
	unit2->print();
	cout<<endl;
	unit3->print();
	cout<<endl;
	unit4->print();
	cout<<endl;
	unit5->print();
	cout<<endl;
	unit6->print();
*/

	return 0;
}
