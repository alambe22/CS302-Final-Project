// Project 5: Chess but Cooler
//
// Author: Alexander Lambert
//
// Description: My part of the project is tying the project together into
// one cohesive program. The actual gameplay and UI part of the game are in here.
// This program calls functions from the other three libraries at the appropriate times,
// making sure that the game actually functions like we intend it to. 
//
// Command: ./main
//
// Controls: Enter choices from the given menus. If bad input is given the 
// program handles it properly.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <set>
#include <SDL2/SDL.h>
#include <cstdio>
// Shivam and Casey's library are included by this
#include "Tom/SDL_cbc/cbc_library.h"

using namespace std;

// Class used to store player information. Stores their units and name
class Player{
	public:
		Player();
		Player(int, vector<vector<pair<char,bool> > >&);
		~Player();
		string name;
		// Units stored as pointers so that different inherited types
		// can be stored together
		vector<Unit*> units;
};

// Sets up all of the units, and their initial locations. The col passed
// lets me know if it should be on the right side for player 2 or the left side
// for player 1
Player::Player(int col, vector<vector<pair<char, bool> > >& unitGrid){
	bool curPlayer = col;
	units.emplace_back(new Sniper(1, col));
	unitGrid[1][col].first = 'S';
	unitGrid[1][col].second = curPlayer;
	units.emplace_back(new Cavalry(2, col, 10));
	unitGrid[2][col].first = 'C';
	unitGrid[2][col].second = curPlayer;
	units.emplace_back(new Biker(3, col));
	unitGrid[3][col].first = 'B';
	unitGrid[3][col].second =curPlayer;
	units.emplace_back(new Infantry(4, col));
	unitGrid[4][col].first = 'I';
	unitGrid[4][col].second = curPlayer;
	units.emplace_back(new Infantry(6, col));
	unitGrid[6][col].first = 'I';
	unitGrid[6][col].second = curPlayer;
	units.emplace_back(new Cavalry(7, col, 10));
	unitGrid[7][col].first = 'C';
	unitGrid[7][col].second = curPlayer;
	units.emplace_back(new Artillery(8, col));
	unitGrid[8][col].first = 'A';
	unitGrid[8][col].second = curPlayer;
	units.emplace_back(new Base(5, col));
	unitGrid[5][col].first = 'b';
	unitGrid[5][col].second = curPlayer;
}

// Goes through and frees all of the memory
Player::~Player(){
	for(unsigned int i=0; i< 8; i++){
		delete units[i];
	}
}

//Helper functions to make cleaner code. Initializes the map
//and reads in player names
int startGame(Map& gameboard, Player* players);

int main(int argc, char* argv[]){
	// Choice, unit, and unit2 are used for menu options.
	// curPlayer tracks whose turn it is. 0 is player 1, 1 is player 2
	int choice, curPlayer, unit, unit2;
	//Used to track unit health during attack
	int health;
	// turnCounter used to track things like weather and time change, i is used for loops
	unsigned int turnCounter=0, i;
	
	// Used to store map choices
	pair<int, int> des, src;
	// Stores where the units are and which player they belong too. False means player 1, true means player 2 (used by graphics)
	vector<vector<pair<char,bool> > > unitGrid(10, vector<pair<char, bool> >(10,make_pair('_', false)));

	// Used for (y/n) choices
	char charChoice;

	// Used for printing information or updating the unitGrid. This removes the need for
	// even more switch cases.
	const char unitSymbols[8] = {'S', 'C', 'B', 'I', 'I', 'C', 'A', 'b'};
	const string unitNames[8] = {"Sniper", "Cavalry", "Biker", "Infantry", "Infantry", "Cavalry", "Artillery", "Base"};

	// Attempts to initialize window and renderer
	if( !init()){
		printf("Failed to initialize!\n");
	}else{
		// Checks if the game loop needs to keep going
		bool quit = false;

		//Event used to see if SDL_QUIT (window close) has happened
		SDL_Event event;

		//Game map
		Map gameboard;

		//The two players are stored in a static array. This makes accessing the players not an 
		//if statement but simply an int that goes between 0 and 1
		Player players[2] = {Player(0, unitGrid), Player(9, unitGrid)};

		//Sets up game and decides starting player
		curPlayer = startGame(gameboard, players);

		//Main Game loop, runs until 6 is chosen
		display(gameboard, unitGrid);
		while(!quit){
			//Checks to see if the window has been closed
			while(SDL_PollEvent(&event) !=0){
				if(event.type == SDL_QUIT)	{
					quit = true;
				}
			}
			
			cout << '\n' << players[curPlayer].name << "\'s turn\n";

			// Loops through the unit list of the current player and sees if any are dead. If they've been
			// dead for 5 turns, it spawns a new one. Otherwise, it increments how many turns it has been dead for.
			for(i=0; i< 7; i++){
				if(players[curPlayer].units[i]->isDead){
					
					//Check to see if a player has been dead for 5 turns
					if(players[curPlayer].units[i]->deadCount ==5){
						//Loops until the unit has been successfully placed.
						while(true){
							// Tells the player what unit, and asks for the row. Checks to make sure the tile is valid.
							cout << "A new " << unitNames[i] << " is ready to be placed. It will be placed in the same column as your base. Please enter which row: \n";
							if(!(cin >> des.first) || des.first <0 || des.first > 9){
								cin.clear();
								cin.ignore();
								cout << "Invalid tile\n";
								continue;
							}
							
							//Sets the column of the destination to be that of the current player's base
							des.second = ((curPlayer==0)?(0):(9));
							if(unitGrid[des.first][des.second].first !='_')
								cout << "Unit already there.\n";
							else{
								//Deletes the old unit, and creates a new one depending
								//on the unit needed to be replaced.
								delete players[curPlayer].units[i];
								switch(i){
									case 0:
										players[curPlayer].units[0] = new Sniper(des.first, des.second);
										break;
									case 1:
									case 5:
										players[curPlayer].units[i] = new Cavalry(des.first, des.second, 10);
										break;
									case 2:
										players[curPlayer].units[2] = new Biker(des.first, des.second);
										break;
									case 4:
									case 3:
										players[curPlayer].units[i] = new Infantry(des.first, des.second);
										break;
									case 6:
										players[curPlayer].units[6] = new Artillery(des.first, des.second);
										break;
								}
								//Changes the unitGrid to match the new unit
								unitGrid[des.first][des.second].first = unitSymbols[i];
								unitGrid[des.first][des.second].second = curPlayer;
								display(gameboard, unitGrid);
								break;
							}
						}
					}else{
						//Increments how many turns the unit has been dead for
						players[curPlayer].units[i]->deadCount++;
					}
				}
			}

			choice = -1;
			//Prints the main menu to the user, and checks if their input is good.
			do{
				if(!cin.good()){
					cin.clear();
					cin.ignore();
				}
				cout << "\nOptions:\n 1. Move Units\n 2. Check tile\n 3. Check unit\n 4. Attack\n 5. End turn\n 6. Quit\n Choice: ";

			}while(!(cin >> choice)|| choice >7 || choice < 0 );

			//Menu
			switch(choice){
				// Move units
				case 1:
					//Lets the player get an idea of which side their units will be on, especially to start
					cout << ((curPlayer == 0)?("\nLeft side:\n"):("\nRight side:\n"));
					
					//Prints out all units that are not dead or haven't moved.
					cout << "Which unit to move?\n";
					for(i=0; i< players[curPlayer].units.size()-1; i++){
						if(players[curPlayer].units[i]->isDead || players[curPlayer].units[i]->getMove())
							continue;
						cout << i << ". "<< unitNames[i] << '\n';
					}
					
					//Makes sure the input is correct, and a valid unit
					if((cin >> choice) && choice < 7 && choice >=0){
						//Checks if it has already moved
						if(players[curPlayer].units[choice]->getMove()){
							cout << "This unit has already been moved this turn.\n";
							break;
						//Checks if the unit is dead
						}else if(players[curPlayer].units[choice]->isDead){
							cout << "This unit is currently dead and cannot move.\n";
							break;
						}else{
							//Lets the player know how a given unit moves
							cout << "Unit: " << unitNames[choice];
							switch(choice){
								//Sniper
								case 0:
									cout << " can move 1 tile in any direction\n";
									break;
								//Cavalry
								case 1:
								case 5:
									cout << " can move 1 tile left or right\n";
									break;
								//Infantry
								case 3:
								case 4:
									cout << " can move 1 tile up, down, left, or right\n";
									break;
								//Artillery
								case 6:
									cout << " can move exactly 3 tiles up, down, left, or right\n";
									break;
								//Biker
								case 2:
									cout << " can move 6 tiles in any direction \n";
									break;
							}
							//Read in the destination
							while(true){

								//Checks input, making sure its proper
								do{
									if(cin.fail()){
										cin.clear();
										cin.ignore();
									}
									cout << "Please enter destination as row and columns: ";
								}while(!(cin >> des.first >> des.second) || des.first <0 || des.first >9 || des.second < 0 || des.second > 9);
								src = players[curPlayer].units[choice]->getPosition();

								//Tells you how far a unit could attack from the new tile
								cout << "Unit range on selected tile: " << gameboard.visibility(des.first, des.second,players[curPlayer].units[choice]->getRange())<< '\n';
								cout << "Do you still want to move (y/n)?\n";
								
								//Read in if they want to continue moving
								cin >> charChoice;
								if(charChoice != 'y')
									continue;
								
								//Updates board
								if(players[curPlayer].units[choice]->move(unitGrid, des, 10, 10)){
									unitGrid[src.first][src.second].first = '_';
									unitGrid[des.first][des.second].first = unitSymbols[choice];
									unitGrid[des.first][des.second].second = curPlayer;
									break;
								}

								//Lets the player try and enter a valid position
								cout << "Try again (y/n)?\n";
								cin >> charChoice;
								if(charChoice != 'y')
									break;
							}
						}
					//Resets cin if an invalid unit is provided
					}else{
						cin.clear();
						cin.ignore();
						cout << "Invalid unit.\n";
					}
					display(gameboard, unitGrid);
					break;
				case 2:
					//Check tile
					cout << "Which tile (enter rows and columns):\n";
					
					//Makes sure that the tile is valid
					if(!(cin >> des.first >> des.second) ||des.first >10 || des.second>10 || des.first<0 || des.second<0){
						cin.clear();
						cin.ignore();
						cout << "Invalid tile or out of bounds\n";
					}else{
						//Prints out the ranges for all units, if they were to be on this tile
						cout << "Attack Ranges for Units:\n";
						cout << "Sniper: " << gameboard.visibility(des.first, des.second, players[curPlayer].units[0]->getRange()) << '\n';
						cout << "Cavalary: " << gameboard.visibility(des.first, des.second, players[curPlayer].units[1]->getRange()) << '\n';
						cout << "Biker: " << gameboard.visibility(des.first, des.second, players[curPlayer].units[2]->getRange()) << '\n';
						cout << "Infantry: " << gameboard.visibility(des.first, des.second, players[curPlayer].units[3]->getRange()) << '\n';
						cout << "Artillery: " << gameboard.visibility(des.first, des.second, players[curPlayer].units[6]->getRange()) << '\n';
						
						//Lets the player know what unit is present on the tile
						switch(unitGrid[des.first][des.second].first){
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
					cout << "Which unit to check?\n";
					
					//Prints out all units that are not dead
					for(i=0; i<8; i++){
						if(players[curPlayer].units[i]->isDead)
							continue;
						cout << i << ". " << unitNames[i] << '\n';
					}
					cout << "Or enter 8 for all units.\n";
					
					//Makes sure the input is valid
					if((cin >> choice) && choice >=0 && choice <= 8){
						//Prints out the given unit, unless the unit is dead
						if(choice < 8){
							if(players[curPlayer].units[choice]->isDead){
								cout << "This " << unitNames[choice] << " is dead, and a new recruit will arrive in " << 5 - players[curPlayer].units[choice]->deadCount << " turns\n";
							}
							cout << "This " << unitNames[choice] << " has the following stats:";
							cout << "\nHealth: " << players[curPlayer].units[choice]->getHealth();
							cout << "\nRange: " << players[curPlayer].units[choice]->getRange();
							cout << "\nDamage: " << players[curPlayer].units[choice]->getDamage();
							cout << "\nMoved this turn: " << ((players[curPlayer].units[choice]->getMove())?("True\n"):("False\n"));
						//Prints out all units, and lets you know which ones are dead
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
					}else{
						cin.clear();
						cin.ignore();
					}
					break;
				case 4:
					//Attack
					cout << "Which unit do you want to attack with?\n";
					//Prints out all units that are not dead or already attacked
					for(i=0; i<7; i++){
						if(players[curPlayer].units[i]->isDead || players[curPlayer].units[i]->getAttack())
							continue;
						cout << i << ". " << unitNames[i] << '\n';
					}
					//Checks if the unit is valid
					if(!(cin >> unit) || unit >7 || unit <0 || players[curPlayer].units[unit]->getAttack() || players[curPlayer].units[unit]->isDead){
						cout << "Invalid unit.\n";
						cin.clear();
						cin.ignore();
						break;
					}
					src = players[curPlayer].units[unit]->getPosition();
					
					//Lets the player know the range of the current unit, given the weather, type of unit, tile, and time of day
					cout << "The selected " << unitNames[unit] << " currently has a range of " << gameboard.visibility(src.first, src.second, players[curPlayer].units[unit]->getRange()) << '\n';
					
					//Prints out all enemy units that are alive
					cout << "Which enemy unit do you want to attack?\n";
					for(i=0; i<8; i++){
						if(players[!curPlayer].units[i]->isDead)
							continue;
						cout << i << ". " << unitNames[i] << '\n';
					}
					//Checks that the second unit is valid
					if( !(cin >> unit2) || unit >8 || unit<0){
						cin.clear();
						cin.ignore();
						cout << "Invalid unit.\n";
						break;
					}

					//Attempts the attack
					if(players[curPlayer].units[unit]->attack(gameboard.visibility(src.first, src.second, players[curPlayer].units[unit]->getRange()),players[!curPlayer].units[unit2])){
						health = players[!curPlayer].units[unit2]->getHealth();
						cout << "Attack succesful, " << players[!curPlayer].name << "'s " << unitNames[unit2] << " health is now: " << ((health<=0)?(0):(health)) << '\n';
						//Checks if the enemy is killed
						if(health <=0){
							//Ends the game and prints out the winning info if the other players base is destroyed
							if(unit2 == 7){
								cout << players[!curPlayer].name << "\'s base has been overrun. Structures burn and no prisoners are taken. " << players[curPlayer].name << " has won the game!\n";
								return 0;
							}

							//Lets the player know that the enemy has been killed
							src = players[!curPlayer].units[unit2]->getPosition();
							cout << players[!curPlayer].name << "\'s " << unitNames[unit2] << " has been destroyed.\n";
							
							//Sets the unit to dead nad updates the unitGrid
							players[!curPlayer].units[unit2]->isDead = true;
							unitGrid[src.first][src.second].first = '_';
							display(gameboard, unitGrid);
						}
					}
					break;
				case 5:
					//Increases the turn, changes weather and time if enough turns have passed
					turnCounter++;
					if(turnCounter%4 ==0){
						gameboard.changeWeather();
					}
					if(turnCounter%5 ==0){
						gameboard.changeTime();
					}
					display(gameboard, unitGrid);

					//Resets the units so that they can attack and move again
					for(i=0; i<7; i++){
						players[curPlayer].units[i]->setMove(false);
						players[curPlayer].units[i]->setAttack(false);
					}
					curPlayer = !curPlayer;
					break;
					//Reprints map
				case 6:
					quit = true;
			}
		}
	}
	//Ends the SDL window
	close();
	return 0;
}

//Initializes board and reads in player names.
int startGame(Map& gameboard, Player* players){
	unsigned int choice;
	//Read in seed, making sure it is proper input
	while(true){
		cout << "Input a seed (put 0 for random)?: ";
		if(!(cin >> choice)){
			cin.clear();
			cin.ignore();
			continue;
		}
		break;
	}

	//Seeds random
	if(choice ==0){
		srand(time(NULL));
		cout << rand()%100;
	}else{
		srand(choice);
	}
	gameboard.resize(10, 10);

	//Readss in the players names
	cout << " Input Player 1's Name: ";
	cin >> players[0].name;

	cout << " Input Player 2's Name: ";
	cin >> players[1].name;

	//Chooses who starts randomly.
	return rand()%2;
}

