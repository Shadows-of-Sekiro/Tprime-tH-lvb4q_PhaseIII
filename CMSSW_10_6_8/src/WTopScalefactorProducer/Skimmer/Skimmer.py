import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection,Object
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import *
from WTopScalefactorProducer.Skimmer.PileupWeightTool import *
from WTopScalefactorProducer.Skimmer.variables import recoverNeutrinoPz

import math
import random
import array


# This is a loose selection to select events for T Tbar semileptonic events where 
# Type 1 and Type 2 events are included in the selection:

# In SF code the final cuts need to be made to choose either type 1 or type 2 selection:
# e.g. for type 1 the W leptonic Pt cut should be tightened to 200 GeV and dPhi cuts applied
# e.g. for type 2 the AK8 Pt cut should be tightened to 400 GeV and dPhi cuts applied

# Type 1 - martially merged Hadronic Top Quark (W is AK8, b is AK4) 
#(AK8 Pt > 200 GeV)

# Type 2 - fully merged Top (Top is AK8, W is most massive SD subjet, b is less massive subjet, require 1 subjet b-tag) 
#(AK8 Pt > 400 GeV): 


# selection aligned with previous SF measurement standard selection
# https://www.evernote.com/shard/s282/sh/7e5d6baa-d100-4025-8bf8-a61bf1adfbc1/f7e86fde2c2a165e


# 1 AK8 Pt > 200 GeV, |eta| < 2.5 , dR(Ak8, lep) > 1.0
# 1 AK4 Pt > 30 GeV, |eta| < 2.5
# 1 lepton , mu pt > 53 GeV or el pt > 120 GeV
# MET Pt > 40(mu) or 80(el) GeV
#Leptonic W - lepton + MET has Pt > 150 GeV # did not apply this since we are missing MET eta
         
class Skimmer(Module):
    def __init__(self, Channel):
        self.chan = Channel
        self.writeHistFile = True
        self.verbose = False
    def beginJob(self, histFile, histDirName):
        Module.beginJob(self, histFile, histDirName)
        # self.addObject( ROOT.TH1F('nGenEv',   'nGenEv',   3, 0, 3) )
        # self.minMupt = 55.
        # self.maxMuEta = 2.4
        # self.maxRelIso = 0.15
        # self.minMuMETPt = 0.

        # #remove  AK8 jet within 1.0 of lepton
        # self.mindRLepJet = 1.0 
       
        # self.minElpt = 120.
        # self.minElMETPt = 80.
     
        # self.minLepWPt = 150.

        # self.minJetPt = 200.
        # self.maxJetEta = 2.5
        
        # self.minWPt = 150.

        # self.minBDisc = 0.8484
        # ### Medium https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation80XReReco

        # #>= 1 CSVmedium akt4 jet
        # self.minAK4Pt = 30.

        #Angular selection (to be implemented later, in fitting code):
        #dR( lepton, leading AK8 jet) > pi/2
        #dPhi(leading AK8 jet, MET) > 2
        #dPhi (leading AK8 jet, leptonic W) >2
        #self.minDPhiWJet = 2.  
        
        self.puWeightTool = PileupWeightTool(yearMC=2017, yearData=2017) #FIXME

        self.nEvent = 0

        
    def endJob(self):
        Module.endJob(self)
        print "Module ended successfully,", self.nEvent, "events analyzed"
        pass
        
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
         self.out = wrappedOutputTree
         # self.out.branch("SelectedJet_softDrop_mass",  "F")
         # self.out.branch("SelectedJet_tau42",  "F")
         # self.out.branch("SelectedJet_tau41",  "F")
         # self.out.branch("SelectedJet_tau32",  "F")
         # self.out.branch("SelectedJet_tau21",  "F")
         # self.out.branch("SelectedJet_tau21_ddt",  "F")
         # self.out.branch("SelectedJet_tau21_ddt_retune",  "F")      
         # self.out.branch("SelectedJet_pt",   "F")
         # self.out.branch("SelectedJet_eta",  "F")
         # self.out.branch("SelectedJet_mass", "F")
         # self.out.branch("SelectedLepton_pt",  "F")
         # self.out.branch("SelectedLepton_iso",  "F")
         # self.out.branch("Wlep_type",  "I")
         # self.out.branch("W_pt",  "F")
         # self.out.branch("W_mass",  "F")
         # self.out.branch("dr_LepJet",  "F")
         # self.out.branch("dphi_LepJet",  "F")
         # self.out.branch("dphi_LepMet",  "F")
         # self.out.branch("dphi_MetJet",  "F")
         # self.out.branch("dphi_WJet"  ,  "F")
         # self.out.branch("maxAK4CSV",  "F")
         # self.out.branch("subMaxAK4CSV",  "F")
         # self.out.branch("minJetMetDPhi",  "F")
         # self.out.branch("HT_HEM1516",  "F")
         # self.out.branch("genmatchedAK8",  "I")
         # self.out.branch("genmatchedAK8Quarks",  "I")
         # self.out.branch("genmatchedAK8Subjet",  "I")
         # self.out.branch("AK8Subjet0isMoreMassive",  "I")
         # self.out.branch("passedMETfilters",  "I")
         # self.out.branch("lheweight",  "F")
         # self.out.branch("puweight",  "F")
         # self.out.branch("topweight",  "F")
         # self.out.branch("btagweight",  "F")
         # self.out.branch("triggerweight",  "F")

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        print "File closed successfully"
        pass

    def getSimplifiedElectronTriggerSF2018(self, pt, eta):
        # /work/pbaertsc/heavy_resonance/NanoTreeProducer/CorrectionTools/leptonEfficiencies/ElectronPOG/Run2018/Ele115orEle35_SF_2018.root
        # Ratio ELE_DATA and ELE_MC
        if pt < 120:
            if eta > -0.9: return 0.97
            else: return 0.90
        elif pt > 500 and abs(eta) > 0.9 and abs(eta) < 1.7: return 0.95
        else: return 0.98

    def getSimplifiedMuonTriggerSF2018(self, pt, eta):
        # https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018_trigger/theJSONfile_2018Data_AfterMuonHLTUpdate.json
        # "Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins"
        if pt < 200: #"pt:[120.0,200.0]"
            if abs(eta) > 2.1: return 0.85
            else: return 0.93
        else: #"pt:[300.0,1200.0]"
            if abs(eta) > 2.1: return 0.82
            else: return 0.89

    def getSubjets(self, p4, subjets, dRmax=0.8):
        ret = []
        for subjet in subjets :
            if p4.DeltaR(subjet.p4()) < dRmax and len(ret) < 2 :
                ret.append(subjet.p4())
        return ret

    def printP4( self, c ):
        if hasattr( c, "p4"):
            s = ' %6.2f %5.2f %5.2f %6.2f ' % ( c.p4().Perp(), c.p4().Eta(), c.p4().Phi(), c.p4().M() )
        else :
            s = ' %6.2f %5.2f %5.2f %6.2f ' % ( c.Perp(), c.Eta(), c.Phi(), c.M() )
        return s
 
    def printCollection(self,coll):
        for ic,c in enumerate(coll):
            s = self.printP4( c )
            print ' %3d : %s' % ( ic, s )
            
    def analyze(self, event):
        """process event, return True (go to next module) or False (fail, go to next event)"""

        # puweight = 1.
        # lheweight = 1.
        # topweight = 1.
        # btagweight = 1.
        # triggerweight = 1.

        isMC = (event.run == 1)

        """Earlier setup of JETMET group as in doSkim.py"""

#         # Preselections: HLT_Mu50&&nMuon>0&&Muon_pt[0]>55.&&fabs(Muon_eta[0])<2.4&&Muon_highPtId[0]>=2&&Muon_isPFcand[0]==1&&Muon_pfIsoId[0]>=4&&nFatJet>0&&FatJet_pt[0]>200&&fabs(FatJet_eta[0])<2.5
#         if not (event.HLT_Mu50 or (event.HLT_Ele32_WPTight_Gsf or event.HLT_Ele35_WPTight_Gsf or event.HLT_Ele40_WPTight_Gsf or event.HLT_Ele115_CaloIdVT_GsfTrkIdT)): return False
#         if not (event.nMuon > 0 or event.nElectron > 0): return False 
#         if not event.nFatJet > 0: return False                                  #?

        
#         # Find high-pT lepton, veto additional leptons, check trigger
#         allmuons = Collection(event, "Muon")
#         allelectrons = Collection(event, "Electron")

#         # Here we make some loose selections for each category 
#         electrons = [x for x in allelectrons if x.pt > 10. and x.cutBased >= 2 and ( abs(x.eta) < 1.44 or ( abs(x.eta) > 1.56 and abs(x.eta) < 2.5 ) )] #loose pt cut for veto 
#         muons     = [x for x in allmuons if x.pt > 10. and x.looseId and abs(x.eta) < self.maxMuEta and x.pfIsoId >= 2] #loose pt cut for veto
        
#         # Ordening the loosely selected categories according to Pt 
#         muons.sort(key=lambda x:x.pt,reverse=True)
#         electrons.sort(key=lambda x:x.pt,reverse=True)

#         # Check if the muon or electron with highest Pt passes the tight selection (additional cuts to the loose selection)
#         electronTight = len(electrons) > 0 and electrons[0].pt > 55. and electrons[0].cutBased >= 4  #and abs(electrons[0].eta) < 2.5 and not (abs(electrons[0].eta) > 1.44 and abs(electrons[0].eta) < 1.56)
#         muonTight = len(muons) > 0 and muons[0].pt > 55. and abs(muons[0].eta) < self.maxMuEta and muons[0].highPtId >= 2 and muons[0].isPFcand and muons[0].pfIsoId >= 6


#         possibleChannels = ["mu", "el", "elmu"]

#         if self.chan not in possibleChannels : 
#           print "Channel not defined! Skipping"
#           print "Please select a channel in the following: "
#           print possibleChannels
#           return False

        
#         # We require one and only one tight muon and no electron (loose) or one and only one tight electron and no (loose) muon 
#         self.Vlep_type = -1
#         lepton = ROOT.TLorentzVector()
#         iso = 0.

#         if ("mu" in self.chan and muonTight and (len(muons) == 1) and (len(electrons) == 0)) :  # There is one tight muon and no other loose electron or muon 
#           triggerMu = event.HLT_Mu50
#           triggerEl = 0
#           #if not triggerMu: return False
#           self.Vlep_type = 0
#           lepton = muons[0].p4()
#           iso = muons[0].pfRelIso03_all
#           if isMC: triggerweight = self.getSimplifiedMuonTriggerSF2018(muons[0].pt, muons[0].eta)

#         elif ("el" in self.chan and electronTight and (len(electrons) == 1) and (len(muons) == 0)) :  # There is a tight electron and no other loose muon or electron
#           triggerEl = (event.HLT_Ele32_WPTight_Gsf or event.HLT_Ele35_WPTight_Gsf or event.HLT_Ele40_WPTight_Gsf or event.HLT_Ele115_CaloIdVT_GsfTrkIdT)
#           triggerMu = 0
#           #if not triggerEl: return False
#           self.Vlep_type = 1
#           lepton = electrons[0].p4()
#           iso = electrons[0].pfRelIso03_all
#           if isMC: triggerweight = self.getSimplifiedElectronTriggerSF2018(electrons[0].pt, electrons[0].eta)

#         else : 
#           return False 


#         passedMETFilters = False
#         try:
#           if event.Flag_goodVertices and event.Flag_globalSuperTightHalo2016Filter and event.Flag_BadPFMuonFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and (isMC or event.Flag_eeBadScFilter) and event.Flag_ecalBadCalibFilterV2:
#             passedMETFilters = True
#         except:
#            passedMETFilters = False
#           # if not passedMETFilters: return False

#         if not passedMETFilters: return False
        
#         # Apply MET cut    
#         met = Object(event, "MET")
# #        if self.Vlep_type == 0 and met.sumEt < self.minMuMETPt : return False
# #        if self.Vlep_type == 1 and met.sumEt < self.minElMETPt : return False
#         MET  = ROOT.TLorentzVector()
#         MET.SetPtEtaPhiE(met.pt, 0., met.phi, met.pt)
        
#         # Apply leptonic W cut
#         WcandLep = lepton + MET
#         # if WcandLep.Perp() < self.minLepWPt :
#         #     return False

#         pz = recoverNeutrinoPz(lepton, MET)
#         neutrino  = ROOT.TLorentzVector()
#         neutrino.SetPxPyPzE(MET.Px(), MET.Py(), pz, math.sqrt(MET.Px()**2 + MET.Py()**2 + pz**2))
#         WcandLep = lepton + neutrino
        
#         if not WcandLep.Pt() >= self.minWPt: return False
        
#         # Find fat jet
#         FatJets = list(Collection(event, "FatJet"))
#         recoAK8 = [ x for x in FatJets ] # if x.p4().Perp() > self.minJetPt and  abs(x.p4().Eta()) < self.maxJetEta and x.msoftdrop > 30. and x.tau1 > 0. and x.tau2 > 0.]
# #        recoAK8.sort(key=lambda x:x.msoftdrop,reverse=True)
#         recoAK8.sort(key=lambda x:x.pt,reverse=True)
#         if not len(recoAK8) > 0 or not recoAK8[0].pt > 200. or not abs(recoAK8[0].eta) < 2.5: return False

#         jetAK8_4v = ROOT.TLorentzVector()
#         #jetAK8_4v.SetPtEtaPhiM(recoAK8[0].pt,recoAK8[0].eta,recoAK8[0].phi,recoAK8[0].mass)
#         jetAK8_4v.SetPtEtaPhiM(recoAK8[0].pt,recoAK8[0].eta,recoAK8[0].phi,recoAK8[0].mass)
        
        
#         #Check for additional b-jet in the event, apply CSV later!
#         Jets = list(Collection(event, "Jet")) 
#         recoAK4 = [ x for x in Jets if x.p4().Perp() > self.minAK4Pt and abs(x.p4().Eta()) < self.maxJetEta and jetAK8_4v.DeltaR(x.p4())>1.0] #x.btagCSVV2 > self.minBDisc
# #        if len(recoAK4) < 1: return False
        
#         # max and second max AK4 CSV
#         bTagValues = [ x.btagCSVV2 for x in recoAK4]
#         maxAK4CSV = -1.
#         subMaxAK4CSV = -1.

#         if len(bTagValues) >= 1 : 
#           maxAK4CSV = max(bTagValues)

#         if len(bTagValues) >= 2 : 
#           bTagValues.remove(maxAK4CSV)
#           subMaxAK4CSV = max(bTagValues) # max([ x.btagCSVV2 for x in [z for z in recoAK4 if z != maxAK4CSV]])
          
        
#         minJetMetDPhi = min([ abs(x.p4().DeltaPhi(MET)) for x in recoAK4]) if len(recoAK4) >= 1 else -1.
        
#         # No lepton overlap
#         dR_jetlep = jetAK8_4v.DeltaR(lepton )
#         if abs(dR_jetlep) < self.mindRLepJet : return False

#         # Angular separation cuts
#         if not dR_jetlep > 1.5708: return False
#         if not abs(jetAK8_4v.DeltaPhi(MET)) > 1.5708: return False
        
#         HT_HEM1516 = 0.
#         for j in Jets:
#             if j.eta > -3.0 and j.eta < -1.3 and j.phi > -1.57 and j.phi < -0.87:
#                 HT_HEM1516 += j.pt

#         # Gen
#         self.isW = 0
#         self.isWqq = 0
#         self.matchedJ = 0
#         self.matchedSJ = 0
        
#         if isMC:
#             try:
#                 if event.LHEWeight_originalXWGTUP < 0.: lheweight = -1.
#             except:
#                 pass
#             puweight = self.puWeightTool.getWeight(event.Pileup_nTrueInt)
#             btagweight = event.btagWeight_CSVV2 if not event.btagWeight_CSVV2==0 else 1.
            
#             ### Look at generator level particles
#             ### find events where :
#             ### a W decays to quarks (Type 1 - partially merged)
#             ###    OR
#             ### a Top decays to W + b (Type 2 - fully merged top quark)
#             gens = Collection(event, "GenPart")
#             Wdaus =  [x for x in gens if x.pt>1 and 0<abs(x.pdgId)<9]
#             Wmoms =  [x for x in gens if x.pt>10 and abs(x.pdgId)==24]

#             TWdaus =  [x for x in gens if x.pt>1 and  0<abs(x.pdgId)<4]
#             Tdaus =  [x for x in gens if x.pt>1 and (abs(x.pdgId)==5  or  abs(x.pdgId)==24 )]
#             Tmoms =  [x for x in gens if x.pt>1 and abs(x.pdgId)==6]
#             Top =  [x for x in gens if x.pdgId==6]
#             AntiTop =  [x for x in gens if x.pdgId==-6]
            
#             realVs = []
#             realVdaus = []

#             realTs = []
#             realWs = []
#             realqs = []
#             self.matchedJ = 0
#             self.matchedSJ = 0

#             if len(Wmoms)>0 and len(Wdaus)>0:
#               for dau in Wdaus:
#                 for mom in Wmoms:
#                   try:
#                     if mom == Wmoms[dau.genPartIdxMother]: 
#                       realVs.append(mom)
#                       realVdaus.append(dau)    
#                   except:
#                     continue    

#             if len(Tmoms)>0 and len(Tdaus)>0:
#               for gdau in TWdaus :
#                 for dau in Tdaus:
#                   for mom in Tmoms:
#                     try:
#                       if mom == Tmoms[dau.genPartIdxMother] and dau == Tdaus[gdau.genPartIdxMother]: 
#                         realTs.append(mom)
#                         realWs.append(dau)
#                         realqs.append(gdau)    
#                     except:
#                       continue  
            
#             if len(Top)>0 and len(AntiTop)>0:
#                 topSF = math.exp(0.0615 - 0.0005 * Top[0].pt)
#                 antitopSF = math.exp(0.0615 - 0.0005 * AntiTop[0].pt)
#                 topweight = math.sqrt(topSF*antitopSF)
                
        
#         # Check if matched to genW and genW daughters
#         #for partially merged:
#         self.isW = 0
#         self.isWqq = 0
#         if isMC == False:
#             genjets = [None] * len(recoAK8)

#         else :
#           # simple gen matching
#           for V in Wmoms:
#             gen_4v = ROOT.TLorentzVector()
#             gen_4v.SetPtEtaPhiM(V.pt,V.eta,V.phi,V.mass)
#             dR = jetAK8_4v.DeltaR(gen_4v)
#             if dR < 0.8: self.isW = 1

          
#           # standard gen matching
#           for V in realVs:
#             gen_4v = ROOT.TLorentzVector()
#             gen_4v.SetPtEtaPhiM(V.pt,V.eta,V.phi,V.mass)
#             dR = jetAK8_4v.DeltaR(gen_4v)
#             if dR < 0.8: 
#               nDau = 0
#               for v in realVdaus:
#                 gen_4v = ROOT.TLorentzVector()
#                 gen_4v.SetPtEtaPhiM(v.pt,v.eta,v.phi,v.mass)
#                 dR = jetAK8_4v.DeltaR(gen_4v)
#                 if dR < 0.8: 
#                   nDau +=1                 
#                   self.isWqq = 1

       
#         #for fully merged:
#         self.SJ0isW = -1
#         # List of reco subjets:
#         recosubjets = list(Collection(event,"SubJet"))
#         # Dictionary to hold ungroomed-->groomed for reco
#         recoAK8Groomed = {}        
#         # Get the groomed reco jets
#         maxrecoSJmass = 1.
#         WHadreco = None
#         for ireco,reco in enumerate(recoAK8):
#             if reco.subJetIdx2 >= len(recosubjets) or reco.subJetIdx1 >= len(recosubjets) :
#                 if self.verbose: print "Reco subjet indices not in Subjet list, Skipping"
#                 continue
#             if reco.subJetIdx1 >= 0 and reco.subJetIdx2 >= 0 :
#                 recoAK8Groomed[reco] = recosubjets[reco.subJetIdx1].p4() + recosubjets[reco.subJetIdx2].p4()
#                 if recosubjets[reco.subJetIdx1].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx1].p4().M() >  recosubjets[reco.subJetIdx2].p4().M() :
#                     maxrecoSJmass = recosubjets[reco.subJetIdx1].p4().M()
#                     WHadreco = recosubjets[reco.subJetIdx1].p4()
#                     if recosubjets[reco.subJetIdx1].btagCSVV2 >  self.minBDisc  or recosubjets[reco.subJetIdx2].btagCSVV2 >  self.minBDisc :
#                         self.SJ0isW = 1
#                 if recosubjets[reco.subJetIdx2].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx2].p4().M() < recosubjets[reco.subJetIdx2].p4().M() :
#                     maxrecoSJmass = recosubjets[reco.subJetIdx1].p4().M()
#                     WHadreco = recosubjets[reco.subJetIdx2].p4()
#                     if recosubjets[reco.subJetIdx1].btagCSVV2 >  self.minBDisc  or recosubjets[reco.subJetIdx2].btagCSVV2 >  self.minBDisc :
#                         self.SJ0isW = 0
#                 if isMC and WHadreco != None and self.SJ0isW >= 0 :
                      
#                     for q in realqs:
#                         gen_4v = ROOT.TLorentzVector()
#                         gen_4v.SetPtEtaPhiM(q.pt,q.eta,q.phi,q.mass)
#                         dR = WHadreco.DeltaR(gen_4v)
#                         if dR < 0.6: self.matchedSJ = 1
#             else :
#                 recoAK8Groomed[reco] = None
#                 WHadreco = None
        
#         # now fill branches
#         self.out.fillBranch("genmatchedAK8",  self.isW)
#         self.out.fillBranch("genmatchedAK8Quarks",  self.isWqq)
#         self.out.fillBranch("genmatchedAK8Subjet", self.matchedSJ)
#         self.out.fillBranch("AK8Subjet0isMoreMassive", self.SJ0isW )
#         self.out.fillBranch("puweight", puweight )
#         self.out.fillBranch("btagweight", btagweight )
#         self.out.fillBranch("triggerweight", triggerweight )
#         self.out.fillBranch("topweight", topweight )
#         self.out.fillBranch("lheweight", lheweight )
#         self.out.fillBranch("passedMETfilters", passedMETFilters)
#         self.out.fillBranch("dr_LepJet"  , abs(dR_jetlep))
#         self.out.fillBranch("dphi_LepJet", abs(jetAK8_4v.DeltaPhi(lepton)))
#         self.out.fillBranch("dphi_LepMet", abs(lepton.DeltaPhi(MET)))
#         self.out.fillBranch("dphi_MetJet", abs(jetAK8_4v.DeltaPhi(MET)))
#         self.out.fillBranch("dphi_WJet"  , abs(jetAK8_4v.DeltaPhi(WcandLep)))
#         self.out.fillBranch("Wlep_type",self.Vlep_type)
#         self.out.fillBranch("W_pt", WcandLep.Pt() )
#         self.out.fillBranch("W_mass", WcandLep.M() )
#         self.out.fillBranch("maxAK4CSV", maxAK4CSV )
#         self.out.fillBranch("subMaxAK4CSV", subMaxAK4CSV )
#         self.out.fillBranch("minJetMetDPhi", minJetMetDPhi )
#         self.out.fillBranch("HT_HEM1516", HT_HEM1516 )
#         self.out.fillBranch("SelectedJet_softDrop_mass",  recoAK8[0].msoftdrop)
#         self.out.fillBranch("SelectedJet_pt",   recoAK8[0].pt)
#         self.out.fillBranch("SelectedJet_eta",  recoAK8[0].eta)
#         self.out.fillBranch("SelectedJet_mass",  recoAK8[0].mass)
#         self.out.fillBranch("SelectedLepton_pt", lepton.Pt())
#         self.out.fillBranch("SelectedLepton_iso",  iso)
#         if recoAK8[0].tau1 > 0.0: 
#           tau21 = recoAK8[0].tau2/recoAK8[0].tau1
#           tau41 = recoAK8[0].tau4/recoAK8[0].tau1
#         else:
#           tau21 = -1.
#           tau41 = -1.
#         if recoAK8[0].tau2 > 0.0: 
#           tau42 = recoAK8[0].tau4/recoAK8[0].tau2
#         else:
#           tau42 = -1.
#         self.out.fillBranch("SelectedJet_tau21",tau21)
#         self.out.fillBranch("SelectedJet_tau21_ddt", tau21+0.063*ROOT.TMath.Log(recoAK8[0].msoftdrop**2/recoAK8[0].pt))
#         self.out.fillBranch("SelectedJet_tau21_ddt_retune", tau21+0.082*ROOT.TMath.Log(recoAK8[0].msoftdrop**2/recoAK8[0].pt))
#         if recoAK8[0].tau2 > 0.0: 
#           tau32 = recoAK8[0].tau3/recoAK8[0].tau2
#         else:
#           tau32 = -1.     
#         self.out.fillBranch("SelectedJet_tau32",tau32)
#         self.out.fillBranch("SelectedJet_tau42",tau42)
#         self.out.fillBranch("SelectedJet_tau41",tau41)

        """////////////////////////////////////////////////////"""        
        """This part ofcode is from me"""
        """////////////////////////////////////////////////////"""        
        """nanoAOD skimming is done considering the final events selection
        for the vv semileptonic final state.
        
        For the vv semileptonic final state we should be either one or two 
        tight leptons, either one Fat jet and two small radius jet or four 
        small radius jets.
        
        Arguments:
            event {instance of event} -- instance of event
        
        Returns:
            boolean -- if the event passes skimming then it returns true and
                       go to the next module else returns false and go to 
                       the next event.
        """
        electrons = Collection(event, "Electron")
        muons = Collection(event, "Muon")
        jets = Collection(event, "Jet")
        fatJets = Collection(event, "FatJet")
        Eventpassed = True
        eventElectrons = 0
        eventMuons = 0
	eventLep  = 0
        eventJets = 0
        eventFatJets = 0
        
        for lep in muons :
            if  lep.pt > 30 :
                eventMuons += 1
		eventLep   += 1
        for lep in electrons :
            if lep.cutBased >= 2 and lep.pt > 30 :
                eventElectrons += 1
		eventLep   += 1
        for jet in jets :
            if jet.pt > 20:
               eventJets += 1
        for fatjet in fatJets :
            if fatjet.pt > 150:
               eventFatJets += 1
        
        if  ( ( eventLep == 0) or ( eventFatJets == 0) ):
            Eventpassed = False
	#        if not ( ((eventElectrons >= 1 or eventMuons >=1)) and ( eventFatJets >= 1) ):
        #    Eventpassed = False
       
        return Eventpassed


# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed
ttbar_semilep = lambda : Skimmer(Channel="elmu") 
