#include "map.h"
#include "Unit.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>

using namespace std;



bool startGame(Map& gameboard, unordered_map<int, Unit*>& p1Units, unordered_map<int, Unit*>& p2Units);
void printMap(vector<vector<char> >& unitGrid, Map& gameboard);
void moveUnit(unordered_map<int, Unit*>& units, vector<vector<char> >& unitGrid);

int main(int argc, char* argv[]){
	int choice, idP1=1, idP2=1;
	unsigned int turnCounter=0, row, col;
	bool curTurn = false;
	bool unitsMoved=false, unitBought=false;
	string theGrid;
	
	do{
		cout << "BOARD OF STRATEGY AND DOOOM AND WIT AND MUCH MORE!!\n  1. Play\n  2. Exit\n";
		cin >> choice;
	}while(choice >2 && choice <1);
	if(choice == 2) return 0;
	
	Map gameboard;
	unordered_map<int,Unit*> p1Units;
	unordered_map<int,Unit*> p2Units;
	vector<vector<char> > unitGrid(15, vector<char>(15, '_'));
	unitGrid[7][0] = 'b';
	unitGrid[7][14] ='b';

	curTurn = startGame(gameboard, p1Units, p2Units);
	printMap(unitGrid, gameboard);
	while(true){
		if(curTurn){
			cout << "Player 1\'s turn\n";
		}else{
			cout << "Player 2\'s turn\n";
		}
		cout << "Options: 1. Move Units\n 2. Buy unit\n 3. Check tile\n 4. End turn\n 5. Reprint Map\n 6. Quit\n Choice: ";
		cin >> choice;
		switch(choice){
			case 1:
				if(!unitsMoved){
					if(curTurn){
						moveUnit(p2Units, unitGrid);
					}else{
						moveUnit(p1Units, unitGrid);
					}
					printMap(unitGrid, gameboard);
					unitsMoved=true;
				}else{
					cout << "All units already moved this turn\n";
				}
				break;
			case 2:
				if(!unitBought){
					if(curTurn){
						if(unitGrid[7][13] == '_'){
							p2Units.emplace(idP1,new Infantry(7,13));
							unitGrid[7][13] = 'i';
							idP1++;
						}else{
							cout << "Space in front of base already occupied. Please move unit first\n";
						}
					}else{
						if(unitGrid[7][1] == '_'){
							p2Units.emplace(idP2, new Infantry(7,13));
							unitGrid[7][1]= 'i';
							idP2++;
						}else{
							cout << "Space in front of base already occupied. Please move unit first\n";
						}
					}
					unitBought = true;
				}else{
					cout << "Unit already bought this turn.\n";
				}
				break;
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
			case 4:
				unitsMoved=false;
				unitBought=false;
				turnCounter++;
				if(turnCounter%4 ==0){
					gameboard.changeWeather();
				}
				printMap(unitGrid, gameboard);
				curTurn = !curTurn;
				break;
			case 5:
				printMap(unitGrid, gameboard);
				break;
			case 6:
				return 0;
		}
		
	}
}

bool startGame(Map& gameboard, unordered_map<int, Unit*>& p1Units, unordered_map<int,Unit*>& p2Units){
	unsigned int choice;
	string size;

	cout << "Input a seed (put 0 for random)?: ";
	cin >> choice;
	
	if(choice ==0){
		srand(time(NULL));
	}else{
		srand(choice);
	}
	gameboard.generateMap();
	p1Units.emplace(0, new Base(7, 0));
	p2Units.emplace(0, new Base(7, 14));
	return rand()%2;
}

void printMap(vector<vector<char> >& unitGrid, Map& gameboard){
	int i, j;
	cout << gameboard.getWeather() << endl;
	for(i=0;i< gameboard.rows(); i++){
		for(j=0; j<gameboard.cols(); j++){
			cout << unitGrid[i][j] << gameboard.grid[i][j] << " ";
		}
		cout << endl;
	}
}

void moveUnit(unordered_map<int, Unit*>& units, vector<vector<char> >& unitGrid){
	unsigned int id, row, col;
	cout << "Current units:\n";
	unordered_map<int, Unit*>::iterator it;

	for(it = units.begin(); it != units.end(); it++){
		cout << it->first << '.' << (it->second)->name << endl;
	}
	cin >> id;
	if(id > units.size()){
		cout<<"Invalid id\n";
		return;
	}
	cout<< "Enter new row and col: ";
	cin >> row >> col;

	if(units[id]->move(row, col)){
		
	}

}

