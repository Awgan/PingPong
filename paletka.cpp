
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "paletka.h"

const std::string paletkaFile = "./obrazy/sprit_pistacja.bmp" ;


Paletka::Paletka( SDL_Renderer * ren, int x, int y )
{
	
	startX = x;
	startY = y;
	pozX = startX;
	pozY = startY;
	
	paletkaRect.x = 0;
	paletkaRect.y = 0;
	paletkaRect.w = szer;
	paletkaRect.h = wys;
	
	player.x = pozX;
	player.y = pozY;
	player.w = szer;
	player.h = wys;
	
	paletkaSurf = SDL_LoadBMP( paletkaFile.c_str() );
	paletkaTex = SDL_CreateTextureFromSurface( ren, paletkaSurf );
}

Paletka::~Paletka()
{
	SDL_FreeSurface( paletkaSurf );
	SDL_DestroyTexture( paletkaTex );
	
}

void Paletka::show( SDL_Renderer * ren ) const
{
	SDL_RenderCopy( ren, paletkaTex, &paletkaRect, &player );
}

void Paletka::moveY( int& dy )
{	
	if(pozY + dy > 0 && pozY + PALETKA_WYS + dy < OKNO_WYS)
	{
		pozY +=dy;
		player.y = pozY;
	}
}

void Paletka::moveX( int& dx )
{
	if ( pozX < OKNO_SZER / 2 )
	{
		if ( pozX + dx > 0 	&&	 pozX + PALETKA_SZER + dx < OKNO_SZER / 2 )
		{
			pozX +=dx;
			player.x = pozX;
		}
	}
	else
	if ( pozX > OKNO_SZER / 2 )
	{
		if ( pozX + PALETKA_SZER + dx < OKNO_SZER 	&& 	pozX + dx > OKNO_SZER / 2 )
		{
			pozX +=dx;
			player.x = pozX;
		}
	}
}

void Paletka::move( int& dx, int& dy )
{
	moveY( dy );
	moveX( dx );	
}
