#include <iostream>
#include <math.h>
#include <string>

#include <SDL2/SDL.h>

#include "paletka.h"
#include "pilka.h"
#include "stale.h"



//static const std::string pilkaFile = "./obrazy/sprit_pistacja.bmp" ;
static const std::string pilkaFile = "./obrazy/kula_ognia_01.bmp";


Pilka::Pilka(SDL_Renderer * ren)
{
	czyodbita = false;
	licz = 0;
	
	pozX = OKNO_SZER / 2;
	pozY = OKNO_WYS / 2;
	
	alfa = 0;
	b = pozY;
	
	kierunek = 'p';
	
	setPilkaRect();
	
	for (int j = 0; j < 2; ++j)
	{
		for ( int i = 0; i < 4; ++i)
		{
			pilkaSprite[j][i].x = 0 + (j * 52);
			pilkaSprite[j][i].y = 6 + (i * 23);
			pilkaSprite[j][i].w = 48;
			pilkaSprite[j][i].h = 23;
		}
	}
	
	pilkaSurf = SDL_LoadBMP( pilkaFile.c_str() );
	
	Uint32 colorkey = SDL_MapRGB( pilkaSurf->format, 255, 12, 255 );
	SDL_SetColorKey( pilkaSurf, SDL_TRUE, colorkey );
	
	pilkaTex = SDL_CreateTextureFromSurface( ren, pilkaSurf );	
}

Pilka::~Pilka()
{
	SDL_DestroyTexture( pilkaTex );
}

void Pilka::reset()
{	
	czyodbita = false;
	
	pozX = OKNO_SZER / 2;
	pozY = OKNO_WYS / 2;

	
	alfa = 0;
	b = pozY;
	
	kierunek =='p'?kierunek = 'l' : kierunek = 'p';
	
	setPilkaRect();
}

void Pilka::move()
{
	int x = 7;
	
	if ( czyodbita == false )
		x = 3;
	else
		x = 7;
	
	switch (kierunek)
	{
		case 'p':
		pozX += x;
		pozY = alfa * pozX + b;
		break;
		
		case 'l':
		pozX -= x;
		pozY = alfa * pozX + b;
		break;
		
		default:
		break;
	}
	pilkaRect.x = pozX;
	pilkaRect.y = pozY;
	
	
}

void Pilka::show( SDL_Renderer * ren, Paletka & p1, Paletka & p2, Cyfra & cyf1, Cyfra & cyf2 )
{
	move();
			
	if ( kolizja( p1, p2 ) == true ) // TODO, powinny być dwa argumenty, każdy do jednej paletki
	{	
		
	}
	else
	if (pozX < 0)
	{
		if ( czyodbita == true)
			cyf2.point();
		reset();		
	}
	else
	if ( pozX > OKNO_SZER )
	{
		if (czyodbita == true)
			cyf1.point();
		reset();
	}
	else
	if ( pozY < 0 || pozY + PILKA_WYS > OKNO_WYS )
	{
		alfa *= -1;
		b = pozY - (alfa * pozX);
	}
		
	
	switch (kierunek)
	{
		case 'p':	
			SDL_RenderCopy( ren, pilkaTex, &pilkaSprite[0][licz/15], &pilkaRect );
			break;
		case 'l':
			SDL_RenderCopy( ren, pilkaTex, &pilkaSprite[1][licz/15], &pilkaRect );
			break;
		default:
			break;
	}
	licz++;
	if (licz > 60 ) licz = 0;
}

bool Pilka::kolizja( Paletka & p1, Paletka & p2 )
{
	int p1Y = p1.getPozY();
	int p2Y = p2.getPozY();
	int p1X = p1.getPozX();
	int p2X = p2.getPozX();
	
	switch (kierunek)
	{
		case 'p':
			if ( 	pozX + PILKA_SZER >= p2X && pozX + PILKA_SZER <= p2X + 15 &&
					( pozY + PILKA_WYS >= p2Y && pozY <= p2Y + PALETKA_WYS )
				)
			{
				katOdbicia( p2, kierunek );
				
				kierunek = 'l';
				//std::cout << "teraz w LEWO!\n";
				return true;
			}	
		break;
		
		case 'l':
			if ( 	pozX <= p1X + PALETKA_SZER && pozX >= p1X + PALETKA_SZER - 15 &&
					( pozY + PILKA_WYS >= p1Y && pozY <= p1Y + PALETKA_WYS )
				)
			{
				katOdbicia( p1, kierunek );
				kierunek = 'p';
				//std::cout << "teraz w PRAWO!\n";
				
				return true;
			}
		break;
		
		default:
		break;
	}
	return false;
}

void Pilka::katOdbicia( Paletka & p1, char & kier)
{
	int piSrY = pozY + ( PILKA_WYS / 2 );
	int p1SrY = p1.getPozY() + ( PALETKA_WYS / 2 );
		
	double katPoz0 = 0;
	double katPozMax = 30;
	
	double katRatio = (katPoz0 + katPozMax) / double( (PALETKA_WYS / 2) );
	//std::cout << "katRatio: " << katRatio << "\n";
	alfa = tan ( (p1SrY - piSrY) * katRatio * 3.1415 / 180 );
	//std::cout << "p1SrY - piSrY= " << p1SrY - piSrY << "\n";
	//std::cout << "alfa: " << alfa << "\n";
	switch (kier)
	{
		case 'p':
		alfa *= 1;
		break;
		
		case 'l':
		alfa *= -1;
		break;
		
		default:
		break;
	}
	
	b = pozY - (alfa * pozX);
	
	czyodbita = true;
}

void Pilka::setPilkaRect()
{
	pilkaRect.x = pozX;
	pilkaRect.y = pozY;
	pilkaRect.w = 48;
	pilkaRect.h = 23;
}




