/*
 * \file L1TRCTOffline.cc
 *
 * \author P. Wittich
 *
 */

#include "RCTOfflineTests/RCTOfflineDQM/interface/L1TRCTOffline.h"
#include "DataFormats/Provenance/interface/EventAuxiliary.h"

//DQMStore
#include "DQMServices/Core/interface/DQMStore.h"




using namespace edm;

const unsigned int NUMREGIONS = 396;

const unsigned int PHIBINS = 18;
const float PHIMIN = -0.5;
const float PHIMAX = 17.5;

// Ranks 6, 10 and 12 bits
const unsigned int R6BINS = 64;
const float R6MIN = -0.5;
const float R6MAX = 63.5;
const unsigned int R10BINS = 1024;
const float R10MIN = -0.5;
const float R10MAX = 1023.5;

const unsigned int ETABINS = 22;
const float ETAMIN = -0.5;
const float ETAMAX = 21.5;

const unsigned int EVBINS = 400;
const float EVMIN = -0.5;
const float EVMAX = 399.5;



const unsigned int PUMBINS = 22;
const float PUMMIN = -0.5;
const float PUMMAX = 21.5;

L1TRCTOffline::L1TRCTOffline(const ParameterSet & ps) :
   rctSource_L1CRCollection_( consumes<L1CaloRegionCollection>(ps.getParameter< InputTag >("rctSource") )),
   rctSource_L1CEMCollection_( consumes<L1CaloEmCollection>(ps.getParameter< InputTag >("rctSource") )),
   filterTriggerType_ (ps.getParameter< int >("filterTriggerType"))
{

  // verbosity switch
  verbose_ = ps.getUntrackedParameter < bool > ("verbose", false);

  if (verbose_)
    std::cout << "L1TRCTOffline: constructor...." << std::endl;


  dbe = NULL;
  if (ps.getUntrackedParameter < bool > ("DQMStore", false)) {
    dbe = Service < DQMStore > ().operator->();
    dbe->setVerbose(0);
  }

  outputFile_ =
      ps.getUntrackedParameter < std::string > ("outputFile", "");
  if (outputFile_.size() != 0) {
    std::
	cout << "L1T Monitoring histograms will be saved to " <<
	outputFile_.c_str() << std::endl;
  }

  bool disable =
      ps.getUntrackedParameter < bool > ("disableROOToutput", false);
  if (disable) {
    outputFile_ = "";
  }


  if (dbe != NULL) {
    dbe->setCurrentFolder("L1T/L1TRCTOffline");
  }


}

L1TRCTOffline::~L1TRCTOffline()
{
}

void L1TRCTOffline::beginJob(void)
{
  nev_ = 0;
}

void L1TRCTOffline::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  //Only histograms booking

  // get hold of back-end interface
  DQMStore *dbe = 0;
  dbe = Service < DQMStore > ().operator->();

  if (dbe) {
    dbe->setCurrentFolder("L1T/L1TRCTOffline");

    triggerType_ =
      dbe->book1D("TriggerType", "TriggerType", 17, -0.5, 16.5);
    // global regions
    rctRegionsNonZeroVsEvt_ =
	dbe->book2D("RctRegionsNonZeroVsEvt", "REGION PUM vs EVT", EVBINS, EVMIN,
                    EVMAX, PUMBINS, PUMMIN, PUMMAX);
    rctRegionsAvgEtVsEvt_ = 
	dbe->book2D("RctRegionsAvgEtVsEvt", " AVERAGE REGION RANK vs EVT", EVBINS, EVMIN,
                    EVMAX, R10BINS, R10MIN, R10MAX);

    rctRegionsMaxEtVsEvt_ =
        dbe->book2D("RctRegionsMaxEtVsEvt", " MAX REGION RANK vs EVT", EVBINS, EVMIN,
                    EVMAX, R10BINS, R10MIN, R10MAX);

    rctRegionsAverageRegionEt_ =
	dbe->book1D("RctRegionsAverageRegionEt", "AVERAGE REGION RANK", R10BINS, R10MIN, R10MAX);

    rctRegionsAvgEtVsEta_ =
	dbe->book2D("RctRegionsAvgEtVsEta", " AVERAGE REGION RANK vs ETA", ETABINS, ETAMIN,
                    ETAMAX, R10BINS, R10MIN, R10MAX);

    // global regions
    rctRegionsNonZero_ =
	dbe->book1D("RctRegionsNonZero", "REGION PUM", PUMBINS, PUMMIN, PUMMAX);
    rctRegionsPumEta0_ =
	dbe->book2D("RctRegionsPumEta0", " PUM BIN", PUMBINS, PUMMIN,
		    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta1_ =
	dbe->book2D("RctRegionsPumEta1", " PUM BIN", PUMBINS, PUMMIN,
		    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta2_ =
        dbe->book2D("RctRegionsPumEta2", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta3_ =
        dbe->book2D("RctRegionsPumEta3", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta4_ =
        dbe->book2D("RctRegionsPumEta4", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta5_ =
        dbe->book2D("RctRegionsPumEta5", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta6_ =
        dbe->book2D("RctRegionsPumEta6", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta7_ =
        dbe->book2D("RctRegionsPumEta7", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta8_ =
        dbe->book2D("RctRegionsPumEta8", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta9_ =
        dbe->book2D("RctRegionsPumEta9", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta10_ =
	dbe->book2D("RctRegionsPumEta10", " PUM BIN", PUMBINS, PUMMIN,
		    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta11_ =
	dbe->book2D("RctRegionsPumEta11", " PUM BIN", PUMBINS, PUMMIN,
		    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta12_ =
        dbe->book2D("RctRegionsPumEta12", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta13_ =
        dbe->book2D("RctRegionsPumEta13", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta14_ =
        dbe->book2D("RctRegionsPumEta14", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta15_ =
        dbe->book2D("RctRegionsPumEta15", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta16_ =
        dbe->book2D("RctRegionsPumEta16", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta17_ =
        dbe->book2D("RctRegionsPumEta17", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta18_ =
        dbe->book2D("RctRegionsPumEta18", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta19_ =
        dbe->book2D("RctRegionsPumEta19", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta20_ =
        dbe->book2D("RctRegionsPumEta20", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);
    rctRegionsPumEta21_ =
        dbe->book2D("RctRegionsPumEta21", " PUM BIN", PUMBINS, PUMMIN,
                    PUMMAX, R10BINS, R10MIN, R10MAX);

    rctIsoEmEtEtaPhi_ =
	dbe->book2D("RctEmIsoEmEtEtaPhi", "ISO EM E_{T}", ETABINS, ETAMIN,
		    ETAMAX, PHIBINS, PHIMIN, PHIMAX);
    rctIsoEmOccEtaPhi_ =
	dbe->book2D("RctEmIsoEmOccEtaPhi", "ISO EM OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);
    rctNonIsoEmEtEtaPhi_ =
	dbe->book2D("RctEmNonIsoEmEtEtaPhi", "NON-ISO EM E_{T}", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);
    rctNonIsoEmOccEtaPhi_ =
	dbe->book2D("RctEmNonIsoEmOccEtaPhi", "NON-ISO EM OCCUPANCY",
		    ETABINS, ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    // global regions
    rctRegionsEtEtaPhi_ =
	dbe->book2D("RctRegionsEtEtaPhi", "REGION E_{T}", ETABINS, ETAMIN,
		    ETAMAX, PHIBINS, PHIMIN, PHIMAX);
    rctRegionsOccEtaPhi_ =
	dbe->book2D("RctRegionsOccEtaPhi", "REGION OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    rctOverFlowEtaPhi_ =
	dbe->book2D("RctBitOverFlowEtaPhi", "OVER FLOW OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    rctTauVetoEtaPhi_ =
	dbe->book2D("RctBitTauVetoEtaPhi", "TAU VETO OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    rctMipEtaPhi_ =
	dbe->book2D("RctBitMipEtaPhi", "MIP OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    rctQuietEtaPhi_ =
	dbe->book2D("RctBitQuietEtaPhi", "QUIET OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    rctHfPlusTauEtaPhi_ =
	dbe->book2D("RctBitHfPlusTauEtaPhi", "HF plus Tau OCCUPANCY", ETABINS,
		    ETAMIN, ETAMAX, PHIBINS, PHIMIN, PHIMAX);

    // local regions
/*
    const int nlocphibins = 2; 
    const float locphimin = -0.5;
    const float locphimax = 1.5;
    const int nlocetabins = 11;
    const float locetamin = -0.5;
    const float locetamax = 10.5;
    rctRegionsLocalEtEtaPhi_ =
	dbe->book2D("RctRegionsLocalEtEtaPhi", "REGION E_{T} (Local)", 
		    nlocetabins, locetamin, locetamax,
		    nlocphibins, locphimin, locphimax);
    rctRegionsLocalOccEtaPhi_ =
	dbe->book2D("RctRegionsLocalOccEtaPhi", "REGION OCCUPANCY (Local)", 
		    nlocetabins, locetamin, locetamax,
		    nlocphibins, locphimin, locphimax);
    rctTauVetoLocalEtaPhi_ =
	dbe->book2D("RctTauLocalVetoEtaPhi", "TAU VETO OCCUPANCY (Local)",
		    nlocetabins, locetamin, locetamax,
		    nlocphibins, locphimin, locphimax);
*/
    // rank histos
    rctRegionRank_ =
	dbe->book1D("RctRegionRank", "REGION RANK", R10BINS, R10MIN,
		    R10MAX);
    rctIsoEmRank_ =
	dbe->book1D("RctEmIsoEmRank", "ISO EM RANK", R6BINS, R6MIN, R6MAX);
    rctNonIsoEmRank_ =
	dbe->book1D("RctEmNonIsoEmRank", "NON-ISO EM RANK", R6BINS, R6MIN,
		    R6MAX);
    // hw coordinates
//    rctEmCardRegion_ = dbe->book1D("rctEmCardRegion", "Em Card * Region",
//				   256, -127.5, 127.5);

    // bx histos
    rctRegionBx_ = dbe->book1D("RctRegionBx", "Region BX", 256, -0.5, 4095.5);
    rctEmBx_ = dbe->book1D("RctEmBx", "EM BX", 256, -0.5, 4095.5);
 
  }
}

void L1TRCTOffline::endJob(void)
{
  if (verbose_)
    std::cout << "L1TRCTOffline: end job...." << std::endl;
  LogInfo("EndJob") << "analyzed " << nev_ << " events";

  if (outputFile_.size() != 0 && dbe)
    dbe->save(outputFile_);

  return;
}

void L1TRCTOffline::analyze(const Event & e, const EventSetup & c)
{
  nev_++;
  if (verbose_) {
    std::cout << "L1TRCTOffline: analyze...." << std::endl;
  }

  // filter according trigger type
  //  enum ExperimentType {
  //        Undefined          =  0,
  //        PhysicsTrigger     =  1,
  //        CalibrationTrigger =  2,
  //        RandomTrigger      =  3,
  //        Reserved           =  4,
  //        TracedEvent        =  5,
  //        TestTrigger        =  6,
  //        ErrorTrigger       = 15

  // fill a histogram with the trigger type, for normalization fill also last bin
  // ErrorTrigger + 1
  double triggerType = static_cast<double> (e.experimentType()) + 0.001;
  double triggerTypeLast = static_cast<double> (edm::EventAuxiliary::ExperimentType::ErrorTrigger)
                          + 0.001;
  triggerType_->Fill(triggerType);
  triggerType_->Fill(triggerTypeLast + 1);

  // filter only if trigger type is greater than 0, negative values disable filtering
  if (filterTriggerType_ >= 0) {

      // now filter, for real data only
      if (e.isRealData()) {
          if (!(e.experimentType() == filterTriggerType_)) {

              edm::LogInfo("L1TRCTOffline") << "\n Event of TriggerType "
                      << e.experimentType() << " rejected" << std::endl;
              return;

          }
      }

  }

  // Get the RCT digis
  edm::Handle < L1CaloEmCollection > em;
  edm::Handle < L1CaloRegionCollection > rgn;

  bool doEm = true;
  bool doHd = true;

  e.getByToken(rctSource_L1CRCollection_,rgn);
 
  if (!rgn.isValid()) {
    edm::LogInfo("DataNotFound") << "can't find L1CaloRegionCollection";
    doHd = false;
  }

  if ( doHd ) {
    // Fill the RCT histograms
    int nonzeroregions = 0;
    int totalregionet = 0;
    int maxregionet = 0;

    // Regions
    for (L1CaloRegionCollection::const_iterator ireg = rgn->begin();
	 ireg != rgn->end(); ireg++) {
      if(ireg->et()>0)
      {
      nonzeroregions++;
      totalregionet += ireg->et();
      if(ireg->et()>maxregionet) maxregionet=ireg->et();        

      rctRegionRank_->Fill(ireg->et());
      if(ireg->et()>5){
	rctRegionsOccEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi());
      }
      rctRegionsEtEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi(), ireg->et());
//      rctTauVetoEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi(),
//			      ireg->tauVeto());

      // now do local coordinate eta and phi
//      rctRegionsLocalOccEtaPhi_->Fill(ireg->rctEta(), ireg->rctPhi());
//      rctRegionsLocalEtEtaPhi_->Fill(ireg->rctEta(), ireg->rctPhi(), 
//				     ireg->et());
//      rctTauVetoLocalEtaPhi_->Fill(ireg->rctEta(), ireg->rctPhi(),
//				   ireg->tauVeto());
      rctRegionBx_->Fill(ireg->bx());
      }


    if(ireg->overFlow())  rctOverFlowEtaPhi_ ->Fill(ireg->gctEta(), ireg->gctPhi());
    if(ireg->tauVeto())   rctTauVetoEtaPhi_  ->Fill(ireg->gctEta(), ireg->gctPhi());
    if(ireg->mip())       rctMipEtaPhi_      ->Fill(ireg->gctEta(), ireg->gctPhi());
    if(ireg->quiet())     rctQuietEtaPhi_    ->Fill(ireg->gctEta(), ireg->gctPhi());
    if(ireg->fineGrain()) rctHfPlusTauEtaPhi_->Fill(ireg->gctEta(), ireg->gctPhi()); 
    
    }//end region loop
    //
    rctRegionsAverageRegionEt_->Fill(totalregionet/NUMREGIONS);
    rctRegionsAvgEtVsEvt_->Fill(nev_,totalregionet/NUMREGIONS);
    rctRegionsMaxEtVsEvt_->Fill(nev_,maxregionet);

    rctRegionsNonZero_->Fill(nonzeroregions/PUMBINS);
    rctRegionsNonZeroVsEvt_->Fill(nev_,nonzeroregions/PUMBINS);
    //second region loop necessary because pum found in prior loop  
    for (L1CaloRegionCollection::const_iterator ireg = rgn->begin();
         ireg != rgn->end(); ireg++) {
      if (ireg->gctEta()==0){
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta0_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==1) {
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta1_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==2){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta2_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==3){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta3_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==4){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta4_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==5){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta5_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==6){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta6_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==7){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta7_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==8){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta8_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==9){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta9_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==10){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta10_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==11){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta11_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==12){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta12_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==13){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta13_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==14){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta14_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==15){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta15_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==16){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta16_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==17){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta17_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==18){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta18_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==19){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta19_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==20){ 
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta20_->Fill(nonzeroregions/PUMBINS,ireg->et());}
      else if (ireg->gctEta()==21){
          rctRegionsAvgEtVsEta_->Fill(ireg->gctEta(),ireg->et());
          rctRegionsPumEta21_->Fill(nonzeroregions/PUMBINS,ireg->et());}
    }

  }//end doHd

  
  e.getByToken(rctSource_L1CEMCollection_,em);
  
  if (!em.isValid()) {
    edm::LogInfo("DataNotFound") << "can't find L1CaloEmCollection";
    doEm = false;
  }
  if ( ! doEm ) return;
  // Isolated and non-isolated EM
  for (L1CaloEmCollection::const_iterator iem = em->begin();
       iem != em->end(); iem++) {
    
 //   rctEmCardRegion_->Fill((iem->rctRegion()==0?1:-1)*(iem->rctCard()));

    if (iem->isolated()) {
      if(iem->rank()>0)
      {
      rctIsoEmRank_->Fill(iem->rank());
      rctIsoEmEtEtaPhi_->Fill(iem->regionId().ieta(),
			      iem->regionId().iphi(), iem->rank());
      if(iem->rank()>10){
	rctIsoEmOccEtaPhi_->Fill(iem->regionId().ieta(),
				 iem->regionId().iphi());
      }
      rctEmBx_->Fill(iem->bx());
      }
    }
    else {
      if(iem->rank()>0)
      { 
      rctNonIsoEmRank_->Fill(iem->rank());
      rctNonIsoEmEtEtaPhi_->Fill(iem->regionId().ieta(),
				 iem->regionId().iphi(), iem->rank());
      if(iem->rank()>10){
	rctNonIsoEmOccEtaPhi_->Fill(iem->regionId().ieta(),
				    iem->regionId().iphi());
      }
      rctEmBx_->Fill(iem->bx());
      }
    }

  }

}
