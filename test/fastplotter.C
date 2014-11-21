TFile * file0 ;

void fastplotter(TString fileName="CTP7DQM.root"){

 gROOT->LoadMacro("tdrstyle.C");
 setTDRStyle();
  

 file0 = new TFile(fileName,"READONLY");

 doHisto("RctBitHfPlusTauEtaPhi","Hf Plus Tau Bit");;
 doHisto("RctEmIsoEmEtEtaPhi","EmIso Occupancy (ET in z axis)");;
 doHisto("RctEmIsoEmOccEtaPhi","EmIso Occupancy");;
 doHisto("RctEmNonIsoEmEtEtaPhi","EmNonIso Occupancy (ET in z axis)");;
 doHisto("RctEmNonIsoEmOccEtaPhi","EmNonIso Occupancy");;
 doHisto("RctRegionsEtEtaPhi","Regions Occupancy (ET in z axis)");
 doHisto("RctRegionsOccEtaPhi","Regions Occupancy");;
 doHisto("RctEmIsoEmRank","EmIso Rank",false);;
 doHisto("RctEmNonIsoEmRank","EmNonIso Rank",false);;
 doHisto("RctRegionRank","Regions Rank",false);;


}

void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="Test", bool do2D=true){
 TCanvas* C1= new TCanvas("T"+name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
          histo->SetTitle(label);
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle("RANK");  
          histo->SetYTitle("Events");
          histo->SetLineWidth(2);
          histo->SetTitle(label);
 }
 C1->SaveAs(name+".png");
}

