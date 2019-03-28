#include "../caseyChallenge8/Map.h"
#include "../ShivamChallenge8/Units.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	string size;
	unsigned int choice, row, col;

	do{
		cout << "BOARD OF STRATEGY AND DOOOM AND WIT AND MUCH MORE!!\n  1. Play\n  2. Exit\n";
		cin >> choice;
	}while(choice >2 && choice <1);
	if(choice == 2) return 0;
	
	//Map gameboard;
	vector<Unit*> p1Units;
	vector<Unit*> p2Units;
	cout <<"Pick a board size: 1. Small\n 2. Medium\n 3. Big\n 4. Custom\n";
	cin >> choice;
	
	switch(choice){
		case 1:
			//gameboard.resize("small");
			break;
		case 2:
			//gameboard.resize("medium");
			break;
		case 3:
			//gameboard.resize("large");
			break;
		case 4:
			cout<<"Warning: Size less than 15x15 or very large may have unexpected results\n";
			cout <<"Enter rows and columns:\n";
			cin >> row >> col;
			//gameboard.resize(row, col);
			break;
	}
	
	
}
