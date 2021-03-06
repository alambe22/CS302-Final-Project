//Tom Hills (jhills)

//see corresponding cpp file for more information

#include <string>
#include <SDL2/SDL.h>
#include "../../Units/Units.h"
#include "../../caseyChallenge8/Map.h"

using namespace std;

bool init();

SDL_Texture* loadTexture();

bool loadMedia();

void close();

void buildMapTileViewport ( int row, int col, Map&m );

void chooseMapTileToDraw ( Map &m, const string &terrain );

void displayWeatherTimeTerrain ( Map &m );

void buildUnitViewport ( int row, int col, vector < vector < pair<char, bool> > > &v );

void displayUnits ( vector < vector < pair<char, bool> > > &v );

void display ( Map& m, vector < vector < pair<char, bool> > > &v );


