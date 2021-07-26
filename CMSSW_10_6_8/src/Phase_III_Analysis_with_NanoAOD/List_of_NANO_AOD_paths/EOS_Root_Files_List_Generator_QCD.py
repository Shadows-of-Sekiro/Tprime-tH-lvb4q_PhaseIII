#!/usr/bin/python

import sys
#import datetime
import os

source	 = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/"

SingleTop_Samples = {
'QCD_Pt-80to120_MuEnr_UL17_v2'      :'QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt80to120_v2/',
'QCD_Pt-120to170_MuEnr_UL17_v2'     :'QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt120to170_v2/',
'QCD_Pt-170to300_MuEnr_UL17_v2'     :'QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt170to300_v2/',
'QCD_Pt-300to470_MuEnr_UL17_v2'     :'QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt300to470_v2/',
'QCD_Pt-470to600_MuEnr_UL17_v2'     :'QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt470to600_v2/',
'QCD_Pt-600to800_MuEnr_UL17_v2'     :'QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt600to800_v2/',
'QCD_Pt-800to1000_MuEnr_UL17_v2'    :'QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt800to1000_v2/',
'QCD_Pt-1000toInf_MuEnr_UL17_v2'    :'QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/QCD_Pt1000toInf_v2/',
'QCD_Pt-50to80_EMEnr_UL17_v2'       :'QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/QCD_Pt50to80_EM_v2/',
'QCD_Pt-80to120_EMEnr_UL17_v2'      :'QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/QCD_Pt80to120_EM_v2/',
'QCD_Pt-120to170_EMEnr_UL17_v2'     :'QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/QCD_Pt120to170_EM_v2/',
'QCD_Pt-170to300_EMEnr_UL17_v2'     :'QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8/QCD_Pt170to300_EM_v2/',
'QCD_Pt-300toInf_EMEnr_UL17_v2'     :'QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/QCD_Pt300toInf_EM_v2/',

}










listofSamples = [
'QCD_Pt-80to120_MuEnr_UL17_v2'  ,  
'QCD_Pt-120to170_MuEnr_UL17_v2' ,  
'QCD_Pt-170to300_MuEnr_UL17_v2' ,  
'QCD_Pt-300to470_MuEnr_UL17_v2' ,  
'QCD_Pt-470to600_MuEnr_UL17_v2' ,  
'QCD_Pt-600to800_MuEnr_UL17_v2' ,  
'QCD_Pt-800to1000_MuEnr_UL17_v2',  
'QCD_Pt-1000toInf_MuEnr_UL17_v2',  
'QCD_Pt-50to80_EMEnr_UL17_v2'   ,  
'QCD_Pt-80to120_EMEnr_UL17_v2'  ,  
'QCD_Pt-120to170_EMEnr_UL17_v2' ,  
'QCD_Pt-170to300_EMEnr_UL17_v2' ,  
'QCD_Pt-300toInf_EMEnr_UL17_v2' ,  
]

#listofSamples.reverse()
os.system ("rm QCD_*v2.txt")

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

