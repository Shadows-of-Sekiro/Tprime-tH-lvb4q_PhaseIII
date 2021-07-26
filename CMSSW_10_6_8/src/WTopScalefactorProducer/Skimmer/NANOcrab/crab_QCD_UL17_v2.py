import sys

name = 'QCD_MuEnriched_UL17_106X_v2'

dataset = {
   #'QCD_Pt80to120_v2'   : '/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   #'QCD_Pt120to170_v2'  : '/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt170to300_v2'  : '/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt300to470_v2'  : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt470to600_v2'  : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt600to800_v2'  : '/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt800to1000_v2' : '/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   'QCD_Pt1000toInf_v2' : '/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17NanoAODv2-106X_mc2017_realistic_v8-v1/NANOAODSIM',
   
   }

#nevents = -1 
eventsPerJob = {
  # 'QCD_Pt80to120_v2' : 1,        
  # 'QCD_Pt120to170_v2' : 1,        
   'QCD_Pt170to300_v2' : 1,        
   'QCD_Pt300to470_v2' : 1,        
   'QCD_Pt470to600_v2' : 1, 
   'QCD_Pt600to800_v2' : 1,
   'QCD_Pt800to1000_v2' : 1,      
   'QCD_Pt1000toInf_v2' : 1,
   }

TotalUnitsPerJob = {
  # 'QCD_Pt80to120_v2' : 2,        
  # 'QCD_Pt120to170_v2' : 6,        
   'QCD_Pt170to300_v2' : 45,        
   'QCD_Pt300to470_v2' : 5,        
   'QCD_Pt470to600_v2' : 4, 
   'QCD_Pt600to800_v2' : 24,
   'QCD_Pt800to1000_v2' : 29,      
   'QCD_Pt1000toInf_v2' : 21,
   }

listOfSamples = [
   #'QCD_Pt80to120_v2',
   #'QCD_Pt120to170_v2',
   'QCD_Pt170to300_v2',
   'QCD_Pt300to470_v2',
   'QCD_Pt470to600_v2',
   'QCD_Pt600to800_v2',
   'QCD_Pt800to1000_v2',
   'QCD_Pt1000toInf_v2',
   ]


if __name__ == '__main__':


        from CRABClient.UserUtilities import config
        config = config()

        config.General.requestName = 'QCD_MuEnriched_UL17_106X_v2'
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
        config.Data.outputDatasetTag = 'QCD_MuEnriched_RunIISummer19UL17NanoAOD_v2'

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

      
