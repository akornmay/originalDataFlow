#ifndef TREEMAKER_H
#define TREEMAKER_H

#include <TTree.h>
#include <string>

/*
  Only a single ROC 0 on BPIX_Digis_Layer2 will have hits
  the Ladder is always 2
  and the Module is always 3

  Clock cycles without a hit are marked by adc = col = row = -1
*/

class TreeMaker {
 public:
  TreeMaker();
  ~TreeMaker();
  TTree& GetTree();
  void AddHit(short adc, short col, short row, bool fake);
  int NextEvent();
 private:
  TTree* myTree_;
  //Declaration of leaves types
  UInt_t          Event_;
  Short_t         Ladder_;
  Short_t         Module_;
  Short_t         adc_;
  Short_t         col_;
  Short_t         row_;
  UInt_t          EventHits_;
  const std::string defaultTreeName = "BPIX_Digis_Layer2";
  const int defaultLadder = 2;
  const int defaultModule = 3;
  const int noHit = -1;
};

#endif
