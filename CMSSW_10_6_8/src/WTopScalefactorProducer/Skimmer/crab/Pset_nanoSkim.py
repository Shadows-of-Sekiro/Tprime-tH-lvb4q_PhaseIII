
import FWCore.ParameterSet.Config as cms
process = cms.Process('NANO')
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),

)
process.source.fileNames = [
       '/store/user/asparker/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/TTToSemiLeptonicTuneCP5PSweights13TeV-powheg-pythia8/180130_175206/0000/80XNanoV0-TTbar_SemiLep_1.root'

]
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.options = cms.untracked.PSet()

process.output = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('94XNanoV0-TTbar_SemiLep.root'), fakeNameForCrab =cms.untracked.bool(True))
process.out = cms.EndPath(process.output)
