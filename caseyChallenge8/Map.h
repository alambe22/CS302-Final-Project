#include "PerlinNoise.h"
#include <string>
#include <vector>
using namespace std;

class Map{
	int r,c,w,t;													//rows, cols, weather index, time index, random map offset
	const string weathers[7] = {"sunny", "cloudy", "windy", "rainy", "snowy", "foggy", "hail"};
	const char terrains[5] = {'O', 'D', 'P', 'F', 'M'};					//ocean, desert, plains, forrest, mountain
	const string times[2] = {"day", "night"};
	double x,y,z,offset;
	PerlinNoise *pn;
	void generateMap(PerlinNoise *pn);

public:
	Map();																//Initializes values with nothing
	~Map();
	vector< vector<char> > map;											//the map
	void resize(int r, int c);											//resize and reconstruct the map with r, c cols
	int rows() const {return r;}										//the number of rows
	int cols() const {return c;}										//the number of columns
	int size() const {return r*c;}										//the size of the map
	string getWeather() const {return weathers[w];}						//get the curernt weather
	int setWeather(string weather);										//set the weather
	void changeWeather();												//change weather randomly
	string getTime() const {return times[t];}							//get the current time
	int setTime(string time);											//set the time
	void changeTime();													//change the time
	int visibility(int row, int col, int range);					//the visibility at position row, col
	void print(vector< vector<char> > &units);
};
