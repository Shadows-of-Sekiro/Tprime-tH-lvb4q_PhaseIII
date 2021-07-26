#! /usr/bin/env python

import os, sys
import ROOT as rt
# import optparse

def drawTH1(tree,var,weight,bins,min,max,titlex = "",titley = "",units = "",drawStyle = "HIST",lumi="1."):
	h = rt.TH1D("tmpTH1","",bins,min,max)
	h.Sumw2()
	if units=="":
	    h.GetXaxis().SetTitle(titlex)
	    h.GetYaxis().SetTitle(titley)
	else:
	    h.GetXaxis().SetTitle(titlex+ " ("+units+")")
	    h.GetYaxis().SetTitle(titley)

	tree.Draw(var+">>tmpTH1","("+weight+")","goff")
	return h
  
def getGenEv (infilename,verbose="True"):
  file = rt.TFile(infilename, 'READ')
  tree = file.Get('Events')
#  event = tree.GetEntry(0)
#  try:
#    LHEScaleSumw = tree.LHEScaleSumw[0]
#    LHEScale = "LHEScaleSumw[0]"
#  except:
#    LHEScaleSumw = 1
#    LHEScale = "1."
#  print "LHEScale is %s = %f " %(LHEScale,LHEScaleSumw)
#  h  =  drawTH1(tree,"genEventSumw","%s"%LHEScale,1,0,0)
#  genEV = h.GetMean()*h.GetEntries()
#  if verbose: print "File = %s   gen events = %i" %(infilename,genEV)

  h  =  drawTH1(tree,"lheweight","1",3,-1.5,1.5)
  genEV = h.GetMean()*h.GetEntries()
  return genEV

# if __name__ == "__main__":
#
#   usage = 'usage: %prog [options]'
#   parser = optparse.OptionParser(usage)
#   parser.add_option('-i', '--input', action='store', type='string', dest='origin', default='/scratch/thaarres/NANO_21march/')
#   parser.add_option('-v', '--verbose', action='store_true', dest='verbose', default=False)
#
#   (options, args) = parser.parse_args()
#
#   origin        = options.origin
#   verboseout    = options.verbose
#
#
#   map ={}
#   for d in os.listdir(origin):
#       if not 'root' in d: continue
#       if 'Muon' in d: continue
#       print "Working on file " ,d
#       infilename,genEV = getGenEv(d, verboseout)
#       map[infilename]=genEV
#   for key, value in map.iteritems():
#     print "file  = " , key
#     print "value = ", value;print ""
#   print '\nDone.'
#


