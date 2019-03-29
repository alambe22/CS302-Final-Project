#include "Unit.h"
#include <string>
#include <cmath>
using namespace std;

Base::Base(int r, int c){
	this->r = r;
	this->c = c;
	maxMoves =0;
	usedMoves=0;
	this->name = "Base";
}

bool Base::move(int row, int col){
	return false;
}

Infantry::Infantry(int r, int c){
	this->r=r;
	this->c=c;
	maxMoves = 2;
	usedMoves = 0;
	name = "Infantry";
}

bool Infantry::move(int row, int col){
	if(maxMoves <= (usedMoves + abs(row-r))){
		return false;
	}
	return true;
}
