import sys

name = 'DYJetsToLL_HT-bin_UL17_106X_v2'

dataset = {
   'DYJetsToLL_M-50_HT-70to100_v2'         : '/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-100to200_v2'        : '/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-200to400_v2'        : '/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-400to600_v2'        : '/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-600to800_v2'        : '/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-800to1200_v2'       : '/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-1200to2500_v2'      : '/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'DYJetsToLL_M-50_HT-2500toInf_v2'       : '/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/RunIISummer20UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',

   }

#nevents = -1 
eventsPerJob = {
   'DYJetsToLL_M-50_HT-70to100_v2'           :1,
   'DYJetsToLL_M-50_HT-100to200_v2'          :1,
   'DYJetsToLL_M-50_HT-200to400_v2'          :1,
   'DYJetsToLL_M-50_HT-400to600_v2'          :1,
   'DYJetsToLL_M-50_HT-600to800_v2'          :1,
   'DYJetsToLL_M-50_HT-800to1200_v2'         :1,
   'DYJetsToLL_M-50_HT-1200to2500_v2'        :1,
   'DYJetsToLL_M-50_HT-2500toInf_v2'         :1,

   }


TotalUnitsPerJob = {
   'DYJetsToLL_M-50_HT-70to100_v2'           : 21,
   'DYJetsToLL_M-50_HT-100to200_v2'          : 14,
   'DYJetsToLL_M-50_HT-200to400_v2'          : 10,
   'DYJetsToLL_M-50_HT-400to600_v2'          : 6,
   'DYJetsToLL_M-50_HT-600to800_v2'          : 31,
   'DYJetsToLL_M-50_HT-800to1200_v2'         : 7,
   'DYJetsToLL_M-50_HT-1200to2500_v2'        : 5,
   'DYJetsToLL_M-50_HT-2500toInf_v2'         : 4,

   }

listOfSamples = [
   'DYJetsToLL_M-50_HT-70to100_v2'           ,
   # 'DYJetsToLL_M-50_HT-100to200_v2'          ,
   # 'DYJetsToLL_M-50_HT-200to400_v2'          ,
   # 'DYJetsToLL_M-50_HT-400to600_v2'          ,
   'DYJetsToLL_M-50_HT-600to800_v2'          ,   
   # 'DYJetsToLL_M-50_HT-800to1200_v2'         ,
   # 'DYJetsToLL_M-50_HT-1200to2500_v2'        ,
   # 'DYJetsToLL_M-50_HT-2500toInf_v2'         ,

   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'DYJetsToLL_HT-bin_UL17_106X_v2'
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
        config.Data.outputDatasetTag = 'DYJetsToLL_HT-bin_RunIISummer19UL17NanoAOD_v2'

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


