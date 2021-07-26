#!/usr/bin/env python
import os, glob, sys
from commands import getoutput
import re
import datetime
import subprocess
import itertools

now = datetime.datetime.now()
timestamp =  now.strftime("%Y_%m_%d")

def split_seq(iterable, size):
    it = iter(iterable)
    item = list(itertools.islice(it, size))
    while item:
        yield item
        item = list(itertools.islice(it, size))
        
def getFileListDAS(dataset,instance="prod/phys03",run=-1):
	cmd='das_client --limit=0 --query="file dataset=%s instance=%s"'%(dataset,instance)
	print "Executing ",cmd
	cmd_out = getoutput( cmd )
	tmpList = cmd_out.split(os.linesep)
	files = []
	for l in tmpList:
	   if l.find(".root") != -1:
	      files.append(l)
	         
	return files 
   
def createJobs(f, outfolder,name,nchunks):
  infiles = []
  for files in f:
    infiles.append("root://cms-xrd-global.cern.ch/"+files)
  cmd = 'python qsub_script_SFs.py %s %s %s %i \n'%(','.join(infiles), outfolder,name,nchunks)
  print cmd
  jobs.write(cmd)
  return 1

def submitJobs(jobList, nchunks, outfolder, batchSystem):
    print 'Reading joblist'
    jobListName = jobList
    print jobList
#    subCmd = 'qsub -t 1-%s -o logs nafbatch_runner_GEN.sh %s' %(nchunks,jobListName)
    subCmd = 'qsub -t 1-%s -o %s/logs/ %s %s' %(nchunks,outfolder,batchSystem,jobListName)
    print 'Going to submit', nchunks, 'jobs with', subCmd
    os.system(subCmd)

    return 1


if __name__ == "__main__":
	outfolder = "%s"%timestamp
	batchSystem = 'psibatch_runner.sh'

	if len(sys.argv) > 1:
		if sys.argv[1].find("TT")!=-1:		patterns = ["/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/thaarres-TTTuneCUETP8M2T413TeV-powheg-pythia8RunIISummer16MiniAODv2-PUMoriond1780XmcRun2asymptotic-4a4b356339e753e24c281c17941d0081/USER"]
		if sys.argv[1].find("ST")!=-1:		patterns = ["/ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8/thaarres-STs-channel4fInclusiveDecays13TeV-amcatnlo-pythia8RunIISummer16MiniAODv2-PUMoriond1780X-4a4b356339e753e24c281c17941d0081/USER","/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/thaarres-STtWantitop5finclusiveDecays13TeV-powheg-pythia8TuneCUETP8M2T4-4a4b356339e753e24c281c17941d0081/USER","/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M2T4/thaarres-STtWtop5finclusiveDecays13TeV-powheg-pythia8TuneCUETP8M2T4RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER"]		
		if sys.argv[1].find("VV")!=-1:		patterns = ["/WW_TuneCUETP8M1_13TeV-pythia8/thaarres-WWTuneCUETP8M113TeV-pythia8RunIISummer16MiniAODv2-PUMoriond1780XmcRun2asymptotic2016-4a4b356339e753e24c281c17941d0081/USER","/WZ_TuneCUETP8M1_13TeV-pythia8/thaarres-WZTuneCUETP8M113TeV-pythia8RunIISummer16MiniAODv2-PUMoriond1780XmcRun2asymptotic2016-4a4b356339e753e24c281c17941d0081/USER","/WW_TuneCUETP8M1_13TeV-pythia8/thaarres-WWTuneCUETP8M113TeV-pythia8RunIISummer16MiniAODv2-PUMoriond1780XmcRun2asymptotic2016-4a4b356339e753e24c281c17941d0081/USER"]	
		if sys.argv[1].find("Wjets")!=-1:	patterns = ["/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-100To200TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER"	,"/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-1200To2500TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-200To400TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-2500ToInfTuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-400To600TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-70To100TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond1780X-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-600To800TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER","/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/asparker-WJetsToLNuHT-800To1200TuneCUETP8M113TeV-madgraphMLM-pythia8RunIISummer16MiniAODv2-PUMoriond17-4a4b356339e753e24c281c17941d0081/USER"]
		if sys.argv[1].find("data")!=-1:	patterns = ["/SingleMuon/thaarres-SingleMuon_Run2017B-17Nov2017-v1-351ed72508aa977f1c65d26f45752bf7/USER","/SingleMuon/thaarres-SingleMuon_Run2017C-17Nov2017-v1-351ed72508aa977f1c65d26f45752bf7/USER","/SingleMuon/thaarres-SingleMuon_Run2017D-17Nov2017-v1-351ed72508aa977f1c65d26f45752bf7/USER","/SingleMuon/thaarres-SingleMuon_Run2017E-17Nov2017-v1-351ed72508aa977f1c65d26f45752bf7/USER","/SingleMuon/thaarres-SingleMuon_Run2017F-17Nov2017-v1-351ed72508aa977f1c65d26f45752bf7/USER"]			
		if sys.argv[1].find("QCD")!=-1:	  patterns = ["/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/arizzi-NanoCrabXmasRunIISummer16MiniAODv2-PUMoriond17_magnetOn_80X_mc___heIV_v6-v1__650-f64d1fc6d0aff52acf7debc448857e96/USER"]
		
		print 'Location of input files', patterns
	else:
		print "No location given, give folder with files"
		exit(0)

	if len(sys.argv) > 2:
		outfolder = sys.argv[2]
		print 'Output goes here: ', outfolder
	else:
		print "Using default output folder: ", outfolder


	
	for pattern in patterns:
		files = getFileListDAS(pattern)
		print "FILELIST = ", files
		name = pattern.split("/")[1].replace("/","")
		if sys.argv[1].find("data")!=-1: name = pattern.split("/")[2].replace("/","")
		print "creating job file " ,'joblist%s.txt'%name
		jobList = 'joblist%s.txt'%name
		jobs = open(jobList, 'w')
		nChunks = 0
		outfolder = name
		try: os.stat(outfolder)
		except: os.mkdir(outfolder)
		try: os.stat(outfolder+'/logs/')
		except: os.mkdir(outfolder+'/logs/')
		filelists = list(split_seq(files,10))	
		for f in filelists:
			print "FILES = ",f
			createJobs(f,outfolder,name,nChunks)
			nChunks = nChunks+1
		
		jobs.close()
		submit = raw_input("Do you also want to submit the jobs to the batch system? [y/n] ")
		# submit = 'y'
		if submit == 'y' or submit=='Y':
			submitJobs(jobList,nChunks, outfolder, batchSystem)
		else:
			print "Not submitting jobs"
		
		
		
