#!/Usr-/bin/env python
import os,sys

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis

from WTopScalefactorProducer.Skimmer.skimmer import Skimmer
#from WTopScalefactorProducer.Skimmer.skimmer import Skimmer

if len(sys.argv)>1:
   infile = sys.argv[1].split(',')
else:
  infile = [
#      "root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/NANOAOD/Nano14Dec2018_ver2-v1/40000/4BF53ABE-BB2D-B147-8BDE-888B21C3E07C.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv4/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/120000/BB978C6D-1770-CB42-A45E-AFAA249DAA82.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv4/ZZ_TuneCP5_13TeV-pythia8/NANOAODSIM/Nano14Dec2018_102X_upgrade2018_realistic_v16-v1/110000/56817FDC-2D4C-7E4B-ABA0-9A1F7BA505C4.root"
#     "root://cms-xrd-global.cern.ch//store/data/Run2018C/EGamma/NANOAOD/Nano1June2019-v1/230000/77B1D6B0-11DB-7D4C-83D5-5CDD162BFE61.root"
#      "root://cms-xrd-global.cern.ch//store/data/Run2018D/SingleMuon/NANOAOD/Nano1June2019-v1/40000/CB01BD35-453E-254D-A273-A867E34D7E52.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv5/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/110000/DDC35B8C-5718-4F41-8499-EDE8E3283FF5.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv5/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/120000/D23F4374-1259-174E-B968-E914679919BD.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL18NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/280000/BD6D7EFB-4430-CA4B-B99A-9FCA42322485.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv5/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/120000/076AB5E0-07CF-B448-A50B-66643744C94B.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv5/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/70000/0AB59AD8-086C-5445-9B19-523D4FCFB729.root"
      "root://cms-xrd-global.cern.ch///store/mc/RunIIAutumn18NanoAODv5/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/120000/C435EF5E-BAAB-3945-9252-6049054D9572.root"
  ]

if len(sys.argv)>2: outputDir = sys.argv[2]
#else: outputDir = "TEST"	
else: outputDir = ""	

#if len(sys.argv)>3: name = sys.argv[3]
#else: name = "TprimeBToTH_M-1500_LH_RunIISummer19UL16.root"
name = "TprimeBToTH_M-1500_LH_RunIISummer19UL16.root"



if len(sys.argv)>4: chunck = sys.argv[4]
else: chunck = ""  

#"keep_and_drop.txt"

if infile[0].find("SingleMuon")!=-1:
  channel = "mu"
  print "Processing a Single Muon dataset file..."
  p=PostProcessor(outputDir, infile, "HLT_Mu50 && nMuon>0 && Muon_pt[0]>55. && nFatJet>0", None,
                    modules=[Skimmer(channel)],provenance=False,fwkJobReport=False,
                    jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt')
                   
elif infile[0].find("EGamma")!=-1:
  channel = "el"
  print "Processing a Single Electron dataset file..."
  p=PostProcessor(outputDir, infile, "(event.HLT_Ele32_WPTight_Gsf || event.HLT_Ele35_WPTight_Gsf || event.HLT_Ele40_WPTight_Gsf || HLT_Ele115_CaloIdVT_GsfTrkIdT) && nElectron>0 && Electron_pt[0]>55. && nFatJet>0", None,
                    modules=[Skimmer(channel)],provenance=False,fwkJobReport=False,
                    jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt')
                    
else:
  print "Processing MC..."
  channel = "elmu"
  p=PostProcessor(".",inputFiles(), None, None,modules=[Skimmer(channel)],provenance=False,fwkJobReport=False,jsonInput=runsAndLumis())
  #p=PostProcessor(outputDir, infile, None, None,modules=[Skimmer(channel)],provenance=False,maxEntries=20,fwkJobReport=False)

p.run()
print "DONE"

#maxEntries=25000
