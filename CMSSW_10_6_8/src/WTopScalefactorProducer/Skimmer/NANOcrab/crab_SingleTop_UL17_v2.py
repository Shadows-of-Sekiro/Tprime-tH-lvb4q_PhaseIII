import sys

name = 'SingleTop_UL17_106X_v2'

dataset = {
   'ST_s-channel_4f_leptonDecays'                : '/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'ST_t-channel_antitop_4f_inclusiveDecays'     : '/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'ST_t-channel_top_4f_inclusiveDecays'         : '/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'ST_tW_top_5f_inclusiveDecays'                : '/ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'ST_tW_antitop_5f_inclusiveDecays'            : '/ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',

   }

#nevents = -1 
eventsPerJob = {
   'ST_s-channel_4f_leptonDecays'                :1,
   'ST_t-channel_antitop_4f_inclusiveDecays'     :1,
   'ST_t-channel_top_4f_inclusiveDecays'         :1,
   'ST_tW_top_5f_inclusiveDecays'                :1,
   'ST_tW_antitop_5f_inclusiveDecays'            :1,

   }

TotalUnitsPerJob = {  
   'ST_s-channel_4f_leptonDecays'                : 22,
   'ST_t-channel_antitop_4f_inclusiveDecays'     : 20,
   'ST_t-channel_top_4f_inclusiveDecays'         : 62,
   'ST_tW_top_5f_inclusiveDecays'                : 14,
   'ST_tW_antitop_5f_inclusiveDecays'            : 15,

   }

listOfSamples = [   
   'ST_s-channel_4f_leptonDecays'                ,
   'ST_t-channel_antitop_4f_inclusiveDecays'     ,
   'ST_t-channel_top_4f_inclusiveDecays'         ,
   'ST_tW_top_5f_inclusiveDecays'                ,
   'ST_tW_antitop_5f_inclusiveDecays'            ,
   
   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'SingleTop_UL17_106X_v2'
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
        config.Data.outputDatasetTag = 'SingleTop_RunIISummer19UL17NanoAOD_v2'

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



