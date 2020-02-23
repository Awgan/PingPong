#ifndef PILKA_H_
#define PILKA_H_

#include "cyfra.h"
#include "paletka.h"

#include <SDL2/SDL.h>


class Pilka
{
	
	private:
		int pozX;
		int pozY;
		SDL_Rect pilkaRect;	
		SDL_Rect pilkaSprite[2][4];	
		double alfa;
		int b;		
		char kierunek;			//TODO: change for random choose start direction	
		SDL_Surface * pilkaSurf;
		SDL_Texture * pilkaTex;
		bool czyodbita;
		int licz;
		
		
		bool kolizja( Paletka & pal1, Paletka & pal2 );
		void move();
		void katOdbicia( Paletka & pal1, char & kier);
		void reset();		
		void setPilkaRect();		
		
	public:
		Pilka(SDL_Renderer * ren);
		~Pilka();
		
		void show( SDL_Renderer * ren, Paletka & pal1, Paletka & pal2, Cyfra &cyf1, Cyfra & cyf2 );
		
};

#endif
