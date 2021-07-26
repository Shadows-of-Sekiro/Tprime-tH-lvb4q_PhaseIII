
#!/Usr-/bin/env python
import os,sys
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from importlib import import_module
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor


from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis
#from Analysis.QJetMass.skimmers.ZPlusJet_SkimNANO import *
from PhysicsTools.NanoAODJMARTools.postprocessing.modules.skimmers.JetPlusStuff_SkimNANO import *


### Get the name of the input file and decide if it is 80XMC , 94X MC , data 2016 or 2017
is80XMC = False
is94XMC = False
is2016Data = False
is2017Data = False
print "Analyzing filename for keywords....."
nameis = str(inputFiles()[0].split('/')[8])
print nameis
if ('SingleMuon' in nameis) or ('SingleElectron' in nameis) : 
    nameis = str(inputFiles()[0].split('/')[8])
    if 'Run2016' in nameis : is2016Data = True
    if 'Run2017' in nameis : is2017Data = True 
else :
    #if len(inputFiles()[0].split('/')[7]) > 100 : nameis = str(inputFiles()[0].split('/')[7][:-10])
    if '16MiniAOD' in str(inputFiles()[0].split('/')[8]) : is80XMC = True
    if '17MiniAOD' in str(inputFiles()[0].split('/')[8]) : is94XMC = True

print "NAMEISSSSS"
print  nameis 

problemS = False
if len(nameis) < 5  : problemS = True


p1=PostProcessor(".",inputFiles() ,"FatJet_pt>170&& (     (nElectron > 0  )    ||   (nMuon > 0  ) ) ","keep_and_drop.txt",[JetPlusStuff_SkimNANO()],provenance=True,fwkJobReport=True,histFileName='nanoskim-histos.root', histDirName='zjets', haddFileName = 'nanoskim-trees.root')








if not problemS : p1.run()

print "DONE"
