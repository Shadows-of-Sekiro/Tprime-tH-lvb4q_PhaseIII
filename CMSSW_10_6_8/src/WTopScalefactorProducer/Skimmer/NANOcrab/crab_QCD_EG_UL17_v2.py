import sys

name = 'QCD_EMEnriched_UL17_106X_v2'

dataset = {
   'QCD_Pt50to80_EM_v2'     :  '/QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt80to120_EM_v2'    :  '/QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt120to170_EM_v2'   :  '/QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt170to300_EM_v2'   :  '/QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt300toInf_EM_v2'   :  '/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',

   
   }

#nevents = -1 
eventsPerJob = {
   'QCD_Pt50to80_EM_v2'     : 1,        
   'QCD_Pt80to120_EM_v2'    : 1,        
   'QCD_Pt120to170_EM_v2'   : 1,        
   'QCD_Pt170to300_EM_v2'   : 1,        
   'QCD_Pt300toInf_EM_v2'   : 1, 

   }

TotalUnitsPerJob = {
   'QCD_Pt50to80_EM_v2'     : 13,        
   'QCD_Pt80to120_EM_v2'    : 8,        
   'QCD_Pt120to170_EM_v2'   : 10,        
   'QCD_Pt170to300_EM_v2'   : 5,        
   'QCD_Pt300toInf_EM_v2'   : 8, 

   }

listOfSamples = [
   'QCD_Pt50to80_EM_v2'    ,
   'QCD_Pt80to120_EM_v2'   ,
   'QCD_Pt120to170_EM_v2'  ,
   'QCD_Pt170to300_EM_v2'  ,
   'QCD_Pt300toInf_EM_v2'  ,

   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'QCD_EMEnriched_UL17_106X_v2'
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
        config.Data.outputDatasetTag = 'QCD_EMEnriched_RunIISummer19UL17NanoAOD_v2'

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
   
