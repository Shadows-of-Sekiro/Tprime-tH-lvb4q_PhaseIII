
import FWCore.ParameterSet.Config as cms
process = cms.Process('NANO')
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),

)
process.source.fileNames = [
'/store/user/asparker/NanoAODJMARTools-skims/nanoskim-JetsandLepton-94XMC-TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8-trees.root'

]
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.options = cms.untracked.PSet()

process.output = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('WtaggingSkim.root'), fakeNameForCrab =cms.untracked.bool(True))
process.out = cms.EndPath(process.output)
