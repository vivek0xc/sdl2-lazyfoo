#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);

void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gStretchedSurface = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface *loadSurface(std::string path)
{
	SDL_Surface *optimizedSurface = NULL;
	SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		exit(-1);
	}
	optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
	if(optimizedSurface == NULL)
	{
		printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		exit(-1);
	}
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

bool loadMedia()
{
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/hello_world.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/VG0017.BMP");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/led_strips_MonaLisa.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/lena.bmp");
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/testnoise.bmp");

	return true;
}

void close()
{
	//	SDL_FreeSurface(gHelloWorld);
	//	gHelloWorld = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;


	if(init())
	{
		if(loadMedia())
		{
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while(!quit)
			{
				while(SDL_PollEvent(&e) != 0)
				{
					if(e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN)
					{
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
								break;
							case SDLK_DOWN:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
								break;
							case SDLK_LEFT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
								break;
							case SDLK_RIGHT:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
								break;
							default:
								gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
								break;
						}
					}

				}
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
				//SDL_BlitSurface(gStretchedSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
		close();
	}

	return 0;
}
