#ifndef PALETKA_H_
#define PALETKA_H_

#include "stale.h"

#include <SDL2/SDL.h>

class Paletka
{		
	private:
		int startX;
		int startY;
		int pozX;
		int pozY;
		enum wymiar { szer = PALETKA_SZER, wys = PALETKA_WYS };
		
		SDL_Surface * paletkaSurf;
		SDL_Rect paletkaRect;
		SDL_Rect player;
		SDL_Texture * paletkaTex;
		
		void moveY( int& dy );
		void moveX( int& dx );
		
	public:
		Paletka( SDL_Renderer * ren, int x, int y );
		~Paletka();
		void show( SDL_Renderer * ren ) const;
		
		void move( int& dx, int& dy );
		SDL_Rect pozycja();
		int getPozY() { return this->pozY; }
		int getPozX() { return this->pozX; }
	
};

#endif
