 //#define Histo

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include <TMinuit.h>
#include <TRandom.h>
#include <string>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include <stdio.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1I.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

// #include "BTagCalibrationStandalone.h"
// #include "BTagCalibrationStandalone.cpp"
//#include "TDCacheFile.h"

#include <TCanvas.h>
#include <TLegend.h>
#include <TList.h>
#include <Riostream.h>
#include <TGraphAsymmErrors.h>
#include <map>

//#include <TRFIOFile.h>

#include "TMath.h"
#include <vector>
#include <TList.h>
#include <TLatex.h>
#include <Riostream.h>
#include <set>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "TKDE.h"

#include <iostream>
#include <array>

//using namespace std;
//using namespace TMath; // To include TMath class functions
//using namespace ROOT;


  // =====Global variables for general purpose
    float dEta = -1.0 , dPhi = -1.0 , dR = 0.0, dPt_mu_jet = 0.0 , dR_mu_jet = 0.0 ;
    
    float passed_dR = 0.0 , passed_dPt = 0.0 , passed_both_dRdPt = 0.0 , passed_no_dRdPt = 0.0 , passed_total_events = 0.0, passed_only_dRdPt = 0.0 ;

    float passed_nojet = 0.0 ;

    double factor = 1.0 , lumi_factor = 1.0 ;  

    float  Parent_Mass = 0.0 ;
    
    std::string Sample_Name ;

    TString Type_of_Muon, Type_of_Jet , Trigger_Check;
  
    vector <int> CatI_Objects;            // for Higgs, b, l & MET 
  
    int T_top  = -1 ;
    int Top_W  = -1 ;
    int top_muon = -1 ;
    int top_electron = -1 ;
    int nearest_jet = -1 ;
    int top_bjet  = -1 ;

    float  P_zv_1         = 0.0 ;
    float  P_zv_2         = 0.0 ;
    float  P_zv           = 0.0 ;
  
    TLorentzVector Top_candidate_1, Top_candidate_2 ;

    TLorentzVector neutrino1, neutrino2, top_bjet_candidate ;

    TLorentzVector Lepton_vector ;     

    Long64_t                 Entries_data;
  
    double Higgs_SDMassCorr = 0.0, Scalar_Sum_pT = 0.0 ;
  
    //---- Cut arrays for different sets------
      float METCut[5] = { 50.0, 50.0, 50.0, 50.0, 50.0} ;
      float Pt_Cut[5] = { 300.0, 300.0, 300.0, 300.0, 300.0} ;
      float St_Cut[8] = { 1000.0, 800.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0} ;
      float Pt_Bjet_Cut[5] = { 200.0, 300.0, 350.0, 400.0, 500.0 };
    
    // =========Vector Elements ===============
      vector <int> n_AK8Jet;
      vector <int> n_ele;
      vector <int> n_Mu ;
      vector <int> b_jet;
      vector <int> n_cleanjet;
      vector <int> b_jettight;
      vector <int> n_jet;
      vector <int> q_jet;
      vector <int> n_forwjet;
      vector <int> b_jetmedium;
      vector <int> puppib_jetloose;
      vector <int> puppib_jet;
      vector <int> puppib_jettight;
      vector <int> puppin_jet;
      vector <int> puppin_forwjet;
      vector <int> puppib_jetmedium;
      vector <int> jet_copy;
      vector <int> jet_sort;      
      vector <int> fjet_sort;      
      vector <int> fjet_copy;
      vector <int> fatjet_copy  ;
      vector <int> fatjet_sort  ;
      
      vector <int> b_jetloose;
      vector <int> not_tagged_bjets ;

      
      vector <int> gen_Wboson    ;
      vector <int> Higgsjets ;
      vector <int> DeltaR_Cleared_Higgsjet ;
      
      vector <int> gen_udscquark ;
      vector <int> W_boson;
      std::vector<int> Unmatched_fatjet;
    //================Global variables for muon , bjet and Higgsjet ===============
    
      int Tprime_muon      = -1 ;
      int Tprime_bjet      = -1 ;
      int Tprime_Higgs     = -1 ; 
      int gen_jet_object   = -1 ;
      int gen_topquark     = -1 ;
      int gen_bquark       = -1 ;

      int Higgs_300        = -1 ;
      int Higgs_400        = -1 ;      
      int bjet_L           = -1 ;      
      int bjet_M           = -1 ;            
      int gen_Tmuon_idx           = -1 ;      
      int gen_Tele_idx     = -1 ;      
      int muon_M           = -1 ;                  

      TString jet_type ;
    
    
    // for puppiSD Mass  correction from puppiCorr.root file
       TFile  *fi ;   
       TF1* puppisd_corrGEN   ;    
       TF1* puppisd_corrRECO_cen ;    
       TF1* puppisd_corrRECO_for ; 
    
    // for muon ID scale factors from efficiency root files
       TH2F*  muon_histo_scale_BCDEF ;
       TH2F*  muon_histo_scale_GH ;
       double muon_ID_factor = 1.0;
    
    //list of histograms
    
      TH1D* Cut_Efficiency_Flow ;

      TH1D* Cut_MiniIso_n_2DLepIso_Flow ;
      TH1D* Cut_MET_Cut_Flow ;
      TH1D* Cut_ST_Cut_Flow ;
      TH1D* Cut_Tau42_Flow ;
      TH1D* Cut_DeepMD_H_Flow ;
      TH1D*  Cut_Higgs_Tagging_Flow ;
      TH1D* Cut_pTHiggs_Flow ;
      TH1D* Cut_SDMass_Flow ;
      TH1D* Cut_ST_Tau42_Flow ;
    
    //=======PileUp Reweighted Scale Factors==========================================
  
      TFile  *PileUp_file ;   
      TH1D*  PieUp_ScaleFactor  ;  
    
      std::map<std::string,double> Luminosity_Normalized_factor = { { "Signal_Files/TprimeB_M1500_V3_", 0.003918872 },  
                                                                   { "list_of_Bkgfiles/Bkg_TTbar_v3_", 0.340461318 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",  275.125841637 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_", 114.422768115 },
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_", 39.277533015 },   
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_", 3.654182189 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_", 0.73909964 },   
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_", 0.22617188 },
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_", 0.04281123 },  
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_", 0.014520617 } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",    4.8467027  } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",   4.8579958   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",   2.5917885   } ,  
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",   0.89134297   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",   0.11482444   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",  0.12691790    } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_", 0.19640666   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",  0.0045575256  }    
                                                                 } ;                                                                                                                       
  


    // ===================create an array of Histograms======================
    // Category wise tag object Histogram // main code
  
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Pt;
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Mt ;  
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Eta ;                          
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Phi ;                          
      std::array< std::array< TH1D*, 2> , 6> h_Histo_Mass ;  
      std::array< std::array< TH1D*, 2> , 6> h_Histo_SD ;  
      std::array< std::array< TH1D*, 2> , 6> h_Histo_tau ; 
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dR ;   
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dEta ;  
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dPhi ;  
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dPt ;   


  
  
    // tag object histogram before Category selection // main code
      std::array< TH1D*, 4> h_tag_N ;  
      std::array< TH1D*, 6> h_tag_Pt ;  
      std::array< TH1D*, 6> h_tag_Eta ;                          
      std::array< TH1D*, 6> h_tag_Mass ;  
      std::array< TH1D*, 6> h_tag_PUPPImass ;
      std::array< TH1D*, 6> h_tag_SD ;  
      std::array< TH1D*, 6> h_tag_Pruned;
      std::array< TH1D*, 6> h_tag_tau21 ;  
      std::array< TH1D*, 6> h_tag_tau32 ;  
      std::array< TH1D*, 6> h_tag_Puppitau21 ;  
      std::array< TH1D*, 6> h_tag_Puppitau32 ;  
      std::array< TH1D*, 6> h_tag_Puppitau42 ;  
      std::array< TH1D*, 6> h_tag_CHStau42 ;  
      std::array< std::array< TH1D*,  6> ,  6> h_dR_tagjet ;
  
  
    // dR, dEta, dPhi Histogram for tagjet - reco object // main code
      std::array< TH1D*, 6>  h_dR_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dPt_lep_tagjet ;
      std::array< TH1D*, 6>  h_dR_Recob1_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recob1_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recob1_tagjet ;   
      std::array< TH1D*, 6>  h_dR_Recob2_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recob2_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recob2_tagjet ;
  
  
    // mc level object histogram
      std::array< TH1D*, 7>  h_mcobject_pt;
      std::array< TH1D*, 7>  h_mcobject_eta;
      std::array< TH1D*, 7>  h_mcobject_mass;   
      std::array< std::array< TH1D*, 7> , 7>  h_dR_MC ;
      std::array< std::array< TH1D*, 7> , 7>  h_dPt_MC ;
      std::array< std::array< TH1D*, 5> , 5>  h_dR_MCReco ;
  
  
    // reco object variables histogram // main code
      std::array< TH1D*, 15>  h_object_pt ;
      std::array< TH1D*, 15>  h_object_eta ;
      std::array< TH1D*, 15>  h_object_phi ;      
      std::array< TH1D*, 8>  h_object_no ;
      std::array< TH1D*, 3>  h_AK8_Jetmass ;
      std::array< TH1D*, 3>  h_AK8_PUPPImass ;
      std::array< TH1D*, 3>  h_AK8_PUPPISDmass;
      std::array< TH2F*, 3>  h_AK8_PUPPIvsmass ;
      std::array< TH2F*, 3>  h_AK8_CHSvsmass ;
      std::array< TH1D*, 3>  h_AK8_CHSmass ;
      std::array< TH1D*, 3>  h_AK8_PUPPItau21 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau31 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau32 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau41 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau42 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau43 ; 
      std::array< TH1D*, 3>  h_AK8_tau21 ; 
      std::array< TH1D*, 3>  h_AK8_tau32 ; 
      std::array< TH1D*, 3>  h_AK8_CHStau42 ; 
      std::array< std::array< TH1D*, 14> , 14>  h_dR_Reco ;
      std::array< std::array< TH1D*, 14> , 14>  h_dEta_Reco ;
      std::array< std::array< TH1D*, 14> , 14>  h_dPhi_Reco ;   
      std::array< TH1D*, 14>  h_dPt_Reco ;
      std::array< std::array< TH1D*, 2> , 2>  h_dR_Reco_lt04  ;
      std::array< std::array< TH1D*, 2> , 2>  h_dPt_Reco_lt10 ;
      std::array< std::array< TH1D*, 2> , 2>  h_dPt_Reco_lt15 ;


      std::array< TH1D*, 3>  h_MET_var ;
      std::array< TH1D*, 9>  h_object_MT ;



      // dPt_dR_mubjet->GetYaxis()->SetTitle("dPT(mu,jet)");
      // dPt_dR_mubjet         ->GetXaxis()->SetTitle("dR(mu,jet)");
      TH2F* dRHbjet_dRlbjet ;
  
      std::array< TH2F*, 4>  h_AK81vsGenObj ;
      std::array< TH2F*, 4>  h_AK82vsGenObj ;
      std::array< TH2F*, 4>  h_AK83vsGenObj ;

      TH1D* h_MC ;  
      TH1D* Good_PV_Histo ;
      TH1D* Good_PV_Pr_Histo ;
      TH1D* ST_Sum_Presel ;
      TH1D* ST_Sum_Evesel ;

      TH1D* h_jetPt_before_jetclean ;
      TH1D* h_jetPt_after_jetclean  ;
      TH1D* h_jetPt_corr_factors ;
      TH2D* h_leadjetPt_factors;
      TH2D* h_subleadjetPt_factors ;

      TH2D* h_leadjetEta_factors   ;
      TH2D* h_subleadjetEta_factors;
      TH2D* h_leadjetPhi_factors   ;
      TH2D* h_subleadjetPhi_factors      ;




      TH2D*  h_leadjetPt_before_after ;

      TH2D*  h_subleadjetPt_before_after  ;

      TH1D* ST_Sum_LeadObj ;  
    // for muon ID study, we define new sets of histogram for pt, eta, phi, vertex
  
      TH1D* Match_Muon_Eta ;
      TH1D* Match_Muon_Phi ;
      TH1D* Match_Primary_Vertex ;
  
      TH1D* Match_Muon_Pt300 ;  // for pT < 300GeV
      TH1D* Match_Muon_Pt1000 ; // for pT > 300GeV
      TH1D* Muon_Pt_ratio ;

      TH1D* Gen_Match_Jet_Pt ; // make histo for efficiency comparisons of Higgs 

      TH1D* h_dR_ak41_ak8Jet1 ;
      TH1D* h_dR_ak42_ak8Jet1 ;
      TH1D* h_dR_ak43_ak8Jet1 ;
      TH1D* h_dR_ak41_ak8Jet2 ;
      TH1D* h_dR_ak42_ak8Jet2 ;
      TH1D* h_dR_ak43_ak8Jet2 ;

      TH1D* h_Wbos1_Mass ;
      TH1D* h_Wbos2_Mass ; 
      TH1D* h_Wbos_Mass_Img ; 

      TH1D* h_Top1_Mass ;
      TH1D* h_Top2_Mass ;      
      TH1D* h_Higgs_Mass ;    

      TH1D* h_Tprime1_Mass ;  
      TH1D* h_Tprime2_Mass ;

      TH1D*  h_dR_Higgs_wrt_Top1 ;
      TH1D*  h_dR_Higgs_wrt_Top2 ;
      TH1D*  h_dR_Higgs_wrt_Topb ;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////==============CREATE NEW SETS OF HISTOGRAM FOR PHASE III==================///////////////////  
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // reco object variables histogram // main code
      std::array< TH1D*, 17>  Hist_object_pt ;
      std::array< TH1D*, 17>  Hist_object_eta ;
      std::array< TH1D*, 17>  Hist_object_phi ;   

      // Histograms for leading and subleading fatjet
      std::array< TH1D*, 20>  Hist_for_Leading_FatJet ; 
      std::array< TH1D*, 20>  Hist_for_Subleading_FatJet ; 
      std::array< TH1D*, 23>  Hist_for_Leading_HiggsJet ; 
      
      std::array< TH1D*, 9>   DeltaR_Hist_FatJet_wrt_jet ;   
      std::array< TH1D*, 9>   DeltaR_Hist_Muon_wrt_jet ; 

      std::array< TH1D*, 9>   Hist_for_bTag_Variable ;   



      // Histograms for Lepton-Jet Cleaned Jets  ===== COmparing before and after effects
      std::array< TH1D*, 20>  Hist_for_LeptonCleaned_Jet ; 
      std::array< TH1D*, 16>  Hist_for_LeptonCleaned_FatJet ;


      TH2F* dPt_dR_mu_cleanjet1  ; 
      TH2F* dPt_dR_mu_jet1  ; 

      TH2F* dPt_dR_mu_cleanjet2  ; 
      TH2F* dPt_dR_mu_jet2  ; 

      std::array< TH2D*, 8> Hist_DeltaR_wrt_Pt_LepCleanJet  ;
      std::array< TH2D*, 4> Hist_DeltaPt_wrt_Pt_LepCleanJet ;

      std::array< TH2D*, 4> Hist_SoftDropMass_wrt_Tau42_LeadFatJet ;    
      std::array< TH2D*, 4> Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet ;    

      //----HISTOGRAMS SETS FOR bTAGGING EFFICIENCIES -----------------------------

      std::array< TH2D*, 3> Hist_2D_BtagEff_Denom  ;
      std::array< TH2D*, 3> Hist_2D_BtagEff_Num ;      


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////============== NEW SETS OF HISTOGRAM FOR PHASE III==================/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////




      void  Clear_Vector() {
         //   for clearing objects vector
         n_AK8Jet.clear(); 
         n_ele.clear(); 
         n_Mu.clear();
         n_jet.clear();    // main code
         n_cleanjet.clear();

         q_jet.clear();    // main code
         n_forwjet.clear(); // main code
         b_jetloose.clear();// main code
         b_jet.clear();    // main code
         b_jetmedium.clear();    // main code
         b_jettight.clear();    // main code

         jet_copy.clear();
         jet_sort.clear();         

         fjet_copy.clear();
         fjet_sort.clear();    

         fatjet_copy.clear()  ;
         fatjet_sort.clear()  ;

         puppin_jet.clear();    // main code
         puppin_forwjet.clear(); // main code
         puppib_jetloose.clear();// main code
         puppib_jet.clear();    // main code
         puppib_jetmedium.clear();    // main code
         puppib_jettight.clear();    // main code

         Higgsjets.clear() ;
         DeltaR_Cleared_Higgsjet.clear();
         W_boson.clear();
         CatI_Objects.clear() ;    

         gen_Wboson.clear();
         gen_udscquark.clear();      

         Unmatched_fatjet.clear() ;   

         not_tagged_bjets.clear() ;        
      }

    // ======================LepIsoCut Study =======================================================
      std::map<int, TString > Cut_LepIso_Variable = {
                                                   { 1  , "Preselect"},
                                                   { 2  , "TkIsoLoose"} ,
                                                   { 3  , "TkIsoTight"} ,                 
                                                   { 4  , "MiniIsoLoose"} ,                  
                                                   { 5  , "MiniIsoMedium"} ,
                                                   { 6  , "MiniIsoTight"} ,
                                                   { 7  , "MiniIsoVeryTight"} ,
                                                   } ;
      


      std::map<int, TString > Cut_Check_Variable = {
                                                   { 1  , "Preselect"     },
                                                   { 2  , "MiniIsolation" } ,
                                                   { 3  , "TrackIsolation"} ,                                                   
                                                   { 4  , "dRgt04dPtgt00" } ,                                                    
                                                   { 5  , "dRgt04dPtgt10" } ,
                                                   { 6  , "dRgt03dPtgt05" } ,
                                                   { 7  , "dRgt03dPtgt10" } ,
                                                   { 8  , "dRgt02dPtgt05" } ,
                                                   { 9  , "dRgt02dPtgt10" } ,
                                                   { 10 , "dRgt01dPtgt05" } ,
                                                   { 11 , "dRgt01dPtgt10" } ,
                                                   } ;


      std::map<TString, double > Cut_LepIso_Test_dR  ={
                                                       {  "dRgt04dPtgt00" , 0.4 } ,  // for dr >  0.4 || dpt  >  05.0 
                                                       {  "dRgt04dPtgt10" , 0.4 } ,  // for dr >  0.4 || dpt  >  10.0 
                                                       {  "dRgt03dPtgt05" , 0.3 } ,  // for dr >  0.3 || dpt  >  05.0 
                                                       {  "dRgt03dPtgt10" , 0.3 } ,  // for dr >  0.3 || dpt  >  10.0 
                                                       {  "dRgt02dPtgt05" , 0.2 } ,  // for dr >  0.2 || dpt >   05.0 
                                                       {  "dRgt02dPtgt10" , 0.2 } ,  // for dr >  0.2 || dpt  >  10.0 
                                                       {  "dRgt01dPtgt05" , 0.1 } ,  // for dr >  0.1 || dpt  >  05.0 
                                                       {  "dRgt01dPtgt10" , 0.1 } ,  // for dr >  0.1 || dpt  >  10.0 
                                                    };



      std::map<TString, double > Cut_LepIso_Test_dPt  ={
                                                         {  "dRgt04dPtgt00" , -1.0  } ,  // for dr >  0.4 || dpt  >  5.0 
                                                         {  "dRgt04dPtgt10" , 10.0 } ,  // for dr >  0.4 || dpt  >  10.0 
                                                         {  "dRgt03dPtgt05" , 5.0  } ,  // for dr >  0.3 || dpt  >  05.0 
                                                         {  "dRgt03dPtgt10" , 10.0 } ,  // for dr >  0.3 || dpt  >  10.0 
                                                         {  "dRgt02dPtgt05" , 5.0  } ,  // for dr >  0.2 || dpt  >  05.0 
                                                         {  "dRgt02dPtgt10" , 10.0 } ,  // for dr >  0.2 || dpt  >  10.0 
                                                         {  "dRgt01dPtgt05" , 5.0  } ,  // for dr >  0.1 || dpt  >  05.0 
                                                         {  "dRgt01dPtgt10" , 10.0 } ,  // for dr >  0.1 || dpt  >  10.0                                                                                                                                                                                                                                                                                     
                                                      };                            

 
    



// ============================================================================================================


//// // //  //       //       ////           //////////   ////////            //////////   
//      //  //       //      //   //         //           //                         // 
//      //  //       //     //     //        //           //                        //
// //////   //// //////    // // // //       //////////   //////     =======    /////
//          //       //   //         //              //   //                       \\\
//          //       //  //           //             //   //                        \\\
//          //       // //             //    //////////   ////////            ///////\\\


///////////////////////////////////////////////////////////////////////////////////////////////////////
//PHASE_III Functions AND HISTOGRAMS..........REMEBER TO CHECK AND EDIT FROM HERE
////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////=========THIS SECTION FOR DEFINING MAPS & KEYS=============//////////////////////////////////////////////////////////////////////////
   std::map<int, TString > Histogram_Object_List = {
                                                   { 0   , "Hist_nMET"}, 
                                                   { 1   , "Hist_nElectron"}, 
                                                   { 2   , "Hist_nMuon"}, 
                                                   { 3   , "Hist_nJet"}, 
                                                   { 4   , "Hist_nFatJet"}, 
                                                   { 5   , "Hist_nForwJet"}, 
                                                   { 6   , "Hist_nCleanJet"}, 
                                                   { 7   , "Hist_nbjet"}, 
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ; 



   std::map<int, TString > Histogram_Pt_List = {
                                                   { 0   , "Hist_MET_pt"}, 
                                                   { 1   , "Hist_MET_sumEt"}, 
                                                   { 2   , "Hist_Electron1_pt"}, 
                                                   { 3   , "Hist_Electron2_pt"}, 
                                                   { 4   , "Hist_Muon1_pt"}, 
                                                   { 5   , "Hist_Muon2_pt"}, 
                                                   { 6   , "Hist_Jet1_pt"}, 
                                                   { 7   , "Hist_Jet2_pt"}, 
                                                   { 8   , "Hist_FatJet1_pt"}, 
                                                   { 9   , "Hist_FatJet2_pt"},  
                                                   { 10  , "Hist_ForwJet1_pt"}, 
                                                   { 11  , "Hist_ForwJet2_pt"}, 
                                                   { 12  , "Hist_CleanJet1_pt"}, 
                                                   { 13  , "Hist_CleanJet2_pt"}, 
                                                   { 14  , "Hist_bJet1_pt"}, 
                                                   { 15  , "Hist_bJet2_pt"}, 
                                                   { 16  , "Hist_topbJet_pt"},   
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;

   std::map<int, TString > Histogram_Eta_List = {
                                                   { 0   , "Hist_MET_eta1"}, 
                                                   { 1   , "Hist_MET_eta2"}, 
                                                   { 2   , "Hist_Electron1_eta"}, 
                                                   { 3   , "Hist_Electron2_eta"}, 
                                                   { 4   , "Hist_Muon1_eta"}, 
                                                   { 5   , "Hist_Muon2_eta"}, 
                                                   { 6   , "Hist_Jet1_eta"}, 
                                                   { 7   , "Hist_Jet2_eta"}, 
                                                   { 8   , "Hist_FatJet1_eta"}, 
                                                   { 9   , "Hist_FatJet2_eta"},  
                                                   { 10  , "Hist_ForwJet1_eta"}, 
                                                   { 11  , "Hist_ForwJet2_eta"}, 
                                                   { 12  , "Hist_CleanJet1_eta"}, 
                                                   { 13  , "Hist_CleanJet2_eta"}, 
                                                   { 14  , "Hist_bJet1_eta"}, 
                                                   { 15  , "Hist_bJet2_eta"}, 
                                                   { 16  , "Hist_topbJet_eta"},                                                      
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;       

   std::map<int, TString > Histogram_Phi_List = {
                                                   { 0   , "Hist_MET_phi1"}, 
                                                   { 1   , "Hist_MET_phi2"}, 
                                                   { 2   , "Hist_Electron1_phi"}, 
                                                   { 3   , "Hist_Electron2_phi"}, 
                                                   { 4   , "Hist_Muon1_phi"}, 
                                                   { 5   , "Hist_Muon2_phi"}, 
                                                   { 6   , "Hist_Jet1_phi"}, 
                                                   { 7   , "Hist_Jet2_phi"}, 
                                                   { 8   , "Hist_FatJet1_phi"}, 
                                                   { 9   , "Hist_FatJet2_phi"},  
                                                   { 10  , "Hist_ForwJet1_phi"}, 
                                                   { 11  , "Hist_ForwJet2_phi"}, 
                                                   { 12  , "Hist_CleanJet1_phi"}, 
                                                   { 13  , "Hist_CleanJet2_phi"}, 
                                                   { 14  , "Hist_bJet1_phi"}, 
                                                   { 15  , "Hist_bJet2_phi"}, 
                                                   { 16  , "Hist_topbJet_phi"},                                                      
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;  

   std::map<int, TString > Histogram_FatJet_List = {

                                                { 0    , "Hist_FatJet1_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_FatJet1_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_FatJet1_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_FatJet1_deepTag_H"},
                                                { 4    , "Hist_FatJet1_deepTag_TvsQCD"},
                                                { 5    , "Hist_FatJet1_deepTag_WvsQCD"},
                                                { 6    , "Hist_FatJet1_tau1"},
                                                { 7    , "Hist_FatJet1_tau2"},
                                                { 8    , "Hist_FatJet1_tau3"},
                                                { 9    , "Hist_FatJet1_tau4"},
                                                { 10   , "Hist_FatJet1_ratio_tau21"}, 
                                                { 11   , "Hist_FatJet1_ratio_tau31"},
                                                { 12   , "Hist_FatJet1_ratio_tau32"}, 
                                                { 13   , "Hist_FatJet1_ratio_tau41"}, 
                                                { 14   , "Hist_FatJet1_ratio_tau42"}, 
                                                { 15   , "Hist_FatJet1_ratio_tau43"}, 
                                                { 16   , "Hist_FatJet1_mass"},
                                                { 17   , "Hist_FatJet1_msoftdrop"},
                                                { 18   , "Hist_FatJet1_msoftdrop_corr"} ,
                                               
                                                { 19   , "Hist_FatJet1_SoftDropMass_wrt_deepTagMD_H4qvsQCD"},                                                
                                                { 20   , "Hist_FatJet1_SoftDropMass_wrt_deepTag_H"},
                                                { 21   , "Hist_FatJet1_SoftDropMass_wrt_tau42"}, 
                                                { 22   , "Hist_FatJet1_SoftDropMass_wrt_tau41"}, 
                                                  
                                                };

   std::map<int, TString > Histogram_FatJet2_List = {                                                                                               
                                                { 0    , "Hist_FatJet2_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_FatJet2_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_FatJet2_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_FatJet2_deepTag_H"},
                                                { 4    , "Hist_FatJet2_deepTag_TvsQCD"},
                                                { 5    , "Hist_FatJet2_deepTag_WvsQCD"},
                                                { 6    , "Hist_FatJet2_tau1"},
                                                { 7    , "Hist_FatJet2_tau2"},                                     
                                                { 8    , "Hist_FatJet2_tau3"},                                                
                                                { 9    , "Hist_FatJet2_tau4"},
                                                { 10   , "Hist_FatJet2_ratio_tau21"}, 
                                                { 11   , "Hist_FatJet2_ratio_tau31"},
                                                { 12   , "Hist_FatJet2_ratio_tau32"}, 
                                                { 13   , "Hist_FatJet2_ratio_tau41"}, 
                                                { 14   , "Hist_FatJet2_ratio_tau42"},                                                
                                                { 15   , "Hist_FatJet2_ratio_tau43"},                                                
                                                { 16   , "Hist_FatJet2_mass"},
                                                { 17   , "Hist_FatJet2_msoftdrop"},
                                                { 18   , "Hist_FatJet2_msoftdrop_corr"} ,

                                                { 19   , "Hist_FatJet2_SoftDropMass_wrt_deepTagMD_H4qvsQCD"}, 
                                                { 20   , "Hist_FatJet2_SoftDropMass_wrt_deepTag_H"},
                                                { 21   , "Hist_FatJet2_SoftDropMass_wrt_tau42"}, 
                                                { 22   , "Hist_FatJet2_SoftDropMass_wrt_tau41"}, 
                                                };


   std::map<int, TString > Histogram_DeltaR_FatJet_List = {                                                                                               
                                                    { 0    , "DeltaR_Hist_FatJet1_wrt_jet1"},
                                                    { 1    , "DeltaR_Hist_FatJet1_wrt_jet2"},
                                                    { 2    , "DeltaR_Hist_FatJet1_wrt_jet3"},
                                                    { 3    , "DeltaR_Hist_FatJet2_wrt_jet1"},
                                                    { 4    , "DeltaR_Hist_FatJet2_wrt_jet2"},
                                                    { 5    , "DeltaR_Hist_FatJet2_wrt_jet3"},
                                                    { 6    , "DeltaR_Hist_FatJet3_wrt_jet1"},
                                                    { 7    , "DeltaR_Hist_FatJet3_wrt_jet2"},
                                                    { 8    , "DeltaR_Hist_FatJet3_wrt_jet3"},

                                                    } ;



   std::map<int, TString > Histogram_DeltaR_Muon_List = {                                                                                               
                                                    { 0    , "DeltaR_Hist_Muon_wrt_jet1"},
                                                    { 1    , "DeltaR_Hist_Muon_wrt_jet2"},
                                                    { 2    , "DeltaR_Hist_Muon_wrt_jet3"},
                                                    { 3    , "DeltaR_Hist_Muon_wrt_cleanjet1"},
                                                    { 4    , "DeltaR_Hist_Muon_wrt_cleanjet2"},
                                                    { 5    , "DeltaR_Hist_Muon_wrt_cleanjet3"},
                                                    { 6    , "DeltaR_Hist_Muon_wrt_bjet1"},
                                                    { 7    , "DeltaR_Hist_Muon_wrt_bjet2"},
                                                    { 8    , "DeltaR_Hist_Muon_wrt_bjet3"},
                                                    } ;


   std::map<int, TString > Histogram_Higgs_List = {

                                                { 0    , "Hist_HiggsJet_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_HiggsJet_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_HiggsJet_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_HiggsJet_deepTag_H"},
                                                { 4    , "Hist_HiggsJet_deepTag_TvsQCD"},
                                                { 5    , "Hist_HiggsJet_deepTag_WvsQCD"},
                                                { 6    , "Hist_HiggsJet_ratio_tau21"}, 
                                                { 7    , "Hist_HiggsJet_ratio_tau31"},
                                                { 8    , "Hist_HiggsJet_ratio_tau32"}, 
                                                { 9    , "Hist_HiggsJet_ratio_tau41"}, 
                                                { 10   , "Hist_HiggsJet_ratio_tau43"},                                                 
                                                { 11   , "Hist_HiggsJet_ratio_tau42"}, 
                                                { 12   , "Hist_HiggsJet_msoftdrop"},                                                
                                                { 13   , "Hist_HiggsJet_mass"},
                                                { 14   , "Hist_HiggsJet_pt"},
                                                { 15   , "Hist_HiggsJet_eta"},                                                
                                                { 16   , "Hist_N_HiggsJet"},
                                                { 17   , "Hist_DeltaR_HiggsJet_wrt_lep"} ,
                                                { 18   , "Hist_DeltaR_HiggsJet_wrt_jet1"} , 
                                                { 19   , "Hist_DeltaR_HiggsJet_wrt_jet2"} ,
                                                { 20   , "Hist_DeltaR_HiggsJet_wrt_jet3"}  ,                                                                                                                                                                                              
                                                { 21   , "Hist_HiggsJet_msoftdrop_corr"}  ,                                              
                                                { 22   , "Hist_N_DeltaR_ClearedHiggsJet"}
                                             };


   std::map<int, TString > Histogram_LepCleanJet_List = {
                                                            { 0   , "Hist_Cleanjet1_pt"}, 
                                                            { 1   , "Hist_Cleanjet2_pt"}, 
                                                            { 2   , "Hist_UnCleanJet1_pt"}, 
                                                            { 3   , "Hist_UnCleanJet2_pt"}, 
                                                            { 4   , "Hist_Cleanjet1_eta"}, 
                                                            { 5   , "Hist_Cleanjet2_eta"}, 
                                                            { 6   , "Hist_UnCleanJet1_eta"}, 
                                                            { 7   , "Hist_UnCleanJet2_eta"}, 
                                                            { 8   , "Hist_Cleanjet1_phi"}, 
                                                            { 9   , "Hist_Cleanjet2_phi"}, 
                                                            { 10  , "Hist_UnCleanJet1_phi"}, 
                                                            { 11  , "Hist_UnCleanJet2_phi"}, 
                                                            { 12  , "DeltaR_Hist_Muon_wrt_Cleanjet1"}, 
                                                            { 13  , "DeltaR_Hist_Muon_wrt_Cleanjet2"}, 
                                                            { 14  , "DeltaR_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            { 15  , "DeltaR_Hist_Muon_wrt_UnCleanjet2"}, 
                                                            { 16  , "DeltaPt_Hist_Muon_wrt_Cleanjet1"}, 
                                                            { 17  , "DeltaPt_Hist_Muon_wrt_Cleanjet2"}, 
                                                            { 18  , "DeltaPt_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            { 19  , "DeltaPt_Hist_Muon_wrt_UnCleanjet2"},  
                                                       } ;


   std::map<int, TString > Histogram_LepCleanFatJet_List = {
                                                                  { 0   , "Hist_CleanFatJet1_pt"}, 
                                                                  { 1   , "Hist_CleanFatJet2_pt"}, 
                                                                  { 2   , "Hist_UnCleanFatJet1_pt"}, 
                                                                  { 3   , "Hist_UnCleanFatJet2_pt"}, 
                                                                  { 4   , "Hist_CleanFatJet1_eta"}, 
                                                                  { 5   , "Hist_CleanFatJet2_eta"}, 
                                                                  { 6   , "Hist_UnCleanFatJet1_eta"}, 
                                                                  { 7   , "Hist_UnCleanFatJet2_eta"}, 
                                                                  { 8   , "Hist_CleanFatJet1_phi"}, 
                                                                  { 9   , "Hist_CleanFatJet2_phi"}, 
                                                                  { 10  , "Hist_UnCleanFatJet1_phi"}, 
                                                                  { 11  , "Hist_UnCleanFatJet2_phi"}, 
                                                                  { 12  , "DeltaR_Hist_Muon_wrt_Cleanfatjet1"}, 
                                                                  { 13  , "DeltaR_Hist_Muon_wrt_Cleanfatjet2"}, 
                                                                  { 14  , "DeltaR_Hist_Muon_wrt_UnCleanfatjet1"}, 
                                                                  { 15  , "DeltaR_Hist_Muon_wrt_UnCleanfatjet2"}, 
                                                                  // { 17  , "Hist_"}, 
                                                                  // { 18  , "Hist_"}, 
                                                                  // { 19  , "Hist_"}, 
                                                                  // { 20  , "Hist_"},  
                                                            } ;

   std::map<int, TString > Histogram_Delta_wrt_Pt_LepCleanJet_List = {
                                                            { 0   , "DeltaR_wrt_Pt_Hist_for_Cleanjet1"},  
                                                            { 1   , "DeltaR_wrt_Pt_Hist_for_Cleanjet2"},  
                                                            { 2   , "DeltaR_wrt_Pt_Hist_for_UnCleanjet1"}, 
                                                            { 3   , "DeltaR_wrt_Pt_Hist_for_UnCleanjet2"}, 
                                                            { 4   , "DeltaR_wrt_Pt_Hist_for_Cleanfatjet1"},  
                                                            { 5   , "DeltaR_wrt_Pt_Hist_for_Cleanfatjet2"},  
                                                            { 6   , "DeltaR_wrt_Pt_Hist_for_UnCleanfatjet1"}, 
                                                            { 7   , "DeltaR_wrt_Pt_Hist_for_UnCleanfatjet2"}, 
                                                            { 8   , "DeltaPt_wrt_Pt_Hist_for_Cleanjet1"},  
                                                            { 9   , "DeltaPt_wrt_Pt_Hist_for_Cleanjet2"},  
                                                            { 10  , "DeltaPt_wrt_Pt_Hist_for_UnCleanjet1"}, 
                                                            { 11  , "DeltaPt_wrt_Pt_Hist_for_UnCleanjet2"}, 
                                                            // { 12  , "DeltaR_Hist_Muon_wrt_Cleanjet1"}, 
                                                            // { 13  , "DeltaR_Hist_Muon_wrt_Cleanjet2"}, 
                                                            // { 14  , "DeltaR_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            // { 15  , "DeltaR_Hist_Muon_wrt_UnCleanjet2"}, 
                                                            // { 17  , "Hist_"}, 
                                                            // { 18  , "Hist_"}, 
                                                            // { 19  , "Hist_"}, 
                                                            // { 20  , "Hist_"},  
     
                                                       } ;         

   // List for Histogram_BtagEff                                                
   std::map<int, TString > Histogram_BtagEff_Denom_List = {
                                                                { 0  , "Hist_2D_BtagEff_Denom_b"}, 
                                                                { 1  , "Hist_2D_BtagEff_Denom_c"}, 
                                                                { 2  , "Hist_2D_BtagEff_Denom_udsg"}, 
                                                                // { 6   , "Denom_"}, 
                                                                // { 7   , "Denom_"}, 
                                                                // { 17  , "Hist_"}, 
                                                                // { 18  , "Hist_"}, 
                                                                // { 19  , "Hist_"}, 
                                                                // { 20  , "Hist_"},  
                                                          } ; 


   std::map<int, TString > Histogram_BtagEff_Num_List = {
                                                              { 0  , "Hist_2D_BtagEff_Num_b"}, 
                                                              { 1  , "Hist_2D_BtagEff_Num_c"}, 
                                                              { 2  , "Hist_2D_BtagEff_Num_udsg"}, 
                                                              // { 6   , "Denom_"}, 
                                                              // { 7   , "Denom_"}, 
                                                              // { 17  , "Hist_"}, 
                                                              // { 18  , "Hist_"}, 
                                                              // { 19  , "Hist_"}, 
                                                              // { 20  , "Hist_"},  
                                                        } ;                                                    




    // Muon Isolation variables and working Points are defined using key & map========================================                                                   
    // MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
    std::map<TString, int > LepIso_IDbit = {  
                                          {"MiniIsoLoose"            , 1  } ,
                                          {"MiniIsoMedium"           , 2  } ,
                                          {"MiniIsoTight"            , 3  } ,
                                          {"MiniIsoVeryTight"        , 4  } , 
                                          {"dR_02_OR_dPt_20" , 5  } ,
                                          {"dR_03_OR_dPt_20" , 6  } ,
                                          {"dR_04_OR_dPt_20" , 7  } ,
                                          {"dR_02_OR_dPt_40" , 8  } ,
                                          {"dR_03_OR_dPt_40" , 9  } ,
                                          {"dR_04_OR_dPt_40"  , 10 } ,                                           
                                          {"dR_04_OR_dPt_60"  , 11 } ,                                          
                                       } ;                                                       

      TString Isolation_Check[11] = { 
                                      "No Isolation",             //0 
                                      "MiniIsoLoose",             //1 
                                      "MiniIsoMedium",            //2 
                                      "MiniIsoTight",             //3 
                                      "MiniIsoVeryTight",         //4 
                                      
                                      
                                      
                                      
                                      
                                      
                                    };
    std::map<float, float > LepIso2D_dR_Selection  = {
                                                       { 5 ,  0.2 } ,  // for dr >  0.2 || dpt  >  20.0 
                                                       { 6 ,  0.3 } ,  // for dr >  0.3 || dpt  >  20.0 
                                                       { 7 ,  0.4 } ,  // for dr >  0.4 || dpt  >  20.0 
                                                       { 8 ,  0.2 } ,  // for dr >  0.2 || dpt  >  40.0 
                                                       { 9 ,  0.3 } ,  // for dr >  0.3 || dpt >   40.0 
                                                       { 10,  0.4 } ,  // for dr >  0.4 || dpt  >  40.0 
                                                       { 11,  0.4 } ,  // for dr >  0.4 || dpt  >  60.0 
                                                   };



    std::map<float, float > LepIso2D_dPt_Selection  ={
                                                         {  5  ,  20.0 } ,  // for dr >  0.2 || dpt  >  20.0
                                                         {  6  ,  20.0 } ,  // for dr >  0.3 || dpt  >  20.0
                                                         {  7  ,  20.0 } ,  // for dr >  0.4 || dpt  >  20.0
                                                         {  8  ,  40.0 } ,  // for dr >  0.2 || dpt  >  40.0
                                                         {  9  ,  40.0 } ,  // for dr >  0.3 || dpt  >  40.0
                                                         {  10 ,  40.0 } ,  // for dr >  0.4 || dpt  >  40.0
                                                         {  11 ,  60.0 } ,  // for dr >  0.4 || dpt  >  60.0
                                                      }; 
    //==============Luminosity Normalization for each samples========================================================

    std::map< int, TString> New_Sample_List = {  
                                                               {  0   , "Tprime_M1000_UL17_v2",                            }, 
                                                               {  1   , "Tprime_M1500_UL17_v2",                            }, 
                                                               {  2   , "Tprime_M1800_UL17_v2",                            }, 
                                                               {  3   , "QCD_Pt-80_MuEnr_UL17_v2",                         }, 
                                                               {  4   , "QCD_Pt-120_MuEnr_UL17_v2",                        }, 
                                                               {  5   , "QCD_Pt-170_MuEnr_UL17_v2",                        }, 
                                                               {  6   , "QCD_Pt-300_MuEnr_UL17_v2",                        }, 
                                                               {  7   , "QCD_Pt-470_MuEnr_UL17_v2",                        }, 
                                                               {  8   , "QCD_Pt-600_MuEnr_UL17_v2",                        }, 
                                                               {  9   , "QCD_Pt-800_MuEnr_UL17_v2",                        }, 
                                                               {  10  , "QCD_Pt-1000_MuEnr_UL17_v2",                       },
                                                               {  11  , "ST_s-channel_4f_leptonDecays_UL17_v2"             }, 
                                                               {  12  , "ST_t-channel_antitop_4f_inclusiveDecays_UL17_v2"  }, 
                                                               {  13  , "ST_t-channel_top_4f_inclusiveDecays_UL17_v2"     }, 
                                                               {  14  , "ST_tW_top_5f_inclusiveDecays_UL17_v2"            }, 
                                                               {  15  , "ST_tW_antitop_5f_inclusiveDecays_UL17_v2"        },
                                                               {  16  , "TT_to_Hadronic_UL17_v2"     },
                                                               {  17  , "TT_to_SemiLeptonic_UL17_v2" },
                                                               {  18  , "TT_to_2L2Nu_UL17_v2"        },     
                                                               {  19  , "QCD_Pt-50_EMEnr_UL17_v2"  },  
                                                               {  20  , "QCD_Pt-80_EMEnr_UL17_v2"  },  
                                                               {  21  , "QCD_Pt-120_EMEnr_UL17_v2" },  
                                                               {  22  , "QCD_Pt-170_EMEnr_UL17_v2" },  
                                                               {  23  , "QCD_Pt-300_EMEnr_UL17_v2" },   
                                                               {  24  , "WJets_LNu_HT-70To100_UL17_v2"    } ,
                                                               {  25  , "WJets_LNu_HT-100To200_UL17_v2"   } ,
                                                               {  26  , "WJets_LNu_HT-200To400_UL17_v2"   } ,  
                                                               {  27  , "WJets_LNu_HT-400To600_UL17_v2"   } ,
                                                               {  28  , "WJets_LNu_HT-600To800_UL17_v2"   } ,
                                                               {  29  , "WJets_LNu_HT-800To1200_UL17_v2"  } ,
                                                               {  30  , "WJets_LNu_HT-1200To2500_UL17_v2" } ,
                                                               {  31  , "WJets_LNu_HT-2500ToInf_UL17_v2"  } , 
                                                               {  32  , "DYJetsToLL_M-50_HT-70To100_UL17_v2"   } ,
                                                               {  33  , "DYJetsToLL_M-50_HT-100To200_UL17_v2"   } ,
                                                               {  34  , "DYJetsToLL_M-50_HT-200To400_UL17_v2"   } ,  
                                                               {  35  , "DYJetsToLL_M-50_HT-400To600_UL17_v2"   } ,
                                                               {  36  , "DYJetsToLL_M-50_HT-600To800_UL17_v2"   } ,
                                                               {  37  , "DYJetsToLL_M-50_HT-800To1200_UL17_v2"  } ,
                                                               {  38  , "DYJetsToLL_M-50_HT-1200To2500_UL17_v2" } ,
                                                               {  39  , "DYJetsToLL_M-50_HT-2500ToInf_UL17_v2"  } , 

                                              
                                        } ;


                                        


    std::map< int, TString> Sample_List = {  // Xsections are in units fb-1 just remember
                                                               {  0   , "temp"              ,                           }, 
                                                               {  1   , "Tprime_M1000",                            }, 
                                                               {  2   , "Tprime_M1500",                            }, 
                                                               {  3   , "Tprime_M1800",                            }, 
                                                               {  4   , "TTbar",                                   }, 
                                                               {  5   , "QCD_Pt-80_MuEnr",                         }, 
                                                               {  6   , "QCD_Pt-120_MuEnr",                        }, 
                                                               {  7   , "QCD_Pt-170_MuEnr",                        }, 
                                                               {  8   , "QCD_Pt-300_MuEnr",                        }, 
                                                               {  9   , "QCD_Pt-470_MuEnr",                        }, 
                                                               {  10  , "QCD_Pt-600_MuEnr",                        }, 
                                                               {  11  , "QCD_Pt-800_MuEnr",                        }, 
                                                               {  12  , "QCD_Pt-1000_MuEnr",                       }, 
                                                               {  13  , "WJets_LNu",                               }, 
                                                               {  14  , "DYJetsToLL",                              }, 

                                                               {  15  , "ST_s-channel_4f_leptonDecays"             }, 
                                                               {  16  , "ST_t-channel_antitop_4f_inclusiveDecays"   }, 
                                                               {  17  , "ST_t-channel_top_4f_inclusiveDecays"      }, 
                                                               {  18  , "ST_tW_top_5f_inclusiveDecays"             }, 
                                                               {  19  , "ST_tW_antitop_5f_inclusiveDecays"         },

                                                               {   20  , "TT_to_Hadronic"      },
                                                               {   21  , "TT_to_SemiLeptonic"  },
                                                               {   22  , "TT_to_2L2Nu"         },     
                                                               {   23  , "QCD_Pt-50_EMEnr"},  
                                                               {   24  , "QCD_Pt-80_EMEnr"},  
                                                               {   25  , "QCD_Pt-120_EMEnr"},  
                                                               {   26  , "QCD_Pt-170_EMEnr"},  
                                                               {   27  , "QCD_Pt-300_EMEnr"},   
                                                               {   28  , "WJets_LNu_HT-70To100"     } ,
                                                               {   29  , "WJets_LNu_HT-100To200"    } ,
                                                               {   30  , "WJets_LNu_HT-200To400"    } ,  
                                                               {   31  , "WJets_LNu_HT-400To600"    } ,
                                                               {   32  , "WJets_LNu_HT-600To800"    } ,
                                                               {   33  , "WJets_LNu_HT-800To1200"   } ,
                                                               {   34  , "WJets_LNu_HT-1200To2500"  } ,
                                                               {   35  , "WJets_LNu_HT-2500ToInf"   } , 

                                                               {   36  , "DYJetsToLL_M-50_HT-70To100"    } ,
                                                               {   37  , "DYJetsToLL_M-50_HT-100To200"    } ,
                                                               {   38  , "DYJetsToLL_M-50_HT-200To400"    } ,  
                                                               {   39  , "DYJetsToLL_M-50_HT-400To600"    } ,
                                                               {   40  , "DYJetsToLL_M-50_HT-600To800"    } ,
                                                               {   41  , "DYJetsToLL_M-50_HT-800To1200"   } ,
                                                               {   42  , "DYJetsToLL_M-50_HT-1200To2500"  } ,
                                                               {   43  , "DYJetsToLL_M-50_HT-2500ToInf"   } , 

                                                                } ;
    
      std::map<TString,double> Sample_X_Section = {  // Xsections are in units fb-1 just remember
                                                               { "temp"              ,                             1.064e+01   },
                                                               { "Tprime_M1000",                              3.044e+01   },  
                                                               { "Tprime_M1500",                              1.064e+01   },  
                                                               { "Tprime_M1800",                              5.828e+00   },  
                                                               { "TTbar",                                     8.317e+05   },  
                                                               { "TT_to_Hadronic"      ,                           3.779e+05},             
                                                               { "TT_to_SemiLeptonic"  ,                           3.653e+05},             
                                                               { "TT_to_2L2Nu"         ,                           8.829e+04},               
                                                               { "QCD_Pt-80_MuEnr",                           8.903e+07   },    
                                                               { "QCD_Pt-120_MuEnr",                          2.074e+07   },
                                                               { "QCD_Pt-170_MuEnr",                          6.903e+06   },   
                                                               { "QCD_Pt-300_MuEnr",                          6.194e+05  },    
                                                               { "QCD_Pt-470_MuEnr",                          5.893e+04  },   
                                                               { "QCD_Pt-600_MuEnr",                          1.846e+04  },
                                                               { "QCD_Pt-800_MuEnr",                          3.294e+03  },  
                                                               { "QCD_Pt-1000_MuEnr",                         1.094e+03  } ,
                                                               { "WJets_LNu",                                 5.294e+07  } ,
                                                               { "DYJetsToLL",                                6.529e+06   } , 

                                                               {  "QCD_Pt-50_EMEnr"  ,                     1.989e+09   },  
                                                               {  "QCD_Pt-80_EMEnr"  ,                     3.665e+08            },  
                                                               {  "QCD_Pt-120_EMEnr" ,                     6.649e+07            },  
                                                               {  "QCD_Pt-170_EMEnr" ,                     1.648e+07            },  
                                                               {  "QCD_Pt-300_EMEnr" ,                     1.099e+06            },

                                                               { "ST_s-channel_4f_leptonDecays"          ,      3.74e+03    },
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays",     6.909e+04   },
                                                               { "ST_t-channel_top_4f_inclusiveDecays"   ,      1.153e+05   },
                                                               { "ST_tW_top_5f_inclusiveDecays"          ,      3.491e+04   },
                                                               { "ST_tW_antitop_5f_inclusiveDecays"     ,       3.497e+04   } ,

                                                               {    "WJets_LNu_HT-70To100"    ,    1.395e+06} ,
                                                               {    "WJets_LNu_HT-100To200"   ,    1.395e+06} ,
                                                               {    "WJets_LNu_HT-200To400"   ,    4.079e+05} ,  
                                                               {    "WJets_LNu_HT-400To600"   ,    5.748e+04} ,
                                                               {    "WJets_LNu_HT-600To800"   ,    1.287e+04} ,
                                                               {    "WJets_LNu_HT-800To1200"  ,    5.366e+03} ,
                                                               {    "WJets_LNu_HT-1200To2500" ,    1.074e+03} ,
                                                               {    "WJets_LNu_HT-2500ToInf"  ,    1.074e+03} , 

                                                               {    "DYJetsToLL_M-50_HT-70To100"    ,  1.465e+05} ,                                                               
                                                               {    "DYJetsToLL_M-50_HT-100To200"   ,  1.607e+05} ,
                                                               {    "DYJetsToLL_M-50_HT-200To400"   ,  4.863e+04} ,  
                                                               {    "DYJetsToLL_M-50_HT-400To600"   ,  6.993e+03} ,
                                                               {    "DYJetsToLL_M-50_HT-600To800"   ,  1.761e+03} ,
                                                               {    "DYJetsToLL_M-50_HT-800To1200"  ,  0.8021e+03} ,
                                                               {    "DYJetsToLL_M-50_HT-1200To2500" ,  0.1937e+03} ,
                                                               {    "DYJetsToLL_M-50_HT-2500ToInf"  ,  0.003514e+03} , 
                                                               // When added 70to100, 2500to Inf update Xsection for respective sample
                                                           } ;
    
    
      std::map<TString,double> Sample_Total_Events = {  // total events from Ntuplized samples just remember
                                                               { "temp"              ,                             400000   },
                                                               { "Tprime_M1000",                              400000   },  
                                                               { "Tprime_M1500",                              400000   },  
                                                               { "Tprime_M1800",                              400000   },  
                                                               { "TTbar",                                     148768378   },  

                                                               { "TT_to_Hadronic"      , 129065100 },             
                                                               { "TT_to_SemiLeptonic"  , 114058500 },             
                                                               { "TT_to_2L2Nu"         , 66259900  }, 
                                                               
                                                               { "QCD_Pt-80_MuEnr",                           613257   }, 

                                                               { "QCD_Pt-120_MuEnr",                          648944   },

                                                               { "QCD_Pt-170_MuEnr",                          36918785   },   

                                                               { "QCD_Pt-300_MuEnr",                          494796  },    

                                                               { "QCD_Pt-470_MuEnr",                          517382   },   


                                                               { "QCD_Pt-600_MuEnr",                          17354151   },

                                                             
                                                               { "QCD_Pt-800_MuEnr",                          16995944  },  

                                                               { "QCD_Pt-1000_MuEnr",                         14751368  } ,
                                                       
                                                               { "WJets_LNu",                                 87960604  } ,


                                                               { "DYJetsToLL",                                199796690   } ,   

                                                               {  "QCD_Pt-50_EMEnr"  ,                     10900663   },  
                                                               {  "QCD_Pt-80_EMEnr"  ,                     9536384            },  
                                                               {  "QCD_Pt-120_EMEnr" ,                     9875695            },  
                                                               {  "QCD_Pt-170_EMEnr" ,                     3728180            },  
                                                               {  "QCD_Pt-300_EMEnr" ,                     2840010            },


                                                               { "ST_s-channel_4f_leptonDecays"          ,     19850000   },
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays",    24265600   },
                                                               { "ST_t-channel_top_4f_inclusiveDecays"   ,     45754100   },
                                                               { "ST_tW_top_5f_inclusiveDecays"          ,     10041965   },
                                                               { "ST_tW_antitop_5f_inclusiveDecays"     ,     9191369   }  ,                                                                                                                              

                                                               {    "WJets_LNu_HT-70To100"    ,   47691676 } ,
                                                               {    "WJets_LNu_HT-100To200"   ,   47691676 } ,
                                                               {    "WJets_LNu_HT-200To400"   ,   42400350 } ,  
                                                               {    "WJets_LNu_HT-400To600"   ,   5470704 } ,
                                                               {    "WJets_LNu_HT-600To800"   ,   5484477 } ,
                                                               {    "WJets_LNu_HT-800To1200"  ,   5389834 } ,
                                                               {    "WJets_LNu_HT-1200To2500" ,   4935967 } ,
                                                               {    "WJets_LNu_HT-2500ToInf"  ,   4935967 } ,   

                                                               {    "DYJetsToLL_M-50_HT-70To100"    , 11961649 } ,
                                                               {    "DYJetsToLL_M-50_HT-100To200"   , 20043136 } ,
                                                               {    "DYJetsToLL_M-50_HT-200To400"   , 12777715 } ,  
                                                               {    "DYJetsToLL_M-50_HT-400To600"   , 6063222 } ,
                                                               {    "DYJetsToLL_M-50_HT-600To800"   , 5304434 } ,
                                                               {    "DYJetsToLL_M-50_HT-800To1200"  , 4960019 } ,
                                                               {    "DYJetsToLL_M-50_HT-1200To2500" , 4828418 } ,
                                                               {    "DYJetsToLL_M-50_HT-2500ToInf"  , 1480047 } ,                                                                                                                              
                                                                 } ;       
    
std::map<TString, std::array <float,3> >InputString_outputarray =   {
                                                               { "Tprime_M1000",         { 1.0, 2.0 ,3.0} },  
                                                               { "Tprime_M1500",         { 1.5, 2.5 ,3.5} },  
                                                               { "Tprime_M1800",         { 1.75, 2.75 ,3.5} }, 

                                                                        }  ;
std::map<TString, std::vector <float> >InputString_outputvec =   {
                                                               { "Tprime_M1000",         { 1.0, 2.0 ,3.0} },  
                                                               { "Tprime_M1500",         { 1.5, 2.5 ,3.5} },  
                                                               { "Tprime_M1800",         { 1.75, 2.75 ,3.5 ,4.0} }, 

                                                                        }  ;

void Luminosity_Normalization(TString sample) {

            TString temp_sample = "NONE";
            TString Dataset     = "NONE";


            for (int i = 0; i < 44; ++i)
            {
                  temp_sample = Sample_List[i];
                  if (!( sample.Contains(temp_sample))) continue ;
                  Dataset     = temp_sample ; 
                  cout <<"\n For Sample = " << Dataset;
            }
    
            double Xsections    = Sample_X_Section[Dataset];
            double Total_Events = Sample_Total_Events[Dataset] ;
                  cout <<"   Xsections = " << Xsections <<" && Events = " << Total_Events <<endl;



            // double Luminosity   = 35.917150 ;  // in units of fb-1 for 2016
            // double Luminosity   = 59.74 ;  // in units of fb-1 for 2018
            double Luminosity   = 41.53 ;  // in units of fb-1 for 2017   
            lumi_factor = ( Xsections / Total_Events ) * Luminosity ;

    
            // return Luminosity ;
}         

TString MC_Channel = "x";

bool Lepton_Trigger_Check(){


     bool trigger_pass = false ; 

     if ( Trigger_Check.Contains("Muon"))     trigger_pass = ( HLT_Mu50 != 0 || HLT_OldMu100 != 0 || HLT_TkMu100 != 0 ) ;
     if ( Trigger_Check.Contains("Electron")) trigger_pass = ( HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165 != 0 || HLT_Ele115_CaloIdVT_GsfTrkIdT != 0 || HLT_Photon200 != 0) ;

     if ( Trigger_Check.Contains("MCSample")) trigger_pass = true ;
     
    //  if ( Trigger_Check.Contains("MCSample") && MC_Channel.Contains("Muonic")) {
    //      trigger_pass = ( HLT_Mu50 != 0 || HLT_OldMu100 != 0 || HLT_TkMu100 != 0 ) ;

    //  }    
    //  if ( Trigger_Check.Contains("MCSample") && MC_Channel.Contains("Electronic")) {
    //   trigger_pass = ( HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165 != 0 || HLT_Ele115_CaloIdVT_GsfTrkIdT != 0 || HLT_Photon200 != 0) ;
    //            cout << "\n For Channel = " << MC_Channel 
    //                 << "\n HLT_Ele50  = " << HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165
    //                 << "\n HLT_Ele115 = " << HLT_Ele115_CaloIdVT_GsfTrkIdT
    //                 << "\n HLT_Photon200 = " << HLT_Photon200 << endl;

    // }

     return trigger_pass ;

}

//=============Pile Up factor calculation using PileUp file ==================================================

float PUWeights(float npv) {
    
        int bin = PieUp_ScaleFactor->GetXaxis()->FindBin( npv );
        float weight = PieUp_ScaleFactor->GetBinContent( bin );
        return  weight ;
      
}


//================Muon ID Scale factor using efficiency root files ===========================================

TString RunBCDEF_UL17_Muon_SF_ID_Root_File = "../Muon_Efficiency_Run2UL/MuonReferenceEfficiencies-master-EfficienciesStudies-UL2017/EfficienciesStudies/UL2017/rootfiles/RunBCDEF_UL_SF_ID.root" ;
TH2F*   Lepton_histo_scale_factor ;
TFile  *Muon_Scale_file ;   

float  Lepton_Scale_Factor_ID = 1.0;


double Muon_ID_ScaleFactor_2016(float pt_muon, float eta){
    
    float pt = ( pt_muon > 119.0 ) ? 119.0 : pt_muon ;  // for pT > 120.0, scale factors are used as for pT = 120.0 

    int     bin  =  muon_histo_scale_BCDEF->FindBin( pt ,fabs(eta) ) ;
    double  fac1 =  muon_histo_scale_BCDEF->GetBinContent( bin ); 
  
    bin          =  muon_histo_scale_GH->FindBin( pt ,fabs(eta) ) ;
    double  fac2 =  muon_histo_scale_GH->GetBinContent( bin ); 
  
    double  lumiBCDEF = 19.690943 ;
    double  lumiGH    = 16.226208 ;
  
    double  fact = ( ( lumiBCDEF*fac1 ) + ( lumiGH*fac2 ) ) / (lumiBCDEF + lumiGH ) ;
 
    // cout <<"for muonPt = " << pt << " ....&& muonEta = " << eta <<"  ..... factBCDEF = " << fac1 << "  ..... factGH = " << fac2  ;

    return  fact ;
  
}  


double Muon_ID_ScaleFactor_UL2017(float pt_muon, float eta){
    
    float pt = ( pt_muon >= 120.0 ) ? 119.999 : pt_muon ;  // for pT > 120.0, scale factors are used as for pT = 120.0 

    int     bin  =  Lepton_histo_scale_factor->FindBin( pt ,fabs(eta) ) ;
    double  fact =  Lepton_histo_scale_factor->GetBinContent( bin ); 
  
    // cout <<"\n for muonPt = " << pt << " ....&& muonEta = " << eta <<"  ..... factBCDEF = " << fact  ;

    return  fact ;
  
} 

//================Electron ID Scale factor using efficiency root files ===========================================

TString Run2_UL17_Electron_SF_LooseID_Root_File = "../Electron_Efficiency_Run2UL/egammaEffi.txt_EGM2D_Loose_UL17.root" ;
TFile  *Electron_Scale_file ;   

double Electron_ID_ScaleFactor_UL2017(float pt_ele, float eta){

        
    float   pt   =  ( pt_ele >= 500.000 ) ? 499.999 : pt_ele ;  // for pT >= 500.0, scale factors are used as for pT = 499.999 

    int     bin  =  Lepton_histo_scale_factor->FindBin( fabs(eta) , pt ) ;
    double  fact =  Lepton_histo_scale_factor->GetBinContent( bin ); 
  
    // cout <<"\n for elePt = " << pt << " ....&& eleEta = " << eta <<"  ..... fact = " << fact  ;



    return  fact ;
  
} 

//------------------------ Muon Isolation test ----------------------------- ////////////////////////////////

std::map<TString,TString> Sample_Type_Muon = {  // to check whether muon is from signal or from background
                                                               { "temp"              ,                             "PromptLepton"   },
                                                               { "Tprime_M1000",                              "PromptLepton"   },  
                                                               { "Tprime_M1500",                              "PromptLepton"   },  
                                                               { "Tprime_M1800",                              "PromptLepton"   },  
                                                               { "TTbar",                                     "PromptLepton"   },    
                                                               { "QCD_Pt-80_MuEnr",                           "FakeLepton"     },    
                                                               { "QCD_Pt-120_MuEnr",                          "FakeLepton"     },
                                                               { "QCD_Pt-170_MuEnr",                          "FakeLepton"     },   
                                                               { "QCD_Pt-300_MuEnr",                          "FakeLepton"     },    
                                                               { "QCD_Pt-470_MuEnr",                          "FakeLepton"     },   
                                                               { "QCD_Pt-600_MuEnr",                          "FakeLepton"     },
                                                               { "QCD_Pt-800_MuEnr",                          "FakeLepton"     },  
                                                               { "QCD_Pt-1000_MuEnr",                         "FakeLepton"     } ,
                                                               { "WJets_LNu",                                 "FakeLepton"     } ,
                                                               { "DYJetsToLL",                                "FakeLepton"     } ,                                                               
                                                               { "ST_s-channel_4f_leptonDecays_v3_",               "FakeLepton"     },
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays_v3_",    "FakeLepton"     },
                                                               { "ST_t-channel_top_4f_inclusiveDecays_v3_",        "FakeLepton"     },
                                                               { "ST_tW_antitop_5f_inclusiveDecays_v3_",           "FakeLepton"     },
                                                               { "ST_tW_top_5f_inclusiveDecays_v3_",               "FakeLepton"     }

                                            } ;

 

/////================= Higgs Tagging Test=======================================

std::map<TString,TString> Sample_Type_Jet = {  // to check whether jet type is from signal or from background
                                                               { "temp"              ,                                        "Higgs"          },  
                                                               { "Tprime_M1000",                                         "Higgs"          },  
                                                               { "Tprime_M1500",                                         "Higgs"          },  
                                                               { "Tprime_M1800",                                         "Higgs"            }, 
                                                               { "TTbar",                                                "Top"            }, 
                                                               { "TTbar",                                                "TopWboson"         }, 
                                                               { "QCD_Pt-80_MuEnr",                                      "udscquark"      },    
                                                               { "QCD_Pt-120_MuEnr",                                     "udscquark"      },
                                                               { "QCD_Pt-170_MuEnr",                                     "udscquark"      },   
                                                               { "QCD_Pt-300_MuEnr",                                     "udscquark"      },    
                                                               { "QCD_Pt-470_MuEnr",                                     "udscquark"      },   
                                                               { "QCD_Pt-600_MuEnr",                                     "udscquark"      },
                                                               { "QCD_Pt-800_MuEnr",                                     "udscquark"      },  
                                                               { "QCD_Pt-1000_MuEnr",                                    "udscquark"      } ,
                                                               { "WJets_LNu",                                            "Wboson"         } ,
                                                               { "DYJetsToLL",                                           "Zboson"         } ,
                                                               { "ST_s-channel_4f_leptonDecays_v3_",                          "Wboson"         } ,  
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays_v3_",               "Wboson"         } ,
                                                               { "ST_t-channel_top_4f_inclusiveDecays_v3_",                   "Wboson"         } ,
                                                               { "ST_tW_antitop_5f_inclusiveDecays_v3_",                      "Wboson"         } ,
                                                               { "ST_tW_top_5f_inclusiveDecays_v3_",                          "Wboson"         } ,                                                               
                                                
                                                } ;  

void Find_Object_type_From_Sample(TString sample) {

      TString temp_sample = "NONE";
      TString Dataset     = "NONE";

      for (int i = 0; i < 20; ++i)
      {
            temp_sample = Sample_List[i];
            if (!( sample.Contains(temp_sample))) continue ;
            Dataset     = temp_sample ; 
            cout <<"\n For Sample = " << Dataset;
      }
    
      Type_of_Muon    = Sample_Type_Muon[Dataset];

      Type_of_Jet     = Sample_Type_Jet[Dataset]; 

      cout <<"   Type of Muon = " << Type_of_Muon <<"  &&& Type of Jet = " << Type_of_Jet << endl;
      
    

}

/////////////////=========THIS SECTION FOR DEFINING NEW SETS OF HOSTOGRAMS=============///////////////////////////////////////////////////////////////////

    // Histograms for Cut flow 
    void Define_Histo_For_Global_Var() 
    {
    //0 
    //1 
    //2 
    //3 
    //4 
    //5 
    //6 
    //7 
    //8 
    //9 
    //10
    //11
    //12
    //13
    //14  
    
           Good_PV_Histo    = new TH1D("Good_PV_Histo", "Good Primary Vertex Distribution", 100, 0.0, 100);
    
           Good_PV_Pr_Histo = new TH1D("Good_PV_Pr_Histo", "Good Primary Vertex (after Pre-Sel) Distribution", 100, 0.0, 100);
    
           h_MC = new TH1D("h_MC", "PileUP (MC) Distribution", 80, 0.0, 80.0);
     
           const int    nBin = 16;
           const double Bin_value[nBin+1] =  {0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1200.0, 1400.0, 1600.0 } ;
    
           Int_t i;
           const Int_t nx = 15;
           const char *cut_pass[nx] = {  "Total Events",                //0                                       
                                         "Primary_Vertex",              //1 
                                         "HLT_Lepton Trig",             //2 
                                         "Forward Jet Tag"    ,         //3     
                                         "MET Cut" ,                    //4                                           
                                         "Lepton Cut",                  //5 
                                         "AK8 Jet Tag" ,                //6 
                                         "Clean Jet Tag",               //7             
                                         "bjet tag",                    //8    
                                         "ST Cut"  ,                    //9   
                                         "Higgs Tag",                   //10    
                                         "Higgs MassCheck",             //11    
                                         "Lep Iso",                     //12                                          
                                         "ST Cut"  ,                    //13  
                                         "dR check(mu, H)",             //14                                                                              
                                         // "dR check(bjet)" ,             //13                                                             
                                         // "Higgs_Pt Cut",                //14                                           

                                                                                                                             
                                         // "bjet Tag" ,                                                       
                                         // "HiggspT > 300",                                    // "dR(Higgs, bjet) Cut" ,    //9
                                         // "dR(mu, bjet) Cut" ,       //10
                                         // "Pt Bjet Cut" ,            // 11                       
                                        };
    
    
           Cut_Efficiency_Flow = new TH1D("Cut_Efficiency_Flow","Cut Efficiency Flow",nx,0,nx);
           Cut_Efficiency_Flow->SetFillColor(38);
    
           for (i=1;i<=nx;i++) {
               Cut_Efficiency_Flow->GetXaxis()->SetBinLabel(i,cut_pass[i-1]);
           }
    
    
    
           const Int_t sx = 6 ;
           const char *cut_St[sx] = {"St > 000GeV", 
                                     "St > 400GeV", 
                                     "St > 500GeV", 
                                     "St > 600GeV", 
                                     "St > 700GeV",
                                     "St > 800GeV",
    
                                    };
        
           Cut_ST_Cut_Flow = new TH1D("Cut_ST_Cut_Flow", "ST Cut_Flow", sx, 0, sx);
           Cut_ST_Cut_Flow->SetFillColor(30) ;
           for (int i = 1; i <= sx; i++)
           {
             Cut_ST_Cut_Flow->GetXaxis()->SetBinLabel(i,cut_St[i-1]);
           }
    
    
           const Int_t Mx = 4 ;
           const char *cut_MT[Mx] = {"MET > 00GeV", 
                                     "MET > 50GeV", 
                                     "MET > 100GeV", 
                                     "MET > 150GeV"
                                    };
        
           Cut_MET_Cut_Flow = new TH1D("Cut_MET_Cut_Flow", "MET Cut Flow", Mx, 0, Mx);
           Cut_MET_Cut_Flow->SetFillColor(20) ;
           for (int i = 1; i <= Mx; i++)
           {
             Cut_MET_Cut_Flow->GetXaxis()->SetBinLabel(i,cut_MT[i-1]);
           }
    
    
           const Int_t taux = 22 ;
           const char *cut_tau[taux] = { "No cut on tau42", //0   
                                         "After_Pt_SD",     //1  
                                         "tau42 < 1.00",    //2  
                                         "tau42 < 0.95",    //3  
                                         "tau42 < 0.90",    //4                                                                    
                                         "tau42 < 0.85",    //5  
                                         "tau42 < 0.80",    //6                                 
                                         "tau42 < 0.75",    //7   
                                         "tau42 < 0.70",    //8                                 
                                         "tau42 < 0.65",    //9   
                                         "tau42 < 0.60",    //10   
                                         "tau42 < 0.55",    //11 
                                         "tau42 < 0.50",    //12                                                                                                     
                                         "tau42 < 0.45",    //13 
                                         "tau42 < 0.40",    //14                                
                                         "tau42 < 0.35",    //15 
                                         "tau42 < 0.30",    //16                                
                                         "tau42 < 0.25",    //17                                
                                         "tau42 < 0.20",    //18                                
                                         "tau42 < 0.15",    //19                               
                                         "tau42 < 0.10",    //20
                                         "tau42 < 0.05",    //21                               
                                       };
        
           Cut_Tau42_Flow = new TH1D("Cut_Tau42_Flow", "Cut Tau42 Flow", taux, 0, taux);
           Cut_Tau42_Flow->SetFillColor(35) ;
           for (int i = 1; i <= taux; i++)
           {
             Cut_Tau42_Flow->GetXaxis()->SetBinLabel(i,cut_tau[i-1]);
           }


           const Int_t staux = 22 ;
           const char *cut_sTtau[staux] = { "No_Selection"  ,        //0   
                                            "After_PT_SD_Sel",       //1   //0      
                                            "tau42<1.00 && ST>600",  //2   //2  
                                            "tau42<0.95 && ST>600",  //3   //3  
                                            "tau42<0.90 && ST>600",  //4   //4                                                                    
                                            "tau42<0.85 && ST>600",  //5   //5  
                                            "tau42<0.80 && ST>600",  //6   //6                                 
                                            "tau42<0.75 && ST>600",  //7   //7   
                                            "tau42<0.70 && ST>600",  //8   //8                                 
                                            "tau42<0.65 && ST>600",  //9   //9   
                                            "tau42<0.60 && ST>600",  //10  //10   
                                            "tau42<0.55 && ST>600",  //11  //11 
                                            "tau42<0.50 && ST>600",  //12  //12                                                                                                     
                                            "tau42<0.45 && ST>600",  //13  //13 
                                            "tau42<0.40 && ST>600",  //14  //14                                
                                            "tau42<0.35 && ST>600",  //15  //15 
                                            "tau42<0.30 && ST>600",  //16  //16                                
                                            "tau42<0.25 && ST>600",  //17  //17                                
                                            "tau42<0.20 && ST>600",  //18  //18                                
                                            "tau42<0.15 && ST>600",  //19  //19                               
                                            "tau42<0.10 && ST>600",  //20  //20
                                            "tau42<0.05 && ST>600",  //21  //21                               
                                       };
        
           Cut_ST_Tau42_Flow = new TH1D("Cut_ST_Tau42_Flow", "Cut ST N Tau42 Flow", staux, 0, staux);
           Cut_ST_Tau42_Flow->SetFillColor(35) ;
           for (int i = 1; i <= staux; i++)
           {
             Cut_ST_Tau42_Flow->GetXaxis()->SetBinLabel(i,cut_sTtau[i-1]);
           }


    
           const Int_t Deepx = 19 ;
           const char *cut_DeepH[Deepx] = { "No cut on DeepMD_H", //0  
                                            "After_Pt_SD",        //1  
                                            "DeepMD_H > 0.10",    //2                                                                       
                                            "DeepMD_H > 0.15",    //3 
                                            "DeepMD_H > 0.20",    //4                                    
                                            "DeepMD_H > 0.25",    //5  
                                            "DeepMD_H > 0.30",    //6                                    
                                            "DeepMD_H > 0.35",    //7 
                                            "DeepMD_H > 0.40",    //8 
                                            "DeepMD_H > 0.45",    //9    
                                            "DeepMD_H > 0.50",    //10                                                                                                        
                                            "DeepMD_H > 0.55",    //11 
                                            "DeepMD_H > 0.60",    //12                                   
                                            "DeepMD_H > 0.65",    //13
                                            "DeepMD_H > 0.70",    //14                                   
                                            "DeepMD_H > 0.75",    //15                                   
                                            "DeepMD_H > 0.80",    //16                                  
                                            "DeepMD_H > 0.85",    //17                                  
                                            "DeepMD_H > 0.90",    //18                               
                                       };
        
           Cut_DeepMD_H_Flow = new TH1D("Cut_DeepMD_H_Flow", "Cut DeepMD_H Flow", Deepx, 0, Deepx);
           Cut_DeepMD_H_Flow->SetFillColor(35) ;

           for (int i = 1; i <= Deepx; i++)
           {
             Cut_DeepMD_H_Flow->GetXaxis()->SetBinLabel(i,cut_DeepH[i-1]);
           }    
    
    
           const Int_t Higgsx = 6;
           const char *cut_Higgs[Higgsx] = { 
                                        "Total Events",
                                        "Events Passed by HiggsSel",                //0                                      
                                        "Mass Window Passed",           //1
                                        "Events with top_prod",           //2
                                        "Events for Top_Cand1" ,            //3                   
                                        "Events for Top_Cand2"
                                       };
           Cut_Higgs_Tagging_Flow = new TH1D("Cut_Higgs_Tagging_Flow","Higgs Tagging Flow",Higgsx,0,Higgsx);
           Cut_Higgs_Tagging_Flow->SetFillColor(38);
    
    
           for (i=1;i<=Higgsx;i++) {
            Cut_Higgs_Tagging_Flow->GetXaxis()->SetBinLabel(i,cut_Higgs[i-1]);
           }
    
    
    
           const Int_t pTx = 7 ;
           const char *cut_pTH[pTx] = { "pT > 200GeV", 
                                        "pT > 250GeV", 
                                        "pT > 300GeV", 
                                        "pT > 350GeV",  
                                        "pT > 400GeV",  
                                        "pT > 450GeV",  
                                        "pT > 500GeV", 
                                       };
         
           Cut_pTHiggs_Flow = new TH1D("Cut_pTHiggs_Flow", "Cut pTHiggs Flow", pTx, 0, pTx);
           Cut_pTHiggs_Flow->SetFillColor(35) ;
           for ( i = 1; i <= pTx; i++)
           {
            Cut_pTHiggs_Flow->GetXaxis()->SetBinLabel(i,cut_pTH[i-1]);
           }
    
    
           const Int_t SDx = 8 ;
           const char *cut_SD[SDx] =   {"SD = [ 50,150]GeV", 
                                        "SD = [ 70,150]GeV", 
                                        "SD = [ 75,150]GeV", 
                                        "SD = [ 80,150]GeV",  
                                        "SD = [ 85,150]GeV",  
                                        "SD = [ 90,150]GeV",  
                                        "SD = [ 95,150]GeV", 
                                        "SD = [100,150]GeV", 
                                       };
    
        
           Cut_SDMass_Flow = new TH1D("Cut_SDMass_Flow", "Cut SDMass Flow", SDx, 0, SDx);
           Cut_SDMass_Flow->SetFillColor(35) ;
           for ( i = 1; i <= SDx; i++)
           {
             Cut_SDMass_Flow->GetXaxis()->SetBinLabel(i,cut_SD[i-1]);
           }


           const Int_t tx = 12 ;

           const char *cut_pt[tx] = {"No Isolation",             //0 
                                     "MiniIsoLoose",             //1 
                                     "MiniIsoMedium",            //2 
                                     "MiniIsoTight",             //3 
                                     "MiniIsoVeryTight",         //4 
                                     "dR > 0.2 OR dPt > 20GeV",  //5 
                                     "dR > 0.3 OR dPt > 20GeV",  //6 
                                     "dR > 0.4 OR dPt > 20GeV",  //7 
                                     "dR > 0.2 OR dPt > 40GeV",  //8 
                                     "dR > 0.3 OR dPt > 40GeV",  //9 
                                     "dR > 0.4 OR dPt > 40GeV",  //10
                                     "dR > 0.4 OR dPt > 60GeV"   //11
                                    };

    
           Cut_MiniIso_n_2DLepIso_Flow = new TH1D("Cut_MiniIso_n_2DLepIso_Flow", "Cut MiniIso N 2DLepIso Flow", tx, 0, tx);
           Cut_MiniIso_n_2DLepIso_Flow->SetFillColor(35) ;
           for (int i = 1; i <= tx; i++)
           {
             Cut_MiniIso_n_2DLepIso_Flow->GetXaxis()->SetBinLabel(i,cut_pt[i-1]);
           }    
    
    
           ST_Sum_Presel = new TH1D("ST_Sum_Presel", "ST Sum Distribution(Preselection)", 100, 0.0, 5000.0 );
           ST_Sum_Presel ->GetYaxis()->SetTitle("Events") ;
    
           ST_Sum_Evesel = new TH1D( "ST_Sum_Evesel", "ST Sum Distribution(Event selection)", 100, 0.0, 5000.0 );
           ST_Sum_Evesel ->GetYaxis()->SetTitle("Events") ;
    
           ST_Sum_LeadObj = new TH1D( "ST_Sum_LeadObj", "ST Sum Distribution(Leading objects)", 100, 0.0, 5000.0 );
           ST_Sum_LeadObj ->GetYaxis()->SetTitle("Events") ;


           h_Wbos_Mass_Img = new TH1D("h_Wbos_Mass_Img", "Wbos Mass Imaginary", 500, 0.0, 1000.0 );
           h_Wbos_Mass_Img ->GetYaxis()->SetTitle("Events") ;      

           h_Wbos1_Mass = new TH1D("h_Wbos1_Mass", "Wbos1 Mass", 500, 0.0, 1000.0 );
           h_Wbos1_Mass ->GetYaxis()->SetTitle("Events") ;  

           h_Wbos2_Mass = new TH1D("h_Wbos2_Mass", "Wbos2 Mass", 500, 0.0, 1000.0 );
           h_Wbos2_Mass ->GetYaxis()->SetTitle("Events") ;  

           h_Top2_Mass = new TH1D("h_Top2_Mass", "Top2 Mass", 500, 0.0, 1000.0 );
           h_Top2_Mass ->GetYaxis()->SetTitle("Events") ;
    
           h_Top1_Mass = new TH1D("h_Top1_Mass", "Top1 Mass", 500, 0.0, 1000.0 );
           h_Top1_Mass ->GetYaxis()->SetTitle("Events") ;    

           h_Higgs_Mass = new TH1D("h_Higgs_Mass", "Higgs Mass", 500, 0.0, 1000.0 );
           h_Higgs_Mass ->GetYaxis()->SetTitle("Events") ; 

           h_Tprime1_Mass = new TH1D("h_Tprime1_Mass", "Tprime1 Mass", 1500, 0.0, 3000.0 );
           h_Tprime1_Mass ->GetYaxis()->SetTitle("Events") ;                

           h_Tprime2_Mass = new TH1D("h_Tprime2_Mass", "Tprime2 Mass", 1500, 0.0, 3000.0 );
           h_Tprime2_Mass ->GetYaxis()->SetTitle("Events") ;                        
    

           h_dR_Higgs_wrt_Top1   = new TH1D("h_dR_Higgs_wrt_Top1", "deltaR Higgs wrt Top1 Distribution", 100, 0.0, 5.0);
           h_dR_Higgs_wrt_Top1 ->GetYaxis()->SetTitle("Events") ;                         

           h_dR_Higgs_wrt_Top2   = new TH1D("h_dR_Higgs_wrt_Top2", "deltaR Higgs wrt Top2 Distribution", 100, 0.0, 5.0);
           h_dR_Higgs_wrt_Top2 ->GetYaxis()->SetTitle("Events") ;                        


           h_dR_Higgs_wrt_Topb   = new TH1D("h_dR_Higgs_wrt_Topb", "deltaR Higgs wrt Topb Distribution", 100, 0.0, 5.0);
           h_dR_Higgs_wrt_Topb ->GetYaxis()->SetTitle("Events") ;              

    } 

   ///////////////////======================= Function Defining Kinematic Histogram ===================================================///////////////////                                             
   void  Define_Kinematic_Histo_for_RecoObject()
   {
    //   New defination of histogram
      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ///// for object histograms//////////////////////
      for(Int_t k = 0 ; k <  17; ++k) {

            index = k ;
            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Pt_List[index] ;            
            pT_title  =  Histogram_Pt_List[index]  + " Distribution" ;   
           
            Hist_object_pt.at(index) = new TH1D(pT_name,pT_title,140, 0, 1400.0);
            Hist_object_pt.at(index) ->GetYaxis()->SetTitle("Events");

            ////////HISTROGRAM FOR ETA OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Eta_List[index] ;            
            pT_title  =  Histogram_Eta_List[index]  + " Distribution" ;   

            Hist_object_eta.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            Hist_object_eta.at(index) ->GetYaxis()->SetTitle("Events");

            ////////HISTROGRAM FOR PHI OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Phi_List[index] ;            
            pT_title  =  Histogram_Phi_List[index]  + " Distribution" ;   

            Hist_object_phi.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            Hist_object_phi.at(index) ->GetYaxis()->SetTitle("Events");

      }


      ////FOR LEADING FATJET HISTOGRAMS//////////////
      for (int i = 0; i < 23; ++i)
      {

            if ( i < 16 ) {

                            ////FOR LEADING FATJET HISTOGRAMS//////////////              

                            pT_name   =  Histogram_FatJet_List[i] ;            
                            pT_title  =  Histogram_FatJet_List[i]  + " Distribution" ;   

                            Hist_for_Leading_FatJet.at(i) = new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
                            Hist_for_Leading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");  

                            ////FOR SUB-LEADING FATJET HISTOGRAMS//////////////
                            pT_name   =  Histogram_FatJet2_List[i] ;            
                            pT_title  =  Histogram_FatJet2_List[i]  + " Distribution" ;   

                            Hist_for_Subleading_FatJet.at(i) = new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
                            Hist_for_Subleading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");      
                          }
                            
            if ( i >= 16 && i < 19 ) { 

                            ////FOR LEADING FATJET HISTOGRAMS//////////////              

                            pT_name   =  Histogram_FatJet_List[i] ;            
                            pT_title  =  Histogram_FatJet_List[i]  + " Distribution" ;   

                            Hist_for_Leading_FatJet.at(i) = new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
                            Hist_for_Leading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");     
   
                            ////FOR SUB-LEADING FATJET HISTOGRAMS//////////////
                            pT_name   =  Histogram_FatJet2_List[i] ;            
                            pT_title  =  Histogram_FatJet2_List[i]  + " Distribution" ;   


                            Hist_for_Subleading_FatJet.at(i) = new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
                            Hist_for_Subleading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");                            
                          }  

            if ( i >= 19 ) { 

                            ////FOR LEADING FATJET HISTOGRAMS//////////////              

                            pT_name   =  Histogram_FatJet_List[i] ;            
                            pT_title  =  Histogram_FatJet_List[i]  + " Distribution" ;   

                            Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at( i - 19) = new TH2D(pT_name,pT_title, 100, 0.0, 500.0, 100, 0.0, 1.0);
                            Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at( i - 19) ->GetYaxis()->SetTitle("Events");     
   
 
                            ////FOR SUB-LEADING FATJET HISTOGRAMS//////////////
                            pT_name   =  Histogram_FatJet2_List[i] ;            
                            pT_title  =  Histogram_FatJet2_List[i]  + " Distribution" ;   


                            Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(i - 19) = new TH2D(pT_name,pT_title, 100, 0.0, 500.0, 100, 0.0, 1.0);
                            Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(i - 19) ->GetYaxis()->SetTitle("Events");                            
                          }  



      }
      





      // for No. object  histograms
      for(Int_t j = 0; j < 8; j++) 
      {  
            pT_name   =  Histogram_Object_List[j] ;
            pT_title  =  Histogram_Object_List[j]  + " Distribution" ;
            h_object_no.at(j) = new TH1D( pT_name, pT_title, 10, 0, 10);  
            h_object_no.at(j) ->GetYaxis()->SetTitle("Events");
        // cout<<"h_object_no["<<j<<"].name() : "<< h_object_no.at(j)->GetName()<<endl;      
      }



   
   }


   void  Define_Kinematic_Histo_for_HiggsJet()
   {

      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ////FOR HiggsJet HISTOGRAMS//////////////
      for(Int_t k = 0 ; k <  23; ++k) {

            index = k ;
            pT_name   =  Histogram_Higgs_List[index] ;            
            pT_title  =  Histogram_Higgs_List[index]  + " Distribution" ;  

            if ( index < 12 ) {

                            ////FOR Discriminators of HiggsJet HISTOGRAMS//////////////               

                            Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 220, -1.1, 1.1) ;
 
                          } 

            if ( (index > 11 && index < 15 ) || (index == 21 ) ){              
                         
                            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
             
                         Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);

                        }


                         /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index == 15 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

                         /////++++ POPULATION HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index == 16 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 8, 0, 8);
            if ( index == 22 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 8, 0, 8);
            
            if ( index >  16 && index < 21 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 500, 0, 5.0);              


            Hist_for_Leading_HiggsJet.at(index) ->GetYaxis()->SetTitle("Events");  

   
      } // END OF THE LOOP!!!!

   }   // END OF THE FUNCTION !!!!!!!!   

   //////////////////=================Function Defining DeltaR and Delta Pt Histograms==============================///////////////////////////////////

   /////////////------Function For Calling Other Functions To Declare Delta R Histo---------------------------------///////////////////////////////////
   void  Define_DelatR_Histo_for_RecoObject() 
   {

         Define_DelatR_Histo_for_Fatjet_wrt_Jet()      ;
         Define_DelatR_Histo_for_Muon_wrt_Jet()        ;

   }


   ////-----------------------Function to define Histogram  of DeltaR  btw Fatjet and Jet--------------------------/////////////////////////////////
   void Define_DelatR_Histo_for_Fatjet_wrt_Jet() 
   {

        TString dR_name  = "Hist";
        TString dR_title = "Distribution";
        
        // Here i = 0 to 2 for leading fatjet
        // Here i = 3 to 5  for sub leading fatjet
        // Here i = 6 to 8  for 3rd leading fatjet,
        // if want to extend histograms, increase i to 9

        for (Int_t i = 0; i < 6; i++) {      
    
          dR_name    =  Histogram_DeltaR_FatJet_List[i] ;
          dR_title   =  Histogram_DeltaR_FatJet_List[i] + "Distribution" ;
                
          DeltaR_Hist_FatJet_wrt_jet.at(i) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
          DeltaR_Hist_FatJet_wrt_jet.at(i) ->GetYaxis()->SetTitle("Events");
               
        } // End of LOOP !!!!      

   }  // END OF FUNCTION !!!!!!!!!!!!!!!

   ////-----------------------Function to define Histogram  of DeltaR  btw Muon and Jet--------------------------/////////////////////////////////
   void Define_DelatR_Histo_for_Muon_wrt_Jet() 
   {

        TString dR_name  = "Hist";
        TString dR_title = "Distribution";
        
        // Here i = 0 to 2 for normal jet
        // Here i = 3 to 5  for clean jet
        // Here i = 6 to 8  for b jet,
        // if want to extend histograms, increase i to 9 depending on your choice

        for (Int_t i = 0; i < 6; i++) {      
    
          dR_name    =  Histogram_DeltaR_Muon_List[i] ;
          dR_title   =  Histogram_DeltaR_Muon_List[i] + "Distribution" ;
                
          DeltaR_Hist_Muon_wrt_jet.at(i) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
          DeltaR_Hist_Muon_wrt_jet.at(i) ->GetYaxis()->SetTitle("Events");
               
        } // End of LOOP !!!!      

   }  // END OF FUNCTION !!!!!!!!!!!!!!!



   ///-------==================-========= Function Definitions for Hitograms of JetLepton Cleaning ---------========================///////////////////

   void  Define_Histograms_For_LeptonJet_Cleaning_Effect()
   {
      Define_Kinematic_Histo_for_LepCleanJet() ;
      // Define_Kinematic_Histo_for_LepCleanFatJet();
      Define_Histo_of_Pt_wrt_Delta_For_CleanJet() ;
   }                                                            

   //-----cLEAN jET hISTOGRAMS dEFINED HERE
   void  Define_Kinematic_Histo_for_LepCleanJet()
   {

        TString   pT_name  = "Hist" ;
        TString   pT_title = "Distribution" ; 

        int index = 0 ;

   
        ////FOR CleanJet HISTOGRAMS//////////////
        for(Int_t k = 0 ; k <  20; ++k) {

              index = k ;
              pT_name   =  Histogram_LepCleanJet_List[index] ;            
              pT_title  =  Histogram_LepCleanJet_List[index]  + " Distribution" ;  


              ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
              if ( index < 4 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);


              /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 3 && index < 8 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

              /////++++ Phi HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 7 && index < 12 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

              /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
              if ( index > 11 && index < 16) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 100, 0, 5.0);              

              /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
              if ( index > 15) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 100, 0, 500.0);     
              Hist_for_LeptonCleaned_Jet.at(index) ->GetYaxis()->SetTitle("Events");  

   
        } // END OF THE LOOP!!!!

              dPt_dR_mu_cleanjet1   = new TH2F("dPt_dR_Hist_mu_cleanjet1", "dPt & dR for mu n cleanjet1 Distribution", 50, 0.0, 5.0, 50, 0.0, 500.0);
              dPt_dR_mu_cleanjet2   = new TH2F("dPt_dR_Hist_mu_cleanjet2", "dPt & dR for mu n cleanjet2 Distribution", 50, 0.0, 5.0, 50, 0.0, 500.0);

              // dPt_dR_muqjet   = new TH2F("dPt_dR_muqjet", "dPt & dR for mu,qjet Distribution", 100, -1.0, 1.0, 500, 0.0, 1000.0);  // for tau42 study
              dPt_dR_mu_jet1   = new TH2F("dPt_dR_Hist_mu_jet1", "dPt & dR for mu n jet1 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);
              dPt_dR_mu_jet2   = new TH2F("dPt_dR_Hist_mu_jet2", "dPt & dR for mu n jet2 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);


   }   // END OF THE FUNCTION !!!!!!!!   


   //-----cLEAN fATjET hISTOGRAMS dEFINED HERE
   void  Define_Kinematic_Histo_for_LepCleanFatJet()
   {

      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ////FOR CleanJet HISTOGRAMS//////////////
      for(Int_t k = 0 ; k <  16; ++k) {

            index = k ;
            pT_name   =  Histogram_LepCleanFatJet_List[index] ;            
            pT_title  =  Histogram_LepCleanFatJet_List[index]  + " Distribution" ;  


            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
            if ( index < 4 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);


            /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index > 3 && index < 8 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

            /////++++ Phi HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index > 7 && index < 12 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

            /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
            if ( index > 11 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 500, 0, 5.0);              


            Hist_for_LeptonCleaned_FatJet.at(index) ->GetYaxis()->SetTitle("Events");  

   
      } // END OF THE LOOP!!!!

   }   // END OF THE FUNCTION !!!!!!!!      


void  Define_Histo_of_Pt_wrt_Delta_For_CleanJet() 
{
        TString   pT_name  = "Hist" ;
        TString   pT_title = "Distribution" ; 

        int index = 0 ;

   
        ////FOR CleanJet 2D HISTOGRAMS//////////////
        for(Int_t k = 0 ; k <  12; ++k) {

              index = k ;
              pT_name   =  Histogram_Delta_wrt_Pt_LepCleanJet_List[index] ;            
              pT_title  =  Histogram_Delta_wrt_Pt_LepCleanJet_List[index]  + " Distribution" ;  


              ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
              if ( index < 8 ) {
                    Hist_DeltaR_wrt_Pt_LepCleanJet.at(index)  = new TH2D(pT_name, pT_title, 200, 0.0, 1000.0 , 100, 0.0, 5.0);
                    Hist_DeltaR_wrt_Pt_LepCleanJet.at(index) ->GetXaxis()->SetTitle("P_{T}(leading jet)(GeV)");  
              }      

              /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 7 ) {
                    Hist_DeltaPt_wrt_Pt_LepCleanJet.at(index - 8)  = new TH2D(pT_name, pT_title, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
                    Hist_DeltaPt_wrt_Pt_LepCleanJet.at(index - 8) ->GetXaxis()->SetTitle("P_{T}(leading jet)(GeV)");  
              }      
   
        } // END OF THE LOOP!!!!

             


}   // END OF THE FUNCTION !!!!!!!!                                                         


void Define_2DHistogram_For_BtagEff()  {

        TString Hist_name  = "Hist_2D_BtagEff_";
        TString Hist_title = "Distribution";
        
        // Here Numerator and Denominator histo defined


        for (Int_t i = 0; i < 3; i++) {      
    
          // For Denominator Histogram ------------------------     
          Hist_name   =  Histogram_BtagEff_Denom_List[i] ;            
          Hist_title  =  Histogram_BtagEff_Denom_List[i]  + " Distribution" ; 
                
          Hist_2D_BtagEff_Denom.at(i)  = new TH2D(Hist_name, Hist_title, 100, 0.0, 1000.0 , 10, 0.0, 3.0);
          Hist_2D_BtagEff_Denom.at(i)  ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
          Hist_2D_BtagEff_Denom.at(i)  ->GetYaxis()->SetTitle("#eta(jet)");  

          // For Numerator Histogram ------------------------
          Hist_name   =  Histogram_BtagEff_Num_List[i] ;            
          Hist_title  =  Histogram_BtagEff_Num_List[i]  + " Distribution" ; 
                
          Hist_2D_BtagEff_Num.at(i)  = new TH2D(Hist_name, Hist_title, 100, 0.0, 1000.0 , 10, 0.0, 3.0);
          Hist_2D_BtagEff_Num.at(i)  ->GetXaxis()->SetTitle("P_{T}(jet)(GeV)");  
          Hist_2D_BtagEff_Num.at(i)  ->GetYaxis()->SetTitle("#eta(jet)"); 

        } // End of LOOP !!!!      

}  // END OF FUNCTION !!!!!!!!!!!!!!!      



/////////////////=========THIS SECTION FOR DEFINING NEW SETS OF FILLING HOSTOGRAMS FUNCTIONS=============///////////////////////////////////////////////


// For Leptons at preselection level, 
//you could also define the channel, 
//if you want to fill according to it
////////////////////////////////////////////////////
//  Prog_ID for defining particle type,, 
//   0   for MET ..    // 1   for MET_su
//   2   for Electron1 //   3   for Electron2
//   4   for Muon1     //   5   for Muon2
//   6   for Jet1      //   7   for Jet2
//   8   for FatJet1   //   9   for FatJet2_
//   10  for ForwJet1  //   11  for ForwJet2
//   12  for CleanJet1 //   13  for CleanJet2
//   14  for bJet1     //   15  for bJet2
///////////////////////////////////////////////////

////////////------  Filling Leptons at Preselction Level------------------- ///////////////////////////////////////////////////////

void Fill_Object_Population(){


      h_object_no.at(1) ->Fill(n_ele.size() , Lepton_Scale_Factor_ID );          //  index 1   for nElectron  Filling Population Plot

      h_object_no.at(2) ->Fill(n_Mu.size() , Lepton_Scale_Factor_ID );           //  index 2   for nMuon  Filling Population Plot

      h_object_no.at(4) ->Fill(n_AK8Jet.size(), factor );        //  index 4   for nFatJet  Filling Population Plot

      h_object_no.at(3) ->Fill(n_jet.size(), factor );           //  index 3   for nJet  Filling Population Plot

      h_object_no.at(5) ->Fill(n_forwjet.size(), factor );       //  index 5   for nForwJet  Filling Population Plot

      h_object_no.at(6) ->Fill(n_cleanjet.size(), factor );      //  index 6   for nCleanJet  Filling Population Plot

      h_object_no.at(7) ->Fill(b_jet.size(), factor );           //  index 7   for nbJet  Filling Population Plot


}



void   Fill_Lepton_Hist_Preselction_LvL( TString lepton, int lep_index , int lep_count)
{
  int Prog_ID = 0 ;

  //// Filling MET for the event
  if (lepton.Contains("YesMET"))
  {
    Prog_ID = 0 ;
    Hist_object_pt.at (Prog_ID)  ->Fill(MET_pt, factor);
    Hist_object_phi.at (Prog_ID)  ->Fill(MET_phi, factor);
    // Hist_object_pt.at (Prog_ID + 1)  ->Fill(MET_sumEt, factor);  // SUM MET filing
    Hist_object_pt.at (Prog_ID + 1)  ->Fill(PuppiMET_pt, factor);  // Puppi MET filing

  }

  //// Filling Electron for the event
  if ( lepton.Contains("YesElectron"))
  {
    Prog_ID = 2 ;

    // cout << "\n passEle = " <<  lep_index << endl;

    Hist_object_pt.at  (Prog_ID + lep_count)  ->Fill(Electron_pt[lep_index],        Lepton_Scale_Factor_ID ); 
    Hist_object_eta.at (Prog_ID + lep_count)  ->Fill(Electron_eta[lep_index],       Lepton_Scale_Factor_ID );
    Hist_object_phi.at (Prog_ID + lep_count)  ->Fill(Electron_phi[lep_index],       Lepton_Scale_Factor_ID );  
  }


  //// Filling Muon for the event
  if ( lepton.Contains("YesMuon"))
  { 
    // cout << "\n STring = " << lepton ;
    Prog_ID = 4 ;

    // cout << "\n passMuon = " <<  lep_index  << endl;

    Hist_object_pt.at  (Prog_ID + lep_count)  ->Fill(Muon_pt[lep_index],  Lepton_Scale_Factor_ID );  
    Hist_object_eta.at (Prog_ID + lep_count)  ->Fill(Muon_eta[lep_index], Lepton_Scale_Factor_ID ); 
    Hist_object_phi.at (Prog_ID + lep_count)  ->Fill(Muon_phi[lep_index], Lepton_Scale_Factor_ID );   
  }


} // END of the function !!!!!!!!!!!


////////////------  Filling Jets at Preselction Level------------------- ///////////////////////////////////////////////////////

void   Fill_Jet_Hist_Preselction_LvL( TString jet, int jet_index , int jet_count)
{
  int Prog_ID = 0 ;

  //// Filling ALLJET for the event
  if (jet.Contains("YesALLJET"))
  {
    Prog_ID = 6 ;
    if ( jet.Contains("Cleaned")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }

  }

  //// Filling Forward jet for the event
  if (jet.Contains("YesForwJet"))
  {
    Prog_ID = 10 ;
    Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
    Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
    Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);

  }


  //// Filling Clean Jet for the event
  if (jet.Contains("CleanJetYes"))
  {
    Prog_ID = 12 ;

    if ( jet.Contains("Lepton")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }


  }

  //// Filling bjet for the event
  if (jet.Contains("bJetYes"))
  {
    Prog_ID = 14 ;

    if ( jet.Contains("LeptonCleaned")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }

  }

  // Filling passed topbjet
  if ( jet.Contains("Topbjet")){

    Prog_ID = 16 ;    
        Hist_object_pt.at   (Prog_ID)     ->Fill(Jet_pt_clean[top_bjet], factor); 
        Hist_object_eta.at  (Prog_ID)     ->Fill(Jet_eta_clean[top_bjet], factor);
        Hist_object_phi.at  (Prog_ID)     ->Fill(Jet_phi_clean[top_bjet], factor);

  }


} // END of the function !!!!!!!!!!!


////////////------  Filling FATJets at Preselction Level------------------- ///////////////////////////////////////////////////////

void   Fill_FatJet_Hist_Preselction_LvL( TString fatjet, int fatjet_index , int fatjet_count)
{
  int Prog_ID = 0 ;

  double  msoftdrop_corr = FatJet_msoftdrop_raw[fatjet_index] * FatJet_msoftdrop_corr_PUPPI[fatjet_index] ;

  //// Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    Prog_ID = 8 ;


    if( fatjet.Contains("Cleaned")){
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt_clean[ fatjet_index], factor); 
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta_clean[fatjet_index], factor);
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi_clean[fatjet_index], factor);
    }

    else{
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt[ fatjet_index], factor);  
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta[fatjet_index], factor); 
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi[fatjet_index], factor); 
    }

    
    Hist_for_Leading_FatJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor); 
    
    Hist_for_Leading_FatJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(6 )   ->Fill(FatJet_tau1[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(7 )   ->Fill(FatJet_tau2[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(8 )   ->Fill(FatJet_tau3[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(9 )   ->Fill(FatJet_tau4[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(16)   ->Fill(FatJet_mass_clean[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(17)   ->Fill(FatJet_msoftdrop[fatjet_index], factor); 

    if ( (!( msoftdrop_corr < 50.0 || msoftdrop_corr > 200.0)) ) {
      Hist_for_Leading_FatJet.at(18)   ->Fill(msoftdrop_corr, factor); 
      Hist_for_Leading_FatJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor); 
      Hist_for_Leading_FatJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor); 

      Hist_for_Leading_FatJet.at(10)   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(11)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(12)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(13)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(14)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(15)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor); 
    
      Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at(0) ->Fill ( msoftdrop_corr, FatJet_deepTagMD_H4qvsQCD[fatjet_index] );
      Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at(1) ->Fill ( msoftdrop_corr, FatJet_deepTag_H[fatjet_index]);
      Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at(2) ->Fill ( msoftdrop_corr, (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]) );
      Hist_SoftDropMass_wrt_Tau42_LeadFatJet.at(3) ->Fill ( msoftdrop_corr, (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]) ) ;
    }
      
  }

  //// Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    Prog_ID = 9 ;

    if( fatjet.Contains("Cleaned")){
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt_clean[ fatjet_index], factor); 
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta_clean[fatjet_index], factor);
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi_clean[fatjet_index], factor);
    }

    else{
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt[ fatjet_index], factor);  
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta[fatjet_index], factor); 
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi[fatjet_index], factor); 
    }


    Hist_for_Subleading_FatJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor); 

    Hist_for_Subleading_FatJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(6 )   ->Fill(FatJet_tau1[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(7 )   ->Fill(FatJet_tau2[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(8 )   ->Fill(FatJet_tau3[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(9 )   ->Fill(FatJet_tau4[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(16)   ->Fill(FatJet_mass_clean[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(17)   ->Fill(FatJet_msoftdrop[fatjet_index], factor); 

    if ( (!( msoftdrop_corr < 50.0 || msoftdrop_corr > 200.0)) ) {

    Hist_for_Subleading_FatJet.at(18)   ->Fill(msoftdrop_corr, factor); 
    Hist_for_Subleading_FatJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor);   
    Hist_for_Subleading_FatJet.at(10)   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(11)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(12)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(13)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(14)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(15)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor); 

    // 
    Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(0) ->Fill ( msoftdrop_corr, FatJet_deepTagMD_H4qvsQCD[fatjet_index] );
    Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(1) ->Fill ( msoftdrop_corr, FatJet_deepTag_H[fatjet_index]);
    Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(2) ->Fill ( msoftdrop_corr, (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]) );
    Hist_SoftDropMass_wrt_Tau42_SubLeadFatJet.at(3) ->Fill ( msoftdrop_corr, (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]) ) ;
    }

  }


} // END of the function !!!!!!!!!!!


////////////------  Filling HiggsJet ------------------- ///////////////////////////////////////////////////////

void   Fill_HiggsJet_Hist_Preselction_LvL( TString fatjet )
{
  // Put "FillHiggsJet" string to only fill

  int Prog_ID = 0 ;

  if( fatjet.Contains("DeltaRClear")) Higgsjets = DeltaR_Cleared_Higgsjet ;
  int fatjet_index = Higgsjets[0];

  double  msoftdrop_corr = FatJet_msoftdrop_raw[fatjet_index] * FatJet_msoftdrop_corr_PUPPI[fatjet_index] ;

  //// Filling ALLJET for the event
  if (fatjet.Contains("Fill"))
  {

    Hist_for_Leading_HiggsJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD   [fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor ) ;

    Hist_for_Leading_HiggsJet.at(6 )   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(7 )   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(8 )   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(9 )   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(10)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor ) ;

    Hist_for_Leading_HiggsJet.at(11)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(12)   ->Fill(FatJet_msoftdrop[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(13)   ->Fill(FatJet_mass_clean[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(14)   ->Fill(FatJet_pt_clean[ fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(15)   ->Fill(FatJet_eta_clean[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(21)   ->Fill(msoftdrop_corr, factor ) ;
  
    Fill_DeltaR_Hist_of_Higgs_wrt_Top_Prod( fatjet_index , fatjet);     
  }

  

} // END of the function !!!!!!!!!!!


void  Fill_DeltaR_Hist_of_Higgs_wrt_Top_Prod( int Higgs_index , TString TopbjetCheck)
{
      // Histogram index 17  for  "Hist_DeltaR_HiggsJet_wrt_lep (muon or ele)
      // Histogram index 18  for  "Hist_DeltaR_HiggsJet_wrt_jet1
      // Histogram index 19  for  "Hist_DeltaR_HiggsJet_wrt_jet2
      // Histogram index 20  for  "Hist_DeltaR_HiggsJet_wrt_jet3
      

      float Higgs_eta = FatJet_eta_clean[Higgs_index] ;
      float Higgs_phi = FatJet_phi_clean[Higgs_index] ;

      float top_prod_eta = 0.0 ; 
      float top_prod_phi = 0.0 ; 
      int   top_prod     = -1 ;

      int   hist_index   = -1 ;  // index for clean jet

      // DELTAr wrt Muon
      if ( n_Mu.size() > 0){

          top_prod       = n_Mu[0];
          top_prod_eta   = Muon_eta[top_prod] ;
          top_prod_phi   = Muon_phi[top_prod] ;

          dR_Calculator(Higgs_eta, Higgs_phi, top_prod_eta, top_prod_phi) ;
    
          Hist_for_Leading_HiggsJet.at(17)  ->Fill(dR, factor ) ;

      } // Muon Loop Ended !!!!!!!
      
      // Delta r wrt to clean jets

      int Ssize   = ( jet_copy.size() >= 2 ) ?  2 : jet_copy.size() ;

      if ( TopbjetCheck.Contains("Topbjet")){
      
         jet_copy[1]  = top_bjet;
         Ssize   = 2 ; // size is fixed as we are checking topbjet and leading bjet
      }  

      for (int kji = 0; kji < Ssize; ++kji)
      {
        top_prod         = jet_copy[kji] ;
        top_prod_eta     = Jet_eta_clean[top_prod] ;
        top_prod_phi     = Jet_phi_clean[top_prod] ;       

        hist_index  = kji + 18 ;  // index for clean jet

        dR_Calculator(Higgs_eta, Higgs_phi, top_prod_eta, top_prod_phi) ;
    
        Hist_for_Leading_HiggsJet.at(hist_index)  ->Fill(dR, factor ) ;

      } // Clean Jet Loop Ended !!!!!!!


} // END of the function !!!!!!!!!!!


/////========== Fiilling the objects after selection criterias are clear =========== ///////////
void Fill_Object_Hist_After_Preselction_LvL(  TString Filling , TString TopbjetCheck, TString LeptonType) 
 {
      int index  = -1 ;
      int count  =  -1 ;
      int JetSize = 0;
 
      Good_PV_Pr_Histo ->Fill( PV_npvsGood,factor);

      // if ( Filling.Contains("Yes") ) ST_Sum_Presel -> Fill(Scalar_Sum_pT, factor) ;
      

      Fill_Lepton_Hist_Preselction_LvL( Filling +"MET" , 0 , 0) ; // both entries 0 for MET 

      if ( LeptonType.Contains("Muon")     && n_Mu.size()  > 0 )    index = n_Mu[0];

      if ( LeptonType.Contains("Electron") && n_ele.size() > 0 )    index = n_ele[0];

      count =  0 ;

      if ( index != -1 ) Fill_Lepton_Hist_Preselction_LvL( Filling + LeptonType , index , count) ;        // Filling Lepton

      // Fill_Lepton_Hist_Preselction_LvL( "Electron" , i , ele_count) ;  // Filling electron

      // Fill Forward jet
      JetSize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_forwjet[count] ;
             Fill_Jet_Hist_Preselction_LvL( Filling + "ForwJet",  index , count) ;                  
        }

      // Fill Clean jet
      JetSize   = ( n_cleanjet.size() >= 2 ) ?  2 : n_cleanjet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_cleanjet[count] ;            
             Fill_Jet_Hist_Preselction_LvL(  "LeptonCleanJet" + Filling ,  index , count) ; 

        } 

      // Fill Lepton Clean bjet
      JetSize   = ( b_jet.size() >= 2 ) ?  2 : b_jet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = b_jet[count] ;            
             Fill_Jet_Hist_Preselction_LvL( "LeptonCleanedbJet" + Filling ,  index , count) ; 

        } 

      // Fill Fat jet
      JetSize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_AK8Jet[count] ;            
             if ( count == 0) Fill_FatJet_Hist_Preselction_LvL(Filling +  "CleanedLeadingJet" ,    index , count) ;  
             if ( count == 1) Fill_FatJet_Hist_Preselction_LvL(Filling +  "CleanedSubleadingJet",  index , count) ;               

        } 

      // Fill topbjet kinematics here if topbjet passed
      count    = 0;
        
      if ( TopbjetCheck.Contains("Topbjet")) Fill_Jet_Hist_Preselction_LvL( TopbjetCheck,  top_bjet , count) ;

      // Delta R distributions 
      Check_deltaR_For_Muon_wrt_LepCleanJets( Filling + TopbjetCheck ) ;  // Put Bjet if deltaR with Bjet otherwise, Jet 
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////======================== FUNCTIONS FOR SELECTION OF OBJECTS===========================/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////============ Loop over electron for seletion===================//////////////////////////////////////////
void  Check_Electrons_For_Event_N_Fill(TString Filling)
{

    int   ele_count = -1 ;  
    float eleEta = 0.0 ; 

    //============ Loop over electron for seletion===================
      for (int i = 0; i < nElectron; ++i)
      {
    
        if (Electron_cutBased[i] < 2.0 )          continue ; // for loose, but move to medium
        eleEta = fabs (Electron_eta[i]) ;
        // cout << "\n before Eta = " << Eta;
        // if ( eleEta > 1.44 && (eleEta < 1.56 || eleEta > 2.5) )    continue ;   

        if (  eleEta > 2.5 )    continue ;          
        if ( eleEta > 1.44 && eleEta < 1.56  )    continue ;          


        if (Electron_pt[i] < 40.0 )             continue ;  

        n_ele.push_back(i);
        
        ele_count ++; 

        if ( ele_count >= 2) continue;

        Fill_Lepton_Hist_Preselction_LvL( Filling  , i , ele_count) ;  // Yes for Filling

      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!


////////////////////============ Loop over MUON for seletion===================//////////////////////////////////////////

void  Check_Muons_For_Event_N_Fill( TString Filling)
{

      int   mu_count = -1 ;
      int   Muon_ID  = -1; 

      for (int ki = 0; ki < nMuon; ++ki)
      {

        Muon_ID = Muon_highPtId[ki] ;
 
        // cout << "\n\n Before Selection, muon have pT = " << Muon_pt[ki] << "  n eta = " << Muon_eta[ki] << "  n HighpTID = " << Muon_ID ;
        // printf("Muon_highPtId = %d", Muon_highPtId[ki] )  ;

        if ( fabs(Muon_eta[ki]) > 2.1 )       continue ;
        if ( Muon_ID < 2  )                   continue ;
        if ( Muon_pt[ki] < 50.0 )             continue ;
    
        n_Mu.push_back(ki);

        mu_count ++; 

        if ( mu_count >= 2) continue;

        Fill_Lepton_Hist_Preselction_LvL( Filling  , ki , mu_count) ;        

      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!      


////////////////////============ Loop over FatJet for seletion===================//////////////////////////////////////////

void  Check_FatJet_For_Event_N_Fill( TString Filling)
{
      int fatjet_count   = -1 ;

      for (int fi = 0; fi < nFatJet; ++fi)
      {
         if ( FatJet_corr_JEC[fi] < 0.0)  continue ;

         if ( FatJet_pt[fi] < 200.0 )        continue ;
         if ( fabs(FatJet_eta[fi]) > 2.4 )     continue ;
         if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

         n_AK8Jet.push_back(fi);
         fatjet_count ++; 

         if ( Filling.Contains("Yes")) {

                if ( fatjet_count == 0) Fill_FatJet_Hist_Preselction_LvL( "LeadingJet" , fi , fatjet_count) ;
                if ( fatjet_count == 1) Fill_FatJet_Hist_Preselction_LvL( "SubleadingJet" , fi , fatjet_count) ;       

         }

      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!   

void  Check_CleanFatJet_For_Event_N_Fill( TString Sorting)
{
      int fatjet_count   = -1 ;

      for (int fi = 0; fi < nFatJet; ++fi)
      {


        if ( FatJet_corr_JEC[fi] < 0.0)  continue ;

        if ( FatJet_pt_clean[fi] < 200.0 )        continue ;
        if ( fabs(FatJet_eta_clean[fi]) > 2.4 )     continue ;
        if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

        // if ( FatJet_pt[fi] < 200.0 )        continue ;
        // if ( fabs(FatJet_eta[fi]) > 2.4 )     continue ;
        // if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

        n_AK8Jet.push_back(fi);

        fatjet_count ++; 

        // no fILLING HERE BUT AFTER SORTING THE  FATJETS, IF YOU WANT UNCOMMENT IT AND PASS "NO" TO SORTING ()
        // if ( fatjet_count >= 2) continue;
        // if ( fatjet_count == 0 &&  Sorting.Contains("NoSorting")) Fill_FatJet_Hist_Preselction_LvL( "CleanedLeading_Jet" , fi , fatjet_count) ;
        // if ( fatjet_count == 1 &&  Sorting.Contains("NoSorting")) Fill_FatJet_Hist_Preselction_LvL( "CleanedSubleading_Jet" , fi , fatjet_count) ;       


      }


      // Sortjet vector is iitialised and further you want to sort it do it on main function .... Means FUCK YOU !!!! :)
      if ( n_AK8Jet.size() > 1 ) {

            fatjet_copy = n_AK8Jet ;
            fatjet_sort = n_AK8Jet ;
            // FatJet_sorting_pT_based_After_Cleaning(Sorting);      // PASS "NO" FOR NO FILLING     

      }

      else             fatjet_sort = n_AK8Jet ; 


}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!! 


////////////////////============ Loop over Jet for seletion===================//////////////////////////////////////////

void  Check_Jet_For_Event_N_Fill( TString Filling )
{
      
      int jet_count = -1 ;      
      int jets      = -1 ;

      for (int ji = 0; ji < nJet; ++ji)
      {
        if ( Jet_corr_JEC[ji] < 0.0  )    continue ;  

        if ( Jet_pt[ji] < 30.0 )        continue ;
        if ( Jet_jetId[ji] < 1 )        continue ;
        
        if ( fabs(Jet_eta[ji]) > 2.4 )  n_forwjet.push_back(ji) ;
        else n_jet.push_back(ji);
        // else Check_Jet_Matched_Lepton_Index_N_Pass( ji ) ;

      }  


      int Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;
      
      if ( Filling.Contains("Yes") ) {
        
         Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;
         for (int jij = 0; jij < Qsize; ++jij )
             {
                  jets = n_jet[jij] ;
                  Fill_Jet_Hist_Preselction_LvL( "ALLJET",  jets , jij) ;                  
             } // end of loop

         Qsize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
         for (int kij = 0; kij < Qsize; ++kij )
             {
                  jets = n_forwjet[kij] ;
                  Fill_Jet_Hist_Preselction_LvL( "ForwJet",  jets , kij) ;                  
             }               
      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!   

void Check_Jet_Matched_Lepton_Index_N_Pass( int jet_index)
{
     

         if ( Jet_electronIdx1[jet_index] == -1 &&  Jet_electronIdx2[jet_index] == -1 
              && Jet_muonIdx1[jet_index] == -1 && Jet_muonIdx2[jet_index] == -1 )  n_jet.push_back(jet_index) ;

}

/////// sELECTION OF cLEAN jET AND fILL aLSO  uSING fILLING STRING
void  Check_CLeanedJet_For_Event_N_Fill( TString Filling )
{
      
      int jet_count = -1 ;      
      int jets      = -1 ;

      for (int ji = 0; ji < nJet; ++ji)
      {
        if ( Jet_corr_JEC[ji] < 0.0  )    continue ;  

        if ( Jet_pt_clean[ji] < 30.0 )    continue ;
        if ( Jet_jetId[ji] < 2 )          continue ;  // for 2016, < 1, 2017/18 < 2
        
        if ( fabs(Jet_eta_clean[ji]) > 2.4 )  n_forwjet.push_back(ji) ;
        else n_jet.push_back(ji);
        // else Check_Jet_Matched_Lepton_Index_N_Pass( ji ) ;

      }  


      int Qsize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
      
      if ( Filling == "Yes") {        
         
         for (int kij = 0; kij < Qsize; ++kij )
             {
                  jets = n_forwjet[kij] ;
                  Fill_Jet_Hist_Preselction_LvL( Filling + "ForwJet",  jets , kij) ;                  
             }               
      } // end of filling   


      // Initialise sorting vector and do it in main function... FUCKER !!!!
      if ( n_jet.size() == 1 ) jet_sort = n_jet ;    

      if ( n_jet.size() > 1 ){
          
            jet_sort = n_jet ; 
            jet_copy = n_jet ;     
      }      

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!  


bool Bjet_Selection_After_drCheck(int c_jet, TString WorkingPoint) { 

           //  for 2016 Era
           // new tagger (see the recipe for DeepFlavour) the tagger is given by the sum: p(b)+p(bb)  
           // DeepCSVL   0.2217        
           // DeepCSVM   0.6321       
           // DeepCSVT   0.8953 

           // Jet_btagDeepB

           // for 2017 Ultra legacy  LINK : https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation106XUL17 
                   // DeepCSV   btagDeepB   
                   // loose   0.1355  
                   // medium  0.4506       
                   // tight   0.7738  

           bool bjet_pass = false;

           if (WorkingPoint.Contains("loose") ){
             if ( Jet_btagDeepB[c_jet] >  0.1355) {
                 b_jetloose.push_back(c_jet) ;   
                 b_jet.push_back(c_jet) ;     
                  
                 bjet_pass = true; 
             }

             else {

                 not_tagged_bjets.push_back(c_jet) ;  // for keeping track of not tagged bquarks for weighting
             }

           }
         


           if (WorkingPoint.Contains("medium") ){
             if ( Jet_btagDeepB[c_jet] >  0.4506) {
                 b_jetmedium.push_back(c_jet) ;  
                 b_jet.push_back(c_jet) ;     
                 bjet_pass = true; 
             }

             else {

                 not_tagged_bjets.push_back(c_jet) ;  // for keeping track of not tagged bquarks for weighting
             }

           }

           if (WorkingPoint.Contains("tight") ){
             if ( Jet_btagDeepB[c_jet] >  0.7738) {
                 b_jettight.push_back(c_jet) ;   
                 b_jet.push_back(c_jet) ;     
                 bjet_pass = true; 
             }

             else {

                 not_tagged_bjets.push_back(c_jet) ;  // for keeping track of not tagged bquarks for weighting
             }

           }
         

           return bjet_pass ;
  }


void Check_Cleaned_Bjet_After_Muon_Isolation( TString WorkingPoint)  {


      int jet_count = -1 ;      
      int jets      = -1 ; 
      bool bjet_pass = true ; 

      // for (int i = 0; i < n_cleanjet.size(); ++i)
      for (int i = 0; i < n_jet.size(); ++i)
      {
          // jets = n_cleanjet[i]  ;
          jets = n_jet[i]  ;

          if ( Jet_pt_clean[jets] < 50.0 ) continue ;
          if ( Bjet_Selection_After_drCheck( jets, WorkingPoint) == 0 ) continue;


          jet_count ++ ;
          if ( jet_count < 2) Fill_Jet_Hist_Preselction_LvL( "LeptonCleanedbJet" + WorkingPoint ,  jets , jet_count) ;

          // SF = DeepCSV2_bTag_SF_Calculator(CSV_OP, JF, sys_type,(*jetPt)[subbjet_index_1[s]], (*jetEta)[subbjet_index_1[s]]); 
          // cout << "\n WorkingPoint = " << WorkingPoint ;
      }


}

///////////////////////////////////////////////////////////////////////////////////////////
///////------====== GENERAL FUNCTIONS ARE DEFINED BELOW  -----------===================
//////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////======================= FUNCTIONS FOR DELTA R N DELTA PT CALCULATION =============================//////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//------------ for  General Functions of dR & dPt ---------------------------

  float dPt_Calculator(const TVector3 & lep , const TVector3 & jet ) {
    // type for jet type, type = 0 is AK4jet, type = 1 is puppijet, type = 2 is 
    float  vec_mag = 0.0 ;
    TVector3 vec_Xprod ; 
  
    vec_Xprod = lep.Cross(jet);
    vec_mag   = jet.Mag();
  
    float dPt =  (vec_Xprod.Mag() ) / vec_mag ;
  
    // cout << "\n dPt calculated = " << dPt ;
    return dPt ;

  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   


  float dR_Calculator( float eta1, float phi1, float eta2, float phi2)  {
  
     const float PI    =  2.0*acos(0.0);
     const float TWOPI =  2.0*PI;
     float PHI         =  fabs( phi1 - phi2 ) ;
     dPhi              = (PHI<=PI)? PHI : TWOPI-PHI;
     dEta              =  fabs( eta1 - eta2 );       
     dR                =  Sqrt(dPhi*dPhi + dEta*dEta) ;
  
     return dR ;
  
  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   

  float delta_phi(float phi1,float phi2) {
     const float PI=2.0*acos(0.0);
     const float TWOPI=2.0*PI;
     float PHI=fabs( phi1 - phi2 ) ;
     return (PHI<=PI)? PHI : TWOPI-PHI;
  
  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   

//------------ for  General Functions of dR & dPt ---------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//CLEANING OF JET FROM FATJETS =====================================
//------ First Delta R   (jet, fatjet) check
//---- Then Cleaning is done ----------------  
void Check_deltaR_N_Cleaning_Jet_from_FatJet( TString Check_OR_Clean)
{

  int   hist_index = -1 ; // Use for indexing histogram in later loop
  // Here index = 0 to 2 for leading fatjet
  // Here index = 3 to 5  for sub leading fatjet
  // Here index = 6 to 8  for 3rd leading fatjet, 

  int   fatjet = -1 ;
  int   slimjet    = -1 ;
  float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ; 

  int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
  int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

  if ( Check_OR_Clean.Contains("CHECK")){

    for (int fi = 0; fi < Fsize; ++fi)
    {
      fatjet = n_AK8Jet[fi] ;
      eta1   = FatJet_eta[fatjet] ;
      phi1   = FatJet_phi[fatjet] ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        // slimjet  = n_jet[ji] ;
        slimjet  = n_cleanjet[ji] ;
        
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
 
        hist_index = 3*fi + ji ;
        // cout << "\n index = " << hist_index;

        DeltaR_Hist_FatJet_wrt_jet.at(hist_index)  ->Fill(dR , factor );
      }

    }

  }
    
    ////////======== HERE WE CHECKED AK4JET OVERLAPPING WITH LEADING AK8JET AND DISCARD THOSE AK4JET WHICH ARE IN Dr < 1.2 RANGE =======//////////////
  if ( Check_OR_Clean.Contains("CLEAN")){

    Ssize   =  n_jet.size() ;
    fatjet  = n_AK8Jet[0] ;
    eta1   = FatJet_eta[fatjet] ;
    phi1   = FatJet_phi[fatjet] ;
    hist_index  = -1 ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
        
        if ( dR > 1.2){
             hist_index ++ ;
             n_cleanjet.push_back(slimjet) ;
             if( hist_index < 2) Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJet",  slimjet , hist_index) ; // Filling Clean Jet at this level============                 
        }     
      } /// END OF JET LOOP !!!!!!!
  }  // END OF CLEANING !!!!!!!!
  

}  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   





/////////////////--------Check DeltaR Distribution Between Muon & Jet---------------////////////////////////////////////////////
void Check_deltaR_For_Muon_wrt_Jet( TString Check)
{

      int   hist_index = -1 ; // Use for indexing histogram in later loop
      // Here index = 0 to 2  for normal jet
      // Here index = 3 to 5  for clean jet
      // Here index = 6 to 8  for b jet,


      int lead_muon = n_Mu[0];
      int slimjet    = -1 ;
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;      

      eta1   = Muon_eta[lead_muon] ;
      phi1   = Muon_phi[lead_muon] ;

      int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        hist_index  = ji ;  // index for normal jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Dirty Jets") ;

      }  

      Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

      for (int kji = 0; kji < Ssize; ++kji)
      {
        slimjet  = n_jet[kji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        hist_index  = kji + 3 ;  // index for clean jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        // cout <<"\n For leading Muon = " << lead_muon <<"     the DeltaR = " << dR ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR) ;
        // Check_deltaR_For_Jet_wrt_MatchedMuon( slimjet, eta2, phi2 ) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Clean Jets") ;        

      }

}




void Check_deltaR_For_Jet_wrt_MatchedMuon( int jet_index, float jet_eta, float jet_phi)
{
     int Jet_MatchedMuon = Jet_muonIdx1[jet_index] ;

     float muon_eta  = Muon_eta[Jet_MatchedMuon] ; 
     float muon_phi  = Muon_phi[Jet_MatchedMuon] ;

     dR_Calculator(jet_eta, jet_phi, muon_eta, muon_phi) ;

     cout <<"\n For Jetmatched Muon = " << Jet_MatchedMuon <<"     the DeltaR = " << dR <<endl;


}



void Check_Jet_Matched_Lepton_Index( int jet_index, TString Jet_Type)
{
     if( Jet_Type == "Dirty Jets"){

         cout <<" \n //////   ========== for Dirty Jets [ " << jet_index << " ] matched leptons are ===========    ////////////" <<endl;
         cout << "   ---------------------Lead Electron  [ " << Jet_electronIdx1[jet_index] << " ]  and Sublead Electron  [ "  << Jet_electronIdx2[jet_index] << " ] ------";
         cout << "\n   ---------------------Lead Muon      [ " << Jet_muonIdx1[jet_index] << " ]  and Sublead Muon  [ "  << Jet_muonIdx2[jet_index] << " ] ------";


     }

     // int Jet_MatchedMuon = Jet_muonIdx1[jet_index] ;

     if( Jet_Type == "Clean Jets"){

         cout <<" \n //////////========== for Clean Jets [ " << jet_index << " ] matched leptons are ==============////////////" <<endl;
         cout << "   ---------------------Lead Electron  [ " << Jet_electronIdx1[jet_index] << " ]  and Sublead Electron  [ "  << Jet_electronIdx2[jet_index] << " ] ------";
         cout << "\n   ---------------------Lead Muon      [ " << Jet_muonIdx1[jet_index] << " ]  and Sublead Muon  [ "  << Jet_muonIdx2[jet_index] << " ] ------";


     }


}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////================= DEFINITION OF JET TAGGING FUNCTIONS====================///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////========== For HiggsJet Selections Using PUPPI Variables===================================

  void  HiggsJet_Selection_Using_PUPPI_Variables(int var, float ST_cut) 
  {
     
 
     int index = -1 ;
     
   // if you want to check only leading fatjet  
     // int Wsize  = ( n_AK8Jet.size() >= 2) ? 2 :  n_AK8Jet.size() ;  

   // if you want to check whole fatjet collection
     // n_AK8Jet   = fatjet_sort ;
     int Wsize  =  n_AK8Jet.size()  ;

     const  Int_t cut = 7 ;
     double Tau42_Cut_loc[cut] = { 0.0, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75} ;
     double tau              =  0.0 ;
     double msoftdrop_corr   =  0.0 ;

     // Loop over fatjet collection
     for (int g = 0 ; g < Wsize ; g ++ ){
  
        index = n_AK8Jet[g] ;
  
        // These selections are from last VHF Talk on 17 Feb 2020
        // link: https://indico.cern.ch/event/889576/contributions/3752894/attachments/1988684/3315032/Tprime_Update_VHF_MEETING_17Feb2020.pdf 

        msoftdrop_corr = FatJet_msoftdrop_raw[index] * FatJet_msoftdrop_corr_PUPPI[index] ;
        // cout <<" \n Delta PUPPI mass = "  << tau ;   //!

        
        tau               =  (FatJet_tau4[index]/FatJet_tau2[index]) ;
        // if( tau > Tau42_Cut_loc[var - 1]  ) continue ;
        if( tau > 0.75  ) continue ;        
        if( msoftdrop_corr > 150.00 || msoftdrop_corr < ST_cut ) continue ;
        if( FatJet_pt_clean[index]  < 400.0 ) continue;     
        Higgsjets.push_back(index);
    
     } /// END of Loop !!!!

  }  // END of FUNCTION !!!!      

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ========================================= Lepton Jet Cleaning effects ---------------- =========================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --------- ========= Delta R of Muon wrt Lep Clean jets ---------=======

void Check_deltaR_For_Muon_wrt_LepCleanJets( TString Check)
{

      int   hist_index = -1 ; // Use for indexing histogram in later loop
      // Here index = 0 to 2  for slim jet
      // Here index = 3 to 5  for fatjet
      // Here index = 6 to 8  for b jet,


      int lead_muon = n_Mu[0];
      int slimjet    = -1 ;
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;      

      eta1   = Muon_eta[lead_muon] ;
      phi1   = Muon_phi[lead_muon] ;

      // int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;
      int Ssize = -1 ;
      int Fsize = -1 ;

      // if ( ( Check.Contains("Bjet")) ) jet_copy = b_jet ;
      // if ( ( Check.Contains("Jet"))  ) jet_copy = n_cleanjet ;      
      if ( Check.Contains("Yes")) Ssize   = ( jet_copy.size() >= 2 ) ?  2 : jet_copy.size() ;

      if ( Check.Contains("Topbjet")){
         jet_copy[1]  = top_bjet;
         Ssize   = 2 ; // size is fixed as we are checking topbjet and leading bjet
      }   

      for (int ji = 0; ji < Ssize; ++ji)
      {
      
        slimjet  = jet_copy[ji] ;
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        hist_index  = ji ;  // index for normal jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR, factor );
        // cout<<" \n Pt for clean jet [" << slimjet << " ] = " << Jet_pt_clean[slimjet] ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Dirty Jets") ;

      }  

      if( Check.Contains("Yes")) Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;

      for (int kji = 0; kji < Fsize; ++kji)
      {
        slimjet  = n_AK8Jet[kji] ;
        eta2     = FatJet_eta_clean[slimjet] ;
        phi2     = FatJet_phi_clean[slimjet] ;       

        hist_index  = kji + 3 ;  // index for clean jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        // cout <<"\n For leading Muon = " << lead_muon <<"     the DeltaR = " << dR ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR, factor );
        // Check_deltaR_For_Jet_wrt_MatchedMuon( slimjet, eta2, phi2 ) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Clean Jets") ;        

      }

} // END of FUNCTION !!!!

//CLEANING OF Lepton-Jet Clean Jets FROM Lepton-Jet Clean FATJETS =====================================
//------ First Delta R   (jet, fatjet) check
//---- Then Cleaning is done ---------------- ===

void Check_deltaR_For_LeptonClean_Jet_from_FatJet( TString Check_OR_Clean)
{

  int   hist_index = -1 ; // Use for indexing histogram in later loop
  // Here index = 0 to 2 for leading fatjet
  // Here index = 3 to 5  for sub leading fatjet
  // Here index = 6 to 8  for 3rd leading fatjet, 

  int   fatjet = -1 ;
  int   slimjet    = -1 ;
  float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ; 

  // n_jet = jet_sort ;  // COMMENT IT IF YOU DON'T WANT SORTED JETS !!!!!!

  int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
  int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

  if ( Check_OR_Clean.Contains("CHECK")){
    // Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

    for (int fi = 0; fi < Fsize; ++fi)
    {
      fatjet = n_AK8Jet[fi] ;
      eta1   = FatJet_eta_clean[fatjet] ;
      phi1   = FatJet_phi_clean[fatjet] ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        // slimjet  = n_cleanjet[ji] ;
        
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
 
        hist_index = 3*fi + ji ;
        // cout << "\n index = " << hist_index;

        DeltaR_Hist_FatJet_wrt_jet.at(hist_index)  ->Fill(dR, factor );
      }

    }

  }

  if ( Check_OR_Clean.Contains("CLEAN")){

    Ssize   =  n_jet.size() ;
    fatjet  = n_AK8Jet[0] ;
    eta1   = FatJet_eta_clean[fatjet] ;
    phi1   = FatJet_phi_clean[fatjet] ;
    hist_index  = -1 ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
        
        if ( dR > 1.2){
             hist_index ++ ;
             n_cleanjet.push_back(slimjet) ;
             if( hist_index < 2 && Check_OR_Clean.Contains("Yes")) Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJetYes",  slimjet , hist_index) ; // Filling Clean Jet at this level============                 
        } 
      }      
      
  } /// END OF JET LOOP !!!!!!!
  
  

}  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////======================== Pt based sorting of Jets==========================================.///////////////////////////////

// ===================================

void FatJet_sorting_pT_based_After_Cleaning( TString Filling) {

      int jmax = -1 ;
      int jt   = -1 ; 
      float max_pT = 0.0;


      if ( Filling.Contains("Sorting")){
        // In case You want Sorting
        for( int i = 0 ; i < fatjet_sort.size(); i++){

          if( fatjet_copy.size() == 0) continue ;

          jmax   = 0;
          max_pT = FatJet_pt_clean[fatjet_copy[0]];  

          for (int k = 0; k < fatjet_copy.size(); k++)
          {
            jt   = fatjet_copy[k];

            if( FatJet_pt_clean[jt] > max_pT ) {
              jmax   = k ;
              max_pT = FatJet_pt_clean[jt];

            }  
          }
         
          fatjet_sort[i] = fatjet_copy[jmax];
          fatjet_copy.erase(fatjet_copy.begin() + jmax);

        }
      }



      // // Filling at preselection Level if Filling is Yes.
      if ( Filling.Contains("Yes")){

          jmax  = ( fatjet_sort.size() >= 2) ? 2 :  fatjet_sort.size() ;  

          for (int i = 0; i < jmax; ++i)
          {
               // jmax = n_AK8Jet[i];
               jt   = fatjet_sort[i] ;

               if ( i == 0) Fill_FatJet_Hist_Preselction_LvL( "CleanedLeadingJet" ,  jt , i ) ;  
               if ( i == 1) Fill_FatJet_Hist_Preselction_LvL( "CleanedSubleadingJet",  jt , i ) ;  
          }
      } // END of FIlling Loop !!!!!

      // cout << "\n Size of copy = " << fatjet_copy.size() ;
}  // END of FUNCTION !!!!  


//-=-=-=-==-=-==-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=---------================------============--------=

void Jet_sorting_pT_based_After_Cleaning(TString Filling) {

      int jmax = -1 ;
      int jt   = -1 ; 

      float max_pT = 0.0;

      if ( Filling.Contains("Sorting")){
      
            // In case You want Sorting        
            for( int i = 0 ; i < jet_sort.size(); i++){

              if( jet_copy.size() == 0) continue ;

              jmax   = 0;
              max_pT = Jet_pt_clean[jet_copy[0]];  

              for (int k = 0; k < jet_copy.size(); k++)
              {
                jt   = jet_copy[k];

                if( Jet_pt_clean[jt] > max_pT ) {
                  jmax   = k ;
                  max_pT = Jet_pt_clean[jt];

                }  
              }
             
              jet_sort[i] =  jet_copy[jmax];
              jet_copy.erase(jet_copy.begin() + jmax);

            }
      }
      
      // // Filling at preselection Level if Filling is Yes.

      if ( Filling.Contains("Yes")){

          jmax  = ( jet_sort.size() >= 2) ? 2 :  jet_sort.size() ;  

          for (int i = 0; i < jmax; ++i)
          {
               // jmax = n_AK8Jet[i];
               jt   = jet_sort[i] ;
               Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJetYes",  jt , i) ;   
          }
      } // END of FIlling Loop !!!!!

}  // END of FUNCTION !!!!  


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // General Functions for Calling and Checking clean Jets functions =========
   void Study_JetLepton_Cleaning_Effect()
   {


      Check_FatJet_For_Event_N_Fill( "No") ;  // Put Yes if you want to plots Jet Histo without pT based sorting

      Check_Jet_For_Event_N_Fill( "No" ) ;  // Put Yes if you want to plots Jet Histo without pT based sorting

      // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet("CHECK") ;  

      if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CLEAN") ;  

      int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
      int Ssize   = ( n_cleanjet.size() >= 2 ) ?  2 : n_cleanjet.size() ;

      int jet_idx = -1 ;

      for (int i = 0; i < Fsize; ++i)
      {
            jet_idx = n_AK8Jet[i] ;
            if ( i == 0 )     Fill_CleanedFatJet_Hist( "LeadingJet", jet_idx , i) ;
            if ( i == 1 )     Fill_CleanedFatJet_Hist( "SubleadingJet", jet_idx , i) ;
     
      }
// Fill_CleanedJet_Hist

      for (int i = 0; i < Ssize; ++i)
      {
            jet_idx = n_cleanjet[i] ;
            if ( i == 0 )     Fill_CleanedJet_Hist( "LeadingJet", jet_idx , i) ;
            if ( i == 1 )     Fill_CleanedJet_Hist( "SubleadingJet", jet_idx , i) ;
     
      }

  }




//----==========--- For Cleaned Fatjet Histograms ------------==========================

void   Fill_CleanedFatJet_Hist( TString fatjet, int fatjet_index , int fatjet_count)
{


  int mu_idx = -1 ;

  if ( n_Mu.size() > 0){
        mu_idx = n_Mu[0] ;

  }

  // Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_FatJet.at(0  + fatjet_count )   ->Fill(FatJet_pt_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(2  + fatjet_count )   ->Fill(FatJet_pt[fatjet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_FatJet.at(4  + fatjet_count )   ->Fill(FatJet_eta_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(6  + fatjet_count )   ->Fill(FatJet_eta[fatjet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_FatJet.at(8  + fatjet_count )   ->Fill(FatJet_phi_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(10 + fatjet_count )   ->Fill(FatJet_phi[fatjet_index]) ;
   
    // for Delta R histo
    if( mu_idx != -1 ){

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta_clean[fatjet_index], FatJet_phi_clean[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(12 + fatjet_count )   ->Fill(dR) ;

            Hist_DeltaR_wrt_Pt_LepCleanJet.at(4  + fatjet_count) ->Fill(   Jet_pt_clean[fatjet_index] , dR  );

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta[fatjet_index], FatJet_phi[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(14 + fatjet_count )   ->Fill(dR) ;

            Hist_DeltaR_wrt_Pt_LepCleanJet.at(6  + fatjet_count) ->Fill(   Jet_pt[fatjet_index] , dR  );

    }        

  }

  // Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_FatJet.at(0  + fatjet_count )   ->Fill(FatJet_pt_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(2  + fatjet_count )   ->Fill(FatJet_pt[fatjet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_FatJet.at(4  + fatjet_count )   ->Fill(FatJet_eta_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(6  + fatjet_count )   ->Fill(FatJet_eta[fatjet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_FatJet.at(8  + fatjet_count )   ->Fill(FatJet_phi_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(10 + fatjet_count )   ->Fill(FatJet_phi[fatjet_index]) ;
   
    // for Delta R histo
    if( mu_idx != -1 ){

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta_clean[fatjet_index], FatJet_phi_clean[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(12 + fatjet_count )   ->Fill(dR) ;
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(4  + fatjet_count) ->Fill(   Jet_pt_clean[fatjet_index], dR  );

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta[fatjet_index], FatJet_phi[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(14 + fatjet_count )   ->Fill(dR) ;
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(6 + fatjet_count) ->Fill(   Jet_pt[fatjet_index], dR  );

    } 

  }  

} // END of the function !!!!!!!!!!!     

//=======---------------=================---------------=======================

void   Fill_CleanedJet_Hist( TString fatjet, int jet_index , int jet_count)
{


  int mu_idx = -1 ;

  if ( n_Mu.size() > 0){
        mu_idx = n_Mu[0] ;

  }
  
  TVector3 vec_lep, vec_jet;


  // Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_Jet.at(0  + jet_count )   ->Fill(Jet_pt_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(2  + jet_count )   ->Fill(Jet_pt[jet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_Jet.at(4  + jet_count )   ->Fill(Jet_eta_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(6  + jet_count )   ->Fill(Jet_eta[jet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_Jet.at(8  + jet_count )   ->Fill(Jet_phi_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(10 + jet_count )   ->Fill(Jet_phi[jet_index]) ;
   
    // for Delta R and Delta Pt histo
    if( mu_idx != -1 ){

            vec_lep.SetPtEtaPhi( Muon_pt[mu_idx],Muon_eta[mu_idx], Muon_phi[mu_idx] ) ;

            dR_mu_jet = dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index]) ;      
            // Hist_for_LeptonCleaned_Jet.at(12 + jet_count )   ->Fill(dR_mu_jet);

            vec_jet.SetPtEtaPhi( Jet_pt_clean[jet_index], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index] ) ;
            dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
            // Hist_for_LeptonCleaned_Jet.at(16 + jet_count )   ->Fill(dPt_mu_jet);

            // dPt_dR_mu_cleanjet1 ->Fill( dR_mu_jet, dPt_mu_jet);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(0  + jet_count) ->Fill(  Jet_pt_clean[jet_index] , dR_mu_jet  );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(0 + jet_count) ->Fill(  Jet_pt_clean[jet_index] , dPt_mu_jet );


            // dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta[jet_index], Jet_phi[jet_index]) ;      
            // Hist_for_LeptonCleaned_Jet.at(14 + jet_count )   ->Fill(dR_mu_jet) ;

            // vec_jet.SetPtEtaPhi( Jet_pt[jet_index], Jet_eta[jet_index], Jet_phi[jet_index] ) ;
            // dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
            // Hist_for_LeptonCleaned_Jet.at(18 + jet_count )   ->Fill(dPt_mu_jet) ;  

            // dPt_dR_mu_jet1  ->Fill( dR, dPt_mu_jet);
            // Hist_DeltaR_wrt_Pt_LepCleanJet.at(2   + jet_count) ->Fill(  Jet_pt[jet_index], dR_mu_jet   );
            // Hist_DeltaPt_wrt_Pt_LepCleanJet.at(2 + jet_count)  ->Fill(  Jet_pt[jet_index], dPt_mu_jet  );         


    }        

  }

  // Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_Jet.at(0  + jet_count )   ->Fill(Jet_pt_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(2  + jet_count )   ->Fill(Jet_pt[jet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_Jet.at(4  + jet_count )   ->Fill(Jet_eta_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(6  + jet_count )   ->Fill(Jet_eta[jet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_Jet.at(8  + jet_count )   ->Fill(Jet_phi_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(10 + jet_count )   ->Fill(Jet_phi[jet_index]) ;
   
    // for Delta R and Delta Pt histo
    if( mu_idx != -1 ){

            vec_lep.SetPtEtaPhi( Muon_pt[mu_idx],Muon_eta[mu_idx], Muon_phi[mu_idx] ) ;

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index]) ;      
            Hist_for_LeptonCleaned_Jet.at(12 + jet_count )   ->Fill(dR_mu_jet) ;

            vec_jet.SetPtEtaPhi( Jet_pt_clean[jet_index], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index] ) ;
            dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
            Hist_for_LeptonCleaned_Jet.at(16 + jet_count )   ->Fill(dPt_mu_jet) ;      

            dPt_dR_mu_cleanjet2 ->Fill( dR_mu_jet, dPt_mu_jet);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(0  + jet_count) ->Fill(   Jet_pt_clean[jet_index], dR_mu_jet  );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(0 + jet_count) ->Fill(   Jet_pt_clean[jet_index], dPt_mu_jet );


            // dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta[jet_index], Jet_phi[jet_index]) ;      
            // Hist_for_LeptonCleaned_Jet.at(14 + jet_count )   ->Fill(dR_mu_jet) ;

            // vec_jet.SetPtEtaPhi( Jet_pt[jet_index], Jet_eta[jet_index], Jet_phi[jet_index] ) ;
            // dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
            // Hist_for_LeptonCleaned_Jet.at(18 + jet_count )   ->Fill(dPt_mu_jet) ;  

            // dPt_dR_mu_jet2  ->Fill( dR_mu_jet, dPt_mu_jet);
            // Hist_DeltaR_wrt_Pt_LepCleanJet.at(2   + jet_count) ->Fill(  Jet_pt[jet_index] , dR_mu_jet  );
            // Hist_DeltaPt_wrt_Pt_LepCleanJet.at(2 + jet_count)  ->Fill(  Jet_pt[jet_index] , dPt_mu_jet );  

    }        

  }  // END of SUbleading Jet Loop

} // END of the function !!!!!!!!!!!   


/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
////////////////////////SELECTIONS APPLIED AND TEST ARE RUN HERE =========//////////////////////////////////////////////////////



void Scalar_Sum_pT_Function( TString LeptonType)
{
  
  Scalar_Sum_pT =  MET_pt ;

  int    b2 = -1 ;
 
  //---- In case of muonic channel 
  if ( LeptonType.Contains("Muon") && n_Mu.size() != 0) {
    
    b2 = n_Mu[0];  
  
    Scalar_Sum_pT += Muon_pt[b2]  ;

  }
  
  //---- In case of electronic channel
  if ( LeptonType.Contains("Electron") && n_ele.size() != 0) {
    
    b2 = n_ele[0];  
  
    Scalar_Sum_pT += Electron_pt[b2]  ;

  }

  //-Only for higgs tagging test, independent of  lep channel
  if (LeptonType.Contains("Lep"))
  {
      if (n_Mu.size() != 0)
      {
            b2 = n_Mu[0];  
        
          Scalar_Sum_pT += Muon_pt[b2]  ;
      }
      
      else {
          if (n_ele.size() != 0)
          {
          b2 = n_ele[0];  
        
          Scalar_Sum_pT += Electron_pt[b2]  ;
          }
      
      }
  }

  for ( int k = 0 ; k < n_AK8Jet.size() ; k ++) {
    b2 =  n_AK8Jet[k];
    Scalar_Sum_pT += FatJet_pt_clean[b2];
  }
  

}


void Scalar_Sum_pT_LeadObj_Function( TString LeptonType)
{
  
  Scalar_Sum_pT =  MET_pt ;

  int    b2 = -1 ;
 
  //---- In case of muonic channel 
  if ( LeptonType.Contains("Muon") && n_Mu.size() != 0) {
    
    b2 = n_Mu[0];  
  
    Scalar_Sum_pT += Muon_pt[b2]  ;

  }
  
  //---- In case of electronic channel
  if ( LeptonType.Contains("Electron") && n_ele.size() != 0) {
    
    b2 = n_ele[0];  
  
    Scalar_Sum_pT += Electron_pt[b2]  ;

  }


  b2            = b_jet[0];

  Scalar_Sum_pT += Jet_pt_clean[b2] ;

  b2            = Higgsjets[0];

  Scalar_Sum_pT += FatJet_pt_clean[b2];
  
}

// Here we are confirming that Higgs far from muon
// As per final decay state of Tprime
void  Check_DeltaR_of_Higgs_wrt_Top_Lepton( TString LeptonType, TString Mass_or_dR_Check )
  {
      // Histogram index 17  for  "Hist_DeltaR_HiggsJet_wrt_lep (muon or ele)
      // Histogram index 18  for  "Hist_DeltaR_HiggsJet_wrt_jet1
      // Histogram index 19  for  "Hist_DeltaR_HiggsJet_wrt_jet2
      // Histogram index 20  for  "Hist_DeltaR_HiggsJet_wrt_jet3
      

      float Higgs_eta = 0.0;
      float Higgs_phi = 0.0;

      // int Hsize   = ( Higgsjets.size() >= 3 ) ?  3 : Higgsjets.size() ;
      int Hsize   = Higgsjets.size() ;
      int top_prod_index     = -1 ;

      float top_prod_eta = - 99.0 ;
      float top_prod_phi = - 99.0 ;


 
      //---- In case of muonic channel 
      if ( LeptonType.Contains("Muon") && n_Mu.size() != 0) {
        
        top_prod_index = n_Mu[0];  
  
        top_prod_eta = Muon_eta[top_prod_index] ;
        top_prod_phi = Muon_phi[top_prod_index] ;

      }
  
      //---- In case of electronic channel
      if ( LeptonType.Contains("Electron") && n_ele.size() != 0) {
        
        top_prod_index = n_ele[0];  
  
        top_prod_eta = Electron_eta[top_prod_index] ;
        top_prod_phi = Electron_phi[top_prod_index] ;

      }

      // int   hist_index   = -1 ;  // index for clean jet
      int   Higgs_index  = -1 ;

      // DELTAr wrt top lepton
      for (int i = 0; i < Hsize; ++i)
      {
          Higgs_index = Higgsjets[i];
          
          if(  Mass_or_dR_Check.Contains("DeltaR")) {

            Higgs_eta = FatJet_eta_clean[Higgs_index] ;
            Higgs_phi = FatJet_phi_clean[Higgs_index] ;
            dR_Calculator(Higgs_eta, Higgs_phi, top_prod_eta, top_prod_phi) ;           

            if ( dR > 1.2 ) DeltaR_Cleared_Higgsjet.push_back(Higgs_index) ;
          }

          if( Mass_or_dR_Check.Contains("Mass")) {

             if ( FatJet_mass_clean[Higgs_index] > 90.0 && FatJet_mass_clean[Higgs_index] < 160.0 ) DeltaR_Cleared_Higgsjet.push_back(Higgs_index) ;          
          }  
      }
      
      // Higgs_index = Higgsjets[0];
      // h_Higgs_Mass -> Fill( FatJet_mass_clean[Higgs_index], factor);
  
  } // END of the function !!!!!!!!!!!

// Here we are confirming that bjet is far from Higgs and not so far from muon
// As per final decay state of Tprime
void  Check_DeltaR_of_bjet_wrt_Top_Lepton_n_Higgs( TString LeptonType )
  {
     

      float Higgs_dR = 0.0;
      float top_prod_dR = 0.0 ;

      int   Higgs_index    = DeltaR_Cleared_Higgsjet[0] ;
      int   muon_index     = n_Mu[0] ; 
      int   ele_index      = n_ele[0];
      int   bjet_index     = -1 ; 

      top_bjet  = -1 ;

      // DELTAr wrt Muon and Higgs
      for (int i = 0; i < b_jet.size(); ++i)
      {
          if ( top_bjet > -1 ) continue ;
          bjet_index  = b_jet[i] ;

          Higgs_dR     = dR_Calculator(FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index],Jet_eta_clean[bjet_index], Jet_phi_clean[bjet_index]) ;
          if( LeptonType.Contains("Muon"))    top_prod_dR  = dR_Calculator(Muon_eta[muon_index], Muon_phi[muon_index], Jet_eta_clean[bjet_index], Jet_phi_clean[bjet_index]) ;
          if( LeptonType.Contains("Electron"))top_prod_dR  = dR_Calculator(Electron_eta[ele_index], Electron_phi[ele_index], Jet_eta_clean[bjet_index], Jet_phi_clean[bjet_index]) ;

          if ( Higgs_dR > 1.2 && top_prod_dR > 0.1) top_bjet = bjet_index ;

      }

  
  } // END of the function !!!!!!!!!!!  

//-------------- Muon Isolation Test and Check --------------------------------


  //-------Find The first two closest jet to muon------------------------

  int Find_Closest_Jet_To_Muon( int muon_index, TString Repeat){


      int   closest  = -1 ;
      int   closejet = -1 ;
      float dR_min   = 99.0;
      float dr_check = 0.0 ;

      // IN CASE OF NO JET, ISOLATION IS NOT APPLIED AND HENCE NIL CLOSEJET
      for( int h =0 ; h < jet_copy.size() ; h ++ ){
  
        closejet    =  jet_copy[h] ;           
        
        dr_check    = dR_Calculator(Muon_eta[muon_index], Muon_phi[muon_index], Jet_eta_clean[closejet], Jet_phi_clean[closejet]) ;  

  
        if ( dr_check < dR_min  ) 
        {
          dR_min      = dr_check ;
          closest     = h ;
        }     

      }

      // cout <<" \n closejet = " << closest ;

      return closest ;               

  } 


  void  Fill_n_Check_Closest_Jet_to_Muon(int val, TString Filling, int muon) {
  
      // Here we are trying to find the closest jet to leading muon
      // Using deltaR between jet and leading muon
      // We look for atmost two such jets and plot dR and dPt
      // Check the respective distribution
      // For one iteration we erase the jet from jet_collection(here jet_copy)
      // 
            
      nearest_jet  = -1 ;   

      int   firstjet_close_muon     = -1;
      int   secondjet_close_muon    = -1;    

      int   jet_index               = -1 ;


      float dR_Selection            =   LepIso2D_dR_Selection[val] ; 
      float dPt_Selection           =   LepIso2D_dPt_Selection[val];

      TVector3 vec_lep, vec_jet;

      // cout << "\n dR_Selection = " << dR_Selection <<"  &&& dPt_Selection = " << dPt_Selection ;

      jet_index            =  Find_Closest_Jet_To_Muon(muon, "No"); 

      firstjet_close_muon  =  jet_copy[jet_index];

      Fill_CleanedJet_Hist( "LeadingJet", firstjet_close_muon , 0) ;

      if (( dR_mu_jet > dR_Selection || dPt_mu_jet > dPt_Selection) && ( jet_index != -1 ) ) {

          // cout << "\n Passed dR_mu_jet = " << dR_mu_jet <<"  &&& Passed dPt_mu_jet = " << dPt_mu_jet  <<endl;
          // passed_dR ++ ;

          nearest_jet = firstjet_close_muon ;
          if ( Filling.Contains("Yes")) Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val, factor);
          // if ( Filling.Contains("Yes")) Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val);

      }      

      Check_DeltaR_N_Pt_for_Closest_Jet_to_Muon( muon , jet_index) ;


      // if ( nearest_jet < -2 ) {

      //     jet_copy.erase(jet_copy.begin() + jet_index);

      //     jet_index            =  Find_Closest_Jet_To_Muon(muon, "No"); 

      //     secondjet_close_muon =  jet_copy[jet_index];

      //     Fill_CleanedJet_Hist( "SubleadingJet", secondjet_close_muon , 1) ;  
    
      //     if (( dR_mu_jet > dR_Selection || dPt_mu_jet > dPt_Selection && ( jet_index != -1 ) ) ) {

      //         nearest_jet = secondjet_close_muon ;
      //     if ( Filling.Contains("Yes")) Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val, factor);

      //     }

      // }

  } 

  // MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
  int Lepton_Isolation_Study_MiniIso_2DLepIso ( TString Isolation, TString LepIsoCheck ){
 
      int pass  = -1 ;
      // TString selection   = Cut_LepIso_Variable[sel_level];

      TString Isolation_Check[12] = { 
                                      "No Isolation",             //0 
                                      "MiniIsoLoose",             //1 
                                      "MiniIsoMedium",            //2 
                                      "MiniIsoTight",             //3 
                                      "MiniIsoVeryTight",         //4 
                                      "dR_02_OR_dPt_20",  //5 
                                      "dR_03_OR_dPt_20",  //6 
                                      "dR_04_OR_dPt_20",  //7 
                                      "dR_02_OR_dPt_40",  //8 
                                      "dR_03_OR_dPt_40",  //9 
                                      "dR_04_OR_dPt_40",  //10 
                                      "dR_04_OR_dPt_60"   //11                                      
                                    };

      int wp_point =  LepIso_IDbit[Isolation] ;

      // wp_point = LepIso_IDbit[Isolation_Check[1]]  ;

      TVector3 vec_lep, vec_jet; 

      int muon      = n_Mu[0];   
      int muon_Iso  = Muon_miniIsoId[muon] ;

      nearest_jet = -1 ;

      // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5);
      Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5, factor);

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( Isolation.Contains("Preselect")) pass = muon ;


      // if ( Isolation.Contains("MiniIso") && (muon_Iso >= wp_point)){

      //    pass = muon ;

      //    Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point, factor);

      // }

      if ( LepIsoCheck.Contains("Yes")){

          for (int i = 1; i < 12; ++i)
          {
              Isolation = Isolation_Check[i] ;

              wp_point =  LepIso_IDbit[Isolation] ;

              // For Checking with Mini-Isolation working points
              if ( Isolation.Contains("MiniIso") && (muon_Iso >= wp_point)){

                 pass = muon ;
                 Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point, factor);
                 // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point);

              }


              if ( Isolation.Contains("dR") && jet_copy.size() > 0 ) Fill_n_Check_Closest_Jet_to_Muon(wp_point,  LepIsoCheck , muon) ;
          }    
      
      }

      
      return pass ;

  }  


  // MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
  int Selection_Lepton_Isolation_Using_MiniIso_2DLepIso ( TString Isolation, TString LepIsoCheck ){
 
      int pass  = -1 ;
      // TString selection   = Cut_LepIso_Variable[sel_level];


      int wp_point =  LepIso_IDbit[Isolation] ;

      TVector3 vec_lep, vec_jet; 

      int muon      = n_Mu[0];   
      int muon_Iso  = Muon_miniIsoId[muon] ;

      nearest_jet = -1 ;

      Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5, factor);

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( Isolation.Contains("Preselect")) pass = muon ;


      wp_point =  LepIso_IDbit[Isolation] ;

      // For Checking with Mini-Isolation working points
      if ( Isolation.Contains("MiniIso") && (muon_Iso >= wp_point)){

          pass = muon ;
          // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point, factor);
      }

      // For Checking with 2d Lepton Isolation working points      
      if ( Isolation.Contains("dR") && jet_copy.size() > 0 ) {

          Fill_n_Check_Closest_Jet_to_Muon(wp_point, LepIsoCheck , muon) ;

          // cout << " \n nearest_jet  = " << nearest_jet ;          
          if ( nearest_jet != -1 )pass = muon ;          

      }    
      
      // cout << " \n pass  = " << pass ;

      return pass ;

  }  



  void Check_DeltaR_N_Pt_for_Closest_Jet_to_Muon( int mu_idx , int close_jet) {
  
      // Here we are trying to find the closest jet to leading muon
      // Using deltaR between jet and leading muon
      // We look for atmost two such jets and plot dR and dPt
      // Check the respective distribution
      // For one iteration we erase the jet from jet_collection(here jet_copy)
      // 
            
      passed_total_events ++ ;      

      int   firstjet_close_muon     = -1;
      int   secondjet_close_muon    = -1;    

      int   jet_index               = -1 ;


      float dR_Selection            =   0.2; 
      float dPt_Selection           =   20.0;

      float  dr_check = 0.0 ;
      TVector3 vec_lep, vec_jet;

      // cout << "\n dR_Selection = " << dR_Selection <<"  &&& dPt_Selection = " << dPt_Selection ;

      // jet_index            =  Find_Closest_Jet_To_Muon(mu_idx, "No"); 

      jet_index            =  close_jet ;
      
      if (  jet_index != -1 ) {

      firstjet_close_muon  =  jet_copy[jet_index];

      vec_lep.SetPtEtaPhi( Muon_pt[mu_idx],Muon_eta[mu_idx], Muon_phi[mu_idx] ) ;

      dR_mu_jet = dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[firstjet_close_muon], Jet_phi_clean[firstjet_close_muon]) ;      
      Hist_for_LeptonCleaned_Jet.at(12 )   ->Fill(dR_mu_jet, factor);

      vec_jet.SetPtEtaPhi( Jet_pt_clean[firstjet_close_muon], Jet_eta_clean[firstjet_close_muon], Jet_phi_clean[firstjet_close_muon] ) ;
      dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
      Hist_for_LeptonCleaned_Jet.at(16 )   ->Fill(dPt_mu_jet, factor);

      dPt_dR_mu_cleanjet1 ->Fill( dR_mu_jet, dPt_mu_jet, factor);


          if ( dR_mu_jet > dR_Selection )      passed_dR ++ ;

          if ( dPt_mu_jet > dPt_Selection )    passed_dPt ++ ;

          if ( dR_mu_jet > 0.2 && dPt_mu_jet > 20.0 ) passed_only_dRdPt ++ ;

          if ( dR_mu_jet < 0.2 && dPt_mu_jet < 20.0 ) passed_no_dRdPt ++ ;

          if ( dR_mu_jet > 0.2 || dPt_mu_jet > 20.0 ) passed_both_dRdPt ++ ;

              // cout << "\n Passed dR_mu_jet = " << dR_mu_jet <<"  &&& Passed dPt_mu_jet = " << dPt_mu_jet  <<endl;

      }

      if ( jet_index == -1 ) {
        passed_nojet ++ ;
        // dr_check = dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[firstjet_close_muon], Jet_phi_clean[firstjet_close_muon] ) ;
        // cout <<" \n dr = " << dr_check ;
        // jet_index            =  Find_Closest_Jet_To_Muon(mu_idx, "Yes"); 

      }  
  }   



//////////////////------------------------------------

//-------Find The first two closest jet to muon------------------------

  int Find_Closest_Jet_To_Electron( int ele_index, TString Repeat){


      int   closest  = -1 ;
      int   closejet = -1 ;
      float dR_min   = 99.0;
      float dr_check = 0.0 ;

      // IN CASE OF NO JET, ISOLATION IS NOT APPLIED AND HENCE NIL CLOSEJET
      for( int h =0 ; h < jet_copy.size() ; h ++ ){
  
        closejet    =  jet_copy[h] ;           
        
        dr_check    = dR_Calculator(Electron_eta[ele_index], Electron_phi[ele_index], Jet_eta_clean[closejet], Jet_phi_clean[closejet]) ;  

  
        if ( dr_check < dR_min  ) 
        {
          dR_min      = dr_check ;
          closest     = h ;
        }     

      }

      // cout <<" \n closejet = " << closest ;

      return closest ;               

  } 


  int Fill_n_Check_Closest_Jet_to_Electron(int val, TString Filling, int electron) {
  
      // Here we are trying to find the closest jet to leading electron
      // Using deltaR between jet and leading electron
      // We look for atmost two such jets and plot dR and dPt
      // Check the respective distribution
      // For one iteration we erase the jet from jet_collection(here jet_copy)
      // 
            
      int pass_jet = -1  ;   

      int   firstjet_close_ele     = -1;

      int   jet_index               = -1 ;


      float dR_Selection            =   LepIso2D_dR_Selection[val] ; 
      float dPt_Selection           =   LepIso2D_dPt_Selection[val];

      TVector3 vec_lep, vec_jet;

      // cout << "\n dR_Selection = " << dR_Selection <<"  &&& dPt_Selection = " << dPt_Selection ;

      jet_index            =  Find_Closest_Jet_To_Electron(electron, "No"); 

      firstjet_close_ele  =  jet_copy[jet_index];

      Fill_CleanedJet_Hist( "LeadingJet", firstjet_close_ele , 0) ;

      if (( dR_mu_jet > dR_Selection || dPt_mu_jet > dPt_Selection) && ( jet_index != -1 ) ) {

          // cout << "\n Passed dR_mu_jet = " << dR_mu_jet <<"  &&& Passed dPt_mu_jet = " << dPt_mu_jet  <<endl;
          // passed_dR ++ ;

          pass_jet = jet_index ;
          // if ( Filling.Contains("Yes")) Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val, factor);
          Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val, factor);

          // if ( Filling.Contains("Yes")) Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + val);

      }     

      Check_DeltaR_N_Pt_for_Closest_Jet_to_Electron( electron, jet_index) ; 

      return pass_jet ;
  } 

  // 
  int Electron_Isolation_Study_MiniIso_2DLepIso ( TString Isolation, TString LepIsoCheck ){
 
      int pass  = -1 ;
      // TString selection   = Cut_LepIso_Variable[sel_level];

      TString Isolation_Check[12] = { 
                                      "No Isolation",             //0 
                                      "MiniIsoLoose",             //1 
                                      "MiniIsoMedium",            //2 
                                      "MiniIsoTight",             //3 
                                      "MiniIsoVeryTight",         //4 
                                      "dR_02_OR_dPt_20",  //5 
                                      "dR_03_OR_dPt_20",  //6 
                                      "dR_04_OR_dPt_20",  //7 
                                      "dR_02_OR_dPt_40",  //8 
                                      "dR_03_OR_dPt_40",  //9 
                                      "dR_04_OR_dPt_40",  //10 
                                      "dR_04_OR_dPt_60"   //11
                                    };

      int wp_point =  LepIso_IDbit[Isolation] ;

      // wp_point = LepIso_IDbit[Isolation_Check[1]]  ;

      TVector3 vec_lep, vec_jet; 

      int electron      = n_ele[0];   
      int ele_Iso      = 0.3 ;

      nearest_jet = -1 ;

      // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5);
      Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5, factor);

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( Isolation.Contains("Preselect")) pass = electron ;

      if ( LepIsoCheck.Contains("Yes")){

          for (int i = 5; i < 12; ++i)
          {
              Isolation = Isolation_Check[i] ;

              wp_point =  LepIso_IDbit[Isolation] ;

              // For Checking with Mini-Isolation working points
              if ( Isolation.Contains("MiniIso") && (ele_Iso >= wp_point)){

                 pass = electron ;
                 Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point, factor);
                 // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point);

              }


              if ( Isolation.Contains("dR") && jet_copy.size() > 0 ) Fill_n_Check_Closest_Jet_to_Electron(wp_point,  LepIsoCheck , electron) ;


          }    
      
      }

      
      return pass ;

  }  


  // MiniIso ID from miniAOD selector (1=MiniIsoLoose, 2=MiniIsoMedium, 3=MiniIsoTight, 4=MiniIsoVeryTight)
  int Selection_Electron_Isolation_Using_MiniIso_2DLepIso ( TString Isolation, TString LepIsoCheck ){
 
      int pass  = -1 ;
      // TString selection   = Cut_LepIso_Variable[sel_level];


      int wp_point =  LepIso_IDbit[Isolation] ;

      TVector3 vec_lep, vec_jet; 

      int electron      = n_ele[0];   
      int ele_Iso      = 0.3 ;

      int pass_jet = -1 ;

      Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5, factor);

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( Isolation.Contains("Preselect")) pass = electron ;


      wp_point =  LepIso_IDbit[Isolation] ;

      // For Checking with Mini-Isolation working points
      if ( Isolation.Contains("MiniIso") && (ele_Iso >= wp_point)){

          pass = electron ;
          // Cut_MiniIso_n_2DLepIso_Flow -> Fill ( 0.5 + wp_point, factor);
      }

      // For Checking with 2d Lepton Isolation working points      
      if ( Isolation.Contains("dR") && jet_copy.size() > 0 ) {

          pass_jet = Fill_n_Check_Closest_Jet_to_Electron(wp_point, LepIsoCheck , electron) ;

          // cout << " \n nearest_jet  = " << nearest_jet ;          
                    
          if ( pass_jet != -1 ) pass = electron ;    
          // cout << "\n pass = " << nearest_jet ;

      }    
      
      // cout << " \n pass  = " << pass ;      
      return pass ;

  }  



  void Check_DeltaR_N_Pt_for_Closest_Jet_to_Electron( int ele_index, int close_jet) {
  
      // Here we are trying to find the closest jet to leading muon
      // Using deltaR between jet and leading muon
      // We look for atmost two such jets and plot dR and dPt
      // Check the respective distribution
      // For one iteration we erase the jet from jet_collection(here jet_copy)
      // 
            
      passed_total_events ++ ;      


      int   firstjet_close_ele     = -1;

      int   jet_index               = -1 ;


      float dR_Selection            =   0.2; 
      float dPt_Selection           =   20.0;

      float  dr_check = 0.0 ;
      TVector3 vec_lep, vec_jet;

      // cout << "\n dR_Selection = " << dR_Selection <<"  &&& dPt_Selection = " << dPt_Selection ;

      // jet_index            =  Find_Closest_Jet_To_Electron(ele_index, "No"); 

      jet_index               =  close_jet ;

      
      if (  jet_index != -1 ) {

      firstjet_close_ele  =  jet_copy[jet_index];

      vec_lep.SetPtEtaPhi( Electron_pt[ele_index],Electron_eta[ele_index], Electron_phi[ele_index] ) ;

      dR_mu_jet = dR_Calculator(Electron_eta[ele_index], Electron_phi[ele_index], Jet_eta_clean[firstjet_close_ele], Jet_phi_clean[firstjet_close_ele]) ;      
      Hist_for_LeptonCleaned_Jet.at(12 )   ->Fill(dR_mu_jet, factor);

      vec_jet.SetPtEtaPhi( Jet_pt_clean[firstjet_close_ele], Jet_eta_clean[firstjet_close_ele], Jet_phi_clean[firstjet_close_ele] ) ;
      dPt_mu_jet  = dPt_Calculator(vec_lep, vec_jet) ;      
      Hist_for_LeptonCleaned_Jet.at(16 )   ->Fill(dPt_mu_jet, factor);

      // cout <<"\n Dpt = " << dPt_mu_jet ;

      dPt_dR_mu_cleanjet1 ->Fill( dR_mu_jet, dPt_mu_jet, factor);


          if ( dR_mu_jet > dR_Selection )      passed_dR ++ ;

          if ( dPt_mu_jet > dPt_Selection )    passed_dPt ++ ;

          if ( dR_mu_jet > 0.2 && dPt_mu_jet > 20.0 ) passed_only_dRdPt ++ ;

          if ( dR_mu_jet < 0.2 && dPt_mu_jet < 20.0 ) passed_no_dRdPt ++ ;

          if ( dR_mu_jet > 0.2 || dPt_mu_jet > 20.0 ) passed_both_dRdPt ++ ;

              // cout << "\n Passed dR_mu_jet = " << dR_mu_jet <<"  &&& Passed dPt_mu_jet = " << dPt_mu_jet  <<endl;

      }

      if ( jet_index == -1 ) {
        passed_nojet ++ ;
        // dr_check = dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[firstjet_close_muon], Jet_phi_clean[firstjet_close_muon] ) ;
        // cout <<" \n dr = " << dr_check ;
        // jet_index            =  Find_Closest_Jet_To_Muon(mu_idx, "Yes"); 

      }  
  }   



//////=========================================================

void Comparison_of_Pt_N_SoftDrop_Selection( int fatjet_index) {

   const  Int_t cut = 8 ;
   float pT_Cut_loc[cut] = { 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0} ;
   
   const  Int_t cutSD = 8 ;
   float SDMass_Cut_loc[cutSD] = { 0.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0} ;

   float cut_pTSD = -1.0 ;

   float pT_higgs = FatJet_pt_clean[fatjet_index] ;
         
   float msoftdrop_corr = FatJet_msoftdrop_raw[fatjet_index] * FatJet_msoftdrop_corr_PUPPI[fatjet_index] ;


   
   for (int i = 1; i < cut; i++)
    {
      //cut_idx is index of pT cut you want to apply, to check whole range, replace cut_idx to 1
      cut_pTSD = pT_Cut_loc[i] ;
      
     if( pT_higgs  > cut_pTSD ) Cut_pTHiggs_Flow->Fill( i + 0.5, factor);  

    }


   if ( msoftdrop_corr < 160.0) {   
        for (int i = 1; i < cutSD ; i++)
         {

           cut_pTSD = SDMass_Cut_loc[i] ;
           
           if(  msoftdrop_corr > cut_pTSD ) Cut_SDMass_Flow->Fill( i+0.5, factor);  

         }
   }    



} 

void Comparison_of_Tau42_N_DeepMD_H( int fatjet_index) {

   const  Int_t cut_tau = 22 ;

   const  Int_t deep_cut = 18 ;

   float Tau42_Cut_Check[cut_tau] =  { 0.0, 1.0, 0.95, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65, 0.6, 0.55, 0.5, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05};

   float DeepMD_H_Cut_Check[deep_cut] =  { 0.0, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90   };
  
   float cut = -1.0 ;

   
   float puppitau = (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]) ;

   
   // lOOP FOR TAU42 CHECK
   for (int i = 2; i < cut_tau; i++)
    {

      cut = Tau42_Cut_Check[i] ;
      
     if(  puppitau < cut ) {

        Cut_Tau42_Flow->Fill(i + 0.5, factor);  
        // if ( Scalar_Sum_pT > 600.0) Cut_ST_Tau42_Flow -> Fill(i + 0.5, factor);  
     }   

    }


   // lOOP FOR DEEPMD_H CHECK
   for (int si = 2; si < deep_cut; si++)
    {

      cut = DeepMD_H_Cut_Check[si] ;
      
     if(  FatJet_deepTagMD_H4qvsQCD[fatjet_index] > cut ) Cut_DeepMD_H_Flow->Fill( si + 0.5, factor);  

    }

} //!!! END of FUNCTION MAN  


void Selection_Comparison_HiggsTagging( TString Higgs_PT_SD_Check) {

   const  Int_t cut = 7 , index = 4;
   // float pT_Cut_loc[cut] = {  200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0} ;
   float pT_Cut_loc = 350.0 ;
   float SD_Cut_loc = 80.0   ;

   //======================Thsi part decides the Pt and SD selection =============

      if ( Higgs_PT_SD_Check.Contains("PT300")) pT_Cut_loc = 300.0 ;
      if ( Higgs_PT_SD_Check.Contains("PT350")) pT_Cut_loc = 350.0 ;
      if ( Higgs_PT_SD_Check.Contains("PT400")) pT_Cut_loc = 400.0 ;
      if ( Higgs_PT_SD_Check.Contains("PT450")) pT_Cut_loc = 450.0 ;

      if ( Higgs_PT_SD_Check.Contains("SD70"))  SD_Cut_loc = 70.0 ;
      if ( Higgs_PT_SD_Check.Contains("SD80"))  SD_Cut_loc = 80.0 ;
      if ( Higgs_PT_SD_Check.Contains("SD90"))  SD_Cut_loc = 90.0 ;
      if ( Higgs_PT_SD_Check.Contains("SD100")) SD_Cut_loc = 100.0 ;
   //==================================SD7=====SD===========7====================
   int jet_idx = -1;

   int anyonecutpassed = -1 ;
  
   double  msoftdrop_corr = 0.0 ;   

   float cut_pT = -1.0 ;               

   Cut_pTHiggs_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

   Cut_SDMass_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

   Cut_Tau42_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
   Cut_DeepMD_H_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER   

   Cut_ST_Tau42_Flow -> Fill(0.5, factor); 

   for (int i = 0; i < n_AK8Jet.size(); ++i)
   {
        if ( anyonecutpassed != -1 )   continue ;

        jet_idx = n_AK8Jet[i];

        if ( Higgs_PT_SD_Check.Contains("withPtSD")) Comparison_of_Pt_N_SoftDrop_Selection( jet_idx ) ;

        if ( FatJet_pt_clean[jet_idx] < pT_Cut_loc ) continue ;
      
        msoftdrop_corr = FatJet_msoftdrop_raw[jet_idx] * FatJet_msoftdrop_corr_PUPPI[jet_idx] ;

        if ( msoftdrop_corr < SD_Cut_loc || msoftdrop_corr > 160.0 ) continue ;

        Cut_Tau42_Flow->Fill(1.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
        Cut_DeepMD_H_Flow->Fill(1.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
        Cut_ST_Tau42_Flow -> Fill(1.5, factor); 

        Comparison_of_Tau42_N_DeepMD_H( jet_idx) ;
   }

}  //!!! END of FUNCTION MAN   !!!!!


//===========  Higgs tagging Function=======================

void HiggsTagging_Using_PT_SD_Tau_N_Deep( TString Higgs_PT_SD_Tau_Deep_Check) {

      float pT_Cut_loc = 300.0  ;
      float SD_Cut_loc = 80.0   ;
      float Tau_Cut_loc = 0.80  ;
      float Deep_MD_Cut_loc = 0.10 ;

      //======================Thsi part decides the Pt and SD selection =============

         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("PT300")) pT_Cut_loc = 300.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("PT350")) pT_Cut_loc = 350.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("PT400")) pT_Cut_loc = 400.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("PT450")) pT_Cut_loc = 450.0 ;

         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("SD70"))  SD_Cut_loc = 70.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("SD80"))  SD_Cut_loc = 80.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("SD90"))  SD_Cut_loc = 90.0 ;
         if ( Higgs_PT_SD_Tau_Deep_Check.Contains("SD100")) SD_Cut_loc = 100.0 ;
        
      //==================================SD7=====SD===========7====================
      int jet_idx = -1;

      int anyonecutpassed = -1 ;
  
      double  msoftdrop_corr = 0.0 ;   

      float cut_pT = -1.0 ;               

      Cut_Higgs_Tagging_Flow -> Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

      // Cut_SDMass_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

      // Cut_Tau42_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
      // Cut_DeepMD_H_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER   

      for (int i = 0; i < n_AK8Jet.size(); ++i)
      {
           // if ( anyonecutpassed != -1 )   continue ;

           jet_idx = n_AK8Jet[i];

           if ( FatJet_pt_clean[jet_idx] < pT_Cut_loc ) continue ;
         
           msoftdrop_corr = FatJet_msoftdrop_raw[jet_idx] * FatJet_msoftdrop_corr_PUPPI[jet_idx] ;

           if ( msoftdrop_corr < SD_Cut_loc || msoftdrop_corr > 160.0 ) continue ;

           Cut_Tau42_Flow->Fill(1.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
           Cut_DeepMD_H_Flow->Fill(1.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

           if ( Tau42_N_DeepMD_H_Selection( Higgs_PT_SD_Tau_Deep_Check, jet_idx)  == -1 ) continue ;
           
           // if ( FatJet_mass_clean[jet_idx] < 90.0 && FatJet_mass_clean[jet_idx] > 160.0 ) continue ;
           anyonecutpassed  = jet_idx;

           Higgsjets.push_back(jet_idx);

      }

      if ( anyonecutpassed != -1 )       {
  
        Cut_Higgs_Tagging_Flow -> Fill(1.5, factor);    //  Events Passed by Higgs Selections


      }
      // return anyonecutpassed ;

}  //!!! END of FUNCTION MAN   !!!!!



int Tau42_N_DeepMD_H_Selection( TString Tau_Deep_Check, int fatjet_index) {


   float Tau42_Cut_Check  = 0.0 ;

   float DeepMD_H_Cut_Check  = 0.0 ;
  
   int   cutpassed = -1 ;

   //======================Thsi part decides the Tau and Deep selection ============

      if ( Tau_Deep_Check.Contains("Tau80")) Tau42_Cut_Check = 0.80 ;
      if ( Tau_Deep_Check.Contains("Tau75")) Tau42_Cut_Check = 0.75 ;

      if ( Tau_Deep_Check.Contains("Deep10")) DeepMD_H_Cut_Check = 0.10 ;
      if ( Tau_Deep_Check.Contains("Deep15")) DeepMD_H_Cut_Check = 0.15 ;
     
   //==================================SD7=====SD===========7====================



   // lOOP FOR TAU42 CHECK
   if ( Tau_Deep_Check.Contains("Tau")){

        if ( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]) < Tau42_Cut_Check) cutpassed = fatjet_index ;

   }
   
   // lOOP FOR DEEPMD_H CHECK
   if ( Tau_Deep_Check.Contains("Deep")) {
      
        if(  FatJet_deepTagMD_H4qvsQCD[fatjet_index] > DeepMD_H_Cut_Check ) cutpassed = fatjet_index ;  

   }

   return cutpassed ; 

}  //!!! END of FUNCTION MAN   !!!!!


//------ Study of Generator Level Information -----------////////
void Study_of_Muon_GenPart_Information(){
  
    //  Quark and lepton codes. 
    // KF  Name  Printed         KF  Name            Printed
    // 1   $\d $   d             11  $\{e}^-$        e-
    // 2   $\u $   u             12  $\nu_{e}$       nu_e
    // 3   $\s $   s             13  $\mu^-$         mu-
    // 4   $\c $   c             14  $\nu_{\mu}$     nu_mu
    // 5   $\b $   b             15  $\tau^-$        tau-
    // 6   $\t $   t             16  $\nu_{\tau}$    nu_tau


    // Gauge boson and other fundamental boson codes. 
    // KF   Name           Printed    
    // 21  $\mathrm{g}$    g          
    // 22  $\gamma$        gamma   
    // 23  $\mathrm{Z}^0$  Z0  
    // 24  $\{W}^+$        W+      
    // 25  $\{H}^0$        H0  

    // Interesting Generator Status Flag  
    // For details link : https://cms-nanoaod-integration.web.cern.ch/integration/master/mc106Xul18_doc.html#GenPart  
    //gen status flags stored bitwise, bits are: 
    // 0  : isPrompt,  <----
    // 1  : isDecayedLeptonHadron, 
    // 2  : isTauDecayProduct, 
    // 3  : isPromptTauDecayProduct, 
    // 4  : isDirectTauDecayProduct, 
    // 5  : isDirectPromptTauDecayProduct, 
    // 6  : isDirectHadronDecayProduct, 
    // 7  : isHardProcess,   <----
    // 8  : fromHardProcess, <----
    // 9  : isHardProcessTauDecayProduct, 
    // 10 : isDirectHardProcessTauDecayProduct, 
    // 11 : fromHardProcessBeforeFSR,   <---- [ CHECK THIS ONE FOR ENSURING HARD COLLISIONS]
    // 12 : isFirstCopy, 
    // 13 : isLastCopy, 
    // 14 : isLastCopyBeforeFSR,   

    gen_Tmuon_idx           = -1 ;

    int gen_IdxMother = -1 ;

    int gen_IdxGrandMother = -1 ;    

    // To get prompt leptons from Tprime, TTbar Samples
    if ( Type_of_Muon.Contains("PromptLepton")) {

        for (int i = 0; i < nGenPart; ++i)
        {
       if ( fabs(GenPart_pdgId[i]) != 13 )  continue ;

       // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

       gen_IdxMother =  GenPart_genPartIdxMother[i];

       gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

       if ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 )  continue ;

       if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


       gen_Tmuon_idx           = i;

       continue ;

       cout << "\n\n Generator Level info for leptons" ;

       cout << "\n Lepton ID = " << GenPart_pdgId[gen_Tmuon_idx] ;

       cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



       cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

       cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



       cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

       cout << "\n Status = "    << GenPart_status[i] ;

       if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
       if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
       if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
       if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;       
        }

    } // END of Loop !!!!   

    // To get fake leptons from QCD Samples
    if ( Type_of_Muon.Contains("FakeLepton")) {

        for (int i = 0; i < nGenPart; ++i)
        {
       if ( fabs(GenPart_pdgId[i]) != 13 )  continue ;

       // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

       gen_IdxMother =  GenPart_genPartIdxMother[i];

       gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

       // if ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 )  continue ;

       // if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


       gen_Tmuon_idx           = i;

       continue ;

       cout << "\n\n Generator Level info for leptons" ;

       cout << "\n Lepton ID = " << GenPart_pdgId[gen_Tmuon_idx] ;

       cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



       cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

       cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



       cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

       cout << "\n Status = "    << GenPart_status[i] ;

       if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
       if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
       if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
       if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;       
        }

    } // END of Loop !!!!

}  // END of Functions !!!!

bool   Muon_Gen_Match (int c_muon) {

   bool match = true ;

   float eta1       = Muon_eta[c_muon];
   float phi1       = Muon_phi[c_muon];
   float pT1        = Muon_pt[c_muon];

   float eta2       = GenPart_eta[gen_Tmuon_idx];
   float phi2       = GenPart_phi[gen_Tmuon_idx];
   float pT2        = GenPart_pt[gen_Tmuon_idx];

   float dpT        = (fabs( pT1 - pT2) / pT2 );
   float dR_min        = dR_Calculator(eta1, phi1, eta2, phi2) ;

   if ( Muon_charge[c_muon] != (GenPart_pdgId[gen_Tmuon_idx] / -13 )) match = false ;

   if( dR_min > 0.1 ) match = false ;
   if( dpT > 0.3 ) match = false ; 


   // if(match == true) {
   // cout << " We have mucharge = " << Muon_charge[c_muon] << "  and gen muCharge = " << (GenPart_pdgId[gen_Tmuon_idx] / -13 )
   //  << " and rel. pT = " << dpT << " and deltaR = " << dR <<endl ;
   // }

   return match ;
}

void Loop_Over_Muon( TString Filling){

      //======================muon selection==========================
      //Here for signal & ttbar sample, gen matched muon are selected and plotted.. REMEMBER!!!!
      //For QCD , gen unmatched muon are selected to study mistag efficiency

      int   mu_count = -1 ;
      int   Muon_ID  = -1;
      int   matched  = -1 ;
      float PTcut    = -1.0;

      for( int f = 0; f <  nMuon ; f++)
        {

          if ( fabs(Muon_eta[f]) > 2.1 )       continue ;

          matched = Muon_Gen_Match(f)  ;

          Muon_ID = Muon_highPtId[f] ;
  
          if ( Filling.Contains("WithoutPT")) PTcut = 0.0;
          if ( Filling.Contains("WithPT"))    PTcut = 50.0;

          if ( (matched == 1) && Type_of_Muon.Contains("PromptLepton") ) mu_count = 1;
          if ( (matched == 0) && Type_of_Muon.Contains("FakeLepton") )   mu_count = 0;

          if ( mu_count == -1 )                 continue ;
          if ( Muon_ID < 2  )                   continue ;
          
          if ( Muon_pt[f] < PTcut )             continue ;

          // cout <<" \n mu_count = " << mu_count ;

          n_Mu.push_back(f) ;

          // if ( mu_count >= 2) continue;

          Fill_Lepton_Hist_Preselction_LvL( Filling  , f , 0) ; 

          mu_count      = -1; 
        }

      h_object_no.at(2) ->Fill(n_Mu.size() , factor );       //  index 2   for nMuon  Filling Population Plot

} 


void Study_of_Higgs_GenPart_Information( TString GenMother ){
  
    //  Quark and lepton codes. 
    // KF  Name  Printed         KF  Name            Printed
    // 1   $\d $   d             11  $\{e}^-$        e-
    // 2   $\u $   u             12  $\nu_{e}$       nu_e
    // 3   $\s $   s             13  $\mu^-$         mu-
    // 4   $\c $   c             14  $\nu_{\mu}$     nu_mu
    // 5   $\b $   b             15  $\tau^-$        tau-
    // 6   $\t $   t             16  $\nu_{\tau}$    nu_tau


    // Gauge boson and other fundamental boson codes. 
    // KF   Name           Printed    
    // 21  $\mathrm{g}$    g          
    // 22  $\gamma$        gamma   
    // 23  $\mathrm{Z}^0$  Z0  
    // 24  $\{W}^+$        W+      
    // 25  $\{H}^0$        H0  

    // Interesting Generator Status Flag  
    // For details link : https://cms-nanoaod-integration.web.cern.ch/integration/master/mc106Xul18_doc.html#GenPart  
    //gen status flags stored bitwise, bits are: 
    // 0  : isPrompt,  <----
    // 1  : isDecayedLeptonHadron, 
    // 2  : isTauDecayProduct, 
    // 3  : isPromptTauDecayProduct, 
    // 4  : isDirectTauDecayProduct, 
    // 5  : isDirectPromptTauDecayProduct, 
    // 6  : isDirectHadronDecayProduct, 
    // 7  : isHardProcess,   <----
    // 8  : fromHardProcess, <----
    // 9  : isHardProcessTauDecayProduct, 
    // 10 : isDirectHardProcessTauDecayProduct, 
    // 11 : fromHardProcessBeforeFSR,   <---- [ CHECK THIS ONE FOR ENSURING HARD COLLISIONS]
    // 12 : isFirstCopy, 
    // 13 : isLastCopy, 
    // 14 : isLastCopyBeforeFSR,   

    gen_Tmuon_idx           = -1 ;

    int gen_IdxMother = -1 ;

    int gen_IdxGrandMother = -1 ;    

    // To get prompt leptons from Tprime, TTbar Samples
    if ( Type_of_Jet.Contains("Higgs")) {

        for (int i = 0; i < nGenPart; ++i)
        {
            if ( fabs(GenPart_pdgId[i]) > 5 )  continue ;

            // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

            gen_IdxMother =  GenPart_genPartIdxMother[i];

            gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

            if ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 )  continue ;

            if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 25 ) continue ;

            gen_udscquark.push_back(i) ;

            // if ( GenMother.Contains("4q")) gen_udscquark.push_back(i) ;
            // if ( GenMother.Contains("WW")) gen_udscquark.push_back(gen_IdxMother) ;

            continue ;

            cout << "\n\n Generator Level info for leptons" ;

            cout << "\n Boson ID = " << GenPart_pdgId[i] ;

            cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



            cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

            cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



            cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

            cout << "\n Status = "    << GenPart_status[i] ;

            if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
            if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
            if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
            if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;       
        }

    } // END of Loop !!!!   

    // To get jets from TTbar Samples
    if ( Type_of_Jet.Contains("Top")) {

        for (int i = 0; i < nGenPart; ++i){

       if ( fabs(GenPart_pdgId[i]) >= 6 )  continue ;

       // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

       gen_IdxMother =  GenPart_genPartIdxMother[i];

       gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

       if ( ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 && fabs(GenPart_pdgId[gen_IdxMother]) != 6 ) )  continue ;

       if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


       gen_udscquark.push_back(i) ;

       continue ;

       cout << "\n\n Generator Level info for leptons" ;

       cout << "\n Lepton ID = " << GenPart_pdgId[i] ;

       cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



       cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

       cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



       cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

       cout << "\n Status = "    << GenPart_status[i] ;

       if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
       if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
       if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
       if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;  

       }

    } // END of Loop !!!!

    // To get jets from QCD Samples
    if ( Type_of_Jet.Contains("udscquark")) {

       for (int i = 0; i < nGenPart; ++i){

       if ( fabs(GenPart_pdgId[i]) >= 5 )  continue ;

       // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

       gen_IdxMother =  GenPart_genPartIdxMother[i];

       gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

       if ( ( fabs(GenPart_pdgId[gen_IdxMother]) > 24 ))  continue ;

       // if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


       gen_udscquark.push_back(i) ;

       continue ;

       cout << "\n\n Generator Level info for leptons" ;

       cout << "\n Lepton ID = " << GenPart_pdgId[i] ;

       cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



       cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

       cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



       cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

       cout << "\n Status = "    << GenPart_status[i] ;

       if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
       if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
       if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
       if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;  

       }

    } // END of Loop !!!!
}  // END of Functions !!!!   


bool FatJet_Gen_Match( int fatjet_index ){

  int   gen_jet = -1 ;

  bool  pass = true ;

  float dR_match = -1.0 ;

  // cout << "\n Size = " << gen_udscquark.size();
  
  for(int f = 0 ; f <  gen_udscquark.size() ; f ++)    {
          

       if( pass == 0) continue;

       gen_jet = gen_udscquark[f];                 

       dR_match = dR_Calculator( GenPart_eta[gen_jet], GenPart_phi[gen_jet], FatJet_eta_clean[fatjet_index], FatJet_phi_clean[fatjet_index]) ; 

       if ( dR_match > 0.8 ) { pass = false ;


        // cout <<"No it don't";
       } 
       // cout <<"\n dR_match = " << dR_match ;       
  }
 
  return pass ; 
}


/// loop over fatjets to check and select type of jets
void Loop_Over_FatJet(TString Filling) {
      

    // FatJet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection);      // PASS "NO" FOR NO FILLING    Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet 
    
     int fatjet_count   = -1 ;

      for (int fi = 0; fi < nFatJet; ++fi)
      {


        if ( FatJet_corr_JEC[fi] < 0.0)  continue ;

        if ( FatJet_pt_clean[fi] < 200.0 )        continue ;
        if ( fabs(FatJet_eta_clean[fi]) > 2.4 )     continue ;
        if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

        if ( FatJet_Gen_Match(fi) == 0 ) continue ;

        n_AK8Jet.push_back(fi);

        fatjet_count ++; 

      }

      
      // Sortjet vector is iitialised and further you want to sort it do it on main function .... Means FUCK YOU !!!! :)
      if ( n_AK8Jet.size() > 1 ) {

            fatjet_copy = n_AK8Jet ;
            fatjet_sort = n_AK8Jet ;
            // FatJet_sorting_pT_based_After_Cleaning(Sorting);      // PASS "NO" FOR NO FILLING     

      }

      else             fatjet_sort = n_AK8Jet ; 

    
      h_object_no.at(4) ->Fill(n_AK8Jet.size(), factor );       //  index 4   for nFatJet  Filling Population Plot

}


//------ Study of Generator Level Electron Information -----------////////
void Study_of_Electron_GenPart_Information(){
  
    //  Quark and lepton codes. 
    // KF  Name  Printed         KF  Name            Printed
    // 1   $\d $   d             11  $\{e}^-$        e-
    // 2   $\u $   u             12  $\nu_{e}$       nu_e
    // 3   $\s $   s             13  $\mu^-$         mu-
    // 4   $\c $   c             14  $\nu_{\mu}$     nu_mu
    // 5   $\b $   b             15  $\tau^-$        tau-
    // 6   $\t $   t             16  $\nu_{\tau}$    nu_tau


    // Gauge boson and other fundamental boson codes. 
    // KF   Name           Printed    
    // 21  $\mathrm{g}$    g          
    // 22  $\gamma$        gamma   
    // 23  $\mathrm{Z}^0$  Z0  
    // 24  $\{W}^+$        W+      
    // 25  $\{H}^0$        H0  

    // Interesting Generator Status Flag  
    // For details link : https://cms-nanoaod-integration.web.cern.ch/integration/master/mc106Xul18_doc.html#GenPart  
    //gen status flags stored bitwise, bits are: 
    // 0  : isPrompt,  <----
    // 1  : isDecayedLeptonHadron, 
    // 2  : isTauDecayProduct, 
    // 3  : isPromptTauDecayProduct, 
    // 4  : isDirectTauDecayProduct, 
    // 5  : isDirectPromptTauDecayProduct, 
    // 6  : isDirectHadronDecayProduct, 
    // 7  : isHardProcess,   <----
    // 8  : fromHardProcess, <----
    // 9  : isHardProcessTauDecayProduct, 
    // 10 : isDirectHardProcessTauDecayProduct, 
    // 11 : fromHardProcessBeforeFSR,   <---- [ CHECK THIS ONE FOR ENSURING HARD COLLISIONS]
    // 12 : isFirstCopy, 
    // 13 : isLastCopy, 
    // 14 : isLastCopyBeforeFSR,   

    gen_Tele_idx           = -1 ;

    int gen_IdxMother = -1 ;

    int gen_IdxGrandMother = -1 ;    

    // To get prompt leptons from Tprime, TTbar Samples
    if ( Type_of_Muon.Contains("PromptLepton")) {

        for (int i = 0; i < nGenPart; ++i) {
             if ( fabs(GenPart_pdgId[i]) != 11 )  continue ;

             // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

             gen_IdxMother =  GenPart_genPartIdxMother[i];

             gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

             if ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 )  continue ;

             if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


             gen_Tele_idx           = i;

             continue ;

             cout << "\n\n Generator Level info for leptons" ;

             cout << "\n Lepton ID = " << GenPart_pdgId[gen_Tele_idx] ;

             cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



             cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

             cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



             cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

             cout << "\n Status = "    << GenPart_status[i] ;

             if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
             if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
             if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
             if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;       
        
       }

    } // END of Loop !!!!   

    // To get fake leptons from QCD Samples
    if ( Type_of_Muon.Contains("FakeLepton")) {

        for (int i = 0; i < nGenPart; ++i)
        {
       if ( fabs(GenPart_pdgId[i]) != 11 )  continue ;

       // if ( !(GenPart_statusFlags[i] >> 11 & 1 ) ) continue ;

       gen_IdxMother =  GenPart_genPartIdxMother[i];

       gen_IdxGrandMother =  GenPart_genPartIdxMother[gen_IdxMother];

       // if ( fabs(GenPart_pdgId[gen_IdxMother]) != 24 )  continue ;

       // if ( fabs(GenPart_pdgId[gen_IdxGrandMother]) != 6 ) continue ;


       gen_Tele_idx           = i;

       continue ;

       cout << "\n\n Generator Level info for leptons" ;

       cout << "\n Lepton ID = " << GenPart_pdgId[gen_Tmuon_idx] ;

       cout << "\n Mother index = " << GenPart_genPartIdxMother[i] ;



       cout << "\n Mother ID    = " << GenPart_pdgId[gen_IdxMother] ;

       cout << "\n Grand Mother index = " << GenPart_genPartIdxMother[gen_IdxMother] ;



       cout << "\n Grand Mother ID = " << GenPart_pdgId[gen_IdxGrandMother] ;

       cout << "\n Status = "    << GenPart_status[i] ;

       if (GenPart_statusFlags[i] >> 0  & 1 ) cout << "\n Status Flags is Prompt " ;       
       if (GenPart_statusFlags[i] >> 7  & 1 ) cout << "\n Status Flags is HardProcess " ;       
       if (GenPart_statusFlags[i] >> 8  & 1 ) cout << "\n Status Flags is from HardProcess " ;       
       if (GenPart_statusFlags[i] >> 11 & 1 ) cout << "\n Status Flags is from HardProcessBeforeFSR " ;       
        }

    } // END of Loop !!!!

}  // END of Functions !!!!



bool   Electron_Gen_Match(int c_ele) {

   bool match = true ;

   float eta1       = Electron_eta[c_ele];
   float phi1       = Electron_phi[c_ele];
   float pT1        = Electron_pt[c_ele];

   float eta2       = GenPart_eta[gen_Tele_idx];
   float phi2       = GenPart_phi[gen_Tele_idx];
   float pT2        = GenPart_pt[gen_Tele_idx];

   float dpT        = (fabs( pT1 - pT2) / pT2 );
   float dR_min        = dR_Calculator(eta1, phi1, eta2, phi2) ;

   if ( Electron_charge[c_ele] != (GenPart_pdgId[gen_Tele_idx] / -11 )) match = false ;

   if( dR_min > 0.1 ) match = false ;
   if( dpT > 0.3 ) match = false ; 

   // cout << " We have mucharge = " << Electron_charge[c_ele] << "  and gen muCharge = " << (GenPart_pdgId[gen_Tele_idx] / -11)
   //  << " and rel. pT = " << dpT << " and deltaR = " << dR <<endl ;

   // if(match == true) {
   // cout << " We have mucharge = " << Electron_charge[c_ele] << "  and gen muCharge = " << (GenPart_pdgId[gen_Tele_idx] / -11 )
   //  << " and rel. pT = " << dpT << " and deltaR = " << dR <<endl ;
   // }

   return match ;
} // END of Functions !!!!


void Loop_Over_Electron(TString Filling){

      //======================muon selection==========================
      //Here for signal & ttbar sample, gen matched muon are selected and plotted.. REMEMBER!!!!
      //For QCD , gen unmatched muon are selected to study mistag efficiency

      int   ele_count = -1 ;
      int   Muon_ID  = -1;
      int   matched  = -1 ;
      float eleEta   =  - 99.0 ;
       


      for( int f = 0; f <  nElectron ; f++)
        {

          eleEta = fabs (Electron_eta[f]) ;
          
          // cout << "\n before Eta = " << eleEta;

          if ( eleEta > 1.44 && (eleEta < 1.56 || eleEta > 2.5) )    continue ;   

          matched = Electron_Gen_Match(f)  ;


          if ( (matched == 1) && Type_of_Muon.Contains("PromptLepton") ) ele_count = 1;
          if ( (matched == 0) && Type_of_Muon.Contains("FakeLepton") )   ele_count = 0;

          if ( ele_count == -1 )                 continue ;
          
          if (Electron_pt[f] < 10.0 )             continue ;  

          // if (Electron_cutBased[i] < 2.0 )          continue ; // for loose, but move to medium

          // cout <<" \n ele_count = " << ele_count ;

          n_ele.push_back(f) ;

          // if ( mu_count >= 2) continue;

          Fill_Lepton_Hist_Preselction_LvL( Filling  , f , 0) ; 

          ele_count      = -1; 
        }

      h_object_no.at(1) ->Fill(n_ele.size() , factor );       //  index 2   for nMuon  Filling Population Plot
 
}   // END of Functions !!!!



///------------------------------

// For Imaginary solutions, Etmiss recalculated keeping Delta = 0
float ReCalculation_ETmiss_for_Imaginary( float Pt_lepton, float Phi_lepton)
{

       float  Wmass          =    80.385 ;

       float  dphi           =  delta_phi(Phi_lepton , MET_phi) ; 

       float  Denominator    =  2.0 * Pt_lepton * ( 1.0 - TMath::Cos(dphi)) ;

       float  Numerator      =  Power( Wmass, 2) ;

       float  New_Et_miss    =  Numerator / Denominator ;     

       return New_Et_miss ;

}


void   W_mass_constraint(int Lepton, TString LeptonType)                                                                                             
{

 
   float  Lepton_Pt      = 0.0 ;
   float  Lepton_Mass    = 0.0 ;
   float  Lepton_En      = 0.0 ;
   float  Lepton_Eta     = 0.0 ;
   float  Lepton_Phi     = 0.0 ;
   float  Calculated_En  = 0.0 ;

   // ------Electron Channel
   if (LeptonType.Contains("Electron"))
   {
          Lepton_Pt      = Electron_pt[Lepton] ;
          Lepton_Mass    = Electron_mass[Lepton] ;
          Lepton_Eta     = Electron_eta[Lepton] ;
          Lepton_Phi     = Electron_phi[Lepton] ;

          Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
          Lepton_En      = Lepton_vector.E();

          // cout << "\n  EleEnergy = "  << Lepton_En;

   }

   // ------Muon Channel
   if (LeptonType.Contains("Muon"))
   {
          Lepton_Pt      = Muon_pt[Lepton] ;
          Lepton_Mass    = Muon_mass[Lepton] ;
          Lepton_Eta     = Muon_eta[Lepton] ;
          Lepton_Phi     = Muon_phi[Lepton] ;

          Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
          Lepton_En      = Lepton_vector.E();

          // cout << "\n  Diff = "  << Lepton_En;
   }

   float  P_zlep           =  Lepton_Pt * SinH(Lepton_Eta) ;
   
   float  dphi           =  delta_phi(Lepton_Phi , MET_phi) ; 
   float  Pt_MET_product =  Lepton_Pt * MET_pt * Cos(dphi)  ;
   
   float  Wmass          =    80.385 ;
   float  MassT          =    Sqrt ( 2 * ( ( Lepton_Pt * MET_pt )  - Pt_MET_product ) ) ;       
   float  PtEtprod_2     =    Power( ( Lepton_Pt * MET_pt ), 2 ) ;

   float  LepPt_2        =    Power( Lepton_Pt , 2 ) ;
   float  LepEn_2        =    Power( Lepton_En , 2 ) ;
   float  MET_2          =    Power( MET_pt , 2 ) ;
   
   float  Apart          =    ((Power ( Wmass , 2) / 2 )  + Pt_MET_product ) ;
   float  Apart_2        =    Power( Apart, 2 ) ;

   
   double Delta          =    LepEn_2 * ( Apart_2  -  PtEtprod_2 ) ;
   


   if ( Delta < 0 ) {

      // Apart                     =   ( ( Power( MassT,2) / 2 ) + Pt_MET_product ) ;
      Apart                     =   (  Lepton_Pt * MET_pt ) ;
      Apart_2                   =   Power( Apart, 2) ;

      cout <<" \n For v1 before Delta = " << Delta  ;

   
      Delta                     =   LepEn_2 * ( Apart_2  - PtEtprod_2 )  ;
      cout <<"  &&&&  after Delta = " << Delta << endl ;   
   }

   P_zv_1 = fabs( ((Apart * P_zlep) + fabs(Sqrt(Delta))) / LepPt_2 );
   P_zv_2 = fabs( ((Apart * P_zlep) - fabs(Sqrt(Delta))) / LepPt_2 );
 
   P_zv    = ( P_zv_1 >  P_zv_2) ?  P_zv_2 :  P_zv_1 ;   
 
   double nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_1 * P_zv_1))) ;
   double massW =   Sqrt(2* ( ( Lepton_En * nu_En ) - Pt_MET_product  -  (P_zlep * P_zv_1) ) );
   // cout << " \n Wmass for Pz1 = " << massW ;

   nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_2 * P_zv_2))) ;
   massW =   Sqrt(2* ( ( Lepton_En * nu_En ) - Pt_MET_product  -  (P_zlep * P_zv_2) ) );
   // cout << " \n Wmass for Pz2 = " << massW ;   

   nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv * P_zv))) ;
   massW =   Sqrt(2* ( ( Lepton_En * nu_En ) - Pt_MET_product  -  (P_zlep * P_zv) ) );
   // cout << " \n Wmass for Pz = " << massW ; 
   // h_topmass[1]->Fill(massW);
   // return P_zv ;

} // END OF FUNCTION !!!!!


void   W_mass_constraint_V2(int Lepton, TString LeptonType)                                                                                             
{

 
   float  Lepton_Pt      = 0.0 ;
   float  Lepton_Mass    = 0.0 ;
   float  Lepton_En      = 0.0 ;
   float  Lepton_Eta     = 0.0 ;
   float  Lepton_Phi     = 0.0 ;
   float  Calculated_En  = 0.0 ;

   float  Etmiss_New     = 0.0 ;

   float  temp_pzv1 = 0.0, temp_pzv2 = 0.0 ;

   TLorentzVector Wbos1, Wbos2, new_XYZM , Img_XYZM;

   // ------Electron Channel
   if (LeptonType.Contains("Electron"))
   {
          Lepton_Pt      = Electron_pt[Lepton] ;
          Lepton_Mass    = Electron_mass[Lepton] ;
          Lepton_Eta     = Electron_eta[Lepton] ;
          Lepton_Phi     = Electron_phi[Lepton] ;

          Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
          Lepton_En      = Lepton_vector.E();

          // cout << "\n  Lepton_Pt = "  << Electron_pt[Lepton]  << "   for Electron = "  << Lepton; 

   }

   // ------Muon Channel
   if (LeptonType.Contains("Muon"))
   {
          Lepton_Pt      = Muon_pt[Lepton] ;
          Lepton_Mass    = Muon_mass[Lepton] ;
          Lepton_Eta     = Muon_eta[Lepton] ;
          Lepton_Phi     = Muon_phi[Lepton] ;

          Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
          Lepton_En      = Lepton_vector.E();

          // cout << "\n  Lepton_Pt = "  << Muon_pt[Lepton]  << "   for Muon = "  << Lepton; 
   }

   float  P_zlep           =  Lepton_Pt * SinH(Lepton_Eta) ;
   
   float  dphi           =  delta_phi(Lepton_Phi , MET_phi) ; 
   float  Pt_MET_product =  Lepton_Pt * MET_pt * TMath::Cos(dphi)  ;
   
   float  Wmass          =    80.385 ;
   float  MassT          =    Sqrt ( 2 * ( ( Lepton_Pt * MET_pt )  - Pt_MET_product ) ) ;       
   float  PtEtprod_2     =    Power( ( Lepton_Pt * MET_pt ), 2 ) ;

   float  LepPt_2        =    Power( Lepton_Pt , 2 ) ;
   float  LepEn_2        =    Power( Lepton_En , 2 ) ;
   float  MET_2          =    Power( MET_pt , 2 ) ;
   
   float  Apart          =    ((Power ( Wmass , 2) / 2.0 )  + Pt_MET_product ) ;
   float  Apart_2        =    Power( Apart, 2 ) ;

   
   float  Delta          =    LepEn_2 * ( Apart_2  -  PtEtprod_2 ) ;
   
   float  nu_En          =    0.0 ;

   // if ( Delta > 0.0) return ;

   if ( Delta > 0.0 ) {

         temp_pzv1 = fabs( ((Apart * P_zlep) + fabs(Sqrt(Delta))) / LepPt_2 );
         temp_pzv2 = fabs( ((Apart * P_zlep) - fabs(Sqrt(Delta))) / LepPt_2 );
       
         // P_zv    = ( P_zv_1 >  P_zv_2) ?  P_zv_2 :  P_zv_1 ;   

         if ( temp_pzv1 < temp_pzv2 ) {

                P_zv_1 = temp_pzv1 ;
                P_zv_2 = temp_pzv2 ;
         } 

         else {

                P_zv_1 = temp_pzv2 ;
                P_zv_2 = temp_pzv1 ;

         }
      

         neutrino1.SetXYZM( MET_pt * TMath::Cos(MET_phi), MET_pt * TMath::Sin(MET_phi), P_zv_1 , 0.00000000) ;
         neutrino2.SetXYZM( MET_pt * TMath::Cos(MET_phi), MET_pt * TMath::Sin(MET_phi), P_zv_2 , 0.00000000) ;
         //-------- UNCOMMENT THIS PART IF YOU WANT TO PLOT wMASS WITHIN THIS LOOP------------ 

         // nu_En   = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_1 * P_zv_1))) ; 
         // neutrino1.SetPxPyPzE( MET_pt*TMath::Cos(MET_phi), MET_pt*TMath::Sin(MET_phi), P_zv_1 ,nu_En);   

         // new_XYZM.SetXYZM( MET_pt * TMath::Cos(MET_phi), MET_pt * TMath::Sin(MET_phi), P_zv_1 , 0.00000000) ;

         // Wbos1 = ( Lepton_vector + neutrino1);
         // Wbos1 = ( Lepton_vector + new_XYZM);

         // h_Wbos1_Mass -> Fill( Wbos1.M(), factor) ;
         // h_Wbos1_Mass -> Fill( Wbos1.M()) ;
       


         // nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_2 * P_zv_2))) ;    
         // neutrino2.SetPxPyPzE( MET_pt*TMath::Cos(MET_phi), MET_pt*TMath::Sin(MET_phi), P_zv_2 ,nu_En);
   
         // Wbos2 = ( Lepton_vector + neutrino2);

         // h_Wbos2_Mass -> Fill( Wbos2.M()) ;

   }



   if ( Delta < 0.0 ) {

      //For   IMAGINARY SOLUTIONS, DELTA IS SET TO "ZER0"

      // Apart                     =   ( ( Power( MassT,2) / 2 ) + Pt_MET_product ) ;

      Etmiss_New             =   ReCalculation_ETmiss_for_Imaginary( Lepton_Pt, Lepton_Phi) ;

      Apart                  =   ((Power ( Wmass , 2) / 2.0 )  + ( Lepton_Pt * Etmiss_New * TMath::Cos(dphi) ) ) ; 
      Apart_2                =   Power( Apart, 2) ;

      // Delta                  =    0.0  ;

      temp_pzv1              =   ( (Apart * P_zlep) / LepPt_2 );

      P_zv_1                 =   temp_pzv1 ;
 
      // nu_En                  = fabs(Sqrt((Etmiss_New * Etmiss_New) + (temp_pzv1 * temp_pzv1))) ; 

      Img_XYZM.SetXYZM(Etmiss_New * TMath::Cos(MET_phi), Etmiss_New*TMath::Sin(MET_phi), temp_pzv1 , 0.00000000) ;
      
      neutrino1.SetXYZM(Etmiss_New * TMath::Cos(MET_phi), Etmiss_New*TMath::Sin(MET_phi), temp_pzv1 , 0.00000000) ;

      Wbos1 = ( Lepton_vector + Img_XYZM);
      
      h_Wbos_Mass_Img -> Fill( Wbos1.M(), factor) ;   
      // h_Wbos_Mass_Img -> Fill( Wbos1.M()) ;  

      // cout << "ZER0" ;

  
   }  // End of Loop !!!!



   

} // END OF FUNCTION !!!!!





void  Top_Candidate_Check( int Lepton, TString LeptonType)
{

      float Higgs_dR = 0.0;
      float top_prod_dR = 0.0 ;

      int   Higgs_index    = Higgsjets[0] ;

      float top_mass   = 0.0 ;


      float  Lepton_Pt      = 0.0 ;
      float  Lepton_Mass    = 0.0 ;
      float  Lepton_En      = 0.0 ;
      float  Lepton_Eta     = 0.0 ;
      float  Lepton_Phi     = 0.0 ;

      TLorentzVector temp_vector ;

      temp_vector.SetXYZM( -99.0, -99.0, -99.0, -99.0 ) ;

      neutrino1 = temp_vector ;

      top_bjet_candidate = temp_vector ;

      // W_mass_constraint( Lepton, LeptonType)  ;
      W_mass_constraint_V2( Lepton, LeptonType)  ;


      if( (neutrino1 == temp_vector) ) return;
      // ------Electron Channel
      if (LeptonType.Contains("Electron"))
      {
             Lepton_Pt      = Electron_pt[Lepton] ;
             Lepton_Mass    = Electron_mass[Lepton] ;
             Lepton_Eta     = Electron_eta[Lepton] ;
             Lepton_Phi     = Electron_phi[Lepton] ;

             Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
             Lepton_En      = Lepton_vector.Energy();

             // cout << "\n  EleEnergy = "  << Lepton_En;

      }

      // ------Muon Channel
      if (LeptonType.Contains("Muon"))
      {
             Lepton_Pt      = Muon_pt[Lepton] ;
             Lepton_Mass    = Muon_mass[Lepton] ;
             Lepton_Eta     = Muon_eta[Lepton] ;
             Lepton_Phi     = Muon_phi[Lepton] ;

             Lepton_vector.SetPtEtaPhiM( Lepton_Pt, Lepton_Eta, Lepton_Phi, Lepton_Mass);
             Lepton_En      = Lepton_vector.Energy();

             // cout << "\n  MuEnergy = "  << Lepton_En;
      }



      double T_mass = 0.0;

      // double nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_1 * P_zv_1))) ; 

      // neutrino1.SetPxPyPzE( MET_pt*TMath::Cos(MET_phi), MET_pt*TMath::Sin(MET_phi), P_zv_1 ,nu_En);



      // nu_En = fabs(Sqrt((MET_pt * MET_pt) + (P_zv_2 * P_zv_2))) ;    
      // neutrino2.SetPxPyPzE( MET_pt*TMath::Cos(MET_phi), MET_pt*TMath::Sin(MET_phi), P_zv_2 ,nu_En);


      // Check top bjet candidate

      // cout <<" \n\n ----------- Check top bjet candidate -----------" ;
      int bjet_index  = -1 ;

      int Bsize  = ( b_jet.size() >= 3 ) ?  3 : b_jet.size() ;



      for (int i = 0 ; i < Bsize ; ++i)
      {

          if( (top_bjet_candidate != temp_vector) ) continue;
    
          bjet_index  = b_jet[i] ;

          Higgs_dR     = dR_Calculator(FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index],Jet_eta_clean[bjet_index], Jet_phi_clean[bjet_index]) ;

          if ( Higgs_dR < 1.2) continue ;
              
          top_bjet_candidate.SetPtEtaPhiM( Jet_pt_clean[bjet_index],Jet_eta_clean[bjet_index], Jet_phi_clean[bjet_index], Jet_mass_clean[bjet_index]) ;

          for (int ji = 0; ji < 2; ++ji)  // 2 is for 2 neutrino candidate
          {
              // Top_candidate = ( Top_candidate + top_bjet_candidate) ;
              if ( ji == 0) Top_candidate_1 = ( neutrino1 + Lepton_vector  + top_bjet_candidate ) ;
// 
              if ( ji == 1) Top_candidate_2 = ( neutrino2 + Lepton_vector  + top_bjet_candidate ) ; 
          }

      }    

      Cut_Higgs_Tagging_Flow -> Fill(3.5, factor) ;

      top_mass   = Top_candidate_1.M();
      h_Top1_Mass -> Fill( top_mass , factor) ;
      if ( top_mass > 100.0 && top_mass < 250.0 )  Cut_Higgs_Tagging_Flow -> Fill(4.5, factor) ;


      top_mass   = Top_candidate_2.M();
      h_Top2_Mass -> Fill( top_mass , factor) ;
      if ( top_mass > 100.0 && top_mass < 250.0 )  Cut_Higgs_Tagging_Flow -> Fill(5.5, factor) ;      

}  // END OF FUNCTION !!!



void Tprime_Candidate_Reconstruction( )
{
  int Higgs_index = Higgsjets[0];

  float deltaR = 0.0 ;

  TLorentzVector Tprime_1, Tprime_2, Higgs, Wbos1, Wbos2;

  Wbos1 = ( Lepton_vector + neutrino1);
  h_Wbos1_Mass -> Fill( Wbos1.M(), factor) ;

  Wbos2 = ( Lepton_vector + neutrino2);
  h_Wbos2_Mass -> Fill( Wbos2.M(), factor) ;

  Higgs.SetPtEtaPhiM( FatJet_pt_clean[Higgs_index],FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index], FatJet_mass_clean[Higgs_index]) ;

  h_Higgs_Mass -> Fill( FatJet_mass_clean[Higgs_index], factor);

  deltaR = dR_Calculator(FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index],top_bjet_candidate.Eta(), top_bjet_candidate.Phi()) ;
  h_dR_Higgs_wrt_Topb -> Fill(deltaR , factor) ;

  deltaR = dR_Calculator(FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index],Top_candidate_1.Eta(), Top_candidate_1.Phi()) ;
  h_dR_Higgs_wrt_Top1 -> Fill(deltaR , factor) ;

  deltaR = dR_Calculator(FatJet_eta_clean[Higgs_index], FatJet_phi_clean[Higgs_index],Top_candidate_2.Eta(), Top_candidate_2.Phi()) ;
  h_dR_Higgs_wrt_Top2 -> Fill(deltaR , factor) ;


  Tprime_1 = ( Higgs + Top_candidate_1) ;
  h_Tprime1_Mass ->Fill( Tprime_1.M(), factor) ;
  // h_Top1_Mass -> Fill( Top_candidate_1.M() , factor) ;


  Tprime_2 = ( Higgs + Top_candidate_2) ;  
  h_Tprime2_Mass ->Fill( Tprime_2.M(), factor) ;
  // h_Top2_Mass -> Fill( Top_candidate_2.M() , factor) ;

}






// ==================================================================================================================================
// ==================================================================================================================================
// --------------------------- Scale factors Calculation for Various Objects --------------------------------------------------------

   //---------------------------------------BTagging Scalefactors------------------------------

   // BTagCalibrationReader reader_up(BTagEntry::OP_LOOSE, "up");  // sys up

   BTagEntry::OperatingPoint DeepCSV_OP = BTagEntry::OP_LOOSE; // required for SF calculation

   BTagEntry::JetFlavor jet_Flavor  =  BTagEntry::FLAV_B ; // required for SF calculation

   std::string systype =  "central";

   double DeepCSV2_bTag_SF_Calculator(BTagEntry::OperatingPoint OP, BTagEntry::JetFlavor JF, std::string sys_type, double JetPt, double JetEta){
   // double DeepCSV2_bTag_SF_Calculator(BTagEntry btag )

             // BTagCalibration calib("csvv2","DeepCSV_106XUL17SF_WPonly_V2p1.csv");
             BTagCalibration calib("deepcsv","DeepCSV_106XUL17SF_WPonly_V2p1.csv");

             float MaxJetPt;
             double jet_scalefactor ;             

             std::string mes_type;
             MaxJetPt = 1000.0;

             if(JF == BTagEntry::FLAV_B || JF == BTagEntry::FLAV_C) mes_type = "comb";
             if(JF == BTagEntry::FLAV_UDSG) mes_type = "incl";
            
             if(sys_type == "central"){

               BTagCalibrationReader reader( OP,                // operating point (LOOSE, MEDIUM, TIGHT OR RESHAPING)
                                             sys_type.c_str()
                                              );  // systematics type (central, up, down..)      

               reader.load( calib,               // calibration instance    
                            JF,                  // btag flavour  
                            mes_type.c_str());   // measurement type            


               if(JetPt > MaxJetPt) JetPt = MaxJetPt;
               jet_scalefactor = reader.eval(JF, JetEta, JetPt, 0.1355);
               return jet_scalefactor;
             }



             if(sys_type == "up" || sys_type == "down"){

                 Bool_t DoubleUncertainty = false;

                 BTagCalibrationReader reader(OP, "central");
                 BTagCalibrationReader reader_sys(OP, sys_type.c_str()); //for up or down

                 reader.load(calib, JF, mes_type.c_str());
                 reader_sys.load(calib, JF, mes_type.c_str());

                 if(JetPt > MaxJetPt){
                   JetPt = MaxJetPt;
                   DoubleUncertainty = true;
                 }

                 jet_scalefactor = reader.eval(JF, JetEta, JetPt, 0.1355);
                 double jet_scalefactor_sys =  reader_sys.eval(JF, JetEta, JetPt, 0.1355);

                 if (DoubleUncertainty) {
                   jet_scalefactor_sys = 2*(jet_scalefactor_sys - jet_scalefactor) + jet_scalefactor; //It will work properly for both up and down.
                                                                                                      //As jet_SF_sys > jet_SF for Up and < jet_SF for down.
                 }

                 return jet_scalefactor_sys;
            }


}



TH2D* h2_btagefficiency_b;
TH2D* h2_btagefficiency_c; 
TH2D* h2_btagefficiency_udsg;

TFile  *bTagEff_file ;   

double btag_weight    = 1.0 ;



void Efficiency_Read_From_bTagEff_Root_Files(TString sample) {

            TString temp_sample = "NONE";
            TString Dataset     = "NONE";


            for (int i = 0; i < 40; ++i)
            {
                  temp_sample = New_Sample_List[i];
                  if (!( sample.Contains(temp_sample))) continue ;
                  Dataset     = temp_sample ; 
            }

            TString InputFilePath = "../BTagEff_Analyzer_For_UltraLegacy/Output_RootFiles_For_BtagEff/" + Dataset + "_ak4_deepCSV_bTaggingEfficiencyMap.root"    ;

            bTagEff_file          = TFile::Open( InputFilePath,"READ");


            h2_btagefficiency_b      = (TH2D*) bTagEff_file->Get("efficiency_b") ;
            h2_btagefficiency_c      = (TH2D*) bTagEff_file->Get("efficiency_c") ;
            h2_btagefficiency_udsg   = (TH2D*) bTagEff_file->Get("efficiency_udsg") ;


}  


void Event_Reweighting_Using_SF_N_MC_btageff(){

    // Method 1a) 
    // Event reweighting using scale factors and MC b-tagging efficiencies
    // as defined in link : https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#b_tagging_efficiency_in_MC_sampl


    // First set run for btagged jets 

    double  SF  = -99.0 ;
    double  eta = -99.0 ;
    double  pt  = -99.0 ;

    int jet  = -1 ;
    int bin = -99 ;
    double eff_factor = -99.0 ;

    double pT_bjet    = -99.0 ;

    double prob_data      = 1.0 ; 
    double prob_mc        = 1.0 ; 

    double not_tagged_prob_mc   = 1.0 ;

    double not_tagged_prob_data = 1.0 ;

    // Reweights for btagged jets
    for (int i = 0; i < b_jet.size(); ++i)
    {
        jet = b_jet[i] ;

        eta         =  fabs( Jet_eta_clean[jet]) ;  

        pT_bjet     =  Jet_pt_clean[jet] ;



        if ( abs(Jet_partonFlavour[jet]) == 5 ) {  // for b quarks

        jet_Flavor  =  BTagEntry::FLAV_B ;        

        SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 


        pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

        bin        =  h2_btagefficiency_b->FindBin( pt , eta ) ;
        eff_factor =  h2_btagefficiency_b->GetBinContent( bin ); 

        prob_mc    = prob_mc * eff_factor ;

        prob_data  = prob_data * eff_factor * SF ;
  

        }


        else {

              if ( abs(Jet_partonFlavour[jet]) == 4 ) {  // for C quarks

                  jet_Flavor  =  BTagEntry::FLAV_C ;          

                  SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 

                  pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

                  bin        =  h2_btagefficiency_c->FindBin( pt , eta ) ;
                  eff_factor =  h2_btagefficiency_c->GetBinContent( bin ); 
  
                  prob_mc    = prob_mc * eff_factor ;

                  prob_data  = prob_data * eff_factor * SF ;
              }

              else {   // for UDSG quarks

                  jet_Flavor  =  BTagEntry::FLAV_UDSG ;          

                  SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 

                  pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

                  bin        =  h2_btagefficiency_c->FindBin( pt , eta ) ;
                  eff_factor =  h2_btagefficiency_c->GetBinContent( bin ); 
  
                  prob_mc    = prob_mc * eff_factor ;

                  prob_data  = prob_data * eff_factor * SF ;

              }

        }

    }


    // Reweights for not btagged jets
    for (int i = 0; i < not_tagged_bjets.size(); ++i)
    {
        jet = not_tagged_bjets[i] ;

        eta         =  fabs( Jet_eta_clean[jet]) ;  

     

        if ( abs(Jet_partonFlavour[jet]) == 5 ) {  // for b quarks

              jet_Flavor  =  BTagEntry::FLAV_B ;        
  
              SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 

              pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

              bin        =  h2_btagefficiency_b->FindBin( pt , eta ) ;
              eff_factor =  h2_btagefficiency_b->GetBinContent( bin ); 

              not_tagged_prob_mc   = not_tagged_prob_mc * ( 1.0 - eff_factor ) ;

              not_tagged_prob_data = not_tagged_prob_data * ( 1.0  - SF * eff_factor ) ;
  

        }


        // Reducible parts.... not need of 
        // else {

        //       if ( abs(Jet_partonFlavour[jet]) == 4 ) {  // for C quarks

        //           jet_Flavor  =  BTagEntry::FLAV_C ;        

        //           SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 

        //           pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

        //           bin        =  h2_btagefficiency_c->FindBin( pt , eta ) ;
        //           eff_factor =  h2_btagefficiency_c->GetBinContent( bin ); 
  
        //           cout << "\n Efficiency = " << eff_factor <<endl ;

        //       }

        //       else {   // for UDSG quarks

        //           jet_Flavor  =  BTagEntry::FLAV_UDSG ;          

        //           SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , pT_bjet, eta); 

        //           pt         = ( pT_bjet >= 1000.0 ) ? 999.999 : pT_bjet ;  // for pT > 1000.0, scale factors are used as for pT = 1000.0 

        //           bin        =  h2_btagefficiency_c->FindBin( pt , eta ) ;
        //           eff_factor =  h2_btagefficiency_c->GetBinContent( bin ); 
  
        //           cout << "\n Efficiency = " << eff_factor <<endl ;


        //       }


        // }

    }
    // jet_Flavor  =  BTagEntry::FLAV_C ; 

    // jet_Flavor  =  BTagEntry::FLAV_UDSG ; 

    cout     << "\n nottaggedprob_mc   = " << not_tagged_prob_mc 
             << "\n nottaggedprob_data = " << not_tagged_prob_data
             << endl ;   

    cout     << "\n prob_mc   = " << prob_mc 
             << "\n prob_data = " << prob_data
             << endl ;             

    btag_weight  = ( prob_data * not_tagged_prob_data ) / ( prob_mc * not_tagged_prob_mc ) ;

    cout << " \n Final weight = " << btag_weight << endl ;



}  


//===================================================================================================================
//===================================================================================================================
//////----------------------OBJECT EFFICIENCY STUDIES ---------------------------------------------------------------
//====================================================================================================================
//===================================================================================================================

void Fill_BTaggingEff_2DHistogram( TString WorkingPoint)  {


      int jet_count = -1 ;      
      int jets      = -1 ; 

      float jet_eta = 0.0 ;
      float btag_discriminator = 0.0 ;

      if ( WorkingPoint.Contains("loose") ) btag_discriminator = 0.1355 ;
 
      for (int i = 0; i < n_jet.size(); ++i)
      {
          jets = n_jet[i]  ;

          jet_eta = fabs(Jet_eta_clean[jets] ) ;

          if ( abs(Jet_partonFlavour[jets]) == 5 )  // for b quark flavor
                {
                   Hist_2D_BtagEff_Denom[0] -> Fill( Jet_pt_clean[jets], jet_eta) ;

                   if ( Jet_btagDeepB[jets] > btag_discriminator )   Hist_2D_BtagEff_Num[0] -> Fill( Jet_pt_clean[jets], jet_eta) ;              
                }      


          else{

                if ( abs(Jet_partonFlavour[jets]) == 4 )  // for c quark flavor
                   {
                      Hist_2D_BtagEff_Denom[1] -> Fill( Jet_pt_clean[jets], jet_eta) ;

                      if ( Jet_btagDeepB[jets] > btag_discriminator )   Hist_2D_BtagEff_Num[1] -> Fill( Jet_pt_clean[jets], jet_eta) ;              
                   }      


               else  // for uds quark & g  flavor
                   {
                      // cout << "\n parton flavor = " << Jet_partonFlavour[jets] ;
                      Hist_2D_BtagEff_Denom[2] -> Fill( Jet_pt_clean[jets], jet_eta) ;

                      if ( Jet_btagDeepB[jets] > btag_discriminator )   Hist_2D_BtagEff_Num[2] -> Fill( Jet_pt_clean[jets], jet_eta) ;              
                   }  

          }          


      }


}    ////END OF FUNCTION !!!!!!!!!