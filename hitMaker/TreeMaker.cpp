#include "TreeMaker.h"

TreeMaker::TreeMaker() {
  myTree_ = new TTree();
  myTree_->SetName(defaultTreeName.c_str());

  // Set branch addresses
  myTree_->Branch("Event",&Event_);
  myTree_->Branch("Ladder",&Ladder_);
  myTree_->Branch("Module",&Module_);
  myTree_->Branch("adc",&adc_);
  myTree_->Branch("col",&col_);
  myTree_->Branch("row",&row_);

  // set default values
  Ladder_ = defaultLadder;
  Module_ = defaultModule;
  Event_ = 0;
  EventHits_ = 0;
}

void TreeMaker::AddHit(short adc, short col, short row) {
  adc_ = adc;
  col_ = col;
  row_ = row;
  EventHits_++;
  myTree_->Fill();
}

int TreeMaker::NextEvent() {
  if (EventHits_==0) {
    AddHit(noHit, noHit, noHit);
  }
  EventHits_=0;
  Event_++;
  return Event_;
}

TreeMaker::~TreeMaker() {
  delete myTree_;
}

TTree& TreeMaker::GetTree() {
  return (*myTree_);
}


