#!/Usr-/bin/env python
import os,sys

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import *

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis

#from Skimmer  import *

from WTopScalefactorProducer.Skimmer.Skimmer import Skimmer
#from PhysicsTools.NanoAODTools.postprocessing.modules.jme.jetmetHelperRun2 import *

from PhysicsTools.NanoAODTools.postprocessing.modules.jme.jetmetHelperRunArjun import *


#from WTopScalefactorProducer.Skimmer.NANOcrab.Skimmer import Skimmer
#from WTopScalefactorProducer.Skimmer.skimmer import Skimmer

"keep_and_drop_data_v2.txt"

isMCTrueFalse=False
Year = 2017
jsonFileName="Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt"
channel = "elmu"

# infile = [
# #      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL16NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v13-v1/240000/8F19747F-C654-DD40-967B-393CD2EEFEE6.root"
#       "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL17NanoAODv2/TprimeBToTH_M-1800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/40000/F00552B1-ACE6-4A4C-BDE3-DB481D8A85CD.root"
# #     "root://cms-xrd-global.cern.ch//store/mc/RunIISummer16NanoAODv7/TTJets_TuneCP5_PSweights_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/100000/46F70FB9-58C6-8C4B-8D0B-39E31788820C.root"
#   ]

testfile = "root://cms-xrd-global.cern.ch//store/data/Run2017E/SingleElectron/NANOAOD/UL2017_MiniAODv1_NanoAODv2-v1/50000/7B09E7ED-A6DA-6149-98FE-9F10C9C69122.root"
#testfile = "root://cms-xrd-global.cern.ch///store/data/Run2017F/SingleMuon/NANOAOD/UL2017_MiniAODv1_NanoAODv2-v2/270000/24FE53A3-6966-2E44-8EA9-9A6C63DD0849.root"

#if testfile.find("Run2016") != -1:
#  Year=2016
#  jsonFileName="Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt"
#if testfile.find("Run2017") != -1:
#  Year=2017
#  jsonFileName="Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt"
#if testfile.find("Run2018") != -1:
#  Year=2018
#  jsonFileName="Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt"

slimJetCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "AK4PFchs")
fatJetCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "AK8PFPuppi")
metCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "MET")


print "\n===> Running over ",Year," data...\n"
print "===> JSON File: ",jsonFileName


#p=PostProcessor(".",[testfile],None,"keep_and_drop_data.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,maxEntries=500,fwkJobReport=True,jsonInput=jsonFileName)

#p=PostProcessor(".",[testfile],None,"keep_and_drop_data.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,maxEntries=1000,fwkJobReport=True,jsonInput=runsAndLumis())

p=PostProcessor(".",inputFiles(),None,"keep_and_drop_data_v2.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,fwkJobReport=True,jsonInput=runsAndLumis())

#p=PostProcessor(".",inputFiles(), None,"keep_and_drop_data.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],fwkJobReport=True,jsonInput=jsonFileName)

#p=PostProcessor(".",inputFiles(), None,"keep_and_drop_data.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],fwkJobReport=True,jsonInput=runsAndLumis())

#p=PostProcessor(".",inputFiles(), None,"keep_and_drop_data.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,fwkJobReport=True,jsonInput=jsonFileName)
#=runsAndLumis()

p.run()
print "DONE"


