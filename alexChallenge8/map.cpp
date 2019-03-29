#include<vector>
#include<string>
#include<cstdlib>
#include "map.h"
using namespace std;

Map::Map(){
	r=15;
	c=15;
	w=rand()%3;
	grid.resize(15, vector<char>(15));
}

void Map::generateMap(){
	int i,j;
	for(i=0; i< r; i++){
		for(j=0; j< c; j++){
			grid[i][j] = terrains[rand()%3];
		}
	}
}

void Map::changeWeather(){
	w=rand()%3;
}

int Map::visibility(int row, int col) const{
	int vis = 3;
	switch(grid[row][col]){
		case 'F':
			vis-=1;
			break;
		case 'M':
			vis+=3;
			break;
	}
	switch(w){
		case 1:
			vis -=2;
			break;
		case 2:
			vis -=3;
			break;
	}
	return (vis <=0)?(1):(vis);
}
