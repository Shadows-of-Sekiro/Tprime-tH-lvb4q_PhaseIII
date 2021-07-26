#!/usr/bin/python

import sys
#import datetime
import os

sourceB = "/eos/user/a/achhetri/Data_UltraLegacy_NanoAOD/SingleMuon/EraB/210223_123351/"
sourceD = "/eos/user/a/achhetri/Data_UltraLegacy_NanoAOD/SingleMuon/EraD/210223_133302/"
sourceE = "/eos/user/a/achhetri/Data_UltraLegacy_NanoAOD/SingleMuon/EraE/210223_133205/"
sourceF = "/eos/user/a/achhetri/Data_UltraLegacy_NanoAOD/SingleMuon/EraF/210223_133055/"


textfileNumber = 0
# os.system ("rm New_Data*.txt")
# for root, dirs, filenames in os.walk(sourceB):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraB.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]



# for root, dirs, filenames in os.walk(sourceC):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraC.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]


# for root, dirs, filenames in os.walk(sourceD):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraD.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]


# for root, dirs, filenames in os.walk(sourceE):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraE.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]


# for root, dirs, filenames in os.walk(sourceF):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraF.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]

# for root, dirs, filenames in os.walk(sourceG):
# 	#print "a: ",root,"\t",dirs,"\t",filenames
	
# 		rootFileList = []
# 		for f in filenames:
# 			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
# 			#print f
# 			#print  textfileNumber
# 			rootFileList.append(f)
#        		fr=open("NewData2016Legacy_EraG.txt", "a") 
#        		for rootFile in rootFileList :
#        		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
#        		del rootFileList[:]     



for root, dirs, filenames in os.walk(sourceB):
	#print "a: ",root,"\t",dirs,"\t",filenames
	
		rootFileList = []
		for f in filenames:
			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
			#print f
			#print  textfileNumber
			rootFileList.append(f)
       		fr=open("NewData2016Legacy_EraH.txt", "a") 
       		for rootFile in rootFileList :
       		         	 fr.write("root://cmseos.fnal.gov/"+root.replace("/eos/uscms","")+"/"+rootFile+"\n")
       		del rootFileList[:]       		         		       
