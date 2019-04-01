#include "Map.h"
#include <iostream>

using namespace std;
void Map::generateMap(PerlinNoise *pn){
	double value = 0.0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			x = (double)j/((double)c) + offset;
			y = (double)i/((double)r) + offset;
			value = pn->noise(x*3.0, y*3.0, z);
			/*if (value < 0.3)
				map[i][j] = terrains[0];
			else if (value < 0.4)
				map[i][j] = terrains[1];
			else if (value < 0.5)
				map[i][j] = terrains[2];
			else if (value < 0.7)
				map[i][j] = terrains[3];
			else
				map[i][j] = terrains[4];
			*/
			if(value < 0.2)
				map[i][j] = terrains[4];
			else if(value < 0.3)
				map[i][j] = terrains[3];
			else if (value < 0.4)
				map[i][j] = terrains[2];
			else if (value < 0.45)
				map[i][j] = terrains[1];
			else if (value < 0.5)
				map[i][j] = terrains[0];
			else if (value < 0.55)
				map[i][j] = terrains[1];
			else if (value < 0.6)
				map[i][j] = terrains[2];
			else if (value < 0.7)
				map[i][j] = terrains[3];
			else
				map[i][j] = terrains[4];
		}
	}
}
Map::Map(){
	r = 0;
	c = 0;
	w = 0;
	t = 0;
	x = 0;
	y = 0;
	z = drand48();
	offset = drand48();
	pn = new PerlinNoise(rand());
}
Map::~Map(){
	delete pn;
}
void Map::resize(int r, int c){
	this->r = r;
	this->c = c;
	map.resize(r);
	for(int i = 0; i < r; i++){
		map[i].resize(c);
	}
	generateMap(pn);
}
int Map::setWeather(string weather){
	for(int i = 0; i < 7; i++){
		if(weathers[i] == weather){
			w = i;
			return 0;
		}
	}
	cout << "Not a possible weather to set" << endl;
	return -1;
}
void Map::changeWeather(){
	w = rand()%7;
}
int Map::setTime(string time){
	if(time == times[0]){
		t = 0;
		return 0;
	}
	else if(time == times[1]){
		t = 1;
		return 0;
	}
	cout << "Not a possible time to set" << endl;
	return -1;
}
void Map::changeTime(){
	t = !t;
}
void Map::print(){
	cout << "Weather: " << weathers[w] << endl;
	cout << "Time: " << times[t] << endl;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}
