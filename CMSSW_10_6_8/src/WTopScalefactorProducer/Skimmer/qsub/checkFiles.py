#!/usr/bin/env python
import os, glob, sys
from commands import getoutput
import re
import ROOT

pattern = "Wprime"
if len(sys.argv) > 1: pattern = sys.argv[1]
delFiles  = True if '-d' in sys.argv else False
isVerbose = True if '-v' in sys.argv else False


nFiles = 0
nGoods = 0
nFails = 0

filelist = glob.glob(pattern+'*.root')

for file in filelist:
  nFiles += 1
  f = ROOT.TFile(file, "read")
  if not f.GetListOfKeys().Contains("Runs"):
  # if not f.GetListOfKeys().Contains("tree"):
      nFails += 1
      cmd = 'rm %s' %file
      if isVerbose: print "FILE IS BUGGY. WILL REMOVE!"
      if isVerbose: print "Remember to resubmit %s" %(pattern)
      
      if isVerbose: print 'Going to execute: ' , cmd
      if delFiles: os.system(cmd)
      
          
  else:
    nGoods += 1
    if isVerbose: print "FILE IS GOOD, KEEPING IT"
    continue

print "Results for", pattern, ":", nFails, "/", nFiles, "failed,", nGoods, "/", nFiles, "are valid"

