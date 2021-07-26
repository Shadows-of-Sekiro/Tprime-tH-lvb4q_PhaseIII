import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection,Object
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import *
from WTopScalefactorProducer.Skimmer.xsec import getXsec

import random
import array


# This is a loose selection to select events for T Tbar semileptonic events where 
# Type 1 and Type 2 events are included in the selection:

# In SF code the final cuts need to be made to choose either type 1 or type 2 selection:
# e.g. for type 1 the W leptonic Pt cut should be tightened to 200 GeV and dPhi cuts applied
# e.g. for type 2 the AK8 Pt cut should be tightened to 400 GeV and dPhi cuts applied

# Type 1 - martially merged Hadronic Top Quark (W is AK8, b is AK4, no subjet b-tags) 
#(AK8 Pt > 200 GeV)

# Type 2 - fully merged Top (Top is AK8, W is most massive SD subjet, b is less massive subjet, require 1 subjet b-tag) 
#(AK8 Pt > 400 GeV): 


# selection aligned with previous SF measurement standard selection
# https://www.evernote.com/shard/s282/sh/7e5d6baa-d100-4025-8bf8-a61bf1adfbc1/f7e86fde2c2a165e


# 1 AK8 Pt > 200 GeV, |eta| < 2.5 , dR(Ak8, lep) > 1.0
# 1 AK4 Pt > 30 GeV, |eta| < 2.5
# 1 lepton , mu pt > 53 GeV or el pt > 120 GeV
# MET Pt > 40(mu) or 80(el) GeV
#Leptonic W - lepton + MET has Pt > 150 GeV
         
class TTbar_SemiLep(Module):
    def __init__(self ):
        self.verbose = False
    def beginJob(self):
        Module.beginJob(self)
           
        self.minMupt = 53.
        self.maxMuEta = 2.4
        self.maxRelIso = 0.1
        self.minMuMETPt = 40.

        #remove  AK8 jet within 1.0 of lepton
        self.mindRLepJet = 1.0 
       
        self.minElpt = 120.
        self.minElMETPt = 80.
     
        self.minLepWPt = 150.

        self.minJetPt = 200.
        self.maxJetEta = 2.5

        self.minBDisc = 0.5 # Very loose, Apply real cut in second script #0.8484
        ### Medium https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation80XReReco

        #>= 1 CSVmedium akt4 jet
        self.minAK4Pt = 30.

        #Angular selection (to be implemented later, in fitting code):
        #dR( lepton, leading AK8 jet) > pi/2
        #dPhi(leading AK8 jet, MET) > 2
        #dPhi (leading AK8 jet, leptonic W) >2
        #self.minDPhiWJet = 2.  


                  
    def endJob(self):
        Module.endJob(self)
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
         self.out = wrappedOutputTree
         self.out.branch("dr_LepJet",  "F")
         self.out.branch("dphi_LepJet",  "F")
         self.out.branch("dphi_MetJet",  "F")
         self.out.branch("dphi_WJet"  ,  "F")
         self.out.branch("SelectedJet_softDrop_mass",  "F")
         self.out.branch("SelectedJet_tau32",  "F")
         self.out.branch("SelectedJet_tau21",  "F")
         self.out.branch("SelectedJet_tau21_ddt",  "F")
         self.out.branch("SelectedJet_tau21_ddt_retune",  "F")      
         self.out.branch("SelectedJet_pt",   "F")
         self.out.branch("SelectedJet_eta",  "F")
         self.out.branch("SelectedJet_mass", "F")
         self.out.branch("SelectedLepton_pt",  "F")
         self.out.branch("SelectedSubJet_softDrop_mass",  "F")
         self.out.branch("SelectedSubJet_tau32",  "F")
         self.out.branch("SelectedSubJet_tau21",  "F")
         self.out.branch("SelectedSubJet_tau21_ddt",  "F")
         self.out.branch("SelectedSubJet_tau21_ddt_retune",  "F")
         self.out.branch("SelectedSubJet_pt",   "F")
         self.out.branch("SelectedSubJet_eta",  "F")
         self.out.branch("SelectedSubJet_mass", "F")
         self.out.branch("Wlep_type",  "I")
         self.out.branch("W_pt",  "F")
         self.out.branch("MET",  "F")
         self.out.branch("AK8Subjet0CSVv2",  "F")
         self.out.branch("AK8Subjet1CSVv2",  "F")
         self.out.branch("genmatchedAK8Subjet",  "I")
         self.out.branch("genmatchedAK8",  "I")
         #self.out.branch("AK8hasSubjetBtag",  "I")
         self.out.branch("AK8Subjet0isMoreMassive",  "I")
         self.out.branch("crossection",  "F")
         self.out.branch("passedMETfilters",  "I")
         self.xs = getXsec(inputFile.GetName())
         print " Cross section for sample: " , inputFile.GetName()
         print self.xs
         pass

    def endFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        pass
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
        weight = 1.0

        isMC = event.run == 1
     
        # Gen
        if isMC:

            ### Look at generator level particles
            ### find events where :
            ### a W decays to quarks (Type 1 - partially merged)
            ###    OR
            ### a Top decays to W + b (Type 2 - fully merged top quark)
            gens = Collection(event, "GenPart")
            Wdaus =  [x for x in gens if x.pt>1 and 0<abs(x.pdgId)<9]
            Wmoms =  [x for x in gens if x.pt>10 and abs(x.pdgId)==24]

            TWdaus =  [x for x in gens if x.pt>1 and  0<abs(x.pdgId)<4]
            Tdaus =  [x for x in gens if x.pt>1 and (abs(x.pdgId)==5  or  abs(x.pdgId)==24 )]
            Tmoms =  [x for x in gens if x.pt>10 and abs(x.pdgId)==6]
                    
            realVs = []
            realVdaus = []

            realTs = []
            realWs = []
            realqs = []
            self.matchedJ = 0
            self.matchedSJ = 0

            if len(Wmoms)>0 and len(Wdaus)>0:
              for dau in Wdaus:
                for mom in Wmoms:
                  try:
                    if mom == Wmoms[dau.genPartIdxMother]: 
                      realVs.append(mom)
                      realVdaus.append(dau)    
                  except:
                    continue    

            if len(Tmoms)>0 and len(Tdaus)>0:
              for gdau in TWdaus :
                for dau in Tdaus:
                  for mom in Tmoms:
                    try:
                      if mom == Tmoms[dau.genPartIdxMother] and dau == Tdaus[gdau.genPartIdxMother]: 
                        realTs.append(mom)
                        realWs.append(dau)
                        realqs.append(gdau)    
                    except:
                      continue  

          
        # Find high-pT lepton, veto additional leptons, check trigger
        allmuons = Collection(event, "Muon")
        allelectrons = Collection(event, "Electron")
        triggerMu = event.HLT_Mu50
        # triggerEl = event.HLT_Ele115_CaloIdVT_GsfTrkIdT
        
        
        

        electrons = [x for x in allelectrons if x.cutBased_HEEP and x.pt > 35 ]	 #loose pt cut for veto 
        muons     = [x for x in allmuons if x.pt > 20 and x.highPtId > 1 and abs(x.p4().Eta()) < self.maxMuEta and x.pfRelIso03_all < 0.1] #loose pt cut for veto
        muons    .sort(key=lambda x:x.pt,reverse=True)
        electrons.sort(key=lambda x:x.pt,reverse=True)
        
        self.Vlep_type = -1
        lepton = ROOT.TLorentzVector()
        if len(electrons) + len(muons) == 1:
          if len(muons) == 1:
            if triggerMu == 0: return False
            if muons[0].pt < self.minMupt : return False
            self.Vlep_type = 0
            lepton = muons[0].p4()
           
          if len(electrons) == 1:
            return False
            # if triggerEl == 0: return False
            # if electrons[0].pt < self.minElpt : return False
            # self.Vlep_type=1
            # lepton = electrons[0].p4()
            
            
        else: return False
        
        # Add filters https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Moriond_2018
        passedMETFilters = False
        try:
          if event.Flag_BadChargedCandidateFilter and event.Flag_BadPFMuonFilter and event.Flag_EcalDeadCellTriggerPrimitiveFilter and event.Flag_HBHENoiseFilter and event.Flag_HBHENoiseIsoFilter and event.Flag_METFilters and event.Flag_ecalBadCalibFilter and event.Flag_globalTightHalo2016Filter and event.Flag_goodVertices:
            passedMETFilters = True
        except:
           passedMETFilters = False
          # if not passedMETFilters: return False

        
        # Apply MET cut    
        met = Object(event, "MET")
        if self.Vlep_type == 0 and met.sumEt < self.minMuMETPt : return False
        if self.Vlep_type == 1 and met.sumEt < self.minElMETPt : return False
        MET  = ROOT.TLorentzVector()
        MET.SetPtEtaPhiE(met.sumEt, 0., met.phi, met.sumEt)
        
        # Apply leptonic W cut
        WcandLep = lepton + MET
        if WcandLep.Perp() < self.minLepWPt :
            return False
        
        #Check for additional b-jet in the event, apply CSV later!
        Jets = list(Collection(event, "Jet")) 
        recoAK4 = [ x for x in Jets if x.p4().Perp() > self.minAK4Pt and abs(x.p4().Eta()) < self.maxJetEta and x.btagCSVV2 > self.minBDisc]
        if len(recoAK4) < 1:
            return False
    
        # Find fat jet
        FatJets = list(Collection(event, "FatJet"))
        recoAK8 = [ x for x in FatJets if x.p4().Perp() > self.minJetPt and  abs(x.p4().Eta()) < self.maxJetEta and x.msoftdrop > 30. and x.tau1 > 0. and x.tau2 > 0.]
        if len(recoAK8) < 1 : return False
        recoAK8.sort(key=lambda x:x.msoftdrop,reverse=True)

        jetAK8_4v = ROOT.TLorentzVector()
        jetAK8_4v.SetPtEtaPhiM(recoAK8[0].pt,recoAK8[0].eta,recoAK8[0].phi,recoAK8[0].mass)
        
        
        # No lepton overlap
        dR_jetlep = jetAK8_4v.DeltaR(lepton )
        if abs(dR_jetlep) < self.mindRLepJet : return False
        
        # Check if matched to genW and genW daughters
        #for partially merged:
        self.isW = 0
        if isMC == False:
            genjets = [None] * len(recoAK8)

        else :          
          for V in realVs:
            gen_4v = ROOT.TLorentzVector()
            gen_4v.SetPtEtaPhiM(V.pt,V.eta,V.phi,V.mass)
            dR = jetAK8_4v.DeltaR(gen_4v)
            if dR < 0.8: 
              nDau = 0
              for v in realVdaus:
                gen_4v = ROOT.TLorentzVector()
                gen_4v.SetPtEtaPhiM(v.pt,v.eta,v.phi,v.mass)
                dR = jetAK8_4v.DeltaR(gen_4v)
                if dR < 0.8: 
                  nDau +=1                 
              if nDau >1: self.isW = 1
              else: self.isW = 0
       
        #for fully merged:
        self.SJ0isW = -1
        # List of reco subjets:
        recosubjets = list(Collection(event,"SubJet"))
        # Dictionary to hold ungroomed-->groomed for reco
        recoAK8Groomed = {}        
        # Get the groomed reco jets
        maxrecoSJmass = 1.
        WHadreco = None
        # save b-disc from both subjets
        self.SJ0Bdisc= 0.
        self.SJ1Bdisc= 0.
        for ireco,reco in enumerate(recoAK8):
            if reco.subJetIdx2 >= len(recosubjets) or reco.subJetIdx1 >= len(recosubjets) :
                if self.verbose: print "Reco subjet indices not in Subjet list, Skipping"
                continue
            if reco.subJetIdx1 >= 0 and reco.subJetIdx2 >= 0 :
                recoAK8Groomed[reco] = recosubjets[reco.subJetIdx1].p4() + recosubjets[reco.subJetIdx2].p4()
                if recosubjets[reco.subJetIdx1].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx1].p4().M() >  recosubjets[reco.subJetIdx2].p4().M() :
                    maxrecoSJmass = recosubjets[reco.subJetIdx1].p4().M()
                    WHadreco = recosubjets[reco.subJetIdx1]
                    self.SJ0isW = 1
                    self.SJ0Bdisc= recosubjets[reco.subJetIdx1].btagCSVV2
                    self.SJ1Bdisc= recosubjets[reco.subJetIdx2].btagCSVV2
                if recosubjets[reco.subJetIdx2].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx1].p4().M() < recosubjets[reco.subJetIdx2].p4().M() :
                    maxrecoSJmass = recosubjets[reco.subJetIdx2].p4().M()
                    WHadreco = recosubjets[reco.subJetIdx2]
                    self.SJ0isW = 0
                    self.SJ0Bdisc= recosubjets[reco.subJetIdx2].btagCSVV2
                    self.SJ1Bdisc= recosubjets[reco.subJetIdx1].btagCSVV2

                if isMC and WHadreco != None and self.SJ0isW >= 0 :
                      
                    for q in realqs:
                        gen_4v = ROOT.TLorentzVector()
                        gen_4v.SetPtEtaPhiM(q.pt,q.eta,q.phi,q.mass)
                        dR = WHadreco.p4().DeltaR(gen_4v)
                        if dR < 0.6: self.matchedSJ = 1
            else :
                recoAK8Groomed[reco] = None
                WHadreco = None
        
        # now fill branches
        if isMC :
            self.out.fillBranch("genmatchedAK8Subjet", self.matchedSJ)
            self.out.fillBranch("genmatchedAK8",  self.isW)
        self.out.fillBranch("AK8Subjet0CSVv2", self.SJ0Bdisc )
        self.out.fillBranch("AK8Subjet1CSVv2", self.SJ1Bdisc )
        self.out.fillBranch("AK8Subjet0isMoreMassive", self.SJ0isW )
        self.out.fillBranch("crossection",self.xs)
        self.out.fillBranch("dr_LepJet"  ,dR_jetlep)
        self.out.fillBranch("dphi_LepJet",jetAK8_4v.DeltaPhi(lepton))
        self.out.fillBranch("dphi_MetJet",jetAK8_4v.DeltaPhi(MET))
        self.out.fillBranch("dphi_WJet"  ,jetAK8_4v.DeltaPhi(WcandLep))
        self.out.fillBranch("Wlep_type",self.Vlep_type)
        self.out.fillBranch("W_pt", WcandLep.Perp() )
        self.out.fillBranch("MET", met.sumEt )
        self.out.fillBranch("SelectedJet_softDrop_mass",  recoAK8[0].msoftdrop)
        self.out.fillBranch("SelectedJet_pt",   recoAK8[0].pt)
        self.out.fillBranch("SelectedJet_eta",  recoAK8[0].eta)
        self.out.fillBranch("SelectedJet_mass",  recoAK8[0].mass)
        self.out.fillBranch("SelectedLepton_pt", lepton.Pt())
        if  WHadreco != None : 
            self.out.fillBranch("SelectedSubJet_softDrop_mass",  WHadreco.mass)
            self.out.fillBranch("SelectedSubJet_pt",   WHadreco.pt)
            self.out.fillBranch("SelectedSubJet_eta",  WHadreco.eta)
            self.out.fillBranch("SelectedSubJet_mass",  WHadreco.mass)

        if recoAK8[0].tau1 > 0.0: 
          tau21 = recoAK8[0].tau2/recoAK8[0].tau1
        else:
          tau21 = -1.          
        self.out.fillBranch("SelectedJet_tau21",tau21)
        self.out.fillBranch("SelectedJet_tau21_ddt", tau21+0.063*ROOT.TMath.Log(recoAK8[0].msoftdrop**2/recoAK8[0].pt))
        self.out.fillBranch("SelectedJet_tau21_ddt_retune", tau21+0.082*ROOT.TMath.Log(recoAK8[0].msoftdrop**2/recoAK8[0].pt))
        if recoAK8[0].tau2 > 0.0: 
          tau32 = recoAK8[0].tau3/recoAK8[0].tau2
        else:
          tau32 = -1.     
        self.out.fillBranch("SelectedJet_tau32",tau32)
        if  WHadreco != None :
            if WHadreco.tau1 > 0.0:
              sjtau21 = WHadreco.tau2/WHadreco.tau1
            else:
              sjtau21 = -1.
            self.out.fillBranch("SelectedSubJet_tau21",sjtau21)
            self.out.fillBranch("SelectedSubJet_tau21_ddt", sjtau21+0.063*ROOT.TMath.Log(WHadreco.mass**2/WHadreco.pt))
            self.out.fillBranch("SelectedSubJet_tau21_ddt_retune", sjtau21+0.082*ROOT.TMath.Log(WHadreco.mass**2/WHadreco.pt))
            if WHadreco.tau2 > 0.0:
              sjtau32 = WHadreco.tau3/WHadreco.tau2
            else:
              sjtau32 = -1.
            self.out.fillBranch("SelectedJet_tau32",sjtau32)


        self.out.fillBranch("passedMETfilters",passedMETFilters)

        return True
# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ttbar_semilep = lambda : TTbar_SemiLep() 
