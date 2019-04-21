//Final Project: SDL portion

//Tom Hills (jhills)

//

#include <ctime>
#include "Map.h"
#include "Units.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <SDL2/SDL.h> //compile: g++ -w -lSDL2 -o challenge08 challenge08.cpp
//#include <SDL2/SDL_image.h>

using namespace std;

//GLOBALS--------------------------------------------------------------------------------------------------------------------
//NOTE: These globals are temporary placeholders until I get past lazyfoo tutorials

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//test image path
string path = "Images/GIGER.bmp";

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gImage = NULL;

//Loads individual image as texture
//SDL_Texture* loadTexture( path );

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

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

			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );

			//Initialize renderer color
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


//SDL_image.h stuff commented out. Keep getting "undefined referenced to 'IMG_Init' and 'IMG_Load'
//...I don't think this is correctly installed on the lab machines, but leaving code here just in case
	
//			//NOTE: These don't work yet b/c I haven't converted to PNG image format yet in other code
//			//...need to figure out what image format I'm going to use.
//			//Initialize PNG loading
//			int imgFlags = IMG_INIT_PNG;
//			
//			if( !( IMG_Init( imgFlags ) & imgFlags ) )
//			{
//				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
//				return false;
//			}
//			else 
//			{
//				//Get window surface
//              gScreenSurface = SDL_GetWindowSurface( gWindow );
//			}
        }
	}
    
	return true;
}

//converts image to screen format to avoid a convert for every blit call
SDL_Surface* loadSurface( string &path )
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() ); //JPEG
//	SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); //PNG -- undefined reference to 'IMG_Load'
	
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); // JPEG
//		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() ); //PNG
	}
	
	else
	{
		//Convert surface to screen format. NOTE: SDL_ConvertSurface returns a copy of "loadedSurface"
		optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
		
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface (optimizedSurface is a COPY of this old surface as returned by SDL_ConvertSurface)
		SDL_FreeSurface( loadedSurface );
	}

	return optimizedSurface;
}

bool loadMedia()
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    gImage = loadSurface( path );
    
	if( gImage == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "Tom/Images/GIGER.bmp", SDL_GetError() );
		return false;
    }

	return true;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface( gImage );
    gImage = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main (int argc, char *args[])
{
	//TEST GAME BOARD
	srand(time(NULL));
	Map m;
	m.resize(10,10);
//	m.print();
//	return 0;
	
	//Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
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
			
				//Apply the image
				SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
