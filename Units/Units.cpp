// Name: Shivam Patel
// Description: Defined the getter functions and print  

using namespace std;
#include "Units.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


//****UNIT******
//base class functions defined
int Unit::getHealth(){return health;}

void Unit::setHealth(int newHealth){health = newHealth;}

int Unit::getRange(){return range;}

int Unit::getDamage(){return damage;}

pair<int,int> Unit::getPosition(){return pos;}

bool Unit:: getMove(){return moveCheck;}

void Unit:: setMove(bool set){moveCheck = set;}

bool Unit:: getAttack(){return attackCheck;}

void Unit:: setAttack(bool attack){attackCheck = attack;}

void Unit::print(){

	printf("Unit Status: \nHealth: %d\nDamage: %d\nRange: %d\nCurrent Position: %d,%d\nMove: %d\nAttack: %d\nisDead: %d\nDead Count: %d\n", health, damage, range,pos.first,pos.second, moveCheck, attackCheck, isDead, deadCount);
}

//for each unit, its attributes, the attack, and move is made differently
//*****UNIT -----> BASE*******
//stationary unit
Base::Base(int row, int col){
	this->health = 20000;
	this->range = 0;
	this->damage = 0;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount = 0;
	this->isDead=false;
	this->attackCheck = false;
}

bool Base::move(vector<vector<pair<char,bool> > >grid,pair<int,int> des, int row, int col){
	printf("The base does not move at any point in the game\n");
	return false;
}

bool Base::attack(int visibility, Unit*){
	printf("The base does not attack at any point in the game\n");
	return false;
}

//*****UNIT -----> SNIPER*******
Sniper::Sniper(int row, int col){
	this->health = 2500;
	this->damage = 550;
	this->range = 6;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount =0;
	this->isDead=false;
	this->attackCheck = false;

}
// can move any direction  but only one tile
bool Sniper::move(vector<vector<pair<char,bool> > >grid,pair<int,int>des, int row, int col){
	bool valid = false;
	//error checking for out of bounds or a unit is at destination 
	if(grid[des.first][des.second].first != '_'){
		printf("Cannot move! A unit is already there\n");
		return false;
	}
	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}

	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);

	//valid moves for the unit to go any direction
	if(rowdiff ==1 && coldiff ==1) valid = true;
	if(rowdiff ==1 && coldiff ==0) valid =true;
	if(rowdiff ==0 && coldiff ==1) valid =true;

	//not a valid destination was given
	if(valid == false){
		printf("Sniper cannot move to that destination. Sniper moves 1 tile in any direction\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
	moveCheck = true;
	return true;
}
//any direction including diagonal with its range depending on the visibility parameter 
bool Sniper::attack(int visibility, Unit* unit2){
	bool valid = false;
	int newRange = visibility;

	int rowdiff = abs(unit2->getPosition().first - pos.first);
	int coldiff = abs(unit2->getPosition().second - pos.second);

	//valid moves to attack
	if(rowdiff <=newRange && coldiff <=newRange) valid = true;
	if(rowdiff <=newRange && coldiff ==0) valid =true;
	if(rowdiff ==0 && coldiff <=newRange) valid =true;

	if(valid == false){
		printf("Sniper cannot attack that Unit\n");
		return false;
	}
	
	//performs the attack and damage to the specified unit
	else{
		int newHealth = unit2->getHealth() - this->damage;
		unit2->setHealth(newHealth);
	}
	//if the attacked unit is dead after attack
	if(unit2->getHealth() <=0) unit2->isDead= true;
	
	attackCheck = true;
	return true;
}


//*****UNIT -----> ARTILLERY*******
Artillery::Artillery(int row, int col){
	this->health = 6000;
	this->damage = 475;
	this->range = 5;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount =0;
	this->isDead = false;
	this->attackCheck = false;

}

//moves 3 tiles at a time ONLY
bool Artillery::move(vector<vector<pair<char,bool> > >grid,pair<int,int> des, int row, int col){
	bool valid = false;
	if(grid[des.first][des.second].first != '_'){
		printf("Cannot move! A unit is already there\n");
		return false;
	}
	
	if(des.first <0 || des.first >=row || des.second<0 || des.second >=col){
		printf("Invalid Move! You went out of bounds!\n");
		return false;
	}


	int rowdiff = abs(des.first - pos.first);
	int coldiff = abs(des.second - pos.second);
	
	//valid moves
	if(rowdiff == 0 && coldiff == 3) valid = true;
	if(rowdiff == 3 && coldiff == 0) valid = true;

	if(valid ==false){
		printf("Invalid move! Artillery moves 3 tiles at time in any adjacent direction to current position.\n");
		return false;
	}
	//update position
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
	moveCheck = true;
	return true;
}

//attacks in any direction including diagonal at a range greater than 1 and up to based on visibility paramter (min. 2)
bool Artillery::attack(int visibility,Unit* unit2){
	bool valid = false;
	int newRange = visibility;
	if(newRange <2){
		newRange =2;
	}

	int rowdiff = abs(unit2->getPosition().first - pos.first);
	int coldiff = abs(unit2->getPosition().second - pos.second);

	//valid moves
	if((rowdiff <=newRange  && rowdiff>1) && (coldiff <=newRange && coldiff >1)) valid = true;
	if((rowdiff <=newRange && rowdiff>1) && coldiff ==0) valid =true;
	if(rowdiff ==0 && (coldiff <=newRange && coldiff >1)) valid =true;

	if(valid == false){
		printf("Artillery cannot attack that Unit\n");
		return false;
	}
	//perform the damage on specified unit
	else{
		int newHealth = unit2->getHealth() - this->damage;
		unit2->setHealth(newHealth);
	}
	if(unit2->getHealth() <=0) unit2->isDead= true;
	attackCheck = true;
	return true;
}
	

//*****UNIT -----> INFANTRY*******
Infantry::Infantry(int row, int col){
	this->health = 3000;
	this->damage = 1100;
	this->range = 3;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount =0;
	this->isDead =false;
	this->attackCheck = false;

}
//moves only left, right, up, and down 1 tile
bool Infantry::move(vector<vector<pair<char,bool> > >grid,pair<int,int>des, int row, int col){
	bool valid = false;
	if(grid[des.first][des.second].first != '_'){
		printf("Cannot move! A unit is already there\n");
		return false;
	}
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
		moveCheck = true;
		return true;
}

//diagonal attacks ONLY range depends on visibility paramter
bool Infantry::attack(int visibility,Unit* unit2){
	bool valid = false;
	int newRange = visibility;

	int rowdiff = abs(unit2->getPosition().first - pos.first);
	int coldiff = abs(unit2->getPosition().second - pos.second);

	//valid moves
	if(rowdiff ==newRange && coldiff ==newRange) valid = true;

	if(valid == false){
		printf("Infantry cannot attack that Unit\n");
		return false;
	}

	//perform the attack on specified unit
	else{
		int newHealth = unit2->getHealth() - this->damage;
		unit2->setHealth(newHealth);
	}
	if(unit2->getHealth() <=0) unit2->isDead= true;
	attackCheck = true;
	return true;

}


//*****UNIT -----> CAVALRY*******
Cavalry::Cavalry(int row, int col,int columnsize){
	this->health = 4000;
	this->damage = 200;
	this->range = columnsize;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount =0;
	this->isDead=false;
	this->attackCheck = false;

}
// 1 tile left or right only
bool Cavalry::move(vector<vector<pair<char,bool> > >grid,pair<int,int>des, int row, int col){
	bool valid = false;
	if(grid[des.first][des.second].first != '_'){
		printf("Cannot move! A unit is already there\n");
		return false;
	}

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
		moveCheck = true;
		return true;
}

//the whole column above or below of its current position (visibility has no affect on range)
bool Cavalry::attack(int visibility,Unit* unit2){
	bool valid = false;

	int rowdiff = abs(unit2->getPosition().first - pos.first);
	int coldiff = abs(unit2->getPosition().second - pos.second);

	//valid moves
	if(rowdiff ==0 && coldiff <=range) valid = true;

	if(valid == false){
		printf("Cavalry cannot attack that Unit\n");
		return false;
	}
	//perform the attack on specidied unit
	else{
		int newHealth = unit2->getHealth() - this->damage;
		unit2->setHealth(newHealth);
	}
	if(unit2->getHealth() <=0) unit2->isDead= true;
	attackCheck = true;
	return true;
}

//*****UNIT -----> BIKER*******
Biker::Biker(int row, int col){
	this->health = 1500;
	this->damage = 425;
	this->range = 2;
	this->pos = make_pair(row,col);
	this->moveCheck = false;
	this->deadCount =0;
	this->isDead =false;
	this->attackCheck = false;

}

//can move up to  6 tiles in any direction including diagonal
bool Biker::move(vector<vector<pair<char,bool> > >grid,pair<int,int>des, int row, int col){
	bool valid = false;
	if(grid[des.first][des.second].first != '_'){
		printf("Cannot move! A unit is already there\n");
		return false;
	}
	
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
	if(rowdiff ==0 && coldiff <=6) valid = true;
	if(rowdiff <=6 && coldiff ==0) valid = true;
	if(rowdiff <=6 && coldiff <=6) valid = true;
	
	if(valid == false){
		printf("Invalid destination. Biker goes up to 6 tiles in any direction from its current position\n");
		return false;
	}
	
	//update the unit's current position to the destination postion
	else{
		pos.first = des.first;
		pos.second = des.second;
	}
		moveCheck = true;
		return true;
}
// left, right, up, or down range depends on visibility
bool Biker::attack(int visibility, Unit* unit2){
	bool valid = false;
	int newRange = visibility;
	int rowdiff = abs(unit2->getPosition().first - pos.first);
	int coldiff = abs(unit2->getPosition().second - pos.second);

	//valid moves
	if(rowdiff ==0 && coldiff ==newRange) valid = true;
	if(rowdiff ==newRange &&coldiff ==0) valid = true;
	if(valid == false){
		printf("Biker cannot attack that Unit\n");
		return false;
	}
	//perform attack on specified unit
	else{
		int newHealth = unit2->getHealth() - this->damage;
		unit2->setHealth(newHealth);
	}
	if(unit2->getHealth() <=0) unit2->isDead= true;
	attackCheck = true;
	return true;
}

