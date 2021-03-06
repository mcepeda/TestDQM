#include "drawGridRct.C"
#include "tdrstyle.C"
TFile * file0 ;

void fastplotterMC(TString fileName="RCTOfflineDQMMC.root"){

//# gROOT->LoadMacro("�$CMRCTOfflinRankests/RCTOfflineDQM/testMC/tdrstyle.C");
 setTDRStyle();

   gStyle->SetPalette(55);
  

 file0 = new TFile(fileName,"READONLY");

 doHisto("RctBitHfPlusTauEtaPhi","Hf Plus Tau Bit");;
 doHisto("RctEmIsoEmEtEtaPhi","EmIso Occupancy (Rank in z axis)");;
 doHisto("RctEmIsoEmOccEtaPhi","EmIso Occupancy");;
 doHisto("RctEmNonIsoEmEtEtaPhi","EmNonIso Occupancy (Rank in z axis)");;
 doHisto("RctEmNonIsoEmOccEtaPhi","EmNonIso Occupancy");;
 doHisto("RctRegionsEtEtaPhi","Regions Occupancy (Rank in z axis)");
 doHisto("RctRegionsOccEtaPhi","Regions Occupancy");;
 doHisto("RctEmIsoEmRank","EmIso Rank",false);;
 doHisto("RctEmNonIsoEmRank","EmNonIso Rank",false);;
 doHisto("RctRegionRank","Regions Rank",false);;
 doHisto("RctRegionRank","Regions Rank Zoomed",false,false,true);;
 doHisto("RctBitMipEtaPhi","Mip Bit");
 doHisto("RctBitOverFlowEtaPhi", "Overflow bit");
 doHisto("RctBitQuietEtaPhi", "Quiet bit");
 doHisto("RctBitTauVetoEtaPhi", "TauVeto bit");
 doHistoEvt("RctRegionsMaxEtVsEvt","Max Region Rank Vs Event","Max region rank", true,161);;
 doHistoEvt("RctIsoEmMaxEtVsEvt","MAX IsoEm RANK vs EVT", "Max IsoEM rank",true,161);
 doHistoEvt("RctNonIsoEmMaxEtVsEvt","MAX NonIsoEm RANK vs EVT", "Max NonIsoEM rank",true,161);

// KEY: TH2F    RctIsoEmMaxEtVsEvt;1     MAX IsoEm RANK vs EVT
// // KEY: TH2F    RctNonIsoEmMaxEtVsEvt;1  MAX NonIsoEm RANK vs EVT
// // KEY: TH2F    RctRegionsMaxEtVsEvt;1   MAX REGION RANK vs EVT
//

}

//doPUM option used in pumplotter.cc
void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true, bool doPUM=false, bool doZoom=false){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TRCTOffline/"+name);
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
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/L1TRCTOffline/"+name);
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
 TH2F *histo=(TH2F*)file0->Get("DQMData/L1T/L1TRCTOffline/"+name);
 histo->Draw("colz,text");
if (doEvt) histo->SetXTitle("EVENT");
else histo->SetXTitle("gctEta");
 histo->SetYTitle(yaxis);
 histo->SetTitle(label);
          if(zoom!=-1) {histo->GetXaxis()->SetRangeUser(0,zoom);  name=name+"_zoom";}
 TProfile *prof=histo->ProfileX();
 prof ->Draw();
 C1->SaveAs(name+".png");
 }
//
//
