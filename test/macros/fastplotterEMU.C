#include "drawGridRct.C"
#include "tdrstyle.C"
TFile * file0 ;

void fastplotterGCTEmu(TString fileName="RCTOfflineDQMMC.root"){

//# gROOT->LoadMacro("Â$CMRCTOfflinRankests/RCTOfflineDQM/testMC/tdrstyle.C");
 setTDRStyle();

   gStyle->SetPalette(55);
  

 file0 = new TFile(fileName,"READONLY");

 doHisto("AllEmOccRankBx","AllEmOccRankBx");;
 doHisto("IsoEmOccEtaPhi","IsoEmOccEtaPhi");;
 doHisto("IsoEmRankEtaPhi","IsoEmOccRankTaaPhi");;
 doHisto("NonIsoEmRankEtaPhi","NonIsoEmOccRankEtaPhi");;
 doHisto("NonIsoEmOccEtaPhi","NonIsoEmOccEtaPhi");;
 doHisto("IsoEmRank","IsoEmRank",false);
 doHisto("NonIsoEmRank","NonIsoEmRank",false);
 
 doHisto("CenJetsEtEtaPhi","CenJetsEtEtaPhi");
 doHisto("CenJetsOccEtaPhi","CenJetsOccEtaPhi");
 doHisto("CenJetsRank","CenJetsRank",false);



/*
 KEY: TH2F  AllEmOccRankBx;1  ALL EM E_{T} PER BX
 KEY: TH2F  AllJetsEtEtaPhi;1 CENTRAL AND FORWARD JET E_{T}
 KEY: TH2F  AllJetsOccEtaPhi;1      CENTRAL AND FORWARD JET OCCUPANCY
 KEY: TH2F  AllJetsOccRankBx;1      ALL JETS E_{T} PER BX
 KEY: TH2F  CenJetsEtEtaPhi;1 CENTRAL JET E_{T}
 KEY: TH2F  CenJetsOccEtaPhi;1      CENTRAL JET OCCUPANCY
 KEY: TH1F  CenJetsRank;1     CENTRAL JET E_{T}
 KEY: TH1F  EtHad;1     H_{T}
 KEY: TH2F  EtHadOccBx;1      H_{T} PER BX
 KEY: TH1F  EtHadOf;1   H_{T} OVERFLOW
 KEY: TH1F  EtMiss;1    MET
 KEY: TH2F  EtMissHtMissCorr;1      MET MHT CORRELATION
 KEY: TH2F  EtMissHtMissPhiCorr;1   MET MHT  #phi  CORRELATION
 KEY: TH2F  EtMissOccBx;1     MET PER BX
 KEY: TH1F  EtMissOf;1  MET OVERFLOW
 KEY: TH1F  EtMissPhi;1 MET  #phi
 KEY: TH1F  EtTotal;1   SUM E_{T}
 KEY: TH2F  EtTotalEtHadCorr;1      Sum E_{T} H_{T} CORRELATION
 KEY: TH2F  EtTotalOccBx;1    SUM E_{T} PER BX
 KEY: TH1F  EtTotalOf;1 SUM E_{T} OVERFLOW
 KEY: TH2F  ForJetsEtEtaPhi;1 FORWARD JET E_{T}
 KEY: TH2F  ForJetsOccEtaPhi;1      FORWARD JET OCCUPANCY
 KEY: TH1F  ForJetsRank;1     FORWARD JET E_{T}
 KEY: TH1F  HtMiss;1    MHT
 KEY: TH2F  HtMissOccBx;1     MHT PER BX
 KEY: TH1F  HtMissOf;1  MHT OVERFLOW
 KEY: TH1F  HtMissPhi;1 MHT  #phi
 KEY: TH2F  TauJetsEtEtaPhi;1 TAU JET E_{T}
 KEY: TH2F  TauJetsOccEtaPhi;1      TAU JET OCCUPANCY
 KEY: TH1F  TauJetsRank;1     TAU JET E_{T}
*/

}

//doPUM option used in pumplotter.cc
void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doPUM=false, bool doZoom=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TGCTEmu/"+name);
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


 C1->SaveAs(name+".png");
if (doPUM) doProfile(name,"Avg "+label);;
}
//Duplicate function-- moved pum plots to pumplotter.cc
void doProfile(TString name="RctRegionsPumEta10",TString label="Test"){
 TCanvas* C1= new TCanvas("T"+name);
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/g/"+name);
 histo->Draw("colz,text");
 histo->SetXTitle("PUM bin");
 histo->SetYTitle("Average Rank");
 histo->SetTitle(label);
 TProfile *prof=histo->ProfileX();
 prof->Draw();
 C1->SaveAs(name+"Avg"+".png");
}


void doHistoEvt(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", TString yaxis="YAxis",bool doEvt, int zoom=-1){
 TCanvas* C1= new TCanvas("T"+name);
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/g/"+name);
 histo->Draw("colz,text");
if (doEvt) histo->SetXTitle("EVENT");
else histo->SetXTitle("GCTEmuEta");
 histo->SetYTitle(yaxis);
 histo->SetTitle(label);
          if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(0,zoom);  name=name+"_zoom";}
 TProfile *prof=histo->ProfileX();
 prof ->Draw();
 C1->SaveAs(name+".png");
 }
//
//
