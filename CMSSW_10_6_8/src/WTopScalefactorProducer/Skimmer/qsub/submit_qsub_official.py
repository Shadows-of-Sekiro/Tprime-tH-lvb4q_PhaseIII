#!/usr/bin/env python
import os, glob, sys
from commands import getoutput
import re
import datetime
import subprocess
import itertools

now = datetime.datetime.now()
timestamp =  now.strftime("%Y_%m_%d")
queue = "all.q"
#queue = "long.q"
#queue = "short.q"
nfilesperjob = 1

listDirectory = "fileLists_Autumn18_v5/"


def split_seq(iterable, size):
    it = iter(iterable)
    item = list(itertools.islice(it, size))
    while item:
        yield item
        item = list(itertools.islice(it, size))

# Other possible definition
#def split_seq(seq,size):
#    """ Split up seq in pieces of size """
#    return [seq[i:i+size] for i in range(0, len(seq), size)]

def getFileListDAS(dataset,instance="prod/phys03",run=-1):
  cmd='das_client --limit=0 --query="file dataset=%s instance=%s"'%(dataset,instance)
#  cmd='das_client --limit=0 --query="file dataset=%s"'%(dataset,)
  print "Executing ",cmd
  cmd_out = getoutput( cmd )
  tmpList = cmd_out.split(os.linesep)
  files = []
  for l in tmpList:
     if l.find(".root") != -1:
        files.append(l)
           
  return files 

def getFileList(name):
  files = open(listDirectory+"/"+name+".txt", "r").read().splitlines()
  return files

def createLists(dataset, name):
  instance="prod/phys03"
  cmd='das_client --limit=0 --query="file dataset=%s"'%(dataset)
  print "Executing ",cmd
  cmd_out = getoutput( cmd )
  tmpList = cmd_out.split(os.linesep)
  files = []
  for l in tmpList:
     if l.find(".root") != -1:
        files.append(l)
        
  fileName = listDirectory+"/"+name+".txt"
  with open(fileName, "w") as f:
    for l in files:
        f.write("%s\n" % l)
  print "Wrote file list", fileName
  return




def createJobs(f, outfolder,name,nchunks):
  infiles = []
  for files in f:
    infiles.append("root://cms-xrd-global.cern.ch/"+files)
  cmd = 'python qsub_script_SFs.py %s %s %s %i \n'%(','.join(infiles), outfolder,name,nchunks)
  #print cmd
  jobs.write(cmd)
  return 1

def submitJobs(jobList, nchunks, outfolder, batchSystem):
    print 'Reading joblist'
    jobListName = jobList
    #print jobList
#    subCmd = 'qsub -t 1-%s -o logs nafbatch_runner_GEN.sh %s' %(nchunks,jobListName)
    subCmd = 'qsub -q %s -t 1-%s -o %s/logs/ %s %s' %(queue,nchunks,outfolder,batchSystem,jobListName)
    print 'Going to submit', nchunks, 'jobs with', subCmd
    os.system(subCmd)

    return 1


if __name__ == "__main__":
  out = "Skimmed_%s/"%timestamp
  batchSystem = 'psibatch_runner.sh'
  createlists = False

  patternsData  = [
    "/SingleMuon/Run2018A-Nano1June2019-v1/NANOAOD",
    "/SingleMuon/Run2018B-Nano1June2019-v1/NANOAOD",
    "/SingleMuon/Run2018C-Nano1June2019-v1/NANOAOD",
    "/SingleMuon/Run2018D-Nano1June2019-v1/NANOAOD",
    "/EGamma/Run2018A-Nano1June2019-v1/NANOAOD",
    "/EGamma/Run2018B-Nano1June2019-v1/NANOAOD",
    "/EGamma/Run2018C-Nano1June2019-v1/NANOAOD",
    "/EGamma/Run2018D-Nano1June2019-v1/NANOAOD",
  ]
  patternsTT    = [
    "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/TT_TuneCH3_13TeV-powheg-herwig7/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19_ext1-v1/NANOAODSIM",
  ]
  patternsST    = [
    "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19_ext1-v1/NANOAODSIM",
    "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19_ext1-v1/NANOAODSIM",
#    "/ST_t-channel_top_5f_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
#    "/ST_t-channel_antitop_5f_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19_ext1-v1/NANOAODSIM",
  ]
  patternsVV    = [
    "/WZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WW_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/ZZ_TuneCP5_13TeV-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
  ]
  patternsWJets = [
    "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
  ]
  patternsQCD = [
    "/QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
    "/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1/NANOAODSIM",
  ]
  
  patterns = []
  if len(sys.argv) > 1:
    if sys.argv[1].find("data")!=-1:  patterns = patternsData  
    if sys.argv[1].find("TT")!=-1:    patterns = patternsTT    
    if sys.argv[1].find("ST")!=-1:    patterns = patternsST    
    if sys.argv[1].find("VV")!=-1:    patterns = patternsVV    
    if sys.argv[1].find("WJets")!=-1: patterns = patternsWJets 
    if sys.argv[1].find("QCD")!=-1:   patterns = patternsQCD
    if sys.argv[1].find("mc")!=-1:    patterns = patternsTT+patternsST+patternsVV+patternsWJets+patternsQCD
    if sys.argv[1].find("all")!=-1:   patterns = patternsTT+patternsST+patternsVV+patternsWJets+patternsQCD+patternsData
  
    print 'Location of input files',  patterns
  else:
    print "No location given, give folder with files"
    exit(0)
  
  if len(sys.argv) > 2:
    if sys.argv[2].find("-c")!=-1: createlists = True
    else:
      out = sys.argv[2]
      print 'Output goes here: ', out
  else:
    print "Using default output folder: ", out
  
  try: os.stat(out)
  except: os.mkdir(out)
  
  if createlists:
      for pattern in patterns:
        name = pattern.split("/")[1].replace("/","") + ("-" + pattern.split("/")[2].split("-")[0] if 'Run201' in pattern else "")
        createLists(pattern, name)
  else:

    numberOfJobs = 0
    for pattern in patterns:
      name = pattern.split("/")[1].replace("/","") + ("-" + pattern.split("/")[2].split("-")[0] if 'Run201' in pattern else "")
      try:
        files = getFileList(name)
      except:
        exit()
        files = getFileListDAS(pattern)
      
  #    print "FILELIST = ", files
      print "creating job file " ,'joblist%s.txt'%name
      jobList = 'joblist%s.txt'%name
      jobs = open(jobList, 'w')
      nChunks = 0
      outfolder = out+name
      try: os.stat(outfolder)
      except: os.mkdir(outfolder)
      try: os.stat(outfolder+'/logs/')
      except: os.mkdir(outfolder+'/logs/')
      
      filelists = list(split_seq(files, nfilesperjob))
      
      print "Creating", len(filelists), "jobs each with files:", [len(x) for x in filelists]
      for f in filelists:
        #print "FILES = ",f
        createJobs(f,outfolder,name,nChunks)
        nChunks = nChunks+1

        numberOfJobs+=1
      
      jobs.close()

      with open("jobCount.txt", "w") as jobCountFile: # putting this here (with w) so that it writes the correct total number of jobs submitted even if the script doesn't run until the end.
        print numberOfJobs
        jobCountFile.write("{0}".format(numberOfJobs))

  #    submit = raw_input("Do you also want to submit the jobs to the batch system? [y/n]")
      submit = 'y'
      if submit == 'y' or submit=='Y':
        submitJobs(jobList,nChunks, outfolder, batchSystem)
      else:
        print "Not submitting jobs"
    
    
    
  
