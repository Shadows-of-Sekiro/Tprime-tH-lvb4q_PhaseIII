#!/Usr-/bin/env python
import os,sys
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import * 

#this takes care of converting the input files from CRAB
from PhysicsTools.NanoAODTools.postprocessing.framework.crabhelper import inputFiles,runsAndLumis
from PhysicsTools.NanoAODTools.WTopScalefactorProducer.Skimmer.TTSkimmer import *


# NOTE : This file is configured to Process MC.
# If you want to process Data then ADD "jsonInput='/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'"
# to the PostProcessor arguement below

# p=PostProcessor(".", inputFiles(),                                                                                          # --> to submit with crab, use this
# p=PostProcessor(".", inputFiles(),
#                  "nFatJet>0&&FatJet_msoftdrop>30&&FatJet_pt>200&&MET_sumEt>40&& ( (nElectron > 0 && HLT_Ele115_CaloIdVT_GsfTrkIdT) || (nMuon > 0 && HLT_Mu50))" ,"keep_and_drop.txt",
#                   modules=[TTbar_SemiLep()],provenance=True,fwkJobReport=True
#                   ,haddFileName=  '94XNanoV0-TTbar_SemiLep.root'  )
p=PostProcessor(".", inputFiles(),
                 "nFatJet>0&&FatJet_msoftdrop>30&&FatJet_pt>200&&MET_sumEt>40&&nMuon>0&&HLT_Mu50" ,"keep_and_drop.txt",
                  modules=[TTbar_SemiLep()],provenance=True,fwkJobReport=True 
                  ,haddFileName=  '94XNanoV0-TTbar_SemiLep.root'  )

p.run()

print "DONE"
