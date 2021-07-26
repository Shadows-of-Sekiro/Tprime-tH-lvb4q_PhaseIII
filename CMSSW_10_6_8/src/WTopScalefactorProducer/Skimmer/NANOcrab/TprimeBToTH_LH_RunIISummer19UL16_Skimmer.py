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

"keep_and_drop_v1.txt"
#"keep_and_drop.txt"

isMCTrueFalse = True
Year = 2017

infile = [
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL16NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v13-v1/240000/8F19747F-C654-DD40-967B-393CD2EEFEE6.root"
#       "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL17NanoAODv2/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/20000/B7413BD3-FA9A-0745-BAEC-A77B97EE7D3E.root"
#       "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL17NanoAODv2/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/250000/87C2EB87-372C-8A47-991A-D7B645077364.root"
     "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL17NanoAODv2/TprimeBToTH_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mc2017_realistic_v8-v1/250000/3CCFF426-A61E-8C49-A2E0-87290F1D08BE.root"
  ]

slimJetCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "AK4PFchs")
fatJetCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "AK8PFPuppi")
metCorrector = createJMECorrector(isMC=isMCTrueFalse, dataYear=Year, jesUncert="All", redojec=True, jetType = "MET")


print "Processing MC..."
channel = "elmu"
#p=PostProcessor(".",infile, None,"keep_and_drop.txt",modules=[Skimmer(channel), slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=False,maxEntries=500,fwkJobReport=False,haddFileName="na1no.root")

#p=PostProcessor(".",infile, None,"keep_and_drop_v1.txt",modules=[Skimmer(channel), slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,maxEntries=2000,fwkJobReport=False,haddFileName="na1no.root")

p=PostProcessor(".",inputFiles(), None,"keep_and_drop_v1.txt",modules=[Skimmer(channel),slimJetCorrector(),fatJetCorrector(),metCorrector()],provenance=True,fwkJobReport=True,jsonInput=runsAndLumis())

#p=PostProcessor(".",inputFiles(), None,"keep_and_drop.txt",modules=[Skimmer(channel)],provenance=True,fwkJobReport=True,jsonInput=runsAndLumis())
#p=PostProcessor(outputDir, infile, None, None,modules=[Skimmer(channel)],provenance=False,maxEntries=20,fwkJobReport=False)

p.run()
print "DONE"

#maxEntries=25000
