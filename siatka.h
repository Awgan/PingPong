#ifndef SIATKA_H_
#define SIATKA_H_

#include <SDL2/SDL.h>


class Siatka
{
	private:
		enum kol{red, orange, blue, white};
		kol kolor;
		int pozX;
		int pozY;
		
		SDL_Rect siatkaRect;
		SDL_Surface * siatkaSurf;
		
		
	public:
		Siatka( int kolor );
		~Siatka();
		void show( SDL_Renderer * ren );
		void zmianaKolor( kol k );
				
};

#endif
