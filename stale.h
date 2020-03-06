#ifndef STALE_H_
#define STALE_H_



const int PALETKA_SZER	= 20;
const int PALETKA_WYS	= 120;

const int PL1_POZ_X		= 50;


const int RUCH 			= 5;

const int PILKA_WYS 	= 23;
const int PILKA_SZER 	= 48;

const int SIATKA_SZER	= 1;


const int WYGRANA		= 10;

extern int OKNO_SZER 		;
extern int OKNO_WYS		;
extern int PL2_POZ_X		;
extern int PL_POZ_Y		;
extern int SIATKA_WYS		;

enum { RED = 81, GREEN = 88, BLUE = 112 };
	
inline void staleRun()
{

PL2_POZ_X		= OKNO_SZER - (PL1_POZ_X + PALETKA_SZER);
PL_POZ_Y		= OKNO_WYS / 2 - PALETKA_WYS / 2;

SIATKA_WYS		= OKNO_WYS;

}

#endif
