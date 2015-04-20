import FWCore.ParameterSet.Config as cms

process = cms.Process("TEST")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')

# Select the Message Logger output you would like to see:
process.load('FWCore.MessageService.MessageLogger_cfi')

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS162_V2::All')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#"file:/afs/cern.ch/user/g/ginnocen/public/MP7testsP5/l1tCalo_2015_EDM.root"

"file:/afs/cern.ch/work/g/ginnocen/public/skim_10_1_wd2.root"

#"/store/mc/Phys14DR/GluGluToHToTauTau_M-125_13TeV-powheg-pythia6/GEN-SIM-RAW/PU40bx25_PHYS14_25_V1-v2/00000/B6422716-7677-E411-B0D2-7845C4FC3665.root"

#"/store/mc/Phys14DR/GluGluToHToZZTo4L_M-125_13TeV-powheg-pythia6/GEN-SIM-RAW/PU20bx25_tsg_PHYS14_25_V1-v1/00000/687FC22A-8A6F-E411-90F2-3417EBE2F0DF.root"
#  "file:/hdfs/store/user/laura/SinglePi0Pt/SinglePi0Pt40/SinglePi0Pt40-0000.root" 
#    "/store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/00000/00309507-AB75-E311-AB10-0025905A60B2.root"
  #  "/store/mc/Fall13dr/TT_Tune4C_13TeV-pythia8-tauola/GEN-SIM-RAW/tsg_PU40bx25_POSTLS162_V2-v1/00000/007939EF-8075-E311-B675-0025905938AA.root",
 
)
)


process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

from SimCalorimetry.HcalTrigPrimProducers.hcaltpdigi_cff import *
process.simHcalTriggerPrimitiveDigis.inputLabel = cms.VInputTag(
    cms.InputTag('hcalDigis'),
    cms.InputTag('hcalDigis')
)

process.HcalTPGCoderULUT.LUTGenerationMode = cms.bool(True)

process.L1TRerunHCALTP_FromRAW = cms.Sequence(
    process.hcalDigis
    * process.simHcalTriggerPrimitiveDigis
)



# RCT
# HCAL input would be from hcalDigis if hack not needed
process.load("L1Trigger.Configuration.SimL1Emulator_cff")
process.simRctDigis.ecalDigis = cms.VInputTag( cms.InputTag( 'ecalDigis:EcalTriggerPrimitives' ) )
process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'simHcalTriggerPrimitiveDigis' ) )


process.output = cms.OutputModule(
    "PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = cms.untracked.vstring('drop *','keep *_*_*_TEST'),
#    outputCommands = cms.untracked.vstring('keep *'),
#    fileName = cms.untracked.string('rct64TTBarEventsFilter.root'),
    fileName = cms.untracked.string('rct64ZEE100EventsEventsFilter.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('')
    )
                                           )

process.runpath = cms.Path(process.L1TRerunHCALTP_FromRAW*process.ecalDigis*process.simRctDigis)#
process.outpath = cms.EndPath(process.output)


