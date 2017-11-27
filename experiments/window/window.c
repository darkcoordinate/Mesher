#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetCaption("SDL Test", "SDL Text");

	SDL_Surface* screen ;
	screen= SDL_SetVideoMode(640, 480, 0, 0);

	SDL_Surface* temp = SDL_LoadBMP("./sdl_logo.bmp");

	SDL_Surface* bg ;
	bg = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	SDL_Event event;

	int gameover = 0;

	while(!gameover)
	{
		if(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					gameover = 1;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;
					}
					break;
			}
		}

		SDL_BlitSurface(bg, NULL, screen, NULL);

		SDL_UpdateRect(screen, 0, 0, 0,0);
	}

	SDL_FreeSurface(bg);

	SDL_Quit();

	return 0;
}
