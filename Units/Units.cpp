// Name: Shivam Patel
// Description: Defined the getter functions and print  

using namespace std;
#include "Units.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//*****UNIT -----> BASE*******

Base::Base(int row, int col){
	this->health = 20000;
	this->range = 0;
	this->damage = 0;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Base::getHealth(){return health;}

int Base::getRange(){return range;}

int Base::getDamage(){return damage;}

pair<int,int> Base::getPosition(){return pos;}

bool Base:: getMove(){return moveCheck;}

void Base:: setMove(bool set){moveCheck = set;}

bool Base::move(pair<int,int> des, int row, int col){
	printf("The base does not move at any point in the game\n");
	return false;
}

bool Base::attack(pair<int,int> des, int visibility, Unit*){
	printf("The base does not attack at any point in the game\n");
	return false;
}


void Base::print(){
	printf("Base Status: \nhealth: %d\nPosition: %d,%d\n", health, pos.first, pos.second);
}


//*****UNIT -----> SNIPER*******
Sniper::Sniper(int row, int col){
	this->health = 2500;
	this->damage = 550;
	this->range = 7;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Sniper::getHealth(){return health;}

int Sniper::getDamage(){return damage;}

int Sniper::getRange(){return range;}

pair<int,int> Sniper::getPosition(){return pos;}

bool Sniper:: getMove(){return moveCheck;}

void Sniper:: setMove(bool set){moveCheck = set;}

bool Sniper::move(pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	//valid moves
	if(rowdiff ==1 && coldiff ==1) valid = true;
	if(rowdiff ==1 && coldiff ==0) valid =true;
	if(rowdiff ==0 && coldiff ==1) valid =true;

	if(valid == false){
		printf("Sniper cannot move to that destination. Sniper moves 1 tile in any direction\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
	return true;
}

bool Sniper::attack(pair<int,int> des, int visibility, Unit*){
	return true;
}

void Sniper::print(){

	printf("Sniper Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first,pos.second);
}


//*****UNIT -----> ARTILLERY*******
Artillery::Artillery(int row, int col){
	this->health = 6000;
	this->damage = 250;
	this->range = 2;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Artillery::getHealth(){return health;}

int Artillery::getDamage(){return damage;}

int Artillery::getRange(){return range;}

pair<int,int> Artillery::getPosition(){return pos;}

bool Artillery:: getMove(){return moveCheck;}

void Artillery:: setMove(bool set){moveCheck = set;}

bool Artillery::move(pair<int,int> des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}


	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);
	
	if(rowdiff == 0 && coldiff == 3) valid = true;
	if(rowdiff == 3 && coldiff == 0) valid = true;

	if(valid ==false){
		printf("Invalid move! Artillery moves 3 tiles at time in any adjacent direction to current position.\n");
		return false;
	}
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
	return true;
}

bool Artillery::attack(pair<int,int> des, int visibility,Unit*){
	return true;
}

void Artillery::print(){
	printf("Artillery Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first,pos.second);
}
	

//*****UNIT -----> INFANTRY*******
Infantry::Infantry(int row, int col){
	this->health = 3000;
	this->damage = 1100;
	this->range = 1;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Infantry::getHealth(){return health;}

int Infantry::getDamage(){return damage;}

int Infantry::getRange(){return range;}

pair<int,int> Infantry::getPosition() {return pos;}

bool Infantry:: getMove(){return moveCheck;}

void Infantry:: setMove(bool set){moveCheck = set;}

bool Infantry::move(pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	//valid moves
	if(rowdiff ==1 && coldiff ==0) valid = true;
	if(rowdiff ==0 && coldiff ==1) valid =true;

	if(valid == false){
		printf("Invalid destination. Infantry only goes 1 tiles adjacent to its current position\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
		return true;
}

bool Infantry::attack(pair<int,int> des, int visibility,Unit*){
	return true;
}

void Infantry::print(){
	printf("Infantry Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first,pos.second);

}

//*****UNIT -----> CAVALRY*******
Cavalry::Cavalry(int row, int col,int columnsize){
	this->health = 4000;
	this->damage = 200;
	this->range = columnsize;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Cavalry::getHealth(){return health;}

int Cavalry::getDamage(){return damage;}

int Cavalry::getRange(){return range;}

pair<int,int> Cavalry::getPosition() {return pos;}

bool Cavalry:: getMove(){return moveCheck;}

void Cavalry:: setMove(bool set){moveCheck = set;}


bool Cavalry::move(pair<int,int>des, int row, int col){
	bool valid = false;
	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);
	//valid moves
	if(rowdiff ==0 && coldiff ==1) valid = true;

	if(valid == false){
		printf("Invalid destination. Cavalry only goes 1 tile left or right its current position\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
		return true;
}

bool Cavalry::attack(pair<int,int>des, int visibility,Unit*){
	return true;
}

void Cavalry::print(){
	printf("Cavalry Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first, pos.second);
}

//*****UNIT -----> BIKER*******
Biker::Biker(int row, int col){
	this->health = 1500;
	this->damage = 425;
	this->range = 1;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
}

int Biker::getHealth(){return health;}

int Biker::getDamage(){return damage;}

int Biker::getRange(){return range;}

pair<int,int> Biker::getPosition(){return pos;}

bool Biker:: getMove(){return moveCheck;}

void Biker:: setMove(bool set){moveCheck = set;}


bool Biker::move(pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	if(rowdiff ==0 && coldiff ==0){
		printf("Destination is same as current position\n");
		return false;
	}
	
	//valid moves
	if(rowdiff ==0 && coldiff <=8) valid = true;
	if(rowdiff <=8 && coldiff ==0) valid = true;
	if(rowdiff <=8 && coldiff <=8) valid = true;
	
	if(valid == false){
		printf("Invalid destination. Biker goes up to 8 tiles in any direction from its current position\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
		return true;
}

bool Biker::attack(pair<int,int> des, int visibility, Unit*){
	return true;
}

void Biker::print(){
	printf("Biker Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first, pos.second);
}

