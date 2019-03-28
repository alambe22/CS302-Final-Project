#include <iostream>
#include <string>
#include "Map.h"

using namespace std;

int main(){
	Map m("medium");
	m.setTime("night");
	m.setWeather("hail");
	m.print();
	m.changeTime();
	m.print();
}
