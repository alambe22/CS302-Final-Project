#include<iostream>
#include<vector>
#include<string>
using namespace std;

class map{
	public:
		map(int size=0);
		char getGrid(int index);
		string getWeather();
		void tick();
		int getWeight(char type);
		int getVisibility(char type);
	private:
		vector<char> grid;
		int curWeather;
		string weathers [] = ["rain", "clear", "foggy", "blizzard"];
		//forest, hill, mountain, plain
		int weights[] = [1, 3, 5, 0];
		int visibility[] = [-1, -2, -10, 0];
	
};

map::map(int size=0){
	int totSize;
	switch(
}
