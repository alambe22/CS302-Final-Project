#include <iostream>
#include <string>
#include <cstdlib>
#include "Map.h"

using namespace std;

int main(){
	srand(5);
	Map m;
	m.resize(25, 25);
	m.print();
	m.resize(15, 15);
	m.print();
}
