import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True

from PhysicsTools.NanoAODTools.postprocessing.framework.datamodel import Collection,Object
from PhysicsTools.NanoAODTools.postprocessing.framework.eventloop import Module
from PhysicsTools.NanoAODTools.postprocessing.tools import *


import random
import array

class TTbar_SemiLep_fullyMerged(Module):
    def __init__(self ):
        self.writeHistFile = True
        self.verbose = True #False
        self.genmatchVerbose = True
    def beginJob(self, histFile, histDirName):
        Module.beginJob(self, histFile, histDirName)


        self.isttbar = True #False
        if 'TTJets_'  in histFile or 'TTToSemiLeptonic' in histFile or '94XNanoV0-TTbar_SemiLep' in histFile  :
           self.isttbar = True 
        if self.isttbar : print "This is a ttbar MC dataset!"



        ### Set bins for Pt dependent scale factor calculation    

        self.TopcandPtBins = [[200,300], [300,400], [400,500],[500, float("inf")]]
        # e.g. h_WcandSubjetpt_Tptbin0 is a 1D histogram for W candidate subjets (most massive SD subjet) within Top candidates of pt 200-300 GeV  

        self.WcandPtBins = [[200,300], [300,500], [500, float("inf") ] ]
        # e.g. h_WcandSubjetpt_ptbin0 1D histogram is for W candidate subjets (most massive SD subjet) with pt 200-300 GeV   

        self.minMupt = 53.
        self.maxMuEta = 2.4
        self.maxRelIso = 0.1
        self.minMuMETPt = 40.

        ### Figure our tree branch for HighPtMuon ???
        #is High Pt


        #remove  AK8 jet within 1.0 of lepton
        self.mindRLepJet = 1.0 
        #veto:
        # High pT muon ID
        #pT > 20 GeV, eta < 2.4??
        #relIso < 0.1


        self.minElpt = 120.
        self.minElMETPt = 80.
        #self.goodElEta = if eta < 1.44, 1.56 < eta < 2.5
        # HEEP v7 + iso
        #veto
        # HEEP + iso pt > 35 remove ecal crack region eta < 1.44, 1.56 < eta < 2.5
        #

        self.minLepWPt = 150.

        self.minJetPt = 350.
        self.maxJetEta = 2.4
        self.minTopmass = 105.
        self.maxTopmass = 250.
        self.maxtau32Top = 0.7



        self.minBDisc = 0.8484
        ### Medium https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation80XReReco

        #>= 1 CSVmedium akt4 jet
        self.minAK4Pt = 50.

        ### 2-D cut ###
        ### dR OR PtRel ###
        self.mindRlepAK4 = 0.4
        self.minPtRel_lepAK4 = 30.

        #Angular selection (not used by Thea now):

        #dR( lepton, leading AK8 jet) > pi/2
        #dPhi(leading AK8 jet, MET) > 2
        
        #dPhi (leading AK8 jet, leptonic W) >2
        #self.minDPhiWJet = 2.  


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

       
      


        
        self.addObject( ROOT.TH1D('h_lep0pt',          'h_lep0pt',        40, 0, 200 ) )
        self.addObject( ROOT.TH1D('h_lep0eta',         'h_lep0eta',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_lep0phi',         'h_lep0phi',      100, -5, 5 ) )

        self.addObject( ROOT.TH1D('h_hadToppt',          'h_hadToppt',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_hadTopeta',         'h_hadTopeta',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_hadTopphi',         'h_hadTopphi',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_hadTopmass',        'h_hadTopmass',      60, 140, 200 ) )
        
        #self.addObject( ROOT.TH1D('h_lepToppt',          'h_lepToppt',        100, 0, 500 ) )
        #self.addObject( ROOT.TH1D('h_lepTopeta',         'h_lepTopeta',      48, -3, 3 ) )
        #self.addObject( ROOT.TH1D('h_lepTopphi',         'h_lepTopphi',      100, -5, 5 ) )
        #self.addObject( ROOT.TH1D('h_lepTopmass',        'h_lepTopmass',      60, 140, 200 ) )
       
        self.addObject( ROOT.TH1D('h_WcandSubjetpt',          'h_WcandSubjetpt',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjeteta',         'h_WcandSubjeteta',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetphi',         'h_WcandSubjetphi',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetmass',        'h_WcandSubjetmass',      100, 50, 150 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjettau21',        'h_WcandSubjettau21',      100, 0,1  ) )
      

        self.addObject( ROOT.TH1D('h_WcandSubjetpt_ptbin0',          'h_WcandSubjetpt_ptbin0',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjeteta_ptbin0',         'h_WcandSubjeteta_ptbin0',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetphi_ptbin0',         'h_WcandSubjetphi_ptbin0',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetmass_ptbin0',        'h_WcandSubjetmass_ptbin0',      100, 50, 150 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjettau21_ptbin0',        'h_WcandSubjettau21_ptbin0',      100, 0, 1 ) )

        self.addObject( ROOT.TH1D('h_WcandSubjetpt_ptbin1',          'h_WcandSubjetpt_ptbin1',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjeteta_ptbin1',         'h_WcandSubjeteta_ptbin1',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetphi_ptbin1',         'h_WcandSubjetphi_ptbin1',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetmass_ptbin1',        'h_WcandSubjetmass_ptbin1',      100, 50, 150 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjettau21_ptbin1',       'h_WcandSubjettau21_ptbin1',      100, 0, 1 ) )

        self.addObject( ROOT.TH1D('h_WcandSubjetpt_ptbin2',          'h_WcandSubjetpt_ptbin2',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjeteta_ptbin2',         'h_WcandSubjeteta_ptbin2',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetphi_ptbin2',         'h_WcandSubjetphi_ptbin2',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjetmass_ptbin2',        'h_WcandSubjetmass_ptbin2',      100, 50, 150 ) )
        self.addObject( ROOT.TH1D('h_WcandSubjettau21_ptbin2',       'h_WcandSubjettau21_ptbin2',      100, 0, 1 ) )
   

        self.WcandSubjetpt = [self.h_WcandSubjetpt_ptbin0, self.h_WcandSubjetpt_ptbin1, self.h_WcandSubjetpt_ptbin2 ]
        self.WcandSubjeteta = [self.h_WcandSubjeteta_ptbin0, self.h_WcandSubjeteta_ptbin1, self.h_WcandSubjeteta_ptbin2 ]
        self.WcandSubjetphi = [self.h_WcandSubjetphi_ptbin0, self.h_WcandSubjetphi_ptbin1, self.h_WcandSubjetphi_ptbin2 ]
        self.WcandSubjetmass = [self.h_WcandSubjetmass_ptbin0, self.h_WcandSubjetmass_ptbin1, self.h_WcandSubjetmass_ptbin2 ]
        self.WcandSubjettau21 = [self.h_WcandSubjettau21_ptbin0, self.h_WcandSubjettau21_ptbin1, self.h_WcandSubjettau21_ptbin2 ]
        
        #self.addObject( ROOT.TH1D('h_WcandSubjetpt_Tptbin0',          'h_WcandSubjetpt_Tptbin0',        100, 0, 500 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjeteta_Tptbin0',         'h_WcandSubjeteta_Tptbin0',      48, -3, 3 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetphi_Tptbin0',         'h_WcandSubjetphi_Tptbin0',      100, -5, 5 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetmass_Tptbin0',        'h_WcandSubjetmass_Tptbin0',      100, 50, 150 ) )

        #self.addObject( ROOT.TH1D('h_WcandSubjetpt_Tptbin1',          'h_WcandSubjetpt_Tptbin1',        100, 0, 500 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjeteta_Tptbin1',         'h_WcandSubjeteta_Tptbin1',      48, -3, 3 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetphi_Tptbin1',         'h_WcandSubjetphi_Tptbin1',      100, -5, 5 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetmass_Tptbin1',        'h_WcandSubjetmass_Tptbin1',      100, 50, 150 ) )

        #self.addObject( ROOT.TH1D('h_WcandSubjetpt_Tptbin2',          'h_WcandSubjetpt_Tptbin2',        100, 0, 500 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjeteta_Tptbin2',         'h_WcandSubjeteta_Tptbin2',      48, -3, 3 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetphi_Tptbin2',         'h_WcandSubjetphi_Tptbin2',      100, -5, 5 ) )
        #self.addObject( ROOT.TH1D('h_WcandSubjetmass_Tptbin2',        'h_WcandSubjetmass_Tptbin2',      100, 50, 150 ) )

        #self.addObject( ROOT.TH1D('h_genjetpt',          'h_genjetpt',   100, 0, 500 ) )
        #self.addObject( ROOT.TH1D('h_genjeteta',         'h_genjeteta',      48, -3, 3 ) )
        #self.addObject( ROOT.TH1D('h_genjetphi',         'h_genjetphi',      100, -5, 5 ) )
        #self.addObject( ROOT.TH1D('h_genjetmass',        'h_genjetmass',      300, 0, 300 ) )
       

        self.addObject( ROOT.TH1D('h_Wleppt',          'h_Wleppt',        100, 0, 500 ) )
        self.addObject( ROOT.TH1D('h_Wlepeta',         'h_Wlepeta',      48, -3, 3 ) )
        self.addObject( ROOT.TH1D('h_Wlepphi',         'h_Wlepphi',      100, -5, 5 ) )
        self.addObject( ROOT.TH1D('h_Wlepmass',        'h_Wlepmass',      100, 50, 150 ) )


        
        if self.isttbar :
            self.addObject( ROOT.TH1D('h_matchedAK8Subjetpt',          'h_matchedAK8Subjetpt',      100, 0, 500 ) )
            self.addObject( ROOT.TH1D('h_matchedAK8Subjeteta',         'h_matchedAK8Subjeteta',      48, -3, 3 ) )
            self.addObject( ROOT.TH1D('h_matchedAK8Subjetphi',         'h_matchedAK8Subjetphi',      100, -5, 5 ) )
            self.addObject( ROOT.TH1D('h_matchedAK8Subjetmass',        'h_matchedAK8Subjetmass',      300, 0, 300 ) )

            self.addObject( ROOT.TH1D('h_unmatchedAK8Subjetpt',          'h_unmatchedAK8Subjetpt',      100, 0, 500 ) )
            self.addObject( ROOT.TH1D('h_unmatchedAK8Subjeteta',         'h_unmatchedAK8Subjeteta',      48, -3, 3 ) )
            self.addObject( ROOT.TH1D('h_unmatchedAK8Subjetphi',         'h_unmatchedAK8Subjetphi',      100, -5, 5 ) )
            self.addObject( ROOT.TH1D('h_unmatchedAK8Subjetmass',        'h_unmatchedAK8jetmass',      300, 0, 300 ) )
    
        

                  
    def endJob(self):
        Module.endJob(self)
        pass
    def beginFile(self, inputFile, outputFile, inputTree, wrappedOutputTree):
        self.out = wrappedOutputTree
        self.out.branch("WHadreco_pt"   ,  "F")
        self.out.branch("WHadreco_eta"  ,  "F")
        self.out.branch("WHadreco_phi"  ,  "F")
        self.out.branch("WHadreco_mass" ,  "F")
        self.out.branch("WHadreco_tau21" ,  "F")
                
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
        if self.verbose:
            print '------------------------ ', event.event
        self.matchedSJ = -1.
        if isMC :
            # Re-do gen level matching

            ### Look at generator level particles
            ### find events where :
            ### a W decays to quarks 
            gens = Collection(event, "GenPart")

            genqs =  [x for x in gens if  0<abs(x.pdgId)<=4]
            genWs =  [x for x in gens if x.pt>1 and  abs(x.pdgId)==24 ]

            realWs = []
            realqs = []
        
            if  len(genWs)>0 and len(genqs) > 0:
                if self.genmatchVerbose : print "genquark loop for this event_____________"
                for igq,gq in enumerate(genqs) :
                    if  gq.genPartIdxMother >= 0 :
                        #print "Gen quark PDG Id is {}".format(gq.pdgId)
                        qmom = gens[gq.genPartIdxMother]
                        qmomId = qmom.pdgId
                        if abs(qmomId) == 24 :
                            if self.genmatchVerbose : 
                                print "W-> q qbar event found"
                                #print "Mother particle index is {}".format(gq.genPartIdxMother)
                                print "PDG Id of mother {}".format(gens[gq.genPartIdxMother].pdgId)
                            for gW in genWs:
                                if  gW == gens[gq.genPartIdxMother]: 
                                    realWs.append(gW)
                                    realqs.append(gq)    
                                    if self.genmatchVerbose :print "Found gen event  W->q+ qbar"
                                else:
                                    continue

        ###### Get reco Top/W candidate #######
        # List of reco muons
        allmuons = Collection(event, "Muon")
        allelectrons = Collection(event, "Electron")
        # Select reco muons:
        muons = [ x for x in allmuons if x.tightId and x.pfRelIso03_all and x.p4().Perp() > self.minMupt and abs(x.p4().Eta())  < self.maxMuEta ]
        # Select reco muons:
        electrons = [ x for x in allelectrons if  x.cutBased_HEEP and x.p4().Perp() > self.minElpt  and (abs(x.p4().Eta()) < 1.44 or (abs(x.p4().Eta()) > 1.56 and  abs(x.p4().Eta()) < 2.5  ))]

        if ( len(muons) + len(electrons) ) < 1 :
            return False

        ### Choose the leading lepton in the event
        lepton = ROOT.TLorentzVector()
        isMu = None #False

        # Keep only events with exactly 1 lepton passing all above pt , eta and cut based ID cuts

        if  ( len(muons) ) == 1 and  ( len(electrons) ) < 1  :
            lepton = muons[0].p4()
            isMu = True

        if  ( len(muons) ) < 1 and  ( len(electrons) ) == 1  :
            lepton = electrons[0].p4()
            isMu = False
      
        if  ( len(muons) ) > 0 and  ( len(electrons) ) > 0  :
            # Veto events with multiple leptons
            return False


        MET_pt = event.PuppiMET_pt     
        
        # Veto events with low MET
        # This ensires presnece of a neutrino
        if isMu and MET_pt < self.minMuMETPt :
            return False
        if not isMu and MET_pt < self.minElMETPt :
            return False


        MET = ROOT.TLorentzVector()

        MET.SetPtEtaPhiM(MET_pt, 0.0, event.PuppiMET_phi , event.PuppiMET_sumEt)

        # Veto low Pt leptonic W events
        WcandLep = lepton + MET
        if WcandLep.Perp() < self.minLepWPt :
            return False

        allrecoAK4jets = list(Collection(event, "Jet")) # are these AK4s ? 
        recojetsAK4 = [ x for x in allrecoAK4jets if x.p4().Perp() > self.minAK4Pt and abs(x.p4().Eta()) < self.maxJetEta]
        if len(recojetsAK4) < 1:  return False
        recojetsAK4.sort(key=lambda x:x.pt,reverse=True)

        mindRObs = 5.0
        bHadreco = None #ROOT.TLorentzVector()
        for ibcand, bcand in enumerate(recojetsAK4 ) :
            tempdR = bcand.p4().DeltaR(lepton)
            ptrel = abs(bcand.p4().Perp() - lepton.Perp())
            #onlt consider b-tagged AK4 jets
            if bcand.btagCSVV2  < self.minBDisc: continue
            #print ptrel
            # Find closest AK4 to the lepton which passes the 2D cut and is b-tagged
            if  tempdR < mindRObs and (tempdR >  self.mindRlepAK4 or ptrel > self.minPtRel_lepAK4 ):
                mindRObs = tempdR
                bHadreco = bcand #.SetPtEtaPhiM( bcand.p4().Perp(), bcand.p4().Eta() , bcand.p4().Phi() , bcand.p4().M())  
    
        # Veto events with no good AK4 Jet that is B-tagged                                                                                                                                                        
        if bHadreco == None : return False

        if self.verbose and bHadreco.p4().Perp() > self.minAK4Pt :
            print '-----'
            print ' reco b candidate AK4:', self.printP4( bHadreco )

        ###### Get list of reco jets #######
        # List of reco jets:
        allrecojets = list(Collection(event, "FatJet"))
        if self.verbose:
            print '----'
            print 'all recojets:'
            self.printCollection( allrecojets )

        recojets = [ x for x in allrecojets if x.p4().Perp() > self.minJetPt and  abs(x.p4().Eta()) < self.maxJetEta ]
        if len(recojets) < 1 : return False
        recojets.sort(key=lambda x:x.pt,reverse=True)


        
        if isMC == False:
            genjets = [None] * len(recojets)

    
        # List of reco subjets:
        recosubjets = list(Collection(event,"SubJet"))
        # Dictionary to hold reco--> gen matching
        #recoToGen = matchObjectCollection( recojets, genjets, dRmax=0.05 )
        # Dictionary to hold ungroomed-->groomed for reco
        recojetsGroomed = {}        
        # Get the groomed reco jets
        maxrecoSJmass = 10.
        WHadrecoSJ = None
        WHadrecoTau21 = -1.
        bHadrecoSJ = None
        TopHadreco = None #ROOT.TLorentzVector()
        TopHadrecoTau32 = -1.
        self.SJ0isW = -1
        maxrecoSJmass = 0.

        for ireco,reco in enumerate(recojets):
            # Keep the first W candidate subjet you find
            #if WHadrecoSJ != None : break

            ## Check that this jet is top tagged
            ## Check Nsubjettiness
            ## Top should have 3 subjets -> b + W(q qbar)
            if reco.tau3 > 0. :
                TopHadrecoTau32 = reco.tau3/reco.tau2
            else : continue 
            if  TopHadrecoTau32 > self.maxtau32Top : continue
            ## Check that leptons are well seperated from the Fat Jet
            if reco.p4().DeltaR(lepton)  <  self.mindRLepJet : continue

            if reco.subJetIdx2 >= len(recosubjets) or reco.subJetIdx1 >= len(recosubjets) :
                if self.verbose: print "Reco subjet indices not in Subjet list, Skipping"
                continue
            if reco.subJetIdx1 >= 0 and reco.subJetIdx2 >= 0 :
                recojetsGroomed[reco] = recosubjets[reco.subJetIdx1].p4() + recosubjets[reco.subJetIdx2].p4()
                if recojetsGroomed[reco].M() < self.minTopmass or recojetsGroomed[reco].M() > self.maxTopmass: continue
                if self.verbose :
                    if self.verbose : print "Top tagged AK8 with 2 Soft Drop subjets of reco index {}".format(ireco)
                    if self.verbose : print "Masses of subjets are {:2.2f} and {:2.2f} GeV".format(recosubjets[reco.subJetIdx1].p4().M() , recosubjets[reco.subJetIdx2].p4().M())
                if recosubjets[reco.subJetIdx1].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx1].p4().M() >  recosubjets[reco.subJetIdx2].p4().M() :
                    maxrecoSJmass = recosubjets[reco.subJetIdx1].p4().M()                  
                    ### Check that one of the subjets is Btagged
                    if recosubjets[reco.subJetIdx1].btagCSVV2 >  self.minBDisc  or recosubjets[reco.subJetIdx2].btagCSVV2 >  self.minBDisc :
                        if recosubjets[reco.subJetIdx1].tau1 > 0. :
                            WHadrecoTau21 = recosubjets[reco.subJetIdx1].tau2 / recosubjets[reco.subJetIdx1].tau1
                            self.SJ0isW = 1


                if recosubjets[reco.subJetIdx2].p4().M() > maxrecoSJmass and recosubjets[reco.subJetIdx1].p4().M() < recosubjets[reco.subJetIdx2].p4().M() :
                    maxrecoSJmass = recosubjets[reco.subJetIdx2].p4().M()
                    ### Check that one of the subjets is Btagged
                    if recosubjets[reco.subJetIdx1].btagCSVV2 >  self.minBDisc  or recosubjets[reco.subJetIdx2].btagCSVV2 >  self.minBDisc :
                        if recosubjets[reco.subJetIdx2].tau1 > 0.:
                            WHadrecoTau21 = recosubjets[reco.subJetIdx2].tau2 / recosubjets[reco.subJetIdx2].tau1
                            self.SJ0isW = 0

                if  self.SJ0isW < -1 : continue            
                else :
                    if self.SJ0isW == 0:
                        WHadrecoSJ = recosubjets[reco.subJetIdx2].p4()
                        TopHadreco = reco.p4()
                        bHadrecoSJ = recosubjets[reco.subJetIdx1].p4()
                        if self.verbose : print "Found reco W candidate subjet 1 of mass {:3.2f}".format(maxrecoSJmass )
                        break
                    if self.SJ0isW == 1:
                        WHadrecoSJ = recosubjets[reco.subJetIdx1].p4()
                        TopHadreco = reco.p4()
                        bHadrecoSJ = recosubjets[reco.subJetIdx2].p4()
                        if self.verbose : print "Found reco W candidate subjet 0 of mass {:3.2f}".format(maxrecoSJmass )
                        break
            else :
                recojetsGroomed[reco] = None
                WHadreco = None
                TopHadreco = None


        if WHadrecoSJ == None or self.SJ0isW < 0 : return False 
 
        # Do gen particle matching to reco subjets
        self.dRW_Wdfar = -1.
        self.dRW_b = WHadrecoSJ.DeltaR(bHadrecoSJ)
        if self.genmatchVerbose : print "dR (reco subjet b candidate , reco subjet W candidate) {:2.2f}".format(self.dRW_b )
        if isMC and len(realqs) > 1 :
            for q in realqs:
                # If the farthest (from the reco W) daughter quark from the gen W is closer to the reco W than the reco b then                                                                 
                # the event is considered a REAL W (ttbar matched) otherwise it is a FAKE W (ttbar unmatched)                                                                                 \
                # if (self.dRW_Wdfar < self.dRW_b) and (self.dRW_Wdfar < 0.4) :                                                                                                                
                gen_4v = ROOT.TLorentzVector()
                gen_4v.SetPtEtaPhiM(q.pt,q.eta,q.phi,q.mass)
                dR = WHadrecoSJ.DeltaR(gen_4v)
                if self.genmatchVerbose : print "dR (gen parton quark W daughter, reco subjet W candidate) {:2.2f}".format(dR )
                if dR > self.dRW_Wdfar : self.dRW_Wdfar = dR
            if (self.dRW_Wdfar < self.dRW_b) and (self.dRW_Wdfar < 0.4)  and (self.dRW_Wdfar > -1.) :
                if self.genmatchVerbose : print "MATCHED TTBAR event: dR between W cand subjet and furthest gen quark is {:2.2f} dR btw W and b subjets is {:2.2f}".format(self.dRW_Wdfar, self.dRW_b )
                self.matchedSJ = 1
            else : self.matchedSJ = 0



        if self.verbose:
            print '----'
            print 'opposite-Z recojets:'
            for recojet in recojets:
                sdmassreco = recojetsGroomed[recojet].M() if recojet in recojetsGroomed and recojetsGroomed[recojet] != None else -1.0
                print '         : %s %6.2f' % ( self.printP4( recojet),  sdmassreco )            


        #self.h_WcandSubjetpt_ptbin0.Fill(-1.)
        #self.h_WcandSubjetpt_ptbin1.Fill(-1.)
        #self.h_WcandSubjetpt_ptbin2.Fill(-1.)

        if WHadrecoSJ.Perp() < self.WcandPtBins[0][0] :
            return False
            '''
            self.out.fillBranch("WHadreco_pt", -1.)
            self.out.fillBranch("WHadreco_eta", -1.)
            self.out.fillBranch("WHadreco_phi", -1.)
            self.out.fillBranch("WHadreco_mass", -1.)
            if self.verbose : print " W subjet tau21  %2.2f "%(WHadrecoTau21)
            self.out.fillBranch("WHadreco_tau21", -1.)

            self.h_WcandSubjetpt.Fill(-1.)
            self.h_WcandSubjeteta.Fill(-1.)
            self.h_WcandSubjetphi.Fill(-1.)
            self.h_WcandSubjetmass.Fill(-1.)

            self.h_lep0pt.Fill(-1.)
            self.h_lep0eta.Fill(-1.)
            self.h_lep0phi.Fill(-1.)

            self.h_Wleppt.Fill(-1.)
            self.h_Wlepeta.Fill(-1.)
            self.h_Wlepphi.Fill(-1.)
            self.h_Wlepmass.Fill(-1.)

            self.h_hadToppt.Fill(-1.)
            self.h_hadTopeta.Fill(-1.)
            self.h_hadTopphi.Fill(-1.)
            self.h_hadTopmass.Fill(-1.)
            if self.isttbar :
                self.h_unmatchedAK8Subjetpt.Fill(-1.)
                self.h_unmatchedAK8Subjeteta.Fill(-1.)
                self.h_unmatchedAK8Subjetphi.Fill(-1.)
                self.h_unmatchedAK8Subjetmass.Fill(-1.)
                self.h_matchedAK8Subjetpt.Fill(-1.)
                self.h_matchedAK8Subjeteta.Fill(-1.)
                self.h_matchedAK8Subjetphi.Fill(-1.)
                self.h_matchedAK8Subjetmass.Fill(-1.)

            '''
     
        # If W candidate subjet has Pt of at least 200 , Fill all histograms and tree branches
        else  :
           
            self.out.fillBranch("WHadreco_pt", WHadrecoSJ.Perp())
            self.out.fillBranch("WHadreco_eta", WHadrecoSJ.Eta())
            self.out.fillBranch("WHadreco_phi", WHadrecoSJ.Phi())
            self.out.fillBranch("WHadreco_mass", WHadrecoSJ.M())
            if self.verbose : print " W subjet tau21  %2.2f "%(WHadrecoTau21)
            self.out.fillBranch("WHadreco_tau21", WHadrecoTau21)
            

            self.h_WcandSubjetpt.Fill(WHadrecoSJ.Perp())
            self.h_WcandSubjeteta.Fill(WHadrecoSJ.Eta())
            self.h_WcandSubjetphi.Fill(WHadrecoSJ.Phi())
            self.h_WcandSubjetmass.Fill(WHadrecoSJ.M())            
            self.h_WcandSubjettau21.Fill( WHadrecoTau21)

            self.h_lep0pt.Fill(lepton.Perp())
            self.h_lep0eta.Fill(lepton.Eta())
            self.h_lep0phi.Fill(lepton.Phi())
           
            self.h_Wleppt.Fill(WcandLep.Perp())
            self.h_Wlepeta.Fill(WcandLep.Eta())
            self.h_Wlepphi.Fill(WcandLep.Phi())
            self.h_Wlepmass.Fill(WcandLep.M())
           
            self.h_hadToppt.Fill(TopHadreco.Perp())
            self.h_hadTopeta.Fill(TopHadreco.Eta())
            self.h_hadTopphi.Fill(TopHadreco.Phi())
            self.h_hadTopmass.Fill(TopHadreco.M())
            
            if self.isttbar :
                if self.matchedSJ > 0  :
                    if self.verbose :print "Filling matched subjet"
                    self.h_matchedAK8Subjetpt.Fill(WHadrecoSJ.Perp())
                    self.h_matchedAK8Subjeteta.Fill(WHadrecoSJ.Eta())
                    self.h_matchedAK8Subjetphi.Fill(WHadrecoSJ.Phi())
                    self.h_matchedAK8Subjetmass.Fill(WHadrecoSJ.M())
                    self.h_unmatchedAK8Subjetpt.Fill(-1.)
                    self.h_unmatchedAK8Subjeteta.Fill(-1.)
                    self.h_unmatchedAK8Subjetphi.Fill(-1.)
                    self.h_unmatchedAK8Subjetmass.Fill(-1.)
                if self.matchedSJ  ==0   :
                    if self.verbose : print "Filling UNmatched subjet"
                    self.h_unmatchedAK8Subjetpt.Fill(WHadrecoSJ.Perp())
                    self.h_unmatchedAK8Subjeteta.Fill(WHadrecoSJ.Eta())
                    self.h_unmatchedAK8Subjetphi.Fill(WHadrecoSJ.Phi())
                    self.h_unmatchedAK8Subjetmass.Fill(WHadrecoSJ.M())
                    self.h_matchedAK8Subjetpt.Fill(-1.)
                    self.h_matchedAK8Subjeteta.Fill(-1.)
                    self.h_matchedAK8Subjetphi.Fill(-1.)
                    self.h_matchedAK8Subjetmass.Fill(-1.)
                else :
                    if self.verbose : print "Filling OTHER - all -1 fill"
                    self.h_unmatchedAK8Subjetpt.Fill(-1.)
                    self.h_unmatchedAK8Subjeteta.Fill(-1.)
                    self.h_unmatchedAK8Subjetphi.Fill(-1.)
                    self.h_unmatchedAK8Subjetmass.Fill(-1.)
                    self.h_matchedAK8Subjetpt.Fill(-1.)
                    self.h_matchedAK8Subjeteta.Fill(-1.)
                    self.h_matchedAK8Subjetphi.Fill(-1.)  
                    self.h_matchedAK8Subjetmass.Fill(-1.)

        
            for ib, binhist in enumerate(self.WcandPtBins) :
                print "for ib {} binhist {} in self.WcandPtBins{}".format(ib, binhist , self.WcandPtBins)
                filled = False
                pthist = self.WcandSubjetpt[ib]
                etahist = self.WcandSubjeteta[ib]
                phihist = self.WcandSubjetphi[ib]
                masshist = self.WcandSubjetmass[ib]
                tau21hist = self.WcandSubjettau21[ib]
                    
                if WHadrecoSJ.Perp() > binhist[0] and WHadrecoSJ.Perp() < binhist[1] :
                    filled = True
                    if self.verbose :print "Filling binned hist {} with SJ of pt {} ".format(pthist, WHadrecoSJ.Perp())
                    pthist.Fill(WHadrecoSJ.Perp())
                    etahist.Fill(WHadrecoSJ.Eta())
                    phihist.Fill(WHadrecoSJ.Phi())
                    masshist.Fill(WHadrecoSJ.M())
                    tau21hist.Fill(WHadrecoTau21)

                else : 
                    pthist.Fill(-1.)
                    etahist.Fill(-1.)
                    phihist.Fill(-1.)
                    masshist.Fill(-1.)
                    tau21hist.Fill(-1.)
                    if self.verbose :print "Filling binned hist {} with SJ of pt {} ".format(pthist, -1)
            
            return True
# define modules using the syntax 'name = lambda : constructor' to avoid having them loaded when not needed

ttbar_semilep = lambda : TTbar_SemiLep_fullyMerged( ) 
