import FWCore.ParameterSet.Config as cms

process = cms.Process('L1TEMULATION')

process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")



process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')

# Select the Message Logger output you would like to see:
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(64)
    )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
"file:/data/L1Ts1calo/rctReferences/htautau_GluGluToHToTauTau_M-125_13TeV-powheg-pythia6__PU40bx25_PHYS14_25_V1-v2__00000__B6422716-7677-E411-B0D2-7845C4FC3665.root"
)
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS161_V12::All')

process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)
process.simRctUpgradeFormatDigis.emTag = cms.InputTag("simRctDigis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("simRctDigis")

process.p1 = cms.Path(
    process.L1TCaloStage1_PPFromRaw
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

process.EmulatorResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                         InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("simRctDigis")
)
process.p2 = cms.Path(process.EmulatorResults )

process.dqmSaver.workflow = cms.untracked.string('/L1TMonitor/Calo/RCTOffline')

process.l1trct = cms.EDAnalyzer("L1TRCTOffline",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./RCTOfflineDQMFROMMC.root'),
    rctSource = cms.InputTag("simRctDigis"),
    verbose = cms.untracked.bool(False),
    filterTriggerType  = cms.int32(-1)
)

process.l1tGct = cms.EDAnalyzer("L1TGCT",
      gctCentralJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","cenJets"),
      gctForwardJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","forJets"),
      gctTauJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","tauJets"),
      gctEnergySumsSource = cms.InputTag("simCaloStage1LegacyFormatDigis"),
      gctIsoEmSource = cms.InputTag("simCaloStage1LegacyFormatDigis","isoEm"),
      gctNonIsoEmSource = cms.InputTag("simCaloStage1LegacyFormatDigis","nonIsoEm"),
      verbose = cms.untracked.bool(False),
      DQMStore = cms.untracked.bool(True),
      disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./RCTOfflineDQMFROMMC.root'),
      filterTriggerType = cms.int32(-1)
)

#This creates DQM-compatible plots
process.p3 = cms.Path(process.l1trct+process.l1tGct+process.dqmSaver)

process.schedule = cms.Schedule(
    process.p1, process.p3, process.p2
    )


process.RCTConfigProducers.eGammaLSB = 1
process.RCTConfigProducers.jetMETLSB = 1
process.l1CaloScales.L1CaloEmEtScaleLSB = 1
process.l1CaloScales.L1CaloRegionEtScaleLSB = 1
process.RCTConfigProducers.eGammaECalScaleFactors = [1., 1., 1., 1., 1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1. ]
process.RCTConfigProducers.jetMETECalScaleFactors = [1., 1., 1., 1., 1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1.,1., 1., 1., 1. ]

process.RCTConfigProducers.eActivityCut= 0.0
process.RCTConfigProducers.hActivityCut= 0.0
process.RCTConfigProducers.eMaxForFGCut= 1024.0
process.RCTConfigProducers.hOeCut= 1024.0




