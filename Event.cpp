#include "Event.h"

void Event::New(long clk, int trg)
{
	clock=clk;
	for(int i=0; i<4; i++) hits[i].clear();
	trigger=(trg==1);
}

