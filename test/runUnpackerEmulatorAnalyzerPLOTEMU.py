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
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS161_V12::All')

# raw data from MP card
process.load('EventFilter.L1TRawToDigi.stage1MP7BufferRaw_cfi')
# pack into arrays
latencies = [ 32, 0 ]
offsets   = [ 6,  60 ]

process.stage1Raw.nFramesPerEvent    = cms.untracked.int32(6)
process.stage1Raw.nFramesOffset    = cms.untracked.vuint32(offsets)
process.stage1Raw.nFramesLatency   = cms.untracked.vuint32(latencies)

#process.stage1Raw.rxFile = cms.untracked.string("/afs/cern.ch/user/g/ginnocen/public/MP7tests_data_1Jet75/rx_summary_nostrobe.txt")
#process.stage1Raw.txFile = cms.untracked.string("/afs/cern.ch/user/g/ginnocen/public/MP7tests_data_1Jet75/tx_summary_nostrobe.txt")
process.stage1Raw.rxFile = cms.untracked.string("rx_summary_final.txt")
process.stage1Raw.txFile = cms.untracked.string("tx_summary_final.txt")


# raw to digi
# I think this will unpack both the rct digis and the Layer 2 digis
process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
process.caloStage1Digis.InputLabel = cms.InputTag('stage1Raw')
process.caloStage1FinalDigis = cms.EDProducer(
    "L1TPhysicalEtAdder",
    InputCollection = cms.InputTag("caloStage1Digis"),
    InputRlxTauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
    InputIsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
    InputPreGtJetCollection = cms.InputTag("caloStage1Digis"),
    InputHFSumsCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
    InputHFCountsCollection = cms.InputTag("caloStage1Digis:HFBitCounts")
)

process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)
process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

#process.load('L1Trigger.L1TCalorimeter.caloStage1LegacyFormatDigis_cfi')
#process.caloStage1LegacyFormatDigis.InputCollection = cms.InputTag("simCaloStage1FinalDigis")
process.simCaloStage1LegacyFormatDigis = cms.EDProducer(
    "L1TCaloUpgradeToGCTConverter",
    InputCollection = cms.InputTag("simCaloStage1FinalDigis"),
    InputRlxTauCollection = cms.InputTag("simCaloStage1Digis:rlxTaus"),
    InputIsoTauCollection = cms.InputTag("simCaloStage1Digis:isoTaus"),
    InputHFSumsCollection = cms.InputTag("simCaloStage1Digis:HFRingSums"),
    InputHFCountsCollection = cms.InputTag("simCaloStage1Digis:HFBitCounts")
)




process.caloStage1LegacyFormatDigis = cms.EDProducer(
    "L1TCaloUpgradeToGCTConverter",
    InputCollection = cms.InputTag("caloStage1Digis"),
    InputRlxTauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
    InputIsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
    InputHFSumsCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
    InputHFCountsCollection = cms.InputTag("caloStage1Digis:HFBitCounts")
)

process.p1 = cms.Path(
    process.stage1Raw +
    process.caloStage1Digis +
    process.simRctUpgradeFormatDigis +
    process.simCaloStage1Digis +
    process.simCaloStage1FinalDigis+
   process.simCaloStage1LegacyFormatDigis+
      process.caloStage1LegacyFormatDigis
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
#    rctSource = cms.InputTag("simRctDigis"),
    rctSource = cms.InputTag("caloStage1Digis"),
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
    outputFile = cms.untracked.string('./RCTOfflineDQMMCEMU.root'),
      filterTriggerType = cms.int32(-1)
)

#This creates DQM-compatible plots
process.p3 = cms.Path(process.l1trct+process.l1tGct+process.dqmSaver)

process.schedule = cms.Schedule(
    process.p1, process.p3, process.p2
    )
