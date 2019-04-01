#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "Map.h"

using namespace std;

int main(){
	srand(time(NULL));
	Map m;
	m.resize(25, 25);
	m.print();
	m.resize(15, 15);
	m.print();
}
