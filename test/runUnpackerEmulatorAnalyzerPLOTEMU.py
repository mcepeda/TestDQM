import FWCore.ParameterSet.Config as cms

process = cms.Process('L1TEMULATION2')

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
    input = cms.untracked.int32(-1)
    )

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
"file:Digis.root"
)
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS161_V12::All')

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

process.EmulatorResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                         InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)

process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)


process.p2 = cms.Path(process.EmulatorResults + process.UnpackerResults)

process.dqmSaver.workflow = cms.untracked.string('/L1TMonitor/Calo/RCTOffline')

process.l1trct = cms.EDAnalyzer("L1TRCTOffline",
    DQMStore = cms.untracked.bool(True),
    disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./RCTOfflineDQMMCEMU.root'),
    rctSource = cms.InputTag("simRctDigis"),
    verbose = cms.untracked.bool(False),
    filterTriggerType  = cms.int32(-1)
)

process.l1tGct = cms.EDAnalyzer("L1TGCT",
      gctCentralJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","cenJets"),
      gctForwardJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","forJets"),
      gctTauJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","tauJets"),
      gctIsoTauJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","isoTauJets"),
      gctEnergySumsSource = cms.InputTag("simCaloStage1LegacyFormatDigis"),
      gctIsoEmSource = cms.InputTag("simCaloStage1LegacyFormatDigis","isoEm"),
      gctNonIsoEmSource = cms.InputTag("simCaloStage1LegacyFormatDigis","nonIsoEm"),
      verbose = cms.untracked.bool(False),
      DQMStore = cms.untracked.bool(True),
      disableROOToutput = cms.untracked.bool(False),
    outputFile = cms.untracked.string('./RCTOfflineDQMMCEMU.root'),
      filterTriggerType = cms.int32(-1)
)

#This creates DQM-compatible plots
process.p3 = cms.Path(process.l1trct+process.l1tGct+process.dqmSaver)

process.schedule = cms.Schedule(
    process.p3, process.p2
    )
