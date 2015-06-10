// a root function to compare the results from the C++ and the Python code

#include "Riostream.h"
#include <vector>

#include "TTree.h"



void CodeResultComparison(TString CppFile, TString PythonFile, int WBC){


  TTree myCPPTree("tree","A tree to store the data for plotting");

//loading the C++ txt file
//the file has 8 data entries
//1)total number of hits
//2)pixel overwrite
//3)column drain busy
//4)time stamp buffer overflow
//5)data buffer overflow
//6)column blocked for readout
//7)reset after readout
//8)pixel fluence
  ifstream inCpp;
  inCpp.open(CppFile);
 

 double pixelflu;
 myCPPTree.Branch("PixelFluence",&pixelflu,"PixelFluence/D");

 double totalhits;
 myCPPTree.Branch("TotalHits",&totalhits,"TotalHits/D");

 double pixover;
 myCPPTree.Branch("PixelOverwrite",&pixover,"PixelOverwrite/D");
 TGraph * pixoverGraph = new TGraph();

 double coldrain;
 myCPPTree.Branch("ColumnDrainBusy",&coldrain,"ColumnDrainBusy/D");
 TGraph * coldrainGraph = new TGraph();

 double ts;
 myCPPTree.Branch("TSBufferOVF",&ts,"TSBufferOVF/D");
 TGraph * tsGraph = new TGraph();

 double db;
 myCPPTree.Branch("DBufferOVF",&db,"DBufferOVF/D");
 TGraph * dbGraph = new TGraph();

 double colblock;
 myCPPTree.Branch("ColBlocked",&colblock,"ColBlocked/D");
 TGraph * colblockGraph = new TGraph();

 double reset;
 myCPPTree.Branch("ResetAfterReadout",&reset,"ResetAfterReadout/D");
 TGraph * resetGraph = new TGraph();
 
 double totalineffhits;
 myCPPTree.Branch("TotalInefficientHits",&totalineffhits,"TotalInefficientHits/D");
 TGraph * totalIneffGraph = new TGraph();

int nlines = 0;


while(true)
  {

    inCpp >> totalhits >> pixover >> coldrain >> ts >> db >> colblock >> reset >> pixelflu;
    if(!inCpp.good()) break;
    
    totalineffhits = pixover + coldrain + ts + db + colblock + reset;
    ++nlines;

    myCPPTree.Fill();


  }
 std::cout << "Finished reading C++ results " << myCPPTree.GetEntries() << "entries " <<  std::endl;
 
 // now let's try to load the other file

 //END {print "'$a'", rate, rate_err, eff, eff_err, -operative, operative_err, -token, token_err, -readout, readout_err, -reset, reset_err, -activated, activated_err, -drained, drained_err, -buffered, buffered_err, -valid, valid_err, -color_ovf, color_ovf_err, -ts_ovf, ts_ovf_err, -retained, retained_err, -reset_ro, reset_ro_err, -reset_ovf, reset_ovf_err}

 
 ifstream inPython;
 inPython.open(PythonFile);
 if(inPython.good()){ std::cout << "All fine" << std::endl;} else { std::cout << "You're fucked" << std::endl;}

 double rate, rate_err, eff, eff_err, operative, operative_err, token, token_err, readout, readout_err, reset, reset_err, activated, activated_err, drained, drained_err, buffered, buffered_err, valid, valid_err, color_ovf, color_ovf_err, ts_ovf, ts_ovf_err, retained, retained_err, reset_ro, reset_ro_err, reset_ovf, reset_ovf_err;
 TString dummy;

 nlines = 0;
 while(true)
   {

     inPython >> dummy >> rate >> rate_err >> eff >> eff_err >> operative >> operative_err >> token >> token_err >> readout >> readout_err >> reset >> reset_err >> activated >> activated_err >> drained >> drained_err >> buffered >> buffered_err >> valid >> valid_err >> color_ovf >> color_ovf_err >> ts_ovf >> ts_ovf_err >> retained >> retained_err >> reset_ro >> reset_ro_err >> reset_ovf >> reset_ovf_err;
     if(!inPython.good()) break;



     for(int ii = 0; ii < myCPPTree.GetEntries(); ++ii)
       {
	 myCPPTree.GetEntry(ii);
	 if( rate < pixelflu*1.05 && rate > pixelflu*0.95)              //if the rates are in withing 5% of each other we have a match
	   {
	     // now we want to fill the graphes
	     // pixelOverWrite
	     pixoverGraph->SetPoint(pixoverGraph->GetN(),100*(pixover/totalhits),activated);
	     //coldrain
	     coldrainGraph->SetPoint(coldrainGraph->GetN(),100*(coldrain/totalhits),color_ovf);
	     //ts
	     tsGraph->SetPoint(tsGraph->GetN(),100*(ts/totalhits),ts_ovf);
	     //db
	     dbGraph->SetPoint(dbGraph->GetN(),100*(db/totalhits),reset_ovf);
	     //colblock
	     colblockGraph->SetPoint(colblockGraph->GetN(),100*(colblock/totalhits),operative);
	     //reset
	     resetGraph->SetPoint(resetGraph->GetN(),100*(reset/totalhits),reset_ro);

	     //total
	     totalIneffGraph->SetPoint(totalIneffGraph->GetN(),100*(totalineffhits/totalhits),100 - eff);
	   }

       }

   }



 std::cout << pixoverGraph->GetN() << endl;


 TCanvas * c1 = new TCanvas("c1","Comparison Plots",2000,1000);
 c1->Divide(4,2);

 int markerstyle = 20;
 int markercolor = 1;
 double markersize = 2.5;

 TGraph * perfect = new TGraph();
 perfect->SetPoint(perfect->GetN(), 0,0);
 perfect->SetPoint(perfect->GetN(), 100,100);

 perfect->SetLineColor(2);

 TMultiGraph * mg[7];

 for(int i = 0; i < 7;++i)
   {
     mg[i] = new TMultiGraph();
     mg[i]->Add(perfect);
   }



 c1->cd(1);
 pixoverGraph->SetMarkerStyle(20);
 pixoverGraph->SetMarkerColor(1);
 pixoverGraph->SetMarkerSize(1);
 mg[0]->Add(pixoverGraph);
 mg[0]->SetTitle("Pixel overwrite;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[0]->Draw("AP");
 mg[0]->GetXaxis()->SetLabelSize(0.05);
 mg[0]->GetYaxis()->SetLabelSize(0.05);
 mg[0]->GetXaxis()->SetTitleSize(0.05);
 mg[0]->GetYaxis()->SetTitleSize(0.05);
 mg[0]->GetYaxis()->SetTitleOffset(1.0);
 mg[0]->GetXaxis()->SetLimits(0,TMath::MaxElement(pixoverGraph->GetN(),pixoverGraph->GetX())*1.1);
 mg[0]->SetMinimum(0);
 mg[0]->SetMaximum(TMath::MaxElement(pixoverGraph->GetN(),pixoverGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[0]->Draw("AP");

 c1->cd(2);
 coldrainGraph->SetTitle("Column drain busy;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 coldrainGraph->SetMarkerStyle(20);
 coldrainGraph->SetMarkerColor(1);
 coldrainGraph->SetMarkerSize(1);
 mg[1]->Add(coldrainGraph);
 mg[1]->SetTitle("Column drain busy;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[1]->Draw("AP");
 mg[1]->GetXaxis()->SetLabelSize(0.05);
 mg[1]->GetYaxis()->SetLabelSize(0.05);
 mg[1]->GetXaxis()->SetTitleSize(0.05);
 mg[1]->GetYaxis()->SetTitleSize(0.05);
 mg[1]->GetYaxis()->SetTitleOffset(1.0);
 mg[1]->GetXaxis()->SetLimits(0,TMath::MaxElement(coldrainGraph->GetN(),coldrainGraph->GetX())*1.1);
 mg[1]->SetMinimum(0);
 mg[1]->SetMaximum(TMath::MaxElement(coldrainGraph->GetN(),coldrainGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[1]->Draw("AP");

 c1->cd(3);
 tsGraph->SetTitle("Time stamp buffer overflow;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 tsGraph->SetMarkerStyle(20);
 tsGraph->SetMarkerColor(1);
 tsGraph->SetMarkerSize(1);
 mg[2]->Add(tsGraph);
 mg[2]->SetTitle("Time stamp buffer overflow;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[2]->Draw("AP");
 mg[2]->GetXaxis()->SetLabelSize(0.05);
 mg[2]->GetYaxis()->SetLabelSize(0.05);
 mg[2]->GetXaxis()->SetTitleSize(0.05);
 mg[2]->GetYaxis()->SetTitleSize(0.05);
 mg[2]->GetYaxis()->SetTitleOffset(1.0);
 mg[2]->GetXaxis()->SetLimits(0,TMath::MaxElement(tsGraph->GetN(),tsGraph->GetX())*1.1);
 mg[2]->SetMinimum(0);
 mg[2]->SetMaximum(TMath::MaxElement(tsGraph->GetN(),tsGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[2]->Draw("AP");

 c1->cd(4);
 dbGraph->SetTitle("Data buffer overflow;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 dbGraph->SetMarkerStyle(20);
 dbGraph->SetMarkerColor(1);
 dbGraph->SetMarkerSize(1);
 mg[3]->Add(dbGraph);
 mg[3]->SetTitle("Data buffer overflow;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[3]->Draw("AP");
 mg[3]->GetXaxis()->SetLabelSize(0.05);
 mg[3]->GetYaxis()->SetLabelSize(0.05);
 mg[3]->GetXaxis()->SetTitleSize(0.05);
 mg[3]->GetYaxis()->SetTitleSize(0.05);
 mg[3]->GetYaxis()->SetTitleOffset(1.0);
 mg[3]->GetXaxis()->SetLimits(0,TMath::MaxElement(dbGraph->GetN(),dbGraph->GetX())*1.1);
 mg[3]->SetMinimum(0);
 mg[3]->SetMaximum(TMath::MaxElement(dbGraph->GetN(),dbGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[3]->Draw("AP");

 c1->cd(5);
 colblockGraph->SetTitle("Column blocked for readout;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 colblockGraph->SetMarkerStyle(20);
 colblockGraph->SetMarkerColor(1);
 colblockGraph->SetMarkerSize(1);
 mg[4]->Add(colblockGraph);
 mg[4]->SetTitle("Column blocked for readout;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[4]->Draw("AP");
 mg[4]->GetXaxis()->SetLabelSize(0.05);
 mg[4]->GetYaxis()->SetLabelSize(0.05);
 mg[4]->GetXaxis()->SetTitleSize(0.05);
 mg[4]->GetYaxis()->SetTitleSize(0.05);
 mg[4]->GetYaxis()->SetTitleOffset(1.0);
 mg[4]->GetXaxis()->SetLimits(0,TMath::MaxElement(colblockGraph->GetN(),colblockGraph->GetX())*1.1);
 mg[4]->SetMinimum(0);
 mg[4]->SetMaximum(TMath::MaxElement(colblockGraph->GetN(),colblockGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[4]->Draw("AP");

 c1->cd(6);
 resetGraph->SetTitle("Readout reset;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 resetGraph->SetMarkerStyle(20);
 resetGraph->SetMarkerColor(1);
 resetGraph->SetMarkerSize(1);
 mg[5]->Add(resetGraph);
 mg[5]->SetTitle("Readout reset;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[5]->Draw("AP");
 mg[5]->GetXaxis()->SetLabelSize(0.05);
 mg[5]->GetYaxis()->SetLabelSize(0.05);
 mg[5]->GetXaxis()->SetTitleSize(0.05);
 mg[5]->GetYaxis()->SetTitleSize(0.05);
 mg[5]->GetYaxis()->SetTitleOffset(1.0);
 mg[5]->GetXaxis()->SetLimits(0,TMath::MaxElement(resetGraph->GetN(),resetGraph->GetX())*1.1);
 mg[5]->SetMinimum(0);
 mg[5]->SetMaximum(TMath::MaxElement(resetGraph->GetN(),resetGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 mg[5]->Draw("AP");

 c1->cd(7);
 totalIneffGraph->SetTitle("Total ineffciciency;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 totalIneffGraph->SetMarkerStyle(20);
 totalIneffGraph->SetMarkerColor(1);
 totalIneffGraph->SetMarkerSize(1);
 mg[6]->Add(totalIneffGraph);
 mg[6]->SetTitle("Total inefficiency;C++ simulation inefficiency (%);Python simulation inefficiecny (%)");
 mg[6]->Draw("AP");
 mg[6]->GetXaxis()->SetLabelSize(0.05);
 mg[6]->GetYaxis()->SetLabelSize(0.05);
 mg[6]->GetXaxis()->SetTitleSize(0.05);
 mg[6]->GetYaxis()->SetTitleSize(0.05);
 mg[6]->GetYaxis()->SetTitleOffset(1.0);
 mg[6]->GetXaxis()->SetLimits(0,TMath::MaxElement(totalIneffGraph->GetN(),totalIneffGraph->GetX())*1.1);
 mg[6]->SetMinimum(0);
 mg[6]->SetMaximum(TMath::MaxElement(totalIneffGraph->GetN(),totalIneffGraph->GetY())*1.1);
 perfect->Fit("pol1","FQ");
 totalIneffGraph->Fit("pol1","FQ");
 totalIneffGraph->GetFunction("pol1")->SetLineColor(3);
 TF1 * fit = new TF1;

 fit = totalIneffGraph->GetFunction("pol1");

 std::cout << fit->GetNpar() << std::endl;

 for (int i=0;i<fit->GetNpar();i++) {
   Float_t value = fit->GetParameter(i);
   printf("%d %f",i,value);
 }

 c1->cd(8);
 TPaveText * pave = new TPaveText(0.1,0.1,0.9,0.9);
 char txt[1000];
 sprintf(txt,"Fit Results");
 pave->AddText(txt);
 sprintf(txt,"Offset:\t %f",fit->GetParameter(0));
 pave->AddText(txt);
 sprintf(txt," Slope:\t %f",fit->GetParameter(1));
 pave->AddText(txt);

 pave->Draw();

 
 char outfilename[256];

 sprintf(outfilename,"Code_Comparison_WBC%d.pdf",WBC);
 c1->SaveAs(outfilename);
 

}


