import sys

name = 'Tprime_LH_UL17v2_106X'

dataset = {
    'TprimeB_to_TH_M1000_LH_v2'  : '/TprimeBToTH_M-1000_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1100_LH_v2'  : '/TprimeBToTH_M-1100_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1200_LH_v2'  : '/TprimeBToTH_M-1200_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1300_LH_v2'  : '/TprimeBToTH_M-1300_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1400_LH_v2'  : '/TprimeBToTH_M-1400_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'TprimeB_to_TH_M1500_LH_v2'  : '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1600_LH_v2'  : '/TprimeBToTH_M-1600_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    #'TprimeB_to_TH_M1700_LH_v2'  : '/TprimeBToTH_M-1700_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
    'TprimeB_to_TH_M1800_LH_v2'  : '/TprimeBToTH_M-1800_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',

   }


#nevents = -1 
eventsPerJob = {
  'TprimeB_to_TH_M1000_LH_v2'  : 10000 , 
  #'TprimeB_to_TH_M1100_LH_v2'  : 10000 ,
  #'TprimeB_to_TH_M1200_LH_v2'  : 10000 ,
  #'TprimeB_to_TH_M1300_LH_v2'  : 10000 ,
  #'TprimeB_to_TH_M1400_LH_v2'  : 10000 ,
  'TprimeB_to_TH_M1500_LH_v2'  : 10000 ,
  #'TprimeB_to_TH_M1600_LH_v2'  : 10000 ,
  #'TprimeB_to_TH_M1700_LH_v2'  : 10000 ,
  'TprimeB_to_TH_M1800_LH_v2'  : 10000 ,
   }

TotalUnitsPerJob = {
  'TprimeB_to_TH_M1000_LH_v2'  : 400000 ,
  #'TprimeB_to_TH_M1100_LH_v2'  : 400000 ,
  #'TprimeB_to_TH_M1200_LH_v2'  : 397700 ,
  #'TprimeB_to_TH_M1300_LH_v2'  : 400000 ,
  #'TprimeB_to_TH_M1400_LH_v2'  : 400000 ,
  'TprimeB_to_TH_M1500_LH_v2'  : 400000 ,
  #'TprimeB_to_TH_M1600_LH_v2'  : 400000 ,
  #'TprimeB_to_TH_M1700_LH_v2'  : 397600 ,
  'TprimeB_to_TH_M1800_LH_v2'  : 400000 ,
   }

listOfSamples = [
   'TprimeB_to_TH_M1000_LH_v2'  ,
   #'TprimeB_to_TH_M1100_LH_v2'  ,
   #'TprimeB_to_TH_M1200_LH_v2'  ,
   #'TprimeB_to_TH_M1300_LH_v2'  ,
   #'TprimeB_to_TH_M1400_LH_v2'  ,
   'TprimeB_to_TH_M1500_LH_v2'  ,
   #'TprimeB_to_TH_M1600_LH_v2'  ,
   #'TprimeB_to_TH_M1700_LH_v2'  ,
   'TprimeB_to_TH_M1800_LH_v2'  ,
   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'Tprime_LH_UL17_106X'
        config.General.workArea = 'crab_Tprime_v5_NANo_AOD_106X'
        #config.General.transferOutputs = True
        config.General.transferLogs = True

        config.JobType.pluginName = 'Analysis'
        config.JobType.psetName = 'PSet.py'
        config.JobType.scriptExe = 'crab_script_Tprime.sh'
        #config.JobType.scriptArgs = ['isMC=1','era=2016','dataRun=X']
        config.JobType.inputFiles = ['TprimeBToTH_LH_RunIISummer19UL16_Skimmer.py','keep_and_drop_v1.txt','../../../PhysicsTools/NanoAODTools/scripts/haddnano.py'] #hadd nano will not be needed once nano tools  are in cmssw
        config.JobType.sendPythonFolder  = True
        config.JobType.allowUndistributedCMSSW = True

        config.Data.inputDataset = '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL16NanoAOD-106X_mcRun2_asymptotic_v13-v1/NANOAODSIM'
        #config.Data.inputDBS = 'phys03'
        config.Data.inputDBS = 'global'
        # config.Data.splitting = 'FileBased'
        config.Data.splitting = 'EventAwareLumiBased'
        # config.Data.unitsPerJob = 1
        # config.Data.totalUnits = 246
        #config.Data.totalUnits = 148768378


        config.Data.outLFNDirBase = '/store/user/achhetri/Tprime_v5_NANo_AOD_106X'
        config.Data.publication = False
        config.Data.outputDatasetTag = 'Tprime_LH_106X_RunIISummer19UL17NanoAODv2'

        config.section_("Site")
        config.Site.storageSite = 'T3_CH_CERNBOX'


        # f=open(sys.argv[1])
        # content = f.readlines()
        # content = [x.strip() for x in content]
        from CRABAPI.RawCommand import crabCommand

        # for dataset in content :

        #         config.Data.inputDataset = dataset


        listOfSamples.reverse()
        for sample in listOfSamples:

           config.General.requestName = sample
           config.Data.inputDataset = dataset[sample]
           config.Data.unitsPerJob = eventsPerJob[sample]
           config.Data.totalUnits = TotalUnitsPerJob[sample]
           config.Data.outputDatasetTag = sample
           crabCommand('submit', config = config)

