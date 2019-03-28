// Description: Implementing the units and its attacks 


using namespace std;
#include "Units.h"
#include <iostream>

//*****UNIT -----> SNIPER*******
Sniper::Sniper(){
	this->health = 2500;
	this->damage = 550;
	this->range = 7;
}

int Sniper::getHealth(){return health;}

int Sniper::getDamage(){return damage;}

int Sniper::getRange(){return range;}

void Sniper::print(){
	cout<<"Sniper Status:"<<endl<<"health: "<<health<<endl<<"damage: "<<damage<<endl<<"range: "<<range<<endl;
}

//*****UNIT -----> ARTILLERY*******
Artillery::Artillery(){
	this->health = 6000;
	this->damage = 250;
	this->range = 2;
}

int Artillery::getHealth(){return health;}

int Artillery::getDamage(){return damage;}

int Artillery::getRange(){return range;}

void Artillery::print(){
	cout<<"Artillery Status:"<<endl<<"health: "<<health<<endl<<"damage: "<<damage<<endl<<"range: "<<range<<endl;
}

//*****UNIT -----> INFANTRY*******
Infantry::Infantry(){
	this->health = 3000;
	this->damage = 1100;
	this->range = 1;
}

int Infantry::getHealth(){return health;}

int Infantry::getDamage(){return damage;}

int Infantry::getRange(){return range;}

void Infantry::print(){
	cout<<"Infantry Status:"<<endl<<"health: "<<health<<endl<<"damage: "<<damage<<endl<<"range: "<<range<<endl;
}

//*****UNIT -----> CAVALRY*******
Cavalry::Cavalry(int rowsize){
	this->health = 4000;
	this->damage = 200;
	this->range = rowsize;
}

int Cavalry::getHealth(){return health;}

int Cavalry::getDamage(){return damage;}

int Cavalry::getRange(){return range;}

void Cavalry::print(){
	cout<<"Cavalry Status:"<<endl<<"health: "<<health<<endl<<"damage: "<<damage<<endl<<"range: "<<range<<endl;
}

//*****UNIT -----> HOPPER*******
Hopper::Hopper(){
	this->health = 1500;
	this->damage = 425;
	this->range = 1;
}

int Hopper::getHealth(){return health;}

int Hopper::getDamage(){return damage;}

int Hopper::getRange(){return range;}

void Hopper::print(){
	cout<<"Hopper Status:"<<endl<<"health: "<<health<<endl<<"damage: "<<damage<<endl<<"range: "<<range<<endl;
}

int main(){
	Hopper h;
	Unit *unit1 = &h;	
	int health=	unit1->getHealth();	
	int damage = unit1->getDamage();
	int range = unit1->getRange();
	unit1->print();
	return 0;

}//end of main
