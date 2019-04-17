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
}

int Base::getHealth(){return health;}

int Base::getRange(){return range;}

int Base::getDamage(){return damage;}

pair<int,int> Base::getPosition(){return pos;}

void Base::move(pair<int,int>pos, pair<int,int> des, int row, int col){

	printf("The base does not move at any point in the game\n");
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
}

int Sniper::getHealth(){return health;}

int Sniper::getDamage(){return damage;}

int Sniper::getRange(){return range;}

pair<int,int> Sniper::getPosition(){return pos;}

void Sniper::move(pair<int,int> pos, pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		exit(1);
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	//valid moves
	if(rowdiff ==1 && coldiff ==1) valid = true;
	if(rowdiff ==1 && coldiff ==0) valid =true;
	if(rowdiff ==0 && coldiff ==1) valid =true;

	if(valid == false){
		printf("Sniper cannot move to that destination. Sniper moves 1 tile in any direction\n");
		exit(1);
	}
	
	//update the unit's current position to the destination postion
	else{
		this->pos.first = des.first;
		this->pos.second = des.second;
	}
	cout<<this->pos.first<<","<<this->pos.second<<endl;
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
}

int Artillery::getHealth(){return health;}

int Artillery::getDamage(){return damage;}

int Artillery::getRange(){return range;}

pair<int,int> Artillery::getPosition(){return pos;}

void Artillery::move(pair<int,int> pos, pair<int,int> des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		exit(1);
	}


	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);
	
	if(rowdiff == 0 && coldiff == 3) valid = true;
	if(rowdiff == 3 && coldiff == 0) valid = true;

	if(valid ==false){
		printf("Invalid move! Artillery moves 3 tiles at time in any adjacent direction to current position.\n");
		exit(1);
	}
	else{
		this->pos.first = des.first;
		this->pos.second = des.second;
	}
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
}

int Infantry::getHealth(){return health;}

int Infantry::getDamage(){return damage;}

int Infantry::getRange(){return range;}

pair<int,int> Infantry::getPosition() {return pos;}

void Infantry::move(pair<int,int> pos, pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		exit(1);
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	//valid moves
	if(rowdiff ==1 && coldiff ==0) valid = true;
	if(rowdiff ==0 && coldiff ==1) valid =true;

	if(valid == false){
		printf("Invalid destination. Infantry only goes 1 tiles adjacent to its current position\n");
		exit(1);
	}
	
	//update the unit's current position to the destination postion
	else{
		this->pos.first = des.first;
		this->pos.second = des.second;
	}

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
}

int Cavalry::getHealth(){return health;}

int Cavalry::getDamage(){return damage;}

int Cavalry::getRange(){return range;}

pair<int,int> Cavalry::getPosition() {return pos;}

void Cavalry::move(pair<int,int> pos, pair<int,int>des, int row, int col){
	bool valid = false;
	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		exit(1);
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);
	//valid moves
	if(rowdiff ==1 && coldiff ==0) valid = true;

	if(valid == false){
		printf("Invalid destination. Cavalry only goes 1 tile above or below its current position\n");
		exit(1);
	}
	
	//update the unit's current position to the destination postion
	else{
		this->pos.first = des.first;
		this->pos.second = des.second;
	}
	cout<<this->pos.first<<","<<this->pos.second<<endl;
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
}

int Biker::getHealth(){return health;}

int Biker::getDamage(){return damage;}

int Biker::getRange(){return range;}

pair<int,int> Biker::getPosition(){return pos;}

void Biker::move(pair<int,int> pos, pair<int,int>des, int row, int col){
	bool valid = false;

	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		exit(1);
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	if(rowdiff ==0 && coldiff ==0){
		printf("Destination is same as current position\n");
		exit(1);
	}
	
	//valid moves
	if(rowdiff ==0 && coldiff <=8) valid = true;
	if(rowdiff <=8 && coldiff ==0) valid = true;
	if(rowdiff <=8 && coldiff <=8) valid = true;
	
	if(valid == false){
		printf("Invalid destination. Biker goes up to 8 tiles in any direction from its current position\n");
		exit(1);
	}
	
	//update the unit's current position to the destination postion
	else{
		this->pos.first = des.first;
		this->pos.second = des.second;
	}

}

void Biker::print(){
	printf("Biker Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\n", health, damage, range,pos.first, pos.second);
}

