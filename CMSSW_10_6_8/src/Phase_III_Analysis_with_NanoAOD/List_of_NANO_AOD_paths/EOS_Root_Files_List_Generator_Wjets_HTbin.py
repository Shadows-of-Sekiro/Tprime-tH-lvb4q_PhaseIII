#!/usr/bin/python

import sys
#import datetime
import os

source	 = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/"

SingleTop_Samples = {
'WJets_LNu_HT-70To100_UL17_v2'        :'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/ST_s-channel_4f_leptonDecays/',
'WJets_LNu_HT-100To200_UL17_v2'       :'WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-100To200_v2/',
'WJets_LNu_HT-200To400_UL17_v2'       :'WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-200To400_v2/',
'WJets_LNu_HT-400To600_UL17_v2'       :'WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-400To600_v2/',
'WJets_LNu_HT-600To800_UL17_v2'       :'WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-600To800_v2/',
'WJets_LNu_HT-800To1200_UL17_v2'      :'WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-800To1200_v2/',
'WJets_LNu_HT-1200To2500_UL17_v2'     :'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/WJetsToLNu_HT-1200To2500_v2/',
'WJets_LNu_HT-2500ToInf_UL17_v2'      :'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/ST_tW_antitop_5f_inclusiveDecays/',

}
  


listofSamples = [
# 'WJets_LNu_HT-70To100_UL17_v2' ,
'WJets_LNu_HT-100To200_UL17_v2'  ,
'WJets_LNu_HT-200To400_UL17_v2'  ,
'WJets_LNu_HT-400To600_UL17_v2'  ,
'WJets_LNu_HT-600To800_UL17_v2'  ,
'WJets_LNu_HT-800To1200_UL17_v2' ,
'WJets_LNu_HT-1200To2500_UL17_v2',
# 'WJets_LNu_HT-2500ToInf_UL17_v2' ,

]

#listofSamples.reverse()
os.system ("rm WJets_LNu_HT*v2.txt")

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

