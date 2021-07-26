#! /usr/bin/env python

import os, multiprocessing, math
from array import array
from ROOT import TFile, TObject, TH1, TH1D, TF1, TLorentzVector
from WTopScalefactorProducer.Skimmer.xsec import getXsec, getSF, getLumi

import optparse
usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('-i', '--input', action='store', type='string', dest='origin', default='/scratch/zucchett/Ntuple/WSF/')
parser.add_option('-f', '--filter', action='store', type='string', dest='filter', default='')
parser.add_option('-s', '--single', action='store_true', dest='single', default=False)
parser.add_option('-v', '--verbose', action='store_true', dest='verbose', default=False)

(options, args) = parser.parse_args()

origin      = options.origin
filterset   = options.filter
singlecore  = options.single
verboseout  = options.verbose

LUMI = 59970.

if not os.path.exists(origin):
    print 'Origin directory', origin, 'does not exist, aborting...'
    exit()


##############################

def processFile(sample_name, verbose=False):
    sample = sample_name.replace(".root", "")
    isMC = not '201' in sample

    
    # Unweighted input
#    treeFile_name = origin + '/' + sample_name
#    if not os.path.exists(treeFile_name): 
#        print '  WARNING: file', treeFile_name, 'does not exist, continuing'
#        return True
    
    # Weighted output
    treeFile_name = origin + '/' + sample + '.root'
    #if os.path.exists(treeFile_name):
    #    print '  WARNING: weighted file exists, overwriting'
        #return True
    
    # Open file
    treeFile = TFile(treeFile_name, 'UPDATE')
    treeFile.cd()

    if isMC:
        # number of events
        runTree = treeFile.Get('Runs')

        genH = TH1D("genH_%s" % sample, "", 1, 0, 0)
        genH.Sumw2()
        #runTree.Draw("genEventSumw>>genH_%s" % sample, "", "goff")
        runTree.Draw("genEventCount>>genH_%s" % sample, "", "goff")
        genEv = genH.GetMean()*genH.GetEntries()
        
        # Cross section
        XS = getXsec(sample)
        #SF = getSF(sample)
        
        Leq = LUMI*XS/genEv if genEv > 0 else 0.

    else: Leq = 1.
    
    print sample, ": Leq =", Leq
    
    # Variables declaration
    eventweightlumi = array('f', [1.0])  # global event weight with lumi
    
    # Looping over file content
    # Tree
    tree = treeFile.Get('Events')
    nev = tree.GetEntriesFast()
    
    # New branches
    eventweightlumiBranch = tree.Branch('eventweightlumi', eventweightlumi, 'eventweightlumi/F')

    # looping over events
    for event in range(0, tree.GetEntries()):
        if verbose and (event%10000==0 or event==nev-1): print ' = TTree:', tree.GetName(), 'events:', nev, '\t', int(100*float(event+1)/float(nev)), '%\r',
        #print '.',#*int(20*float(event)/float(nev)),#printProgressBar(event, nev)
        tree.GetEntry(event)
        # Initialize
        eventweightlumi[0] = 1.
        
        # Weights
        if isMC:
            eventweightlumi[0] = Leq * tree.lheweight * tree.btagweight * tree.triggerweight #tree.puweight
        else:
            eventweightlumi[0] = 1.
            
        # Fill the branches
        eventweightlumiBranch.Fill()

    tree.Write("", TObject.kOverwrite)
    if verbose: print ' '
        
    treeFile.Close() 



jobs = []
for d in os.listdir(origin):
    if not '.root' in d: continue
    if len(filterset)>0 and not filterset in d: continue
    
    if singlecore:
        print " -", d
        processFile(d, verboseout)
    else:
        p = multiprocessing.Process(target=processFile, args=(d,verboseout,))
        jobs.append(p)
        p.start()
    #exit()
    
print '\nDone.'

