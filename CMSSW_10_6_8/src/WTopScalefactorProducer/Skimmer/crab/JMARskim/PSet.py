import FWCore.ParameterSet.Config as cms
process = cms.Process('NANO')
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(),

)
process.source.fileNames = [
    #
    #  2017
    #
    # DY MC:
    '/store/user/srappocc/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/DYJetsToLLM-50TuneCP513TeV-madgraphMLM-pythia8RunIIFall17MiniAOD-RECOSIMstep94Xmc2017/180330_193745/0000/test94X_NANO_100.root'
    #'/store/user/rappocc/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/DYJetsToLLM-50TuneCP513TeV-madgraphMLM-pythia8RunIIFall17MiniAOD-RECOSIMstep94Xmc2017/180330_193745/0000/test94X_NANO_1.root',
    # SingleMuon Data:
    #'/store/user/rappocc/SingleMuon/SingleMuon_Run2017D-17Nov2017-v1/180330_195316/0000/test_data_94X_NANO_1.root'
    # SingleElectron Data:
    #'/store/user/rappocc/SingleElectron/SingleElectron_Run2017D-17Nov2017-v1/180330_195129/0000/test_data_94X_NANO_1.root'

    #  2016
    # NANOAOD + reclustering + PUPPI 
    #'/store/user/srappocc/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/DYJetsToLLM-50TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond1780X/180330_202448/0000/test80X_NANO_101.root'
    # DY MC:
    #'/store/user/rappocc/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/DYJetsToLLM-50TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond1780X/180330_202448/0000/test80X_NANO_1.root'
    # SingleMuon Data:
    #'/store/user/srappocc/SingleMuon/SingleMuon_Run2016G-07Aug17-v1/180329_205803/0000/test_data_80X_NANO_100.root'
    # SingleElectron Data:
]
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.options = cms.untracked.PSet()

process.output = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('nanoskim-trees.root'), fakeNameForCrab =cms.untracked.bool(True))
# 80XNanoV0-LepZandJet-nanoTrees.root
# 80XNanoV0-MC-ext2_DYJetsToLL_M-50_TuneCUETP8M1-responses.root
# NrecPUPPI-JetPlusStuff-nanoTrees.root
process.out = cms.EndPath(process.output)
# nanoskim-trees.root
