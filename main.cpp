// Challenge 8: Preparing for Final Project
//
// Author: Alexander Lambert
//
// Description: My part of the project is tying the project together into
// one cohesive program. To get practice and get started on this, I made a 
// mini version of our project and tied it all together. This file contains the
// actual "game" and is what the user interacts with.
#include "caseyChallenge8/Map.h"
#include "Units/Units.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>

using namespace std;

class Player{
	public:
		Player();
		int curUnitId;
		string name;
		Base hq;
		unordered_map<int, Unit*> units;
};

Player::Player(){
	curUnitId = 0;
}

//Helper functions to make cleaner code
int startGame(Map& gameboard, Player* players);

int main(int argc, char* argv[]){
	int choice, curPlayer, start;
	unsigned int turnCounter=0;
	bool unitBought=false, allMoved=false;
	unordered_map<int, Unit*>::iterator it;
	pair<int, int> des;
	vector<vector<bool> > unitGrid(15, vector<bool>(15));

	// Start menu
	do{
		cout << "Chess, But Cooler\n  1. Play\n  2. Exit\n";
		cin >> choice;
	}while(choice >2 && choice <1);
	if(choice == 2) return 0;
	
	Map gameboard;
	
	Player players[2];

	curPlayer = startGame(gameboard, players);
	
	gameboard.print();
	//This is the main game loop. As long as the player does not
	//choose "6" the game will keep running. Eventually this will be
	//tied to victory conditions as well
	while(true){
		cout << players[curPlayer].name << "\'s turn\n";

		cout << "Options: 1. Move Units\n 2. Buy unit\n 3. Check tile\n 4. End turn\n 5. Reprint Map\n 6. Quit\n Choice: ";
		cin >> choice;

		//Menu
		switch(choice){
			// Move units
			case 1:
				if(!allMoved){
					for(it = players[curPlayer].units.begin(); it!=players[curPlayer].units.end();it++){
						cout << "Enter unit " << (*it)->first "\'s destination (row, col): ";
						cin >> des.first >> des.second;
						(*it)->move(src, des, 15, 15);
					}
					allMoved=true;
				}else{
					cout << "All units already moved this turn\n";
				}
				gameboard.print();
				break;
			case 2:
				if(!unitBought){
					//Figure out which base and unit map to add to
					cout << "\nOptions:\n 1. Sniper\n 2. Artillery\n 3. Infantry\n 4. Cavalry\n 5. Biker\n 6. Cancel\n Choice: ";
					cin >> choice;
					
					cout << "\nStarting Row In Base Column: ";
					do{
						cin >> start;
						if(!unitGrid() break;
					while(true);
					switch(choice){
						case 1:

					}
					
					unitBought = true;
				}else{
					cout << "Unit already bought this turn.\n";
				}
				break;
			//Returns information about selected tile, like visibility
			//and presence of unit
			case 3:
				cout << "Which tile (enter rows and columns): ";
				cin >> row >> col;
				if(row >15 || col>15){
					cout << "\nInvalid move, out of bounds\n";
				}else{
					cout << "\n Visibility: "<< gameboard.visibility(row, col) << endl;
					if(unitGrid[row][col] == 'i'){
						cout << "Infantry present on this tile\n";
					}else if(unitGrid[row][col] == '_'){
						cout << "Base present on this tile\n";
					}
				}
				break;
			//Switches turns, and resets relevant information.
			case 4:
	//			unitsMoved=false;
				unitBought=false;
				turnCounter++;
				if(turnCounter%4 ==0){
					gameboard.changeWeather();
				}
				printMap(unitGrid, gameboard);
				curTurn = !curTurn;
				break;
			//Reprints map
			case 5:
				printMap(unitGrid, gameboard);
				break;
			//Exits game
			case 6:
				return 0;
		}
		
	}
}

//Initializes board and puts bases into unit maps. Currently only makes a board
//of 15x15, but in the future it will handle varying sizes.
int startGame(Map& gameboard, Player* players){
	unsigned int choice;

	cout << "Input a seed (put 0 for random)?: ";
	cin >> choice;
	
	if(choice ==0){
		srand(time(NULL));
	}else{
		srand(choice);
	}
	gameboard.resize(15, 15);
	
	cout << "\n Input Player 1's Name: ";
	cin >> players[0].name;

	cout << "\n Input Player 2's Name: ";
	cin >> players[1].name;

	return rand()%2;
}

