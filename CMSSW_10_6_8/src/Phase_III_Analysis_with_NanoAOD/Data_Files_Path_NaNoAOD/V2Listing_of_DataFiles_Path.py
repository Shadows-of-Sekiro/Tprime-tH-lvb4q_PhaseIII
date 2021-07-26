#!/usr/bin/python

import sys
#import datetime
import os


SingleLepton_Samples = {
# 'EraB_Muon'         :'SingleMuon/EraB/210302_133004/',
# 'EraD_Muon'         :'SingleMuon/EraD/210302_132910/',
# 'EraE_Muon'         :'SingleMuon/EraE/210302_132743/',
# 'EraF_Muon'         :'SingleMuon/EraF/210302_132425/',
# 'EraB_Electron'     :'SingleElectron/EraB_Ele/210302_133609/',
# 'EraC_Electron'     :'SingleElectron/EraC_Ele/210302_133506/',
# 'EraD_Electron'     :'SingleElectron/EraD_Ele/210302_133346/',
# 'EraE_Electron'     :'SingleElectron/EraE_Ele/210302_133236/',
# 'EraF_Electron'     :'SingleElectron/EraF_Ele/210302_133122/',
}


SingleLepton_Samples = {
'EraB_Muon'         :'SingleMuon/EraB/210326_124829/',
'EraD_Muon'         :'SingleMuon/EraD/210326_124728/',
'EraE_Muon'         :'SingleMuon/EraE/210326_124630/',
'EraF_Muon'         :'SingleMuon/EraF/210326_124529/',
'EraB_Electron'     :'SingleElectron/EraB_Ele/210326_133732/',
'EraC_Electron'     :'SingleElectron/EraC_Ele/210326_133632/',
'EraD_Electron'     :'SingleElectron/EraD_Ele/210326_133533/',
'EraE_Electron'     :'SingleElectron/EraE_Ele/210326_133434/',
'EraF_Electron'     :'SingleElectron/EraF_Ele/210326_133333/',
}


listofSamples = [
'EraB_Muon',
'EraD_Muon',
'EraE_Muon',
'EraF_Muon',
'EraB_Electron' ,
'EraC_Electron' ,
'EraD_Electron' ,
'EraE_Electron' ,
'EraF_Electron' ,
]

#listofSamples.reverse()
os.system ("rm *.txt")

for sample in listofSamples:
	
    source  = "/eos/user/a/achhetri/Data_UltraLegacy_NanoAOD/" + SingleLepton_Samples[sample]
    textfileNumber = 0
    for root, dirs, filenames in os.walk(source):
    	#print "a: ",root,"\t",dirs,"\t",filenames
    	
        rootFileList = []
        fr=open(sample + "_v2.txt", "a")     
        for f in filenames:


          #os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
          #print f
          #print  textfileNumber
          rootFileList.append(f)
          # fr=open(sample.replace(f, f + "_v2.txt"), "a")      

          for rootFile in rootFileList :

           	fr.write(root.replace("/eos/uscms","")+"/"+rootFile+"\n")
          del rootFileList[:]








