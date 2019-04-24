// Challenge 8: Preparing for Final Project
//
// Author: Alexander Lambert
//
// Description: My part of the project is tying the project together into
// one cohesive program. To get practice and get started on this, I made a 
// mini version of our project and tied it all together. This file contains the
// actual "game" and is what the user interacts with.
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <set>
#include <SDL2/SDL.h>
#include <cstdio>
#include "Tom/SDL_cbc/cbc_library.h"

using namespace std;

class Player{
	public:
		Player();
		Player(int, vector<vector<char> >&);
		string name;
		vector<Unit*> units;
		set<int> deadUnits;
};

Player::Player(int col, vector<vector<char> >& unitGrid){
	units.emplace_back(new Sniper(1, col));
	unitGrid[1][col] = 'S';
	units.emplace_back(new Cavalry(2, col, 10));
	unitGrid[2][col] = 'C';
	units.emplace_back(new Biker(3, col));
	unitGrid[3][col] = 'B';
	units.emplace_back(new Infantry(4, col));
	unitGrid[4][col] = 'I';
	units.emplace_back(new Infantry(6, col));
	unitGrid[6][col] = 'I';
	units.emplace_back(new Cavalry(7, col, 10));
	unitGrid[7][col] = 'C';
	units.emplace_back(new Artillery(8, col));
	unitGrid[8][col] = 'A';
	units.emplace_back(new Base(5, col));
	unitGrid[5][col] = 'b';
}

//Helper functions to make cleaner code
int startGame(Map& gameboard, Player* players);

int main(int argc, char* argv[]){
	int choice, curPlayer, unit, unit2;
	unsigned int turnCounter=0, i;
	pair<int, int> des, src;
	vector<vector<char> > unitGrid(10, vector<char>(10, '_'));
	char charChoice;
	const char unitSymbols[8] = {'S', 'C', 'B', 'I', 'A', 'I', 'C', 'b'};
	const string unitNames[8] = {"Sniper", "Cavalry", "Biker", "Infantry", "Artillery", "Infantry", "Cavalry", "Base"};
	set<int>::iterator it;

	if( !init()){
		printf("Failed to initialize!\n");
	}else{

		bool quit = false;

		SDL_Event event;

		Map gameboard;

		Player players[2] = {Player(0, unitGrid), Player(9, unitGrid)};

		curPlayer = startGame(gameboard, players);

		//This is the main game loop. As long as the player does not
		//choose "6" the game will keep running. Eventually this will be
		//tied to victory conditions as well
		display(gameboard, unitGrid);
		while(!quit){
			while(SDL_PollEvent(&event) !=0){
				if(event.type == SDL_QUIT)	{
					quit = true;
				}
			}
			

			cout << '\n' << players[curPlayer].name << "\'s turn\n";

			if(players[curPlayer].deadUnits.size() > 0){
				for(it = players[curPlayer].deadUnits.begin(); it != players[curPlayer].deadUnits.end(); it++){
					if(players[curPlayer].units[*it]->deadCount ==5){
						while(true){
							cout << "A new " << unitNames[*it] << " is ready to be placed. Enter the cordinates where it should go. The column must be one of the first 3 on your side.\n";
							cin >> des.first >> des.second;

							if(unitGrid[des.first][des.second] != '_')
								cout << "Unit already there.\n";
							else if( (des.second != 0 && curPlayer ==0) || (des.second != 9 && curPlayer==1)){
								cout << "Too far from base.\n";
							}else{
								delete players[curPlayer].units[*it];
								switch(*it){
									case 0:
										players[curPlayer].units[0] = new Sniper(des.first, des.second);
										break;
									case 1:
										players[curPlayer].units[1] = new Cavalry(des.first, des.second, 10);
										break;
									case 2:
										players[curPlayer].units[2] = new Biker(des.first, des.second);
										break;
									case 3:
										players[curPlayer].units[3] = new Infantry(des.first, des.second);
										break;
									case 4:
										players[curPlayer].units[4] = new Infantry(des.first, des.second);
										break;
									case 5:
										players[curPlayer].units[5] = new Cavalry(des.first, des.second, 10);
										break;
									case 6:
										players[curPlayer].units[6] = new Artillery(des.first, des.second);
								}
								unitGrid[des.first][des.second] = unitSymbols[*it];
								it = players[curPlayer].deadUnits.erase(it);
								break;
							}
						}
					}else{
						players[curPlayer].units[*it]->deadCount++;
					}
				}
			}
			choice = -1;
			cout << "Options:\n 1. Move Units\n 2. Check tile\n 3. Check unit\n 4. Attack\n 5. End turn\n 6. Quit\n Choice: ";
			cin >> choice;

			//Menu
			switch(choice){
				// Move units
				case 1:
					cout << ((curPlayer == 0)?("\nLeft side:\n"):("\nRight side:\n"));
					cout << "Which unit to move?\n";
					for(i=0; i< players[curPlayer].units.size()-1; i++){
						if(players[curPlayer].units[i]->isDead)
							continue;
						cout << i << ". "<< unitNames[i] << '\n';
					}

					if(cin >> choice){
						if(players[curPlayer].units[choice]->getMove()){
							cout << "This unit has already been moved this turn.\n";
							break;
						}else{
							cout << "Unit: " << unitNames[choice];
							switch(choice){
								case 0:
									cout << " can move 1 tile in any direction\n";
									break;
								case 1:
								case 5:
									cout << " can move 1 tile left or right\n";
									break;
								case 3:
								case 4:
									cout << " can move 1 tile up, down, left, or right\n";
									break;
								case 6:
									cout << " can move 3 tiles up, down, left, or right\n";
									break;
								case 2:
									cout << " can move 6 tiles in any direction \n";
									break;
							}
							while(true){
								do{
									cout << "Please enter destination as row and columns: ";
								}while(!(cin >> des.first >> des.second));
								src = players[curPlayer].units[choice]->getPosition();

								if(players[curPlayer].units[choice]->move(unitGrid, des, 10, 10)){
									unitGrid[src.first][src.second] = '_';
									unitGrid[des.first][des.second] = unitSymbols[choice];
									break;
								}
								cout << "Try again (y/n)?\n";
								cin >> charChoice;
								if(charChoice != 'y')
									break;
							}
						}
					}else{
						cout << "Invalid unit.\n";
					}
					display(gameboard, unitGrid); //TOM: added this
					break;
				case 2:
					cout << "Which tile (enter rows and columns): ";
					cin >> des.first >> des.second;
					if(des.first >10 || des.second>10 || des.first<0 || des.second<0){
						cout << "\nInvalid tile, out of bounds\n";
					}else{
						cout << "\n Visibility: "<< gameboard.visibility(des.first, des.first) << endl;
						switch(unitGrid[des.first][des.second]){
							case '_':
								cout << "No unit";
								break;
							case 'I':
								cout << "Infantry";
								break;
							case 'A':
								cout << "Artillery";
								break;
							case 'S':
								cout << "Sniper";
								break;
							case 'C':
								cout << "Cavalry";
								break;
							case 'B':
								cout << "Biker";
								break;
							case 'b':
								cout << "Base";
						}
						cout << " present on this tile\n";
					}
					break;
				case 3:
					// Check unit
					cout << "Which unit to check (0-7), or enter 8 for all units?\n";
					cin >> choice;
					if(choice < 8){
						if(players[curPlayer].units[choice]->isDead){
							cout << "This " << unitNames[choice] << " is dead, and a new recruit will arrive in " << 5 - players[curPlayer].units[choice]->deadCount << " turns\n";
						}
						cout << "This " << unitNames[choice] << " has the following stats:";
						cout << "\nHealth: " << players[curPlayer].units[choice]->getHealth();
						cout << "\nRange: " << players[curPlayer].units[choice]->getRange();
						cout << "\nDamage: " << players[curPlayer].units[choice]->getDamage();
						cout << "\nMoved this turn: " << ((players[curPlayer].units[choice]->getMove())?("True\n"):("False\n"));
					}else{
						for(i=0; i< 8; i++){
							cout << i << ". ";
							if(players[curPlayer].units[i]->isDead){
								cout << "This " << unitNames[i] << " is dead, and a new recruit will in " << 5- players[curPlayer].units[i]->deadCount << " turns\n";
							}else{
								cout << "This " << unitNames[i] << " has the following stats:";
								cout << "\nHealth: " << players[curPlayer].units[i]->getHealth();
								cout << "\nRange: " << players[curPlayer].units[i]->getRange();
								cout << "\nDamage: " << players[curPlayer].units[i]->getDamage();
								cout << "\nMoved this turn: " << ((players[curPlayer].units[i]->getMove())?("True\n"):("False\n"));
							}
						}
					}
					break;
				case 4:
					//Attack
					cout << "Which unit do you want to attack with? (0-7)";
					cin >> unit;
					src = players[curPlayer].units[unit]->getPosition();
					cout << "Which enemy unit do you want to attack? (0-7, 8 for base)";
					cin >> unit2;
					if(players[curPlayer].units[unit]->attack(gameboard.visibility(src.first, src.second),players[curPlayer+1%2].units[unit2])){
						if(players[curPlayer+1%2].units[unit2]->getHealth() <=0){
							if(unit2 == 8){
								cout << players[curPlayer+1%2].name << "'s base has been overrun. Structures burn and no prisoners are taken. " << players[curPlayer].name << " has won the game!\n";
								return 0;
							}
							players[curPlayer+1%2].units[unit2]->isDead = true;
							players[curPlayer+1%2].deadUnits.insert(unit2);
						}
					}
					break;
				case 5:
					turnCounter++;
					if(turnCounter%4 ==0){
						gameboard.changeWeather();
					}
					if(turnCounter%5 ==0){
						gameboard.changeTime();
					}
					display(gameboard, unitGrid);
					for(i=0; i<7; i++){
						players[curPlayer].units[i]->setMove(false);
					}
					curPlayer = (curPlayer==1)?(0):(1);
					break;
					//Reprints map
				case 6:
					quit = true;
			}
		}
	}
	close();
	return 0;
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
	gameboard.resize(10, 10);

	cout << " Input Player 1's Name: ";
	cin >> players[0].name;

	cout << " Input Player 2's Name: ";
	cin >> players[1].name;

	return rand()%2;
}

