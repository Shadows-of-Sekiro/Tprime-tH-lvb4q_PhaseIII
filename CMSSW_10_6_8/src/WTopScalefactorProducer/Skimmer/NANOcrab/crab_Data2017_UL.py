name = 'Data2017_UL_106X'

dataset = {
   'EraB'   : '/SingleMuon/Run2017B-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'EraD'   : '/SingleMuon/Run2017D-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'EraE'   : '/SingleMuon/Run2017E-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   'EraF'   : '/SingleMuon/Run2017F-UL2017_MiniAODv1_NanoAODv2-v2/NANOAOD',
   #'EraG'   : '/SingleMuon/Run2017G-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   #'EraH'   : '/SingleMuon/Run2017H-UL2017_MiniAODv1_NanoAODv2-v1/NANOAOD',
   }


#nevents = -1 
eventsPerJob = {
   'EraB'   :        10,
   'EraD'   :        10,
   'EraE'   :        10,
   'EraF'   :        10,
   #'EraG'   :        6,
   #'EraH'   :        6,
   }

listOfSamples = [
   'EraB',
   'EraD',
   'EraE',
   'EraF',
   #'EraG',
   #'EraH',
   ]

if __name__ == '__main__':

	      #from WMCore.Configuration import Configuration
	      #config = Configuration()

         from CRABClient.UserUtilities import config
         config = config()

         from CRABAPI.RawCommand import crabCommand
         from multiprocessing import Process

         def submit(config):
             res = crabCommand('submit', config = config)

         config.General.workArea = 'crab_'+name
         config.General.transferLogs = False

         config.JobType.pluginName = 'Analysis'
         config.JobType.psetName = 'PSet.py'
         config.JobType.scriptExe = 'crab_script_Data.sh'
         #config.JobType.scriptArgs = ['isMC=1','era=2016','dataRun=X']
         config.JobType.inputFiles = ['Data_RunIIUL_Skimmer.py','keep_and_drop_data_v2.txt','../../../PhysicsTools/NanoAODTools/scripts/haddnano.py','Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'] #hadd nano will not be needed once nano tools  are in cmssw
         config.JobType.sendPythonFolder  = True
         config.JobType.allowUndistributedCMSSW = True

         #config.Data.inputDBS = 'global'
         config.Data.splitting    = 'LumiBased'
         config.Data.lumiMask     = 'Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
         config.Data.totalUnits   = -1
         # config.Data.outLFNDirBase = '/store/group/lpcqstar/TPrime/Arjun/PhaseII/Data_Ntuples/Data2016Legacy/' + name


         config.Data.outLFNDirBase = '/store/user/achhetri/Data_UltraLegacy_NanoAOD'
         config.Data.publication = False
         config.Data.outputDatasetTag = 'Data2017_UL_106X'

         config.section_('User')
         #Site

         config.section_("Site")
         config.Site.storageSite = 'T3_CH_CERNBOX'


         # f=open(sys.argv[1])
         # content = f.readlines()
         # content = [x.strip() for x in content]
         from CRABAPI.RawCommand import crabCommand

         # for dataset in content :

         # config.Data.inputDataset = dataset


         listOfSamples.reverse()
         for sample in listOfSamples:

            config.General.requestName = sample
            config.Data.inputDataset = dataset[sample]
            config.Data.unitsPerJob = eventsPerJob[sample]
            config.Data.outputDatasetTag = sample
            crabCommand('submit', config = config)


