#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include <algorithm>

//
// hit data structure
//

class pxhit {
 public:
   long timeStamp; 
   bool trigger;
   int roc;
   int row;
   int dcol;
   int CD_Select;
   double pulseHeight;
   bool wrongTS;
   bool operator < (const pxhit& b)const{
     long aa=roc*1000+dcol;
     long bb=b.roc*1000+b.dcol;
     return (aa<bb);
   };
   void clear() { timeStamp=0;} ;
   void printhit();
};

typedef std::vector<pxhit> hit_vector;
typedef std::vector<pxhit>::iterator hit_iterator;
typedef std::vector<pxhit>::const_iterator hit_const_iterator;

class Event 
{
public:
   hit_vector hits[4];
   long clock;
   bool trigger;
   void New(long clk, int trg);
};

#endif /*EVENT_H_*/
