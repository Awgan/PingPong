
#include "cyfra.h"
#include "stale.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

const std::string sprCyfra = "./obrazy/cyfry.bmp";



Cyfra::Cyfra( SDL_Renderer * ren, int xx)
{
		value = 0;
		
		kafelek = SDL_LoadBMP( sprCyfra.c_str() );				
		Uint32 colorkey = SDL_MapRGB( kafelek->format, 0, 0, 0 );
		SDL_SetColorKey( kafelek, SDL_TRUE, colorkey );
				
		tex = SDL_CreateTextureFromSurface( ren, kafelek );
		
			//first digit, left one
		digitRect.x = xx;
		digitRect.y = OKNO_WYS / 15;
		digitRect.w = 36;
		digitRect.h = 55;
			//second digit, right one
		digitRect2.x = xx + digitRect.w;
		digitRect2.y = OKNO_WYS / 15;
		digitRect2.w = 36;
		digitRect2.h = 55;
		
		
	for (int i = 0; i< 10; i++)
	{		
		arrCyfra[i].x = 8 + (i * 46);
		arrCyfra[i].y = 20;
		arrCyfra[i].w = 36;
		arrCyfra[i].h = 55;	
	}
	
}

Cyfra::~Cyfra()
{
	SDL_DestroyTexture( tex );
	if ( tex == nullptr )
		std::cout << "Cyfra: Tex Destroyed\n";
	SDL_FreeSurface( kafelek );
	if ( kafelek == nullptr )
		std::cout << "Cyfra: Surf Destroyed\n";
		
}

void Cyfra::show(SDL_Renderer * ren )
{
	if (value <= 9)
	{
		SDL_RenderCopy( ren, tex, &arrCyfra[value], &digitRect );
	}
	else
	if (value >= 10)
	{
		SDL_RenderCopy( ren, tex, &arrCyfra[value/10], &digitRect );
		SDL_RenderCopy( ren, tex, &arrCyfra[value%10], &digitRect2 );
	}	
}

void Cyfra::point()
{
	value++;
}


void Cyfra::res()
{
	value = 0;
}



























