
#include "HitMaker.h"

HitMaker::HitMaker(double hitRate, std::vector<double>& probs) {
  myDice_.SetSeed(0);
  clusterSizeDistribution_ = nullptr;
  SetClusterSizeProbabilities(probs);
  double averageClusterSize = clusterSizeDistribution_->GetMean();
  if (averageClusterSize>0) {
    clusterRate_ = hitRate / averageClusterSize;
    hitRate_ = hitRate;
    averageClusterCount_ = clusterRate_ * nRows * nColumns * pixelLength_ * pixelWidth_ / clockSpeed_;
    INFO_PRINT(hitRate_);
    INFO_PRINT(averageClusterSize);
    INFO_PRINT(clusterRate_);
    INFO_PRINT(averageClusterCount_);
  } else {
    std::cerr << "ERROR: the cluster size distribution has non-positive mean" << std::endl;
  }
}

HitMaker::HitMaker() {
  clusterSizeDistribution_ = nullptr;
  myDice_.SetSeed(0);
}

HitMaker::~HitMaker() {
  if (clusterSizeDistribution_) delete clusterSizeDistribution_;
}

void HitMaker::SetClusterSizeProbabilities(std::vector<double>& probs) {
  if (clusterSizeDistribution_) delete clusterSizeDistribution_;
  int nP = probs.size();
  if (nP > maxClusterSize) {
    std::cerr << "Cluster size distribution exceeds maximum allowed cluster size ("
	      << maxClusterSize << "). Ignoring cluster sizes " << nP << " and above."
	      << std::endl;
    nP = maxClusterSize;
  }
  clusterSizeDistribution_ = new TH1D("clusterSizeDistribution"
				     , "Cluster size distribution",
				     nP, 1, 1+nP);

  for (int i=0; i<nP; ++i) {
    clusterSizeDistribution_->Fill(1+i, probs[i]);
  }

}

int HitMaker::IntRand(int NN) {
  return int(myDice_.Rndm()*NN);
}

void HitMaker::GenerateEvents(unsigned long nEvents, TreeMaker& aTreeMaker) {
  int nClusters;
  int hitCol, hitRow, clusterSize;
  int randDirX, randDirY;
  for (unsigned long i=0; i<nEvents; ++i) {
    nClusters = myDice_.Poisson(averageClusterCount_);
    DEBUG_PRINT(nClusters);
    for (int j=0; j<nClusters; ++j) {
      hitCol = myDice_.Rndm() * nColumns;
      hitRow = myDice_.Rndm() * nRows;
      clusterSize = clusterSizeDistribution_->GetRandom();
      DEBUG_PRINT(clusterSize);
      int clusterOrientation = IntRand(2);
      const int *thisClusterCol, *thisClusterRow;
      if (clusterOrientation) {
      	thisClusterCol = templateClusterCoord1;
      	thisClusterRow = templateClusterCoord2;
      } else {
      	thisClusterCol = templateClusterCoord2;
      	thisClusterRow = templateClusterCoord1;
      }
      DEBUG_PRINT(clusterOrientation);
      for (int s=0; s<clusterSize; ++s) {
	aTreeMaker.AddHit(defaultAdc, hitCol+thisClusterCol[s], hitRow+thisClusterRow[s], false);
	DEBUG_PRINT2(hitCol+thisClusterCol[s], hitRow+thisClusterRow[s]);
	//	aTreeMaker.AddHit(defaultAdc, hitCol, hitRow);
      }
    }
    aTreeMaker.NextEvent();
  }
}
