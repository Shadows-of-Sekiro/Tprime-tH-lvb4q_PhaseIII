name = 'Tprime_v5_NANo_AOD_106X'

dataset = {
  'TprimeBToTH_M-1500_LH_RunIISummer19UL16'     : '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL16NanoAOD-106X_mcRun2_asymptotic_v13-v1/NANOAODSIM',
  # 'TprimeBToTH_M-1500_LH_RunIISummer19UL16'     : '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL16NanoAOD-106X_mcRun2_asymptotic_v13-v1/NANOAODSIM',
 } 


#nevents = -1 
eventsPerJob = {
  'TprimeBToTH_M-1500_LH_RunIISummer19UL16'     :  10000,
  # 'TprimeBToTH_M-1500_LH_RunIISummer19UL16'     :  10000,
   }

listOfSamples = [
  'TprimeBToTH_M-1500_LH_RunIISummer19UL16' ,
  # 'TprimeBToTH_M-1500_LH_RunIISummer19UL16' ,
   ]

if __name__ == '__main__':

	#from WMCore.Configuration import Configuration
	#config = Configuration()

   from CRABClient.UserUtilities import config, getUsernameFromSiteDB
   config = config()

   from CRABAPI.RawCommand import crabCommand
   from multiprocessing import Process

   def submit(config):
       res = crabCommand('submit', config = config)

   config.General.workArea = 'crab_'+name
   config.General.transferLogs = False

   config.JobType.pluginName = 'Analysis'
   config.JobType.psetName = 'PSet.py'    
   #PSet.py is a local file for crab to run and check, not included in main process
   
   config.JobType.scriptExe = 'crab_script_Tprime.sh'
   #.sh file to run main python file, only to be run in main crab job

   config.JobType.inputFiles = ['TprimeBToTH_LH_RunIISummer19UL16_Skimmer.py']
   # main python file for job

   config.JobType.sendPythonFolder     = True
   config.JobType.allowUndistributedCMSSW = True
   
   # config.JobType.outputFiles = ['TprimeBToTH_M-1500_LH_RunIISummer19UL16.root']

   config.Data.inputDBS = 'global'
   config.Data.splitting    = 'EventAwareLumiBased'
 #  config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
   config.Data.publication = False
   config.Data.totalUnits = -1
   config.Data.outLFNDirBase = '/eos/user/a/achhetri/Tprime_PhaseIII/Signal/' + name

   config.section_('User')
   #Site
   config.section_('Site')
   # config.Site.storageSite = 'T3_US_FNALLPC'
   config.Site.storageSite = 'T3_CH_CERNBOX'
 #  config.Site.storageSite = 'T2_IN_TIFR'
 #  config.Site.blacklist = ['T2_BR_SPRACE', 'T2_US_Wisconsin', 'T1_RU_JINR', 'T2_RU_JINR', 'T2_EE_Estonia']

   listOfSamples.reverse()
   for sample in listOfSamples:

      config.General.requestName = sample
      config.Data.inputDataset = dataset[sample]
      config.Data.unitsPerJob = eventsPerJob[sample]
      config.Data.outputDatasetTag = sample
      p = Process(target=submit, args=(config,))
      p.start()
      p.join()
