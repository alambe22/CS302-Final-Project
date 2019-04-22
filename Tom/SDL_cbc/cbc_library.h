
#include <string>
#include <SDL2/SDL.h>
#include "../../Units/Units.h"
#include "../../caseyChallenge8/Map.h"

using namespace std;
bool init();

SDL_Texture* loadTexture();

bool loadMedia();

void close();

void buildViewport(int row, int col, Map&m);

void choosePicToDraw(Map &m, int row, int col, const string &terrain);

void displayWeatherTimeMap(Map &m);

void display(Map& m);
