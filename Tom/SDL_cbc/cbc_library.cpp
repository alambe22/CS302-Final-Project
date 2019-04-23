//Final Project: SDL portion

//Tom Hills (jhills)

//
#include "cbc_library.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <SDL2/SDL.h> //compile: g++ -w -lSDL2 -o challenge08 challenge08.cpp
//#include <SDL2/SDL_image.h>

using namespace std;

//GLOBALS-------------------------------------------------------------------------------------------------------------------
	//screen dimension constants
//	const int SCREEN_WIDTH = 640;
//	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	//image path
	string path;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Current displayed texture
	SDL_Texture* gTexture = NULL;

	//Rectangle for viewport
	SDL_Rect viewport;

//FUNCTIONS-----------------------------------------------------------------------------------------------------------------
bool init()
{
	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false; 
	}

 	else
    {
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
        gWindow = SDL_CreateWindow( "Chess, but COOLER!!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
									SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return false;
        }

		else
        {

			//Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            
			if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return false;
            }
            
			else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			}
        }
	}
    
	return true;
}

SDL_Texture* loadTexture()
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() ); //BMP
    
	if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    
	else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        
		if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

//loads texture with BMP image passed in path
//NOTE: passing a copy of gTexture pointer should be ok because the same memory address should be referenced in both copies. 
bool loadMedia() 
{
    //Load BMP texture
    gTexture = loadTexture();
    
	if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        return false;
    }

	return true;
}

void close()
{
	//Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

//builds and renders one element from map to corresponding viewport in window
void buildMapTileViewport(int row, int col, Map &m)
{
//NOTE: Made a HUGE mistake with integer division...see commented out code below == () portion is ALWAYS ZERO 
//	viewport.x = ( col / m.map[row].size() ) * SCREEN_WIDTH;
	
	//assign dimensions to viewport
	viewport.x = ( col * SCREEN_WIDTH ) / m.map[row].size();
	viewport.y = ( row * SCREEN_HEIGHT ) / m.map.size();
	viewport.w = SCREEN_WIDTH / m.map[row].size();
	viewport.h = SCREEN_HEIGHT / m.map.size();
	SDL_RenderSetViewport( gRenderer, &viewport );

	//Render texture to screen
	SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
}

//chooses picture based on map parameters
//NOTE: passing map object because I weather, time, etc to choose the picture
void chooseMapTileToDraw(Map &m, const string &terrain)
{
	//get weather and time from map
	string weather = m.getWeather();
	string time = m.getTime();

	//set picture path based on map parameters
	if (weather == "cloudy" && time == "day") {path = "Images/cloudy/day/" + terrain; return;}
	else if (weather == "cloudy" && time == "night") {path = "Images/cloudy/night/" + terrain; return;}
	
	else if (weather == "foggy" && time == "day") {path = "Images/foggy/day/" + terrain; return;}
	else if (weather == "foggy" && time == "night") {path = "Images/foggy/night/" + terrain; return;}
	
	else if (weather == "hail" && time == "day") {path = "Images/hail/day/" + terrain; return;}
	else if (weather == "hail" && time == "night") {path = "Images/hail/night/" + terrain; return;}
	
	else if (weather == "rainy" && time == "day") {path = "Images/rainy/day/" + terrain; return;}
	else if (weather == "rainy" && time == "night") {path = "Images/rainy/night/" + terrain; return;}
	
	else if (weather == "snowy" && time == "day") {path = "Images/snowy/day/" + terrain; return;}
	else if (weather == "snowy" && time == "night") {path = "Images/snowy/night/" + terrain; return;}
	
	else if (weather == "sunny" && time == "day") {path = "Images/sunny/day/" + terrain; return;}
	else if (weather == "sunny" && time == "night") {path = "Images/sunny/night/" + terrain; return;}
	
	else if (weather == "windy" && time == "day") {path = "Images/windy/day/" + terrain; return;}
	else if (weather == "windy" && time == "night") {path = "Images/windy/night/" + terrain; return;}
}

//renders icons to game window that correspond to the current map configuration 
void displayWeatherTimeTerrain(Map &m)
{
	for (int row = 0; row < m.map.size(); ++row)
	{
		for (int col = 0; col < m.map[row].size(); ++col)
		{
			switch(m.map[row][col])
			{
				case 'O':
					
					chooseMapTileToDraw(m, "river.bmp");
				
					//Load media
					if( !loadMedia() ) 
					{
						printf( "Failed to load media for row %d and col %d!\n", row, col );
					}

					else { buildMapTileViewport(row, col, m); }
					
					break;

				case 'D':
					
					chooseMapTileToDraw(m, "desert.bmp");
					
					//Load media
					if( !loadMedia() ) 
					{
						printf( "Failed to load media for row %d and col %d!\n", row, col );
					}

					else { buildMapTileViewport(row, col, m); }
					
					break;
				
				case 'P':

					chooseMapTileToDraw(m, "plains.bmp");
					
					//Load media
					if( !loadMedia() ) 
					{
						printf( "Failed to load media for row %d and col %d!\n", row, col );
					}

					else { buildMapTileViewport(row, col, m); }
					
					break;

				case 'F':
					
					chooseMapTileToDraw(m, "forest.bmp");
					
					//Load media
					if( !loadMedia() ) 
					{
						printf( "Failed to load media for row %d and col %d!\n", row, col );
					}

					else { buildMapTileViewport(row, col, m); }
					
					break;

				case 'M':
					
					chooseMapTileToDraw(m, "mountain.bmp");
					
					//Load media
					if( !loadMedia() ) 
					{
						printf( "Failed to load media for row %d and col %d!\n", row, col );
					}

					else { buildMapTileViewport(row, col, m); }
					
					break;

				default:
					cout << "Invalid m.map entry\n" << endl;
					exit(1);
			}
		}
	}
}

//draws unit image to correct location within tile viewport
void buildUnitViewport(int row, int col, vector<vector<char> > &v)
{
    //assign dimensions to viewport
    viewport.x = (( col * SCREEN_WIDTH ) / v[row].size()) + ( SCREEN_WIDTH / v[row].size() ) / 4;
    viewport.y = ( row * SCREEN_HEIGHT ) / v.size() + 2 * ( SCREEN_HEIGHT / v.size() ) / 4; 
    viewport.w = ( SCREEN_WIDTH / v[row].size() ) / 2;
    viewport.h = ( SCREEN_HEIGHT / v.size() ) / 2;
    SDL_RenderSetViewport( gRenderer, &viewport );

    //Render texture to screen
    SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
}

//draws units if present in corresponding tile
void displayUnits(vector <vector<char> > &v)
{
    for (int row = 0; row < v.size(); ++row)
    {
        for (int col = 0; col < v[row].size(); ++col)
        {
            switch(v[row][col])
            {
                case '_':

                    /*Do nothing. No unit present on tile.*/
                    break;

                //sniper unit
                case 'S':

                    path = "Images/Units/sniper.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;

               //artillery
                case 'A':

                    path = "Images/Units/artillery.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;

                //infantry unit
                case 'I':

                    path = "Images/Units/infantry.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;

                //cavalry unit
                case 'C':

                    path = "Images/Units/cavalry.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;

                //biker unit
                case 'B':

                    path = "Images/Units/biker.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;

                //base unit
                case 'b':

                    path = "Images/Units/base.bmp";

                    //Load media
                    if( !loadMedia() )
                    {
                        printf( "Failed to load media for row %d and col %d!\n", row, col );
                    }

                    else { buildUnitViewport(row, col, v); }

                    break;
                
				default:
                    cout << "Invalid m.map entry\n" << endl;
                    exit(1);
            }
        }
    }
}


/*int main (int argc, char *args[])
{
	//create game board
//	srand(time(NULL));//put this back later when I want random maps
	Map m;
	m.resize(10,10);
	m.print();
	
//TEST
//string test;

	//Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    
	else
    {
		//game loop boolean
		bool quit = false;

		//Event handler
		SDL_Event event;

		//game loop
		while ( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &event ) != 0 )
			{
				//User requests quit
				if( event.type == SDL_QUIT )
				{
					quit = true;
				}
			}
			
//cout << "Blah me:\n";
//cin >> test;
//cout << "You entered: " << test << endl;

			//Clear screen
			SDL_RenderClear( gRenderer );

			//displays a grid of icons representing the current map configuration
			displayWeatherTimeTerrain( m );

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
    }

    //Free resources and close SDL
    close();

    return 0;
}*/

void display( Map &m, vector<vector<char> > &v )
{
	SDL_RenderClear( gRenderer );
	displayWeatherTimeTerrain( m );
	displayUnits( v );
	SDL_RenderPresent( gRenderer );
}