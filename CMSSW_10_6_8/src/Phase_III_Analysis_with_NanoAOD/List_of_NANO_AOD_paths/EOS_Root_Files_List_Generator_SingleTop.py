#!/usr/bin/python

import sys
#import datetime
import os

source	 = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/"

SingleTop_Samples = {
'ST_s-channel_4f_leptonDecays_UL17_v2'                :'ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/ST_s-channel_4f_leptonDecays/',
'ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2'     :'ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/ST_t-channel_antitop_4f_inclusiveDecays/',
'ST_t-channel_top_4f_inclusiveDecays_UL17_v2'         :'ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/ST_t-channel_top_4f_inclusiveDecays/',
'ST_tW_top_5f_inclusiveDecays_UL17_v2'                :'ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/ST_tW_top_5f_inclusiveDecays/',
'ST_tW_antitop_5f_inclusiveDecays_UL17_v2'            :'ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8/ST_tW_antitop_5f_inclusiveDecays/',


}




listofSamples = [
'ST_s-channel_4f_leptonDecays_UL17_v2'              ,  
'ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2'   ,  
'ST_t-channel_top_4f_inclusiveDecays_UL17_v2'       ,  
'ST_tW_top_5f_inclusiveDecays_UL17_v2'              ,  
'ST_tW_antitop_5f_inclusiveDecays_UL17_v2'          ,  


]

#listofSamples.reverse()
os.system ("rm ST_*v2.txt")

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

