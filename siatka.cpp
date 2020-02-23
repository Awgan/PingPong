

#include "siatka.h"
#include "stale.h"

#include <iostream>
#include <string>



const std::string siatkaFile = "./obrazy/sprit_pistacja.bmp" ;


Siatka::Siatka( int k )
{
	pozX = (OKNO_SZER / 2) - (SIATKA_SZER / 2);
	pozY = 0;
	kolor = red;
	
	siatkaRect.x = pozX; 
	siatkaRect.y = pozY;
	siatkaRect.w = SIATKA_SZER;
	siatkaRect.h = 30;
	
	siatkaSurf = SDL_LoadBMP( siatkaFile.c_str() );
	
}

Siatka::~Siatka()
{
	}

void Siatka::show( SDL_Renderer * ren )
{
	SDL_Texture * tex = SDL_CreateTextureFromSurface( ren, siatkaSurf );
	
	for ( int i = 0; i < OKNO_WYS / (2 * siatkaRect.h); i++ )
	{
		SDL_RenderCopy( ren, tex, NULL, &siatkaRect );
		
		//siatkaRect.x = pozX; 
		siatkaRect.y = siatkaRect.y + 3 * siatkaRect.h;
		//siatkaRect.w = SIATKA_SZER;
		//siatkaRect.h = 30;
	}
	
	SDL_DestroyTexture( tex );
	
	siatkaRect.y = pozY;
}



void Siatka::zmianaKolor( kol k )
{
	kolor = k;
}









