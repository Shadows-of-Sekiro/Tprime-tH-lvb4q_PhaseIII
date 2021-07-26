#!/usr/bin/env python
import os, glob, sys
from commands import getoutput
import re
import ROOT

pattern = "Wprime"
if len(sys.argv) > 1: pattern = sys.argv[1]
isVerbose = True if '-v' in sys.argv else False
isResubmit = True if '-r' in sys.argv else False
isDelete = True if '-d' in sys.argv else False

nTotalFiles = 0
nTotalGoods = 0
nTotalFails = 0


for sample in os.listdir(pattern):
    if isVerbose: print "Now checking", sample

    nFiles = 0
    nGoods = 0
    nFails = 0

    jobName = sample #pattern.split('/')[1]
    resubFile = "resublist"+jobName+".txt"
    
    if os.path.isfile(resubFile): os.system("rm "+resubFile)
    
    filelist = glob.glob(pattern+'/'+jobName+'/*.root')
    # filelist = glob.glob('/scratch/thaarres/SUBSTRUCTURE/LOLAoutput/*.root')
    
    for file in filelist:
      nFiles += 1
      f = ROOT.TFile(file, "read")
      if not f.GetListOfKeys().Contains("Runs"):
      # if not f.GetListOfKeys().Contains("tree"):
          nFails += 1
          cmd = 'rm %s' %file
          if isVerbose: print "FILE IS BUGGY. WILL REMOVE!"
          if isVerbose: print "Remember to resubmit %s" %(sample)
          
          if isVerbose: print 'Going to execute: ' , cmd
          if isResubmit or isDelete: os.system(cmd)
          if isResubmit:
              jobs = open("joblist"+jobName+".txt", "r").read().splitlines()
              jobFailed = [x for x in jobs if file.split('/')[2].split('_')[0] in x][0]
              if len(jobFailed) > 0:
                  with open(resubFile, "a") as f:
                      f.write(jobFailed+"\n")
                  
              
      else:
        nGoods += 1
        #if isVerbose: print "FILE IS GOOD, KEEPING IT"
        continue

    if isResubmit and nFails > 0:
        subCmd = 'qsub -q %s -t 1-%d -o %s/logs/ %s %s' %("all.q",nFails,pattern+"/"+jobName,'psibatch_runner.sh',resubFile)
        if isVerbose: print 'Going to execute: ' , subCmd
        os.system(subCmd)

    if isVerbose: print "In", jobName, "valid roofiles:", nGoods, "/", nFiles, ", failed:", nFails, "/", nFiles

    nTotalFiles += nFiles
    nTotalGoods += nGoods
    nTotalFails += nFails

print "In summary, valid roofiles:", nTotalGoods, "/", nTotalFiles, ", failed:", nTotalFails, "/", nTotalFiles
