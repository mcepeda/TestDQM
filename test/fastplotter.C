TFile * file0 ;

void fastplotter(TString fileName="CTP7DQM.root",TString label="test"){

 gROOT->LoadMacro("plotting/tdrstyle.C");
 setTDRStyle();
  

 file0 = new TFile(fileName,"READONLY");

 doHisto("RctBitHfPlusTauEtaPhi",label);;
 doHisto("RctEmIsoEmEtEtaPhi",label);;
 doHisto("RctEmIsoEmOccEtaPhi",label);;
 doHisto("RctEmNonIsoEmEtEtaPhi",label);;
 doHisto("RctEmNonIsoEmOccEtaPhi",label);;
 doHisto("RctRegionsEtEtaPhi",label);;
 doHisto("RctRegionsOccEtaPhi",label);;
 doHisto("RctEmIsoEmRank",label,false);;
 doHisto("RctEmNonIsoEmRank",label,false);;
 doHisto("RctRegionRank",label,false);;


}

void doHisto(TString name="RctBitHfPlusTauEtaPhi", TString label="ttbar", bool do2D=true){
 TCanvas* C1= new TCanvas(name);
 TH1F *histo=(TH1F*)file0->Get("DQMData/L1T/L1TCTP7/"+name);
 if(do2D) {
          histo->Draw("colz,text");
          histo->SetXTitle("#eta");
          histo->SetYTitle("#phi");
 }
 else     {histo->Draw("hist"); 
           C1->SetLogy(true); 
          histo->SetXTitle("RANK");  
          histo->SetYTitle("Events");
 }
 C1->SaveAs(name+"_"+label+".png");
}

