#include "Map.h"
#include <iostream>
#include <cstdlib>
using namespace std;
float lerp(float num1, float num2, float x){
	return ((x*(num2-num1) + num1));
}
void noise1(int size, vector<float> &result){
	vector<float> random;
	random.resize(size);
	result.resize(size);
	srand(1);
	for(int i = 0; i < size; i++){
		random[i] = rand()%10;
	}
	float step = 1;
	int counter = size;
	float divisor = 0;
	while(counter != 1){
		for(int i = 0; i < size; i += counter){
			for(int j = i; j < i+counter; j++){
				result[j] += step*lerp(random[i], random[(i+counter)%size], (1.0*j)/(1.0*counter));
			}
		}
		divisor += step;
		counter /= 2;
		step /= 2;
	}
	for(int i = 0; i < size; i++)
		result[i] /= divisor;
}
void Map::generateMap(){
	srand(1);
	vector<char> row;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			row.push_back(terrains[rand()%5]);
		}
		grid.push_back(row);
		row.resize(0);
	}
	grid[r/2][0] = '1';
	grid[r/2][c-1] = '2';
	/*vector<float> random;
	noise1(15, random);
	for(int i = 0; i < 15; i++)
		cout << random[i] << endl;
	
	*/
}
Map::Map(string size){
	if (size == "small"){
		r = 15; c = 15;
	}
	else if (size == "medium"){
		r = 25; c = 25;
	}
	else if (size == "large"){
		r = 35; c = 35;
	}
	else{
		cout << "Incorrect value for size." << endl << "Use either \"small\", \"medium\", or \"large\"" << endl;
		exit(0);
	}
	t = 0;
	w = rand()%7;
	generateMap();
}
Map::Map(int r, int c){
	this->r = r;
	this->c = c;
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
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
