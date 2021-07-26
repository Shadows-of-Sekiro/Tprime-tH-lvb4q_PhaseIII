import sys

name = 'WJetsToLNu_HT-bin_UL17_106X_v2'

dataset = {
   'WJetsToLNu_HT-100To200_v2'       : '/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'WJetsToLNu_HT-200To400_v2'       : '/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'WJetsToLNu_HT-400To600_v2'       : '/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'WJetsToLNu_HT-600To800_v2'       : '/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'WJetsToLNu_HT-800To1200_v2'      : '/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'WJetsToLNu_HT-1200To2500_v2'     : '/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',

   }

#nevents = -1 
eventsPerJob = {
   'WJetsToLNu_HT-100To200_v2'       :1,
   'WJetsToLNu_HT-200To400_v2'       :1,
   'WJetsToLNu_HT-400To600_v2'       :1,
   'WJetsToLNu_HT-600To800_v2'       :1,
   'WJetsToLNu_HT-800To1200_v2'      :1,
   'WJetsToLNu_HT-1200To2500_v2'     :1,

   }

TotalUnitsPerJob = {  
   'WJetsToLNu_HT-100To200_v2'       : 31,
   'WJetsToLNu_HT-200To400_v2'       : 34,
   'WJetsToLNu_HT-400To600_v2'       : 10,
   'WJetsToLNu_HT-600To800_v2'       : 7,
   'WJetsToLNu_HT-800To1200_v2'      : 6,
   'WJetsToLNu_HT-1200To2500_v2'     : 6,

   }

listOfSamples = [   
   'WJetsToLNu_HT-100To200_v2'       ,
   'WJetsToLNu_HT-200To400_v2'       ,
   'WJetsToLNu_HT-400To600_v2'       ,
   'WJetsToLNu_HT-600To800_v2'       ,
   'WJetsToLNu_HT-800To1200_v2'      ,
   'WJetsToLNu_HT-1200To2500_v2'     ,
 
   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'WJetsToLNu_HT-bin_UL17_106X_v2'
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
        config.Data.splitting = 'FileBased'
        #config.Data.splitting = 'EventAwareLumiBased'
        # config.Data.unitsPerJob = 1
        # config.Data.totalUnits = 246
        #config.Data.totalUnits = 148768378


        config.Data.outLFNDirBase = '/store/user/achhetri/Tprime_v5_NANo_AOD_106X'
        config.Data.publication = False
        config.Data.outputDatasetTag = 'WJetsToLNu_HT-bin_RunIISummer19UL17NanoAOD_v2'

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



