#ifndef CYFRA_H_
#define CYFRA_H_

#include <SDL2/SDL.h>


class Cyfra
{
	private:
		
		int value;
		
		SDL_Surface * kafelek;
		SDL_Texture * tex;
		SDL_Rect digitRect;			//place for first digit
		SDL_Rect digitRect2;		//place for second digit
		
		SDL_Rect arrCyfra[10];		//array for place info of each digit from bmp file
		
	public:
		
		Cyfra( SDL_Renderer * ren, int xx );
		~Cyfra();
		
		void show( SDL_Renderer * ren );
		void point();
		int result() { return value; }		
		void res();
		
};





#endif
