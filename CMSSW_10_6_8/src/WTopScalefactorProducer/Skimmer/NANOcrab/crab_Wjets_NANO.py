import sys

if __name__ == '__main__':


	from CRABClient.UserUtilities import config 
	config = config()
	
	config.General.requestName = 'WJetsToLNu_NANOv2'
	config.General.workArea = 'crab_Tprime_v5_NANo_AOD_106X'
	#config.General.transferOutputs = True
	config.General.transferLogs = True
	
	config.JobType.pluginName = 'Analysis'
	config.JobType.psetName = 'PSet.py'
	config.JobType.scriptExe = 'crab_script_Tprime.sh'
	#config.JobType.scriptArgs = ['isMC=1','era=2016','dataRun=X']
	config.JobType.inputFiles = ['TprimeBToTH_LH_RunIISummer19UL16_Skimmer.py','keep_and_drop_v1.txt','../../../PhysicsTools/NanoAODTools/scripts/haddnano.py'] #hadd nano will not be needed once nano tools 	are in cmssw
	config.JobType.sendPythonFolder  = True
	config.JobType.allowUndistributedCMSSW = True
	
	config.Data.inputDataset = '/TprimeBToTH_M-1500_LH_TuneCP5_PSweights_13TeV-madgraph_pythia8/RunIISummer19UL16NanoAOD-106X_mcRun2_asymptotic_v13-v1/NANOAODSIM'
	#config.Data.inputDBS = 'phys03'
	config.Data.inputDBS = 'global'
	config.Data.splitting = 'FileBased'
	#config.Data.splitting = 'EventAwareLumiBased'
	config.Data.unitsPerJob = 1
	config.Data.totalUnits = 41
	#config.Data.totalUnits = 148768378
	
	
	config.Data.outLFNDirBase = '/store/user/achhetri/Tprime_v5_NANo_AOD_106X'
	config.Data.publication = False
	config.Data.outputDatasetTag = 'WJetsToLNu_RunIIUL17NanoAODv2'
	
	config.section_("Site")
	config.Site.storageSite = 'T3_CH_CERNBOX'


        f=open(sys.argv[1])
   	content = f.readlines()
    	content = [x.strip() for x in content]
    	from CRABAPI.RawCommand import crabCommand
    	
	for dataset in content :

        	config.Data.inputDataset = dataset
        	crabCommand('submit', config = config)


