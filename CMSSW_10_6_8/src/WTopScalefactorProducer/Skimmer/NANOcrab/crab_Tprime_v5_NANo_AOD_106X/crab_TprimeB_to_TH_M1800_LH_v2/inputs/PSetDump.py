import FWCore.ParameterSet.Config as cms

process = cms.Process("NANO")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/RunIIAutumn18NanoAODv5/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/120000/C435EF5E-BAAB-3945-9252-6049054D9572.root')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(11)
)

process.output = cms.OutputModule("PoolOutputModule",
    fakeNameForCrab = cms.untracked.bool(True),
    fileName = cms.untracked.string('tree.root')
)


process.out = cms.EndPath(process.output)


