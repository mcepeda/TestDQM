#include "drawGridRct.C"
#include "tdrstyle.C"
TFile * file0 ;

void fastplotterGCTEMU(TString fileName="RCTOfflineDQMMCEMU.root"){

//# gROOT->LoadMacro("Â$CMRCTOfflinRankests/RCTOfflineDQM/testMC/tdrstyle.C");
 setTDRStyle();

   gStyle->SetPalette(55);
  

 file0 = new TFile(fileName,"READONLY");

 doHisto("IsoEmOccEtaPhi","IsoEmOccEtaPhi");;
 doHisto("IsoEmRankEtaPhi","IsoEmOccRankTaaPhi");;
 doHisto("NonIsoEmRankEtaPhi","NonIsoEmOccRankEtaPhi");;
 doHisto("NonIsoEmOccEtaPhi","NonIsoEmOccEtaPhi");;
 doHisto("IsoEmRank","IsoEmRank",false);
 doHisto("NonIsoEmRank","NonIsoEmRank",false);

 doHisto("CenJetsEtEtaPhi","CenJetsEtEtaPhi");
 doHisto("CenJetsOccEtaPhi","CenJetsOccEtaPhi");
 doHisto("CenJetsRank","CenJetsRank",false);

 doHisto("AllJetsEtEtaPhi","AllJetsEtEtaPhi");
 doHisto("AllJetsOccEtaPhi","AllJetsOccEtaPhi");
 doHisto("AllJetsRank","AllJetsRank",false);

 doHisto("ForJetsEtEtaPhi","ForJetsEtEtaPhi");
 doHisto("ForJetsOccEtaPhi","ForJetsOccEtaPhi");
 doHisto("ForJetsRank","ForJetsRank",false);

 doHisto("AllEmOccRankBx","AllEmOccRankBx");;

 doHisto("EtHad","EtHad",false);
 doHisto("EtMiss","EtMiss",false);
 doHisto("EtTotal","EtTotal",false);
 doHisto("HtMiss","HtMiss",false);

 doHisto("TauJetsEtEtaPhi","TauJetsEtEtaPhi");
 doHisto("TauJetsOccEtaPhi","TauJetsOccEtaPhi");
 doHisto("TauJetsRank","TauJetsRank",false);

}

//doPUM option used in pumplotter.cc
void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doPUM=false, bool doZoom=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TGCT/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#Eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);

          drawGridRct();

 }
 else if(doPUM){
          histo->Draw("colz,text");
          histo->SetXTitle("PUM bin");
          histo->SetYTitle("Rank");
          histo->SetTitle(label);
 }
 else if(doZoom){
          histo->Draw("hist");
          name=name+"_zoom";
          histo->SetName(name);
          histo->SetXTitle("Rank");
          histo->SetTitle(label);
          histo->SetYTitle("Events");
          histo->SetLineWidth(2);
          histo->GetXaxis()->SetRangeUser(0,50);
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle("RANK");  
          histo->SetYTitle("Events");
          histo->SetLineWidth(2);
          histo->SetTitle(label);
 }


 C1->SaveAs(name+"_EMU.png");
if (doPUM) doProfile(name,"Avg "+label);;
}
//
//
