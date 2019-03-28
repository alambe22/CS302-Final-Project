#include "Map.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Map::Map(string size){
	if (size == "small"){
		r = 15; c = 15;
	}
	else if (size == "medium"){
		r = 25; c = 25;
	}
	else if (size == "large"){
		r = 35; c = 35;
	}
	else{
		cout << "Incorrect value for size." << endl << "Use either \"small\", \"medium\", or \"large\"" << endl;
		exit(0);
	}
}
Map::Map(int r, int c){
	this->r = r;
	this->c = c;
}
