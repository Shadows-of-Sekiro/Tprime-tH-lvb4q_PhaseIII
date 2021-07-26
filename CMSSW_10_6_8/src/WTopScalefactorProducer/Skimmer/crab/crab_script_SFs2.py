#!/Usr-/bin/env python
import os,sys
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis
from PhysicsTools.NanoAODTools.WTopScalefactorProducer.Skimmer.TTbar_SemiLep_fullyMerged  import *


# NOTE : This file is configured to Process MC.
# If you want to process Data then ADD "jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'  "
# to the PostProcessor arguement below

# p=PostProcessor(".", inputFiles(),                                                                                          # --> to submit with crab, use this
loc = './'
infiles = [
'W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8.root',
'W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8.root',
'W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8.root',
'W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8.root',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_1.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_2.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_3.root',
'ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root',
'ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8.root',
'ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8.root',
'ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8.root',
'ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8.root',
'SingleMuon_NANO_Run2017B-17Nov2017-v1.root',
'SingleMuon_NANO_Run2017C-17Nov2017-v1.root',
'SingleMuon_NANO_Run2017D-17Nov2017-v1.root',
'SingleMuon_NANO_Run2017E-17Nov2017-v1.root',
'SingleMuon_NANO_Run2017F-17Nov2017-v1.root',
'SingleMuon_NANO_Run2017H-17Nov2017-v1.root',
'WW_TuneCP5_13TeV-pythia8.root',
'WZ_TuneCP5_13TeV-pythia8.root ',
'ZZ_TuneCP5_13TeV-pythia8.root'
]

for afile in infiles :
    nameis = afile[:-5]
    print nameis
    if 'SingleMuon' not in nameis :
        p=PostProcessor(".", [afile],
    "nFatJet>0&&FatJet_msoftdrop>105&&FatJet_pt>350&&MET_sumEt>40&& ( (nElectron > 0 && HLT_Ele115_CaloIdVT_GsfTrkIdT) || (nMuon > 0 && HLT_Mu50))" ,"keep_and_drop.txt",
    modules=[TTbar_SemiLep_fullyMerged()],provenance=True,fwkJobReport=True ,
    histFileName= 'fullyMerged_'+nameis+'_hists.root', histDirName='ttbar_semilep' , haddFileName= 'fullyMerged_'+nameis+'_hadded.root' , postfix="_fullyMerged"  )
    else : 
        p=PostProcessor(".", [afile],
    "nFatJet>0&&FatJet_msoftdrop>105&&FatJet_pt>350&&MET_sumEt>40&& ( (nElectron > 0 && HLT_Ele115_CaloIdVT_GsfTrkIdT) || (nMuon > 0 && HLT_Mu50))" ,"keep_and_drop.txt",
    modules=[TTbar_SemiLep_fullyMerged()],provenance=True,fwkJobReport=True ,
    histFileName= 'fullyMerged_'+nameis+'_hists.root', histDirName='ttbar_semilep' , haddFileName= 'fullyMerged_'+nameis+'_hadded.root' , postfix="_fullyMerged", jsonInput = 'Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt' )
    p.run()

    print "DONE with {}".format(nameis)
