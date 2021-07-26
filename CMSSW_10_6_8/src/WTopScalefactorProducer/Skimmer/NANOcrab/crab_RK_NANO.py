import sys

#from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config 

config = Configuration()

config.section_("General")
config.General.requestName = 'NanoPost1'
config.General.workArea = 'crab_Tprime_v5_NANo_AOD_106X'
config.General.transferLogs=True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'crab_script_Tprime.sh'
config.JobType.inputFiles = ['TprimeBToTH_LH_RunIISummer19UL16_Skimmer.py','keep_and_drop.txt','../../../PhysicsTools/NanoAODTools/scripts/haddnano.py'] #hadd nano will not be needed once nano tools are in cmssw
config.JobType.sendPythonFolder     = True
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.inputDataset = '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL16NanoAOD-106X_mcRun2_asymptotic_v13-v1/NANOAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'EventAwareLumiBased'
config.Data.unitsPerJob = 1000




config.Data.outLFNDirBase ='/store/user/achhetri/Tprime_v5_NANo_AOD_106X'
#config.Data.outLFNDirBase = '/eos/user/a/achhetri/Tprime_PhaseIII/Signal/Tprime_v5_NANo_AOD_106X'
config.Data.publication = False
config.Data.outputDatasetTag = 'TprimeBToTH_M-1500_LH_RunIISummer19UL16'
config.section_("Site")
config.Site.storageSite = "T3_CH_CERNBOX"
