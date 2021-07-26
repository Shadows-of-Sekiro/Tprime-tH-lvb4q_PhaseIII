#!/Usr-/bin/env python
import os,sys

from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 
from Skimmer  import *
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
 #     "root://cms-xrd-global.cern.ch//store/mc/RunIIAutumn18NanoAODv5/TTJets_TuneCP5_13TeV-madgraphMLM-pythia8/NANOAODSIM/Nano1June2019_102X_upgrade2018_realistic_v19-v1/70000/183B8B0C-AA6C-A041-895D-31FC5BEECFC4.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL16NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v13-v1/240000/8F19747F-C654-DD40-967B-393CD2EEFEE6.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL18NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/100000/1803342B-485C-7743-AE52-F5703C99AFE9.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL18NanoAOD/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/100000/01B32844-F4EC-1240-A875-B28D9282C080.root"
#      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL16NanoAOD/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v13-v1/110000/02D168D8-87D6-F04D-82B4-851DE8AEEBEC.root"
      "root://cms-xrd-global.cern.ch//store/mc/RunIISummer19UL16NanoAOD/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/NANOAODSIM/106X_mcRun2_asymptotic_v13-v1/240000/8F19747F-C654-DD40-967B-393CD2EEFEE6.root"
 #     "root://cms-xrd-global.cern.ch//store/mc/RunIISummer16NanoAODv7/TTJets_TuneCP5_PSweights_13TeV-amcatnloFXFX-pythia8/NANOAODSIM/PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1/100000/46F70FB9-58C6-8C4B-8D0B-39E31788820C.root"
  ]

if len(sys.argv)>2: outputDir = sys.argv[2]
else: outputDir = "TEST"	

if len(sys.argv)>3: name = sys.argv[3]
else: name = "test.root"

if len(sys.argv)>4: chunck = sys.argv[4]
else: chunck = ""  

#"keep_and_drop.txt"

#if infile[0].find("SingleMuon")!=-1:
#  channel = "mu"
#  print "Processing a Single Muon dataset file..."
#  p=PostProcessor(outputDir, infile, "HLT_Mu50 && nMuon>0 && Muon_pt[0]>55. && nFatJet>0", None,
#                    modules=[Skimmer(channel)],provenance=False,fwkJobReport=False,
#                    jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt')
#                   
#elif infile[0].find("EGamma")!=-1:
#  channel = "el"
#  print "Processing a Single Electron dataset file..."
#  p=PostProcessor(outputDir, infile, "(event.HLT_Ele32_WPTight_Gsf || event.HLT_Ele35_WPTight_Gsf || event.HLT_Ele40_WPTight_Gsf || HLT_Ele115_CaloIdVT_GsfTrkIdT) && nElectron>0 && Electron_pt[0]>55. && nFatJet>0", None,
#                    modules=[Skimmer(channel)],provenance=False,fwkJobReport=False,
#                    jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt')
#                    
#else:
print "Processing MC..."
channel = "elmu"
p=PostProcessor(outputDir, infile, None, None,
                    modules=[Skimmer(channel)],provenance=False,maxEntries=2500,fwkJobReport=False)
p.run()
print "DONE"

#maxEntries=25000
