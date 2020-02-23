
#include <SDL2/SDL.h>

#include <iostream>
#include <string>


#include "cyfra.h"
#include "paletka.h"
#include "pilka.h"
#include "siatka.h"
#include "stale.h"

void staleRun();

 int OKNO_SZER 		;
 int OKNO_WYS		;
 int PL2_POZ_X		;
 int PL_POZ_Y		;
 int SIATKA_WYS		;


int main ( int argc, char * argv[] )
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		std::cout << "SDL_Inint error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Window * win = SDL_CreateWindow("PingPong", 0, 0, 400, 400, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	if ( win == nullptr )
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;	
	}
		//
		//get and set size of playground		
		struct playground 
		{
			int cw, ch;
		}pGround;
		
		SDL_GetWindowSize(win, &pGround.cw, &pGround.ch);
		
		OKNO_SZER 	= pGround.cw;
		OKNO_WYS	= pGround.ch;
		
		staleRun();	
		
		std::cout << pGround.cw << " " << pGround.ch << '\n';
	
	
	SDL_Renderer * ren = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() <<std::endl;
		SDL_Quit();
		return 1;
	}
	
	std::string sciezka = "./obrazy/tlo_czarne.bmp";
	SDL_Surface * bmp = SDL_LoadBMP(sciezka.c_str());
	if ( bmp == NULL)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;		
	}
	
	SDL_Texture * tlo = SDL_CreateTextureFromSurface( ren, bmp );
	SDL_FreeSurface( bmp );
	if ( tlo == NULL )
	{
		SDL_DestroyRenderer( ren );
		SDL_DestroyWindow( win );
		std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	Paletka player1( ren, PL1_POZ_X, PL_POZ_Y );
	Paletka player2( ren, PL2_POZ_X, PL_POZ_Y );
	SDL_Event ev;
	Pilka pil(ren);
	Siatka siata(1);
	Cyfra cyf1(ren, OKNO_SZER / 4);
	Cyfra cyf2(ren, 3 * OKNO_SZER / 4);
	int ruch1 = 0;
	int ruch2 = 0;
	int ruch1x = 0;
	int ruch2x = 0;
	
	bool dalej = true;
	
	while ( ev.type != SDL_QUIT && dalej  )
	{
		while( cyf1.result() < WYGRANA && cyf2.result() < WYGRANA && ev.type != SDL_QUIT && ev.key.keysym.sym != SDLK_n )
		{
			while ( SDL_PollEvent( &ev ) ){
				if ( ev.type == SDL_KEYDOWN )
				{
					switch ( ev.key.keysym.sym ){
					
					case SDLK_s :
						ruch1 = RUCH;
						break;
					
					case SDLK_w :
						ruch1 = -RUCH;
						break;
					
					case SDLK_a :
						ruch1x = -RUCH;
						break;
					
					case SDLK_d :
						ruch1x = RUCH;
						break;
					
					case SDLK_k :
						ruch2 = RUCH;
						break;
					
					case SDLK_i :
						ruch2 = -RUCH;
						break;
						
					case SDLK_j :
						ruch2x = -RUCH;
						break;
					
					case SDLK_l :
						ruch2x = RUCH;
						break;
					
					default :
						break;
					}
				}
				
				if ( ev.type == SDL_KEYUP )
				{
					switch (ev.key.keysym.sym){
					
					case SDLK_s :
						ruch1 = 0;
						break;
					
					case SDLK_w :
						ruch1 = 0;
						break;
					
					case SDLK_a :
						ruch1x = 0;
						break;
					
					case SDLK_d :
						ruch1x = 0;
						break;
					
					case SDLK_k :
						ruch2 = 0;
						break;
					
					case SDLK_i :
						ruch2 = 0;
						break;
					
					case SDLK_j :
						ruch2x = 0;
						break;
					
					case SDLK_l :
						ruch2x = 0;
						break;
					default :
						break;
					}
				}
				
				
				
			}
			
			SDL_RenderClear( ren );
			SDL_RenderCopy( ren, tlo, NULL, NULL );
			siata.show( ren );
			
			player1.move (ruch1x, ruch1);
			player2.move (ruch2x, ruch2);
			
			player2.show( ren );
			player1.show( ren );	
							
			pil.show( ren, player1, player2, cyf1, cyf2 );
			
			cyf1.show( ren );
			cyf2.show( ren );
			
			SDL_RenderPresent( ren );	
		}
		
		std::cout << "Gramy dalej? (y/n)\n";
		SDL_PumpEvents();
		//SDL_PollEvent( &ev ); 
		do
		{
			SDL_PollEvent( &ev );
			if ( ev.key.keysym.sym == SDLK_y )
			{
				dalej = true;
				cyf1.res();
				cyf2.res();
				std::cout << "bylo!\n";
			}
			else 
			if ( ev.key.keysym.sym == SDLK_n )
			{
				dalej = false;
			}
		} while ( ev.key.keysym.sym != SDLK_y && ev.key.keysym.sym != SDLK_n && ev.type != SDL_QUIT);
		
		
	}
	
	
	
	
	
	SDL_DestroyTexture( tlo );
	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );
	SDL_Quit();
	
return 0;
}



