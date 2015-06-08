#ifndef HITMAKER_H
#define HITMAKER_H

#include <TH1D.h>
#include <vector>
#include <TRandom3.h>
#include <iostream>
#include "TreeMaker.h"

#undef FULL_DEBUG

#define INFO_PRINT(x) std::cerr << #x"=" << x << std::endl
#define INFO_PRINT2(x, y) std::cerr << #x"=" << x << ", " << #y"=" << y << std::endl

#ifdef FULL_DEBUG
#define DEBUG_PRINT(x) std::cerr << #x"=" << x << std::endl
#define DEBUG_PRINT2(x, y) std::cerr << #x"=" << x << ", " << #y"=" << y << std::endl
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINT2(x, y)
#endif

class HitMaker {
 public:
  HitMaker(double hitRate, std::vector<double>& probs);  
  ~HitMaker();
  void SetClusterSizeProbabilities(std::vector<double>& probs);
  void GenerateEvents(unsigned long nEvents, TreeMaker& aTreeMaker);
 private:
  HitMaker();
  TH1D* clusterSizeDistribution_;
  double clusterRate_;
  double hitRate_;
  double averageClusterCount_;
  TRandom3 myDice_;

  int IntRand(int);

  const int nColumns = 56;
  const int nRows = 80;
  const double pixelLength_ = 0.015; // cm
  const double pixelWidth_  = 0.010; // cm
  const double clockSpeed_  = 40;    // MHz
  const short defaultAdc = 50;

  const int maxClusterSize = 6;
  const int templateClusterCoord1[6] = { +0, +1, +0, +1, +0, +1};
  const int templateClusterCoord2[6] = { +0, +0, +1, +1, -1, -1};
  
};


#endif
