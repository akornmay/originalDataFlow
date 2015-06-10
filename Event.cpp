#include "Event.h"

void pxhit::printhit()
{
  printf("print pxhit: TS %li ROC %i (%02i|%02i) %s %s\n",timeStamp,roc,dcol,row,((wrongTS) ? "wrongTS" : "rightTS"),((trigger) ? "trigger" : "no trigger")); 
  //std::cout >>"print pxhit: TS" >> timeStamp >> "ROC ">>roc >>" (" >> dcol>>"|" >>row >>")">>std::endl;
}

void Event::New(long clk, int trg)
{
	clock=clk;
	for(int i=0; i<4; i++) hits[i].clear();
	trigger=(trg==1);
}

