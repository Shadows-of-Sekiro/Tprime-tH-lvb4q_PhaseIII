#!/usr/bin/env python
import os, sys
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor
from  TTbar_SemiLep_fullyMerged import *
#from PhysicsTools.NanoAODTools.WTopScalefactorProducer.Skimmer.TTbar_SemiLep import *
if len(sys.argv)>1:
     infileis = sys.argv[1]
else:
     infileis = [
                 "root://cmsxrootd.fnal.gov//store/user/asparker/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TTJetsTuneCUETP8M113TeV-madgraphMLM-pythia8/180126_175048/0000/80XNanoV0-TTbar_SemiLep_94.root",
                 "root://cmsxrootd.fnal.gov//store/user/asparker/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TTJetsTuneCUETP8M113TeV-madgraphMLM-pythia8/180126_175048/0000/80XNanoV0-TTbar_SemiLep_95.root",
                 "root://cmsxrootd.fnal.gov//store/user/asparker/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TTJetsTuneCUETP8M113TeV-madgraphMLM-pythia8/180126_175048/0000/80XNanoV0-TTbar_SemiLep_96.root",
                 "root://cmsxrootd.fnal.gov//store/user/asparker/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TTJetsTuneCUETP8M113TeV-madgraphMLM-pythia8/180126_175048/0000/80XNanoV0-TTbar_SemiLep_97.root",


     ]
if len(sys.argv)>2:
    outputDir = sys.argv[2]
else:
    outputDir = "TTJetsTuneCUETP8M113TeV-madgraphMLM-pythia8-SkimmedSkim"	
if len(sys.argv)>3:
    name = sys.argv[3]
else:
    name = "tree"
p=PostProcessor(".", infileis  ,"FatJet_msoftdrop>130&&FatJet_pt>350&&MET_sumEt>40&& ( (nElectron > 0 && HLT_Ele115_CaloIdVT_GsfTrkIdT) || (nMuon > 0 && HLT_Mu50))" ,modules=[TTbar_SemiLep_fullyMerged()],provenance=True ,histFileName= 'fullyMerged_hists.root', histDirName='ttbar_semilep'  , haddFileName=  'fullyMerged_hadded.root' , postfix="_fullyMerged" )
p.run()
