// Local includes
#include "HitMaker.h"
#include "TreeMaker.h"

// standard includes
#include <iostream>
#include <cstdlib>
#include <vector>

// ROOT includes
#include <TTree.h>

int main(int argc, char* argv[]) {

  if (argc<4) {
    std::cout << "Syntax: " << argv[0]
	      << " nEvents pixelRate p1 p2 p3 ...\n"
	      << " for ii in ;do ./FillMaker 5000000 ${ii} 1 4 3 2 && mv aTree.root ParticleData${ii}MHz.root; done" << std::endl;
    return -1;
  }

  long nEvents = atol(argv[1]);
  double pixelRate = atof(argv[2]);
  std::vector<double> hitProbs;
  for (int i=3; i<argc; ++i) {
    hitProbs.push_back(atof(argv[i]));
  }
  
  std::cout << "Pixel rate : " << pixelRate << " MHz/cm^2" << std::endl;
  int i=1;
  for (auto hp : hitProbs) {
    std::cout << "Probability(size=" << i << ") = " << hp << std::endl;
  }

  HitMaker myHitMaker(pixelRate, hitProbs);
  TreeMaker myTreeMaker;
  myHitMaker.GenerateEvents(nEvents, myTreeMaker);
  TTree& myTree = myTreeMaker.GetTree();
  myTree.SaveAs("aTree.root");

  return 0;
}
