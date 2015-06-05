//this will be simple root function

#include "Riostream.h"

void plottable(TString filename,int WBC){

//load txt file
//the file has 8 data entries
//1)total number of hits
//2)pixel overwrite
//3)column drain busy
//4)time stamp buffer overflow
//5)data buffer overflow
//6)column blocked for readout
//7)reset after readout
//8)pixel fluence

ifstream in;
in.open(filename);

double totalhits;
double pixover;
double coldrain;
double ts;
double db;
double colblock;
double reset;
double pixelflu;

double totalineffhits;

int nlines = 0;

TGraph * g[7]; 
TMultiGraph * mg = new TMultiGraph();


for(int ii = 0; ii < 7; ++ii)
  {

g[ii] = new TGraph();

}


while(true)
  {

in >> totalhits >> pixover >> coldrain >> ts >> db >> colblock >> reset >> pixelflu;
if(!in.good()) break;

totalineffhits = pixover + coldrain + ts + db + colblock + reset;
++nlines;

//std::cout <<  totalhits << pixover << coldrain << ts << db << colblock << reset << pixelflu << std::endl;
 


g[0]->SetPoint(g[0]->GetN(),pixelflu,100*(totalineffhits/totalhits));
g[1]->SetPoint(g[1]->GetN(),pixelflu,100*(pixover/totalhits));
g[2]->SetPoint(g[2]->GetN(),pixelflu,100*(coldrain/totalhits));
g[3]->SetPoint(g[3]->GetN(),pixelflu,100*(ts/totalhits));
g[4]->SetPoint(g[4]->GetN(),pixelflu,100*(db/totalhits));
g[5]->SetPoint(g[5]->GetN(),pixelflu,100*(colblock/totalhits));
g[6]->SetPoint(g[6]->GetN(),pixelflu,100*(reset/totalhits));


}
int marksize = 2.5;
//style
g[0]->SetLineColor(1);
g[0]->SetMarkerColor(1);
g[0]->SetMarkerStyle(33);
g[0]->SetMarkerSize(marksize);
//
g[1]->SetLineColor(6);
g[1]->SetMarkerColor(6);
g[1]->SetMarkerStyle(22);
g[1]->SetMarkerSize(marksize);
//
g[2]->SetLineColor(4);
g[2]->SetMarkerColor(4);
g[2]->SetMarkerStyle(21);
g[2]->SetMarkerSize(marksize);
//
g[3]->SetLineColor(2);
g[3]->SetMarkerColor(2);
g[3]->SetMarkerStyle(5);
g[3]->SetMarkerSize(marksize);
//
g[4]->SetLineColor(2);
g[4]->SetMarkerColor(2);
g[4]->SetMarkerStyle(4);
g[4]->SetMarkerSize(marksize);
//
g[5]->SetLineColor(9);
g[5]->SetMarkerColor(9);
g[5]->SetMarkerStyle(33);
g[5]->SetMarkerSize(marksize);
//
g[6]->SetLineColor(28);
g[6]->SetMarkerColor(28);
g[6]->SetMarkerStyle(25);
g[6]->SetMarkerSize(marksize);
//


mg->SetTitle("Inefficiencies versus particle hit rate from DataFlow simulation;Particle pixel hit rate (MHz/cm^2);ROC inefficiency (%)");




for(int ii = 0; ii < 7; ++ii)
  {

mg->Add(g[ii]);

}

TCanvas c("c1","c1",2000,1200);
c.cd();
c.SetGrid();
//style
mg->Draw("ACP");
//axis
mg->GetXaxis()->SetLimits(0.0,250);

//legend
 char legendtitle[256];
 sprintf(legendtitle," WBC %d",WBC);
   TLegend * leg = new TLegend(0.1,0.5,0.40,0.9,legendtitle);

leg->AddEntry(g[0],"Total inefficiency","LP");
leg->AddEntry(g[1],"Pixel overwrite","LP");
leg->AddEntry(g[2],"Column drain busy (3rd hit)","LP");
leg->AddEntry(g[3],"Time stamp buffer overflow","LP");
leg->AddEntry(g[4],"Data buffer overflow","LP");
leg->AddEntry(g[5],"Column blocked for readout","LP");
leg->AddEntry(g[6],"Reset after readout","LP");
leg->Draw();


char outfilename[256];

sprintf(outfilename,"Ineff_Detail_WBC%d.pdf",WBC);
c.SaveAs(outfilename);


}
