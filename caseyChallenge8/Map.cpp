/*	Casey Mathews
 *	Description: Implement all of the functions for Map.h which is used in
 *	main to create the map, handle weather, time, and visibility, and print the map to console
 *	Credit to Paul Silisteanu for his perlin noise implementation.
 */
#include "Map.h"
#include <iostream>

using namespace std;
//generate the map using perlin noise
void Map::generateMap(PerlinNoise *pn){
	double value = 0.0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			x = (double)j/((double)c) + offset;
			y = (double)i/((double)r) + offset;
			//get a noise value
			value = pn->noise(x*3.0, y*3.0, z);
			//determine which type of terrain is associated with the corrordinate
			//something like M F P D O D P F M with random generation
			if(value < 0.2)
				map[i][j] = terrains[4];
			else if(value < 0.29)
				map[i][j] = terrains[3];
			else if (value < 0.39)
				map[i][j] = terrains[2];
			else if (value < 0.44)
				map[i][j] = terrains[1];
			else if (value < 0.51)
				map[i][j] = terrains[0];
			else if (value < 0.56)
				map[i][j] = terrains[1];
			else if (value < 0.61)
				map[i][j] = terrains[2];
			else if (value < 0.71)
				map[i][j] = terrains[3];
			else
				map[i][j] = terrains[4];
		}
	}
}
//how far a unit can see based on the terrain, weather, and time of day
int Map::visibility(int r, int c) const{
	int range = 5;		//base range
	float tMod = 0;		//terrain modifier
	float wMod = 0;		//weather modifier
	float dMod = 0;		//daylight modifier
	switch(map[r][c]){
		case 'O': tMod = 0.5; break;
		case 'D': tMod = 0.5; break;
		case 'P': tMod = 0.75; break;
		case 'F': tMod = 0.25; break;
		case 'M': tMod = 1.5; break;
	}
	switch(w){
		case 0: wMod = 1.0; break;
		case 1: wMod = 0.9; break;
		case 2: wMod = 0.9; break;
		case 3: wMod = 0.7; break;
		case 4: wMod = 0.5; break;
		case 5: wMod = 0.4; break;
		case 6: wMod = 0.6; break;
	}
	switch(t){
		case 0: dMod = 1.0; break;
		case 1: dMod = 0.8; break;
	}
	range *= (tMod * wMod * dMod);
	if(range < 1) range = 1;
	return range;
}
//initialize values in constructor
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
//delete all allocated memory
Map::~Map(){
	delete pn;
}
//used to resize the generated map to a certain size
void Map::resize(int r, int c){
	this->r = r;
	this->c = c;
	map.resize(r);
	for(int i = 0; i < r; i++){
		map[i].resize(c);
	}
	generateMap(pn);
}
//set the weather given a string
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
//change the weather randomly
void Map::changeWeather(){
	w = rand()%7;
}
//set the time given a string
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
//set the time to the other time of day
void Map::changeTime(){
	t = !t;
}
//print out the map in color to the console
void Map::print(vector< vector<char> > &units){
	cout << "Weather: " << weathers[w] << endl;
	cout << "Time: " << times[t] << endl;
	string str;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			switch(map[i][j]){
				case 'O': str = "\e[34m"; break;
				case 'D': str = "\e[93m"; break;
				case 'P': str = "\e[92m"; break;
				case 'F': str = "\e[32m"; break;
				case 'M': str = "\e[90m"; break;
			}
			cout << str + map[i][j] + units[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\e[0" << endl;
}
