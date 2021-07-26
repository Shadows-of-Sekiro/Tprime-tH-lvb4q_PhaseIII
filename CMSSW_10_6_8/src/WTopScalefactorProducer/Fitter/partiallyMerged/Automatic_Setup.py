
#! /usr/bin/env python
import os
import glob
import math
import array
import ROOT
import ntpath
import sys
import subprocess

from optparse import OptionParser
from subprocess import Popen
from ROOT import gROOT, gStyle, gSystem, TLatex

parser = OptionParser()
parser.add_option('--clean', action='store_true', dest='vclean', default=False, help='Clean all the .so files')

(options, args) = parser.parse_args()

if __name__ == "__main__":
 
  ROOT.gSystem.AddIncludePath("-I$ROOFITSYS/include");
  inPath = os.getenv("PWD")
  os.chdir(inPath+"/PDFs");
  ROOT.gROOT.ProcessLine(".L HWWLVJRooPdfs.cxx+");
  ROOT.gSystem.Load("HWWLVJRooPdfs_cxx.so");
