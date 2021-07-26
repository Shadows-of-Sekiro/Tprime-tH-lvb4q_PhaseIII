#!/usr/bin/python

import sys
#import datetime
import os

source   = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/"

SingleTop_Samples = {
'DYJetsToLL_M-50_HT-70To100_UL17_v2'         :'DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-70to100_v2/',
'DYJetsToLL_M-50_HT-100To200_UL17_v2'        :'DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-100to200_v2/',
'DYJetsToLL_M-50_HT-200To400_UL17_v2'        :'DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-200to400_v2/',
'DYJetsToLL_M-50_HT-400To600_UL17_v2'        :'DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-400to600_v2/',
'DYJetsToLL_M-50_HT-600To800_UL17_v2'        :'DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-600to800_v2/',
'DYJetsToLL_M-50_HT-800To1200_UL17_v2'       :'DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-800to1200_v2/',
'DYJetsToLL_M-50_HT-1200To2500_UL17_v2'      :'DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-1200to2500_v2/',
'DYJetsToLL_M-50_HT-2500ToInf_UL17_v2'       :'DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-2500toInf_v2/',

}




listofSamples = [
'DYJetsToLL_M-50_HT-70To100_UL17_v2' ,
# 'DYJetsToLL_M-50_HT-100To200_UL17_v2' ,
# 'DYJetsToLL_M-50_HT-200To400_UL17_v2' ,
# 'DYJetsToLL_M-50_HT-400To600_UL17_v2' ,
'DYJetsToLL_M-50_HT-600To800_UL17_v2' ,
# 'DYJetsToLL_M-50_HT-800To1200_UL17_v2' ,
# 'DYJetsToLL_M-50_HT-1200To2500_UL17_v2' ,
'DYJetsToLL_M-50_HT-2500ToInf_UL17_v2' ,

]

#listofSamples.reverse()
os.system ("rm DYJetsToLL_M-50_HT*v2.txt")

for sample in listofSamples:
  
    source_ST  = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/" + SingleTop_Samples[sample]
    textfileNumber = 0
    for root, dirs, filenames in os.walk(source_ST):
      #print "a: ",root,"\t",dirs,"\t",filenames
      
        rootFileList = []
        for f in filenames:


          #os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
          #print f
          #print  textfileNumber
          rootFileList.append(f)
          fr=open(sample.replace("_v2","_v2.txt"), "a") 

          for rootFile in rootFileList :

            fr.write(root.replace("/eos/uscms","")+"/"+rootFile+"\n")
          del rootFileList[:]

