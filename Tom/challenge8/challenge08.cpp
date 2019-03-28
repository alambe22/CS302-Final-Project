//Tom Hills (jhills)

//

//#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <SDL2/SDL.h> //g++ -w -lSDL2 -o challenge08 challenge08.cpp

//GLOBALS--------------------------------------------------------------------------------------------------------------------
//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gImage = NULL;

bool init()
{
    //Initialization flag
//    bool success = true;

	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false; 
	}

 	else
    {
        //Create window
        gWindow = SDL_CreateWindow( "CS302 Gameboard Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
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
        }
	}
    
//
////    return success;
	return true;
}


bool loadMedia()
{
    //Loading success flag
//    bool success = true;

    //Load splash image
    gImage = SDL_LoadBMP( "Images/GIGER.bmp" );
    
	if( gImage == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "Tom/Images/GIGER.bmp", SDL_GetError() );
		return false;
//        success = false;
    }

//    return success;
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
            //Apply the image
            SDL_BlitSurface( gImage, NULL, gScreenSurface, NULL );

			//Update the surface
            SDL_UpdateWindowSurface( gWindow );
           
			//Wait two seconds
            SDL_Delay( 5000 );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
