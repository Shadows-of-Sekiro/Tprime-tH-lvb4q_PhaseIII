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
    float dEta = -1.0 , dPhi = -1.0 , dR = 0.0  ;
    
    double factor = 1.0 , lumi_factor ;  

    float  Parent_Mass = 0.0 ;
    
    std::string Sample_Name ;
  
    vector <int> CatI_Objects;            // for Higgs, b, l & MET 
  
    int T_top  = -1 ;
    int Top_W  = -1 ;
    int top_Mu = -1 ;
    int nearest_jet = -1 ;

  
  
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
      vector <int> b_jetloose;
      vector <int> b_jet;
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
      vector <int> AK8_copy  ;
      vector <int> AK8_sort  ;
   
      
      vector <int> gen_Wboson    ;
      vector <int> Higgsjets ;
      
      vector <int> gen_udscquark ;
      vector <int> W_boson;
    
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
      int muon_T           = -1 ;            
      int muon_M           = -1 ;                  

      TString jet_type ;
    
    
    // for puppiSD Mass  correction from puppiCorr.root file
       TFile  *fi ;   
       TF1* puppisd_corrGEN   ;    
       TF1* puppisd_corrRECO_cen ;    
       TF1* puppisd_corrRECO_for ; 
    
    // for muon ID scale factors from efficiency root files
       TFile  *Muon_Scale_file ;   
       TH2F*  muon_histo_scale_BCDEF ;
       TH2F*  muon_histo_scale_GH ;
       double muon_ID_factor = 1.0;
    
    //list of histograms
    
      TH1D* Cut_Efficiency_Flow ;

      TH1D* Cut_LepIso_dPt_Flow ;
      TH1D* Cut_MET_Cut_Flow ;
      TH1D* Cut_ST_Cut_Flow ;
      TH1D* Cut_Tau42_Flow ;
      TH1D*  Cut_Higgs_Tagging_Flow ;
      TH1D* Cut_pTHiggs_Flow ;
      TH1D* Cut_SDMass_Flow ;
    
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
      
      TH2F* dPt_dR_mubjet  ; 
      TH2F* dPt_dR_muqjet  ; 
      // dPt_dR_mubjet->GetYaxis()->SetTitle("dPT(mu,jet)");
      // dPt_dR_mubjet         ->GetXaxis()->SetTitle("dR(mu,jet)");
      TH2F* dRHbjet_dRlbjet ;
  
      std::array< TH2F*, 4>  h_AK81vsGenObj ;
      std::array< TH2F*, 4>  h_AK82vsGenObj ;
      std::array< TH2F*, 4>  h_AK83vsGenObj ;
  
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

      TH1D* h_Parent_Mass ;
      

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////



      void  Clear_Vector() {
         //   for clearing objects vector
         n_AK8Jet.clear(); 
         n_ele.clear(); 
         n_Mu.clear();
         n_jet.clear();    // main code
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

         AK8_copy.clear()  ;
         AK8_sort.clear()  ;

         puppin_jet.clear();    // main code
         puppin_forwjet.clear(); // main code
         puppib_jetloose.clear();// main code
         puppib_jet.clear();    // main code
         puppib_jetmedium.clear();    // main code
         puppib_jettight.clear();    // main code

         Higgsjets.clear() ;
         W_boson.clear();
         CatI_Objects.clear() ;    

         gen_Wboson.clear();
         gen_udscquark.clear();      
           
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
      
      std::map<TString, int > LepIso_IDbit = {  
                                        {"TkIsoLoose"           , 11 } ,
                                        {"TkIsoTight"           , 12 } ,
                                        {"MiniIsoLoose"         , 18 } ,
                                        {"MiniIsoMedium"        , 19 } ,
                                        {"MiniIsoTight"         , 20 } ,
                                        {"MiniIsoVeryTight"     , 21 } , 
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

    //==============Luminosity Normalization for each samples========================================================
    
    
      std::map<std::string,double> Sample_X_Section = {  // Xsections are in units fb-1 just remember
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  3.136e+01   },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  1.091e+01   },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  5.970e+00   },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  7.306e+05   },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   1.056e+08   },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  2.562e+07   },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  8.690e+06   },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  8.075e+05   },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  7.925e+04   },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  2.525e+04   },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 4.723e+03   },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 1.613e+03   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   1.352e+06   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  1.345e+06   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  3.581e+05   } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  4.872e+04   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  1.208e+04   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 5.457e+03   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                1.337e+03   } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 3.217e+01   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             1.704e+05   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            1.474e+05   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            4.107e+04   } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            5.671e+03   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            1.352e+03   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           6.253e+02   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          1.511e+02   } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           3.668e+00   } ,                                                                
                                                               { "list_of_Bkgfiles/ST_s-channel_4f_leptonDecays_v3_",               3.365e+03   },
                                                               { "list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays_v3_",    7.441e+04   },
                                                               { "list_of_Bkgfiles/ST_t-channel_top_4f_inclusiveDecays_v3_",        1.233e+05   },
                                                               { "list_of_Bkgfiles/ST_tW_antitop_5f_inclusiveDecays_v3_",           3.809e+04   },
                                                               { "list_of_Bkgfiles/ST_tW_top_5f_inclusiveDecays_v3_",               3.806e+04   }
                                                                 } ;
    
    
      std::map<std::string,double> Sample_Total_Events = {  // total events from Ntuplized samples just remember
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  100000.0  },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  100000.0  },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  100000.0  },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  76915549.0 },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   13895437.0 },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  7897731.0 },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  7947159.0 },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  7937590.0 },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  3972819.0 },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  4010136.0 },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 3962749.0 },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 3990117.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   10020533.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  9945478.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  4963240.0 } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  1963464.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  3779141.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 1544513.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                244532.0  } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 253561.0  } , 
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             9691660.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            2751187.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            962195.0  } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            1070454.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            8292957.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           2673066.0 } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          596079.0  } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           399492.0  } ,
                                                               { "list_of_Bkgfiles/ST_s-channel_4f_leptonDecays_v3_",               1000000.0 },
                                                               { "list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays_v3_",    38811017.0  },
                                                               { "list_of_Bkgfiles/ST_t-channel_top_4f_inclusiveDecays_v3_",        67105876.0  },
                                                               { "list_of_Bkgfiles/ST_tW_antitop_5f_inclusiveDecays_v3_",           992024.0  },
                                                               { "list_of_Bkgfiles/ST_tW_top_5f_inclusiveDecays_v3_",               998276.0  }                                                                                                                                
                                                                 } ;       
    
      double Luminosity_Normalization(std::string sample) {
    
        double Xsections    = Sample_X_Section[sample];
        double Total_Events = Sample_Total_Events[sample] ;
        double Luminosity   = 35.917150 ;  // in units of fb-1
    
        double factor1 = ( Xsections / Total_Events ) * Luminosity ;
    
        return factor1 ;
      }  
    
    //=============Pile Up factor calculation using PileUp file ==================================================

      float PUWeights(float npv) {
    
        int bin = PieUp_ScaleFactor->GetXaxis()->FindBin( npv );
        float weight = PieUp_ScaleFactor->GetBinContent( bin );
        return  weight ;
      
      }


//================Muon ID Scale factor using efficiency root files ===========================================

  double Muon_ID_ScaleFactor(float pt_muon, float eta){
    
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

//============General Object selections  functions=============

  void   Cut_AK8jet(int c_jet, int var) {

    if((*AK8JetPt)[c_jet] >= 200.0 && fabs((*AK8JetEta)[c_jet]) <= 2.4 && (*AK8JetPFLooseId)[c_jet] == 1 )  n_AK8Jet.push_back(c_jet) ;

  } 


  bool   Cut_Muon(int c_muon) {

    bool pass_muon = true;
    if ( (*muPt)[c_muon] <= 50.0 ) pass_muon = false;  //  Pt cut changed to 50 for trigger value
    if ( fabs((*muEta)[c_muon]) >= 2.1 ) pass_muon = false;
    bool tight_muon = (*muIDbit)[c_muon]>> 4 & 1;    //for tight muon ID >> 3  // for highpT ID >> 4
    if ( tight_muon == 0 ) pass_muon = false;
 
    return pass_muon ;

  }

// for checking ===================================
  bool ak8Jet_ID_Check(int c_jet, TString wp) { 
  
  
      float eta[2] =  { 2.4, 3.0 };
      float pt[2]  =  { 30.0, 15.0} ;
      bool  pass_jetID = false ;
  
      // AK8JetCHF->  chargedHadronEnergyFraction // 0.0
      // AK8JetNHF->  neutralHadronEnergyFraction //0.99
      // AK8JetCEF->  chargedEmEnergyFraction     //0.99
      // AK8JetNEF->  neutralEmEnergyFraction     //0.99
      // AK8JetNCH->  chargedMultiplicity         //0
      // AK8JetNNP->  neutralMultiplicity         //0
      // AK8JetMUF->  muonEnergyFraction 
      // AK8Jetnconstituents-> chargedMultiplicity + neutralMultiplicity  //1  
  

     if(fabs((*AK8JetEta)[c_jet]) <= 2.7 ) {
  
       if(wp == "loose"){ // for loose JetID check
  
        pass_jetID = (((*AK8JetNHF)[c_jet]<0.99 && (*AK8JetNEF)[c_jet]<0.99 && (((*AK8JetNCH)[c_jet] + (*AK8JetNNP)[c_jet]) > 1)) && (((fabs((*AK8JetEta)[c_jet])<=2.4 && (*AK8JetCHF)[c_jet]>0 && (*AK8JetNCH)[c_jet]>0 && (*AK8JetCEF)[c_jet]<0.99)) || (fabs((*AK8JetEta)[c_jet])>2.4))) ;
        // cout <<"\n It worked";       
       }
  
       if(wp == "tight"){ // for tight JetID check
  
        pass_jetID = (((*AK8JetNHF)[c_jet]<0.90 && (*AK8JetNEF)[c_jet]<0.90 && (((*AK8JetNCH)[c_jet] + (*AK8JetNNP)[c_jet]) > 1)) && (((fabs((*AK8JetEta)[c_jet])<=2.4 && (*AK8JetCHF)[c_jet]>0 && (*AK8JetNCH)[c_jet]>0 && (*AK8JetCEF)[c_jet]<0.99)) || (fabs((*AK8JetEta)[c_jet])>2.4)) ) ;
       }
  
       if(wp == "tightLepVeto"){ // for tightLepVeto JetID check
  
        pass_jetID = (((*AK8JetNHF)[c_jet]<0.90 && (*AK8JetNEF)[c_jet] < 0.90 && (((*AK8JetNCH)[c_jet] + (*AK8JetNNP)[c_jet]) > 1) && (*AK8JetMUF)[c_jet] < 0.8) && (((fabs((*AK8JetEta)[c_jet])<=2.4 && (*AK8JetCHF)[c_jet]>0 && (*AK8JetNCH)[c_jet]>0 && (*AK8JetCEF)[c_jet]<0.90)) || (fabs((*AK8JetEta)[c_jet])>2.4)) ) ;
       }
  
     }

     // For |eta|>2.7 &&  |eta| <= 3.0 Apply // HERE LOOSE & TIGHT ID SIMILAR SO SAME CONDITION APPLIED.
  
     if(fabs((*AK8JetEta)[c_jet]) > 2.7 && fabs((*AK8JetEta)[c_jet]) <= 3.0 ) {
  
        // for JetID check  
        pass_jetID = ( (*AK8JetNHF)[c_jet] < 0.98 && (*AK8JetNEF)[c_jet] > 0.01 && (*AK8JetNNP)[c_jet] > 2 ) ;     
  
     }

     // For |eta|>3.0 Apply  // HERE LOOSE & TIGHT ID SIMILAR SO SAME CONDITION APPLIED.
  
     if(fabs((*AK8JetEta)[c_jet]) > 3.0 ) {
  
        // fOR  JetID check  
        pass_jetID = ( (*AK8JetNEF)[c_jet] < 0.90 && (*AK8JetNNP)[c_jet] > 10 ) ;      
     }
  
  
     return pass_jetID ;
    
  }


  bool ak4Jet_ID_Check(int c_jet, TString wp) { 
  
  
      float eta[2] =  { 2.4, 3.0 };
      float pt[2]  =  { 30.0, 15.0} ;
      bool  pass_jetID = false ;
  
      // jetCEF  -> chargedEmEnergyFraction
      // jetNEF  -> neutralEmEnergyFraction
      // jetCHF  -> chargedHadronEnergyFraction
      // jetNHF  -> neutralHadronEnergyFraction
      // jetNCH  -> chargedMultiplicity
      // jetNNP  -> neutralMultiplicity
      // jetMUF  -> muonEnergyFraction

  
     if(fabs((*jetEta)[c_jet]) <= 2.7 ) {
  
       if(wp == "loose"){ // for loose JetID check
  
        pass_jetID = (((*jetNHF)[c_jet]<0.99 && (*jetNEF)[c_jet]<0.99 && (((*jetNCH)[c_jet] + (*jetNNP)[c_jet]) > 1)) && (((fabs((*jetEta)[c_jet])<=2.4 && (*jetCHF)[c_jet]>0 && (*jetNCH)[c_jet]>0 && (*jetCEF)[c_jet]<0.99)) || (fabs((*jetEta)[c_jet])>2.4))) ;
        // cout <<"\n It worked";       
       }
  
       if(wp == "tight"){ // for tight JetID check
  
        pass_jetID = (((*jetNHF)[c_jet]<0.90 && (*jetNEF)[c_jet]<0.90 && (((*jetNCH)[c_jet] + (*jetNNP)[c_jet]) > 1)) && (((fabs((*jetEta)[c_jet])<=2.4 && (*jetCHF)[c_jet]>0 && (*jetNCH)[c_jet]>0 && (*jetCEF)[c_jet]<0.99)) || (fabs((*jetEta)[c_jet])>2.4)) ) ;
       }
  
       if(wp == "tightLepVeto"){ // for tightLepVeto JetID check
  
        pass_jetID = (((*jetNHF)[c_jet]<0.90 && (*jetNEF)[c_jet] < 0.90 && (((*jetNCH)[c_jet] + (*jetNNP)[c_jet]) > 1) && (*jetMUF)[c_jet] < 0.8) && (((fabs((*jetEta)[c_jet])<=2.4 && (*jetCHF)[c_jet]>0 && (*jetNCH)[c_jet]>0 && (*jetCEF)[c_jet]<0.90)) || (fabs((*jetEta)[c_jet])>2.4)) ) ;
       }
  
     }

     // For |eta|>2.7 &&  |eta| <= 3.0 Apply // HERE LOOSE & TIGHT ID SIMILAR SO SAME CONDITION APPLIED.
  
     if(fabs((*jetEta)[c_jet]) > 2.7 && fabs((*jetEta)[c_jet]) <= 3.0 ) {
  
        // for JetID check  
        pass_jetID = ( (*jetNHF)[c_jet] < 0.98 && (*jetNEF)[c_jet] > 0.01 && (*jetNNP)[c_jet] > 2 ) ;
        // cout <<"\n It worked";       
  
     }

     // For |eta|>3.0 Apply  // HERE LOOSE & TIGHT ID SIMILAR SO SAME CONDITION APPLIED.
  
     if(fabs((*jetEta)[c_jet]) > 3.0 ) {
  
        // fOR  JetID check  
        pass_jetID = ( (*jetNEF)[c_jet] < 0.90 && (*jetNNP)[c_jet] > 10 ) ;
        // cout <<"\n It worked";         
     }
  
  
     return pass_jetID ;
    
  }


  void Cut_bjet_check(int c_jet, int wp, int cut) { 


    float eta[2] =  { 2.4, 3.0 };
    float pt[2]  =  { 30.0, 15.0} ;

    if( (*jetPt)[c_jet] >= 30.0){
      if (fabs((*jetEta)[c_jet]) < 2.4 ){ 
        // cout <<"\n It worked again";       
        n_jet.push_back(c_jet) ;
        // if ( (*jetPFLooseId)[c_jet] == 1 )n_jet.push_back(c_jet) ;

        if(wp >= 1 ){
          if(((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.2219) {
              b_jetloose.push_back(c_jet) ;   
              b_jet.push_back(c_jet) ;     
               
          }
          else {
              q_jet.push_back(c_jet) ;
          }
        }

        else{         
           n_forwjet.push_back(c_jet) ;

        }
      }
    }
  
  }


  void Cut_bjet(int c_jet, int wp) { 

    //  for 2016 Era
    // new tagger (see the recipe for DeepFlavour) the tagger is given by the sum: p(b)+p(bb)  
    // DeepCSVL   0.2217        
    // DeepCSVM   0.6321       
    // DeepCSVT   0.8953 

    if( (*jetPt)[c_jet] >= 30.0){
      if(fabs((*jetEta)[c_jet]) < 2.4 ){ 

        if ( (*jetPFLooseId)[c_jet] == 1 )n_jet.push_back(c_jet) ;

        if (wp == 2 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.2217) {
              b_jetloose.push_back(c_jet) ;   
              b_jet.push_back(c_jet) ;     
               
          }
          else {
              q_jet.push_back(c_jet) ;
          }
        }


        if (wp == 3 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.6321) {
              b_jetmedium.push_back(c_jet) ;  
              b_jet.push_back(c_jet) ;     
          }
          else {
              q_jet.push_back(c_jet) ;
          }
        }

        if (wp == 4 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.8953) {
              b_jettight.push_back(c_jet) ;   
              b_jet.push_back(c_jet) ;     
          }
          else {
              q_jet.push_back(c_jet) ;
          }
        }

      }

      else{
        n_forwjet.push_back(c_jet) ;

      }
    }

  }


  void Cut_bjet_After_drCheck(int c_jet, int wp) { 

    //  for 2016 Era
    // new tagger (see the recipe for DeepFlavour) the tagger is given by the sum: p(b)+p(bb)  
    // DeepCSVL   0.2217        
    // DeepCSVM   0.6321       
    // DeepCSVT   0.8953 


    if( (*jetPt)[c_jet] >= 30.0){

        if (wp == 2 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.2217) {
              b_jetloose.push_back(c_jet) ;   
              b_jet.push_back(c_jet) ;     
               
          }
        }
      

        if (wp == 3 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.6321) {
              b_jetmedium.push_back(c_jet) ;  
              // b_jet.push_back(c_jet) ;     
          }
        }

        if (wp == 4 ){
          if ( ((*jetDeepCSVTags_b)[c_jet] + (*jetDeepCSVTags_bb)[c_jet]) >  0.8953) {
              b_jettight.push_back(c_jet) ;   
              b_jet.push_back(c_jet) ;     
          }
        }
      }

  }


void AK8jet_sorting_pT_based() {

      int jmax = -1 ;
      int jt   = -1 ; 
      float max_pT = 0.0;



      for( int i = 0 ; i < AK8_sort.size(); i++){

        if( AK8_copy.size() == 0) continue ;

        jmax   = 0;
        max_pT = (*AK8JetPt)[AK8_copy[0]];  

        for (int k = 0; k < AK8_copy.size(); k++)
        {
          jt   = AK8_copy[k];

          if( (*AK8JetPt)[jt] > max_pT ) {
            jmax   = k ;
            max_pT = (*AK8JetPt)[jt];

          }  
        }
       
        AK8_sort[i] = AK8_copy[jmax];
        AK8_copy.erase(AK8_copy.begin() + jmax);

      }

}



void jet_sorting_pT_based()
{
  int jmax = -1 ;
  int jt   = -1 ; 
  float max_pT = 0.0;



  for( int i = 0 ; i < jet_sort.size(); i++){

    if( jet_copy.size() == 0) continue ;

    jmax   = 0;
    max_pT = (*jetPt)[jet_copy[0]];  

    for (int k = 0; k < jet_copy.size(); k++)
    {
      jt   = jet_copy[k];

      if( (*jetPt)[jt] > max_pT ) {
        jmax   = k ;
        max_pT = (*jetPt)[jt];

      }  
    }
   

    jet_sort[i] = jet_copy[jmax];
    jet_copy.erase(jet_copy.begin() + jmax);


  }

}

void forwjet_sorting_pT_based()
{
  int jmax = -1 ;
  int jt   = -1 ; 
  float max_pT = 0.0;



  for( int i = 0 ; i < fjet_sort.size(); i++){

    if( fjet_copy.size() == 0) continue ;

    jmax   = 0;
    max_pT = (*jetPt)[fjet_copy[0]];  

    for (int k = 0; k < fjet_copy.size(); k++)
    {
      jt   = fjet_copy[k];

      if( (*jetPt)[jt] > max_pT ) {
        jmax   = k ;
        max_pT = (*jetPt)[jt];

      }  
    }
   

    fjet_sort[i] = fjet_copy[jmax];
    fjet_copy.erase(fjet_copy.begin() + jmax);


  }

}

/*
  void Cut_puppibjet(int c_jet, int wp) {     
    if( (*puppijetPt)[c_jet] >= 30.0){
      if (fabs((*puppijetEta)[c_jet]) < 2.4 ){ 
        if (wp == 1 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.2219) {
               puppib_jetloose.push_back(c_jet) ;   
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

        if (wp == 2 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.6324) {
               puppib_jetmedium.push_back(c_jet) ;  
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

        if (wp == 3 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.8958) {
               puppib_jettight.push_back(c_jet) ;   
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

      }

      else{
         puppin_forwjet.push_back(c_jet) ;

      }
    
    }

  }   
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


// for  General Functions of dR & dPt ---------------------------
  float dPt_Calculator(const TVector3 & lep , const TVector3 & jet ) {
    // type for jet type, type = 0 is AK4jet, type = 1 is puppijet, type = 2 is 
    float  vec_mag = 0.0 ;
    TVector3 vec_Xprod ; 
  
    vec_Xprod = lep.Cross(jet);
    vec_mag   = jet.Mag();
  
    float dPt =  (vec_Xprod.Mag() ) / vec_mag ;
  
    //cout << "\n dPt calculated = " << dPt ;
    return dPt ;
  }


  float dR_Calculator( float eta1, float phi1, float eta2, float phi2)  {
  
     const float PI    =  2.0*acos(0.0);
     const float TWOPI =  2.0*PI;
     float PHI         =  fabs( phi1 - phi2 ) ;
     dPhi              = (PHI<=PI)? PHI : TWOPI-PHI;
     dEta              =  fabs( eta1 - eta2 );       
     dR                =  Sqrt(dPhi*dPhi + dEta*dEta) ;
  
     return dR ;
  
  }

  float delta_phi(float phi1,float phi2) {
     const float PI=2.0*acos(0.0);
     const float TWOPI=2.0*PI;
     float PHI=fabs( phi1 - phi2 ) ;
     return (PHI<=PI)? PHI : TWOPI-PHI;
  
  }
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


// For Jet Selections ====================================

  void  Higgs_selection(int var, float ST_cut) {
     
     // jet_Tagger general purpose tagger Higgs, top & W 
  
     int jt = -1 ;
     //float t42 = PUPPItau[var-1] ;
  
     int Wsize  = ( n_AK8Jet.size() >= 2) ? 2 :  n_AK8Jet.size() ;
  
     //t42 = 0.75 ;
     //if (var%2 == 0) t42 = 0.65 ;
     for (int g = 0 ; g < Wsize ; g ++ ){
  
        // if ( n_AK8Jet[g] == -1 )   continue;   // inckude this condition if you are tagging jets other than Higgs
        jt = n_AK8Jet[g] ;
        // cout << "Higgs_SDMassCorr  = " << Higgs_SDMassCorr << endl ;
  
        if ( Jet_Tagger(jt, "Higgs", var, ST_cut) == -1 ) continue ; // name of tagger and index of jet passed
        // if ((*AK8JetPt)[jt] < pT_cut ) continue ;
        Higgsjets.push_back(jt);
        // n_AK8Jet[g] = -1 ;    // inckude this condition if you are tagging jets other than Higgs
    
     }
  }        


  void Wjet_selection(int var)  {
  
     // jet_Tagger general purpose tagger Higgs, top & W 
  
     float Puppi_SDmass = 0.0 ;
     float pt = 0.0 ;
     float tau21 = 0.0 ;
     int jt = -1 ;
     //float t42 = PUPPItau[var-1] ;
  
     int Wsize  = ( n_AK8Jet.size() >= 3) ? 3 :  n_AK8Jet.size() ;
     for (int g = 0 ; g < Wsize ; g ++ ){
        
        if ( n_AK8Jet[g] == -1 )   continue;
        jt = n_AK8Jet[g] ;
  
        if (var <= 6){
           
           Puppi_SDmass     =  (*AK8puppiSDMassL2L3Corr)[jt] ;
           tau21            =  ((*AK8puppiTau2)[jt]/(*AK8puppiTau1)[jt]) ;
           pt               =   (*AK8JetPt)[jt] ; 
           
        }
  
      //  if ( Jet_Tagger(pt, Puppi_SDmass, tau21, "Wjet") == -1 ) continue ;
        W_boson.push_back(jt);
        n_AK8Jet[g] = -1 ;    
     }
  
  }


// general tagger  function ==========================================
  int  Jet_Tagger ( int index, TString jet, int tau_cut, float ST_cut ) {
    
    int pass_jet = -1 ;
  
    const  Int_t cut = 7 ;
    double Tau42_Cut_loc[cut] = { 0.0, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75} ;

    double tau              =  0.0 ;
    double SD_mass          =  (*AK8puppiSDMass)[index] ;
    double pt               =  (*AK8JetPt)[index] ; 
    float  eta              =  (*AK8JetEta)[index] ; 
    double corr_SD          =  0.0 ;
  
  
    if ( jet == "Higgs") {   // for Higgs tagger  
  
      tau               =  ((*AK8puppiTau4)[index]/(*AK8puppiTau2)[index]) ;
      // Higgs_SDMassCorr  =  0.0 ;
  
      // if( (pt >= pT_cut ) && (tau < Tau42_Cut_loc[tau_cut - 1]  ) ) {      
      if( (tau < Tau42_Cut_loc[tau_cut - 1]  ) ) {      
      corr_SD         =  getPUPPIweight(pt, eta) ;
      }
  
      SD_mass           =  corr_SD * SD_mass ;
  
      if( SD_mass >=  ST_cut && SD_mass <= 150.0 ) {
  
        pass_jet                   =   1 ;
        Higgs_SDMassCorr           =   SD_mass ;
  
      }  
  
        
    }
  
    if ( jet == "Wjet") {   // for Wjet tagger 
  
      tau               =  ((*AK8puppiTau2)[index]/(*AK8puppiTau1)[index]) ;
  
      if( (pt >= 200.0 ) && (tau < 0.55  ) ) {      
      corr_SD           =  getPUPPIweight(pt, eta) ;
      }
  
      SD_mass           =  corr_SD * SD_mass ;
      if( SD_mass <=  65.0 || SD_mass >= 105.0 ) pass_jet = -1 ;
    }
    
    return pass_jet ;
  
  }


  float  getPUPPIweight(float puppipt, float puppieta ) {
  
      // PUPPI correction to Soft Drop Masss for Higgtagger
      //TFile *file = TFile::Open( "puppiCorr.root","READ");
      //TFile* file = TFile::Open( puppiFile_.c_str(),"READ" );
    
      float genCorr  = 1.;
      float recoCorr = 1.;
      float totalWeight = 1.;
    
      genCorr =  puppisd_corrGEN->Eval( puppipt );
    
      if( fabs(puppieta)  <= 1.3 ){
        recoCorr = puppisd_corrRECO_cen->Eval( puppipt );
      }
    
      else{
        recoCorr = puppisd_corrRECO_for->Eval( puppipt );
      }
     
      totalWeight = genCorr * recoCorr;
    
    
      return totalWeight;
  
  }

//======Lepton Isolation Study ==============================================================
  int Lepton_Isolation_Study ( int sel_level, bool bjet_check ){
  
      int pass  = -1 ;
      TString selection   = Cut_Check_Variable[sel_level];
      TVector3 vec_lep, vec_jet;

      
      int muon  = n_Mu[0];
      float eta1       = (*muEta)[muon];
      float phi1       = (*muPhi)[muon];
      vec_lep.SetPtEtaPhi( (*muPt)[muon], (*muEta)[muon] , (*muPhi)[muon] ) ;

      nearest_jet = -1 ;

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( bjet_check ) nearest_jet  = Lepton_Isolation_Bjet( sel_level );
      else              nearest_jet  = Lepton_Isolation_Muon_Njet( sel_level) ; 

      float eta2       = (*jetEta)[nearest_jet] ;
      float phi2       = (*jetPhi)[nearest_jet] ; 
      vec_jet.SetPtEtaPhi( (*jetPt)[nearest_jet], (*jetEta)[nearest_jet], (*jetPhi)[nearest_jet] ) ;

      if ( selection == "Preselect") pass = 1 ;

      if ( selection == "TrackIsolation"){

          if ( ( (*muIDbit)[muon]>> 11 & 1 ) == 1 ) pass = 1 ;
          // Match_Muon_Pt1000 ->Fill ((*muIsoTrk) [muon]) ;
          // Match_Muon_Pt300 ->Fill ((*muPt)[muon]) ;
          // Muon_Pt_ratio    ->Fill ((*muIsoTrk) [muon] / (*muPt)[muon]) ;
      }


      if ( selection == "MiniIsolation"){

          if ( (*muPt)[muon] < 50.0 ) dr_test =  0.2 ;
          if ( (*muPt)[muon] > 200.0) dr_test =  0.05 ;
          if ( (*muPt)[muon] >50.0 && (*muPt)[muon] < 200.0 ) dr_test = (10.0 / (*muPt)[muon]) ; 

          dr_min =  dR_Calculator(eta1, phi1, eta2, phi2) ;
          if ( dr_min > dr_test) pass = 1 ;
      }

      if ( selection == "dRgt04dPtgt00" ){

          cout << "\n Sel = " << selection ;
          dr_test  = Cut_LepIso_Test_dR[selection]  ;
          dpt_test = Cut_LepIso_Test_dPt[selection] ;
          dr_min   = dR_Calculator(eta1, phi1, eta2, phi2) ;
          // dpt_min  = dPt_Calculator(vec_lep, vec_jet) ;

          if ( dr_min < dr_test  ) pass = 1 ;
          // if ( dr_min > dr_test || dpt_min > dpt_test ) pass = 1 ;

      }


      return pass ;

  }

  // int Lepton_Isolation_Study_v2 ( int sel_level){
    int Lepton_Isolation_Study_v2 ( TString selection){
 
      int pass  = -1 ;
      // TString selection   = Cut_LepIso_Variable[sel_level];
      int wp_point =  LepIso_IDbit[selection] ;

      TVector3 vec_lep, vec_jet; 
      int muon  = n_Mu[0];     
      nearest_jet = -1 ;

      // bool bjet_check = true ; // true for closest bjet and false for closest jet
      double dr_test   = -1.0, dr_min = -1.0, dpt_min = -1.0, dpt_test = -1.0 ;

      if ( selection == "Preselect") pass = muon ;

      else{

          if ( ( (*muIDbit)[muon]>> wp_point & 1 ) == 1 ) pass = muon ;
          // Match_Muon_Pt1000 ->Fill ((*muIsoTrk) [muon]) ;
          // Match_Muon_Pt300 ->Fill ((*muPt)[muon]) ;
          // Muon_Pt_ratio    ->Fill ((*muIsoTrk) [muon] / (*muPt)[muon]) ;
      }

      return pass ;

  }

  void   Fill_DeltaR_Pt_For_Nearest_Jet_Muon( int close_jet ) {
  


    int   j                = n_Mu[0] ;
    TVector3 vec_lep, vec_jet;
    float dPt        = 0.0 ;
  
    float eta1       = (*muEta)[j];
    float phi1       = (*muPhi)[j];
    vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;
  
    float eta2       = (*jetEta)[close_jet] ;
    float phi2       = (*jetPhi)[close_jet] ;         

    float dR_min     = dR_Calculator(eta1, phi1, eta2, phi2) ;   

    //cout << "\n jet = "   << close_jet  ;

    vec_jet.SetPtEtaPhi( (*jetPt)[close_jet], (*jetEta)[close_jet], (*jetPhi)[close_jet] ) ;
    dPt  = dPt_Calculator(vec_lep, vec_jet) ;
  
    h_dR_Reco.at(0).at(1)->Fill(dR_min , factor);  
    if (dR_min <= 0.4 ) h_dR_Reco_lt04.at(0).at(0)->Fill(dR_min , factor);

    h_dPt_Reco.at(1)->Fill(dPt , factor );
    if (dPt <= 10.0 ) h_dPt_Reco_lt10.at(0).at(0)->Fill(dPt , factor); 
    if (dPt <= 15.0 ) h_dPt_Reco_lt15.at(0).at(0)->Fill(dPt , factor); 
    dPt_dR_mubjet->Fill(dR_min, dPt,factor);

  
}


// 2-D Lepton Isoaltion for bjet

  void Fill_Lepton_Isolation_Muon_Bjet(int val) {
  

          
    int   close_jet    = -1;
    int   b2           = -1 ;
    int   j                = n_Mu[0] ;
    TVector3 vec_lep, vec_jet;
    float dPt        = 0.0 ;
  
    float mu_pT      = (*muPt)[j] ;

    float eta1       = (*muEta)[j];
    float phi1       = (*muPhi)[j];
    vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;
  
    float eta2       = (*jetEta)[close_jet] ;
    float phi2       = (*jetPhi)[close_jet] ;  
    float dR_min     = 999.0 ;
  
    for( int h =0 ; h < b_jet.size() ; h ++ ){
  
        b2    =  b_jet[h] ;          
  
        eta2  = (*jetEta)[b2] ;
        phi2  = (*jetPhi)[b2] ;    
        
        dR_Calculator(eta1, phi1, eta2, phi2) ;
  
        if ( dR_min > dR) {
          dR_min      = dR ;
          close_jet   = b2 ;
         }     
      }    
  
    eta2              = (*jetEta)[close_jet] ;
    phi2              = (*jetPhi)[close_jet] ;  
    dR_min            = dR_Calculator(eta1, phi1, eta2, phi2) ;   
    vec_jet.SetPtEtaPhi( (*jetPt)[close_jet], (*jetEta)[close_jet], (*jetPhi)[close_jet] ) ;
    dPt  = dPt_Calculator(vec_lep, vec_jet) ;
  
    h_dR_Reco.at(0).at(1)->Fill(dR_min , factor);  
    if (dR_min <= 0.4 ) h_dR_Reco_lt04.at(0).at(0)->Fill(dR_min , factor);

    h_dPt_Reco.at(1)->Fill(dPt , factor );
    if (dPt <= 10.0 ) h_dPt_Reco_lt10.at(0).at(0)->Fill(dPt , factor); 
    if (dPt <= 15.0 ) h_dPt_Reco_lt15.at(0).at(0)->Fill(dPt , factor); 
    dPt_dR_mubjet->Fill( dPt,dR_min,factor);
    
    
 
  }


  int Lepton_Isolation_Bjet(int val) {
  
    const  Int_t cut = 5 ;
    float  dPt_Cut[cut] = { 10.0,10.0, 10.0, 10.0, 10.0} ;
    float cut_pt     =  0.0 ;
          
    int   close_jet    = -1;
    int   b2           = -1 ;
    int   j                = n_Mu[0] ;
    TVector3 vec_lep, vec_jet;
    float dPt        = 0.0 ;
  
    float eta1       = (*muEta)[j];
    float phi1       = (*muPhi)[j];
    vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;
  
    float eta2       = (*jetEta)[close_jet] ;
    float phi2       = (*jetPhi)[close_jet] ;  
    float dR_min     = 999.0 ;
  
    for( int h =0 ; h < b_jet.size() ; h ++ ){
  
        b2    =  b_jet[h] ;          
  
        eta2  = (*jetEta)[b2] ;
        phi2  = (*jetPhi)[b2] ;    
        
        dR_Calculator(eta1, phi1, eta2, phi2) ;
  
        if ( dR_min > dR) {
          dR_min      = dR ;
          close_jet   = b2 ;
         }     
      }    
  

    
    return close_jet ;
  
  }

// 2-D Lepton Isoaltion for qjet 
  int Lepton_Isolation_Muon_Qjet(int val) {
  
    const  Int_t cut = 4 ;
    // float  dPt_Cut[cut] = {10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0} ;
    float  dPt_Cut[cut] = {10.0, 10.0, 10.0, 10.0} ;
  
    int   j                = -1;
    if (q_jet.size() == 0  ) {
      j = -1 ;
    }
  
    else {
      int   close_jet    = -1;
      int   b2           = -1 ;
      j                = n_Mu[0] ;
      TVector3 vec_lep, vec_jet;
      float dPt        = 0.0 ;
      float cut_pt     =  0.0 ;
    
      float eta1       = (*muEta)[j];
      float phi1       = (*muPhi)[j];
      vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;
    
      float eta2       = (*jetEta)[close_jet] ;
      float phi2       = (*jetPhi)[close_jet] ;  
      float dR_min     = 999.0 ;
  
      for( int h =0 ; h < q_jet.size() ; h ++ ){

        b2    =  q_jet[h] ;          

        eta2  = (*jetEta)[b2] ;
        phi2  = (*jetPhi)[b2] ;    
        
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        if ( dR_min > dR) {
          dR_min      = dR ;
          close_jet   = b2 ;
        }     
      }    
  
    
      eta2              = (*jetEta)[close_jet] ;
      phi2              = (*jetPhi)[close_jet] ;  
      dR_min            = dR_Calculator(eta1, phi1, eta2, phi2) ;   
      vec_jet.SetPtEtaPhi( (*jetPt)[close_jet], (*jetEta)[close_jet], (*jetPhi)[close_jet] ) ;
      dPt  = dPt_Calculator(vec_lep, vec_jet) ;
      //dPt_dR_mubjet->Fill(dR_min, dPt);
    
      
      dPt_dR_mubjet->Fill(dR_min, dPt);
      
      cut_pt = dPt_Cut[val-1] ;
    
      // cout << "\n j = " << j << "  &&   close jet = " << close_jet << "...... dPt = " << dPt ;
          
      if(  (dR_min > 0.4 )  || dPt > cut_pt )  j = n_Mu[0] ;        
      
      else j = -1 ;
    
    }
      
    return j ;

  }



int Lepton_Isolation_Muon_Njet(int val)
{
  const  Int_t cut = 4 ;
  int   close_jet    = -1;

  //  float  dPt_Cut[cut] = {10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0} ;
  float  dPt_Cut[cut] = {10.0, 10.0, 10.0, 10.0} ;

  int   j                = -1;
  if (n_jet.size() == 0 ) j = -1 ;

  else{
  close_jet    = -1;
  int   b2           = -1 ;
  j                = n_Mu[0] ;
  TVector3 vec_lep, vec_jet;
  float dPt        = 0.0 ;
  float cut_pt     =  0.0 ;
  float eta1       = (*muEta)[j];
  float phi1       = (*muPhi)[j];
  vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;

  float eta2       = (*jetEta)[close_jet] ;
  float phi2       = (*jetPhi)[close_jet] ;  
  float dR_min     = 999.0 ;

  for( int h =0 ; h < n_jet.size() ; h ++ ){

      b2    =  n_jet[h] ;          

      eta2  = (*jetEta)[b2] ;
      phi2  = (*jetPhi)[b2] ;    
      
      dR_Calculator(eta1, phi1, eta2, phi2) ;

      if ( dR_min > dR) {
        dR_min      = dR ;
        close_jet   = b2 ;
       }     
    }    

  
 

 }

      return close_jet ;
}


  void Fill_Lepton_Isolation_Muon_Njet(int val) {
  

          
    int   close_jet    = -1;
    int   b2           = -1 ;
    int   j            = n_Mu[0] ;
    TVector3 vec_lep, vec_jet;
    float dPt        = 0.0 ;
  
    float mu_pT      = (*muPt)[j] ;
    float eta1       = (*muEta)[j];
    float phi1       = (*muPhi)[j];
    vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;
  
    float eta2       = (*jetEta)[close_jet] ;
    float phi2       = (*jetPhi)[close_jet] ;  
    float dR_min     = 999.0 ;
  
    for( int h =0 ; h < n_jet.size() ; h ++ ){
  
        b2    =  n_jet[h] ;          
  
        eta2  = (*jetEta)[b2] ;
        phi2  = (*jetPhi)[b2] ;    
        
        dR_Calculator(eta1, phi1, eta2, phi2) ;
  
        if ( dR_min > dR) {
          dR_min      = dR ;
          close_jet   = b2 ;
        }     
    }    
    
    eta2              = (*jetEta)[close_jet] ;
    phi2              = (*jetPhi)[close_jet] ;  
    dR_min            = dR_Calculator(eta1, phi1, eta2, phi2) ;   
    vec_jet.SetPtEtaPhi( (*jetPt)[close_jet], (*jetEta)[close_jet], (*jetPhi)[close_jet] ) ;
    dPt  = dPt_Calculator(vec_lep, vec_jet) ;
    
    // dPt_dR_mubjet->Fill(dR_min, (*muPt)[j], factor);
    dPt_dR_mubjet->Fill( dR_min, dPt,factor);
    dPt_dR_muqjet->Fill( dR_min, dPt );

    // h_dR_Reco.at(0).at(3)->Fill(dR_min , factor);  
    // if (dR_min <= 0.4 ) h_dR_Reco_lt04.at(0).at(1)->Fill(dR_min , factor);
    
    // h_dPt_Reco.at(3)->Fill(dPt , factor );
    // if (dPt <= 10.0 ) h_dPt_Reco_lt10.at(0).at(1)->Fill(dPt , factor); 
    // if (dPt <= 15.0 ) h_dPt_Reco_lt15.at(0).at(1)->Fill(dPt , factor); 

    
 
  }
// dR Higgs and between muon && bjet=====================

int dR_Higgs_mubjet_Cut(int topbjet)
{

  int   pass_cat    = -1 ;
  int   jet1       = Higgsjets[0] ;
  int   j          = n_Mu[0] ;
  float dR_check1   = -1.0,  dR_check2   = -1.0;
  float eta1  = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, eta3 = 0.0, phi3 = 0.0;

  eta1  = (*muEta)[j];
  phi1  = (*muPhi)[j];

  eta2  = (*jetEta)[topbjet] ;
  phi2  = (*jetPhi)[topbjet] ;  

  eta3  = (*AK8JetEta)[jet1] ;
  phi3  = (*AK8JetPhi)[jet1] ;

  dR_check1 = dR_Calculator(eta3, phi3, eta1, phi1) ;
  dR_check2 = dR_Calculator(eta3, phi3, eta2, phi2) ;

  if ( dR_check2 > 2.0 && dR_check1 > 2.0 ) {
         pass_cat    = 1 ;
         CatI_Objects.push_back(-1);              //vague value as all histogram defined from index =1                 
         CatI_Objects.push_back(jet1);               // Higgsjet at 0th place
         CatI_Objects.push_back(topbjet);         //  bjet at 1st place 
         CatI_Objects.push_back(j);            //  muon at 2nd place & MET is global
         
  }

  return pass_cat ;
}


int dR_Higgs_mubjet_Cut_v2(int mu)
{

  //int   pass_cat    = -1 ;
  int   jet1        = Higgsjets[0] ;
  int   topbjet     = -1  ;
  float dR_check1   = -1.0,  dR_check2   = -1.0;
  float eta1  = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, eta3 = 0.0, phi3 = 0.0;
  int   b2    = -1 ;
  eta1  = (*muEta)[mu];
  phi1  = (*muPhi)[mu];

  eta3  = (*AK8JetEta)[jet1] ;
  phi3  = (*AK8JetPhi)[jet1] ;

  dR_check1 = dR_Calculator(eta3, phi3, eta1, phi1) ;

  int size4  = ( b_jet.size() >= 3) ? 3 : b_jet.size() ;
  for( int h =0 ; h < b_jet.size() ; h ++ ){
      if ( topbjet != -1 ) continue ;

      b2    =  b_jet[h] ;          
      //if ( (*jetPt)[b2] < 50.0 ) continue ;

      eta2          = (*jetEta)[b2] ;
      phi2          = (*jetPhi)[b2] ;    
      dR_check2     = dR_Calculator(eta1, phi1, eta2, phi2) ;

      if ( dR_check2 > 1.5  ) continue ;

      dR_check2 = dR_Calculator(eta3, phi3, eta2, phi2) ;

      if ( dR_check2 > 2.0 && dR_check1 > 2.0 ) { 

            topbjet  = b2 ;
            CatI_Objects.push_back(-1);              //vague value as all histogram defined from index =1                 
            CatI_Objects.push_back(jet1);               // Higgsjet at 0th place
            CatI_Objects.push_back(topbjet);         //  bjet at 1st place 
            CatI_Objects.push_back(mu);            //  muon at 2nd place & MET is global        

        }


   }   

  return topbjet ;
}


////Changing to  seperate cut  fro Higs, muon and bjet step wise
  int dR_Higgs_mu_Cut_v2(int mu)
    {
    
      //int   pass_cat    = -1 ;
      int   jet1        = Higgsjets[0] ;
      float dR_check1   = -1.0;
      float eta1  = 0.0 , eta3 = 0.0, phi1 = 0.0, phi3 = 0.0;
    
      eta1  = (*muEta)[mu];
      phi1  = (*muPhi)[mu];
    
      eta3  = (*AK8JetEta)[jet1] ;
      phi3  = (*AK8JetPhi)[jet1] ;
    
      dR_check1 = dR_Calculator(eta3, phi3, eta1, phi1) ;
    
    
      if ( dR_check1 < 2.0 ) mu = -1 ;
    
      return mu  ;
    }


 int dR_Higgs_bjet_Cut_v2()
    {
    
      int   b2          = -1 ;
      int   jet1        = Higgsjets[0] ;
      int   topbjet     = -1  ;
      float dR_check2   = -1.0;
      float eta2 = 0.0, phi2 = 0.0, eta3 = 0.0, phi3 = 0.0;
    
      eta3  = (*AK8JetEta)[jet1] ;
      phi3  = (*AK8JetPhi)[jet1] ;
    
      for( int h =0 ; h < b_jet.size() ; h ++ ){
          if ( topbjet != -1 ) continue ;
    
          b2    =  b_jet[h] ;          
    
          eta2  = (*jetEta)[b2] ;
          phi2  = (*jetPhi)[b2] ;    
    
          dR_check2 = dR_Calculator(eta3, phi3, eta2, phi2) ;
    
          if ( dR_check2 > 2.0 ) {
              topbjet          = b2 ;
              Tprime_Higgs     = jet1 ;
            }
       }   
    
      return topbjet ;
    }
    

  void dR_mu_bjet_Cut_v2(int jet)
    {
    
      int   pass_cat    = -1 ;
      float dR_check1   = -1.0 ;
      float eta1  = 0.0 , phi1 = 0.0, eta2 = 0.0, phi2 = 0.0;
    
      eta1  = (*muEta)[Tprime_muon];
      phi1  = (*muPhi)[Tprime_muon];
        
      eta2  = (*jetEta)[jet] ;
      phi2  = (*jetPhi)[jet] ;    
      if ( dR_Calculator(eta1, phi1, eta2, phi2) < 1.5 ) {
          pass_cat    = 1 ;
          Tprime_bjet = jet ; 
          CatI_Objects.push_back(-1);                         //vague value as all histogram defined from index =1                 
          CatI_Objects.push_back(Tprime_Higgs);               // Higgsjet at 0th place
          CatI_Objects.push_back(Tprime_bjet);                //  bjet at 1st place 
          CatI_Objects.push_back(Tprime_muon);                //  muon at 2nd place & MET is global                         
       }   
    
      // return pass_cat ;
     
    }   



 //////////////////////////////////////////////////////////////////////////////////////////////////
 void dR_Higgs_bjet_Cut_v3(int jet)
    {

      //// first muon bjet condition checked bjet and then higgs bjet checked
    
      int   b2          = -1 ;
      int   jet1        = Higgsjets[0] ;
      int   topbjet     = -1  ;
      float dR_check2   = -1.0;
      float eta2 = 0.0, phi2 = 0.0, eta3 = 0.0, phi3 = 0.0;
    
      eta3  = (*AK8JetEta)[jet1] ;
      phi3  = (*AK8JetPhi)[jet1] ;
    
      eta2  = (*jetEta)[jet] ;
      phi2  = (*jetPhi)[jet] ;   

      if ( dR_Calculator(eta3, phi3, eta2, phi2) > 2.0 ) {
          //pass_cat    = 1 ;
          Tprime_bjet = jet ; 
          Tprime_Higgs= jet1;
          CatI_Objects.push_back(-1);                         //vague value as all histogram defined from index =1                 
          CatI_Objects.push_back(Tprime_Higgs);               // Higgsjet at 0th place
          CatI_Objects.push_back(Tprime_bjet);                //  bjet at 1st place 
          CatI_Objects.push_back(Tprime_muon);                //  muon at 2nd place & MET is global                         
       }   
    
      // return pass_cat ;
     
    } 
    
    

  int dR_mu_bjet_Cut_v3()
    {
    
      int   pass_cat    = -1 ;
      float dR_check1   = -1.0 ;
      float eta1  = 0.0 , phi1 = 0.0, eta2 = 0.0, phi2 = 0.0;
      int   topbjet     = -1  ;
      int   b2          = -1 ;

      eta1  = (*muEta)[Tprime_muon];
      phi1  = (*muPhi)[Tprime_muon];
     
      for( int h =0 ; h < b_jet.size() ; h ++ ){
          if ( topbjet != -1 ) continue ;
    
          b2    =  b_jet[h] ;          
    
          eta2  = (*jetEta)[b2] ;
          phi2  = (*jetPhi)[b2] ;    
    
          dR_check1 = dR_Calculator(eta1, phi1, eta2, phi2) ;
    
          if ( dR_check1 < 1.5 ) {
              topbjet          = b2 ;
            }
       }   
    
      return topbjet ;

    }
    

//========================================================================///////////////////////      
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void Tau42_Cut_Apply() {

   const  Int_t cut = 21 , index = 4;
   float Tau42_Cut_loc[cut] =  { 0.0, 1.0, 0.95, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65, 0.6, 0.55, 0.5, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05};

   int jet_idx = n_AK8Jet[0] ;
   
   float cut_tau = -1.0 ;

   // if ( ((*AK8puppiSDMass)[jet_idx] >= 90.0 && (*AK8puppiSDMass)[jet_idx] <= 140.0 ) ) Cut_Efficiency_Flow->Fill(5.5,factor);      // for SDmass cut bin  //               
   
   float puppitau = ((*AK8puppiTau4)[jet_idx]/(*AK8puppiTau2)[jet_idx]) ;

   // Cut_Tau42_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
   
   for (int i = 1; i < cut; i++)
    {

      cut_tau = Tau42_Cut_loc[i] ;
      
     if(  puppitau < cut_tau ) Cut_Tau42_Flow->Fill(i, factor);  

    }

} 

void pTHiggs_Cut_Apply( int cut_idx, int cut_idx2) {

   const  Int_t cut = 7 , index = 4;
   float pT_Cut_loc[cut] = {  200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0} ;

   int jet_idx = n_AK8Jet[0] ;
   
   float cut_pT = -1.0 ;

   float pT_higgs = (*AK8JetPt)[jet_idx] ;
               

   Cut_pTHiggs_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
   Cut_Tau42_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER
   Cut_SDMass_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

   
   for (int i = (cut_idx -1); i < cut_idx; i++)
    {
      //cut_idx is index of pT cut you want to apply, to check whole range, replace cut_idx to 1
      cut_pT = pT_Cut_loc[i] ;
      
     if( pT_higgs  > cut_pT ) {
      
      Cut_pTHiggs_Flow->Fill(i, factor);  
      SDMass_Cut_Apply(cut_idx2) ;

      }

    }

} 

void SDMass_Cut_Apply(int cut_idx2) {

   const  Int_t cut = 8 , index = 4;
   float SDMass_Cut_loc[cut] = { 50.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0} ;

   int jet_idx = n_AK8Jet[0] ;
   
   float cut_SD = -1.0 ;

   float SDMass =  (*AK8puppiSDMass)[jet_idx] ;

   // if ( ((*AK8puppiSDMass)[jet_idx] >= 90.0 && (*AK8puppiSDMass)[jet_idx] <= 140.0 ) ) Cut_Efficiency_Flow->Fill(5.5,factor);      // for SDmass cut bin  //               
   
   

   // Cut_SDMass_Flow->Fill(0.5, factor); // fOR NO CUT BIN .... OKAY JUST REMEBER

  if ( SDMass < 150.0) {   
   for (int i = cut_idx2-1; i < cut_idx2 ; i++)
    {

      cut_SD = SDMass_Cut_loc[i] ;
      
     if(  SDMass > cut_SD ) {
      Cut_SDMass_Flow->Fill(i, factor);  
        Tau42_Cut_Apply();
       } 
    }
  }  
}


int MET_Cut_Apply(float cut_val) {

    int pass = -1 ;
    // float cut_val = METCut[vr -1] ;

    if ( pfMET > cut_val)   pass = 1 ;


    return pass ;


}



int Pt_Bjet_Cut_Apply(int var) {
    int cut_pass = -1 ;
    int bjet = b_jet[0];
    float cut = Pt_Bjet_Cut[var -1] ;

    if ( (*jetPt)[bjet] > cut ) cut_pass = 1 ;
    

    return cut_pass ;

}


void Scalar_Sum_pT_Function()
{
  
  Scalar_Sum_pT =  pfMET ;

  int    b2 = n_Mu[0];

  Scalar_Sum_pT += (*muPt)[b2]  ;

  // for (int j = 0 ; j < n_jet.size() ; j ++) {
  //   b2 =  n_jet[j];
  //   Scalar_Sum_pT += (*jetPt)[b2] ;

  // }

  for ( int k = 0 ; k < n_AK8Jet.size() ; k ++) {
    b2 =  n_AK8Jet[k];
    Scalar_Sum_pT += (*AK8JetPt)[b2];
  }

  ST_Sum_Presel -> Fill(Scalar_Sum_pT, factor) ;

  

}

void Scalar_Sum_pT_LeadObj_Function()
{
  
  float  Sum_pT =  pfMET ;

  int    b2     = n_Mu[0];

  Sum_pT += (*muPt)[b2]  ;

  b2            = b_jet[0];

  Sum_pT += (*jetPt)[b2] ;

  b2            = Higgsjets[0];

  Sum_pT += (*AK8JetPt)[b2];

  ST_Sum_LeadObj ->Fill( Sum_pT, factor) ;
  

}


int St_Cut_Apply(float cut)
{

   // int higgs    = CatI_Objects[1] ;
   // int topbjet  = CatI_Objects[2] ;
   // int topmu    = CatI_Objects[3] ;

   int pass   = 1 ;
   int passMT = 1 ;
   // int index = vr ;
   // float St     =  (*AK8JetPt)[higgs] + (*jetPt)[topbjet] + (*muPt)[topmu] +  pfMET ;
   float St     =  Scalar_Sum_pT ;   
   // float cut    =  St_Cut[index] ;

   // if ( vr == 11) passMT = MET_Cut_Apply(2);
   if ( St < cut ) pass = -1 ;   

   // if ( passMT != 1 || pass != 1 ) pass = -1 ;

   return pass ;
   

} 


void St_MET_Cut_Apply_v2()
{

   const  Int_t cut = 6 , index = 4;
   float St_Cut_loc[cut] = { 0.0, 400.0, 500.0, 600.0, 700.0, 800.0} ;
   float MET_Cut_loc[index] = { 0.0, 50.0, 100.0, 150.0} ;

   // int higgs    = CatI_Objects[1] ;   // Relax it when calculating object from category I
   // int topbjet  = CatI_Objects[2] ;
   // int topmu    = CatI_Objects[3] ;

   int pass = -1 ;
   
   // float St     =  (*AK8JetPt)[higgs] + (*jetPt)[topbjet] + (*muPt)[topmu] +  pfMET ;
   float St     =  Scalar_Sum_pT ;
   float cut_ST    =  0.0 ;
   float cut_MT    =  0.0 ;


   for (int i = 0; i < cut; i++)
    {

      cut_ST = St_Cut_loc[i] ;
      
     if(  St > cut_ST ) Cut_ST_Cut_Flow->Fill(i, factor);  

    }

   for ( int j = 0; j < index ; j ++) 
   {
     cut_MT = MET_Cut_loc[j] ;

     if (  pfMET  > cut_MT ) Cut_MET_Cut_Flow->Fill(j , factor);
   }


} 

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////AUXILLARY FUNCTIONS FOR  TESTING ////////////////////////////

std::map<std::string,TString> Sample_Type_Jet = {  // to check whether jet type is from signal or from background
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  "Higgs"          },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  "Higgs"          },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  "Higgs"          },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "Top"            }, 
                                                               // { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "TopWboson"         }, 
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   "udscquark"      },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  "udscquark"      },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  "udscquark"      },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  "udscquark"      },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  "udscquark"      },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  "udscquark"      },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 "udscquark"      },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 "udscquark"      } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  "Wboson"         } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            "Zboson"         } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           "Zboson"         } ,   
                                                 } ;  


void Gen_Parent_Check(){

  
  TLorentzVector Parent, daughter1, daughter2, daughter3, daughter4;
  int idx = -1 ;
  bool pass = false ;


  
    if ( jet_type == "Higgs"){  // for higgs matched jet
       if (  gen_Wboson.size() == 2  && gen_udscquark.size() == 4 ){

        // cout <<"\n No it don't";

        gen_jet_object = gen_Wboson[0];
        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin
        AK8Jet_Gen_Match(gen_jet_object, "Yes") ;

        //for calculating parent mass from decay products
        for (int i = 0; i < 4; ++i)
        {
          idx = gen_udscquark[i] ;
          daughter1.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);
          Parent += daughter1;
        }

        Parent_Mass = Parent.M();

       }
    }
  

    if ( jet_type == "Top"){  // for top matched jets
       if (  gen_udscquark.size() == 2 && gen_bquark != -1 ){
// gen_Wboson.size() == 1  &&
        gen_jet_object = gen_bquark;
        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin  
        AK8Jet_Gen_Match(gen_jet_object, "Yes") ;


        //for calculating parent mass from decay products
        for (int i = 0; i < 2; ++i)
        {
          idx = gen_udscquark[i] ;
          daughter1.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);
          Parent += daughter1;
        }

        daughter2.SetPtEtaPhiE (  (*mcPt)[gen_bquark], (*mcEta)[gen_bquark], (*mcPhi)[gen_bquark], (*mcE)[gen_bquark]);
        Parent += daughter2 ;
        Parent_Mass = Parent.M();

       }
       }
    

    if ( jet_type == "TopWboson"){  // for Wtop matched jets
       if ( gen_jet_object != -1 && gen_topquark  != -1  && gen_udscquark.size() == 2 && gen_bquark != -1 ){

        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin
        AK8Jet_Gen_Match(gen_jet_object, "Yes") ;

        //for calculating parent mass from decay products
        for (int i = 0; i < 2; ++i)
        {
          idx = gen_udscquark[i] ;
          daughter1.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);
          Parent += daughter1;
        }

        Parent_Mass = Parent.M();        

       }
    }

    if ( jet_type == "udscquark"){  // for qcd matched jets
       if ( gen_jet_object != -1 ){

        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin
        AK8Jet_Gen_Match(gen_jet_object, "No") ;
        Parent.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);

        Parent_Mass = Parent.M();

       }
    }

    if ( jet_type == "Wboson"){  // for W matched jets
       // if ( gen_jet_object != -1 && gen_udscquark.size() == 4 ){}

       if ( gen_jet_object != -1 ){

        // cout <<"No it don't";
        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin
        AK8Jet_Gen_Match(gen_jet_object,  "No") ;

        Parent.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);

        Parent_Mass = Parent.M(); 

       }

       
    }

    if ( jet_type == "Zboson"){  // for Z matched jets
       // if ( gen_jet_object != -1  && gen_udscquark.size() == 2 ){}

       if ( gen_jet_object != -1 ){

        Cut_Higgs_Tagging_Flow->Fill(1.5,factor);      // for No cut bin
        AK8Jet_Gen_Match(gen_jet_object, "No") ;

        Parent.SetPtEtaPhiE( (*mcPt)[idx], (*mcEta)[idx], (*mcPhi)[idx], (*mcE)[idx]);

        Parent_Mass = Parent.M();
       }

       
    }

}


void AK8Jet_Gen_Match(int gen_jet, TString mom ){

  float eta1 = -1.0;
  float phi1 = -1.0;
  float eta2 = -1.0;
  float phi2 = -1.0;

  if ( mom == "No"){
    eta2 = (*mcEta)[gen_jet];
    phi2 = (*mcPhi)[gen_jet];
  }
  
  if (mom == "Yes")
  {
   eta2 = (*mcMomEta)[gen_jet];
   phi2 = (*mcMomPhi)[gen_jet];
  }

  bool pass = false ;
  
  for(int f = 0 ; f <  nAK8Jet ; f ++)    {
          
       // if( var1 == 1 ) n_AK8Jet.push_back(f) ;
       if( pass == 1) continue;
       if((*AK8JetPt)[f] <= 200.0 )      continue ;
       if(fabs((*AK8JetEta)[f]) >= 2.4 ) continue;
       if((*AK8JetPFLooseId)[f] != 1 )   continue ; 

       eta1 = (*AK8JetEta)[f];
       phi1 = (*AK8JetPhi)[f];                   

       if ( dR_Calculator( eta1, phi1, eta2, phi2) > 0.4)  continue;
       pass = true ;
        n_AK8Jet.push_back(f) ; 
        // cout <<"No it don't";

  }
 
}



void  SD_Mass_Check_Correction ( int index ) {
    
    int pass_jet = -1 ;
  
  
    double SD_mass          =  (*AK8puppiSDMass)[index] ;
    double pt               =  (*AK8JetPt)[index] ; 
    float  eta              =  (*AK8JetEta)[index] ; 
    double corr_SD          =  0.0 ;
    
  
   
      corr_SD               =  getPUPPIweight(pt, eta) ;
 
      Higgs_SDMassCorr      =  corr_SD * SD_mass ;
  
      // if( SD_mass >=  90.0 && SD_mass <= 140.0 ) {
  
      //   pass_jet                   =   1 ;
      //   Higgs_SDMassCorr           =   SD_mass ;

      // }  
  
      // return pass_jet ;  

}

void Fill_Gen_Matched_AK8Jet( int pass_jet) {

         int id  = 12 ;
         int idx = 0  ;
         float ptau1 = 0.0 ;
         float puppi_mass = 0.0 , CHS_mass = 0.0 ; 

         int Hsize        =   Higgsjets.size()  ;
         // h_object_no.at(2) ->Fill(n_AK8Jet.size() ,factor) ;
         h_object_no.at(2) ->Fill(Hsize ,factor) ;

         Hsize  = ( Higgsjets.size() >= 2) ? 2 : Higgsjets.size() ;
         // Hsize  = 1 ;
         for (int k = 0 ; k < Hsize ; k ++ ) {         

              pass_jet = Higgsjets[k] ;
              // h_Parent_Mass ->Fill(Parent_Mass, factor);

              Gen_Match_Jet_Pt  ->Fill((*AK8JetPt)[pass_jet] ,factor);  
              h_object_pt.at(id+k) ->Fill((*AK8JetPt)[pass_jet] ,factor); 
              h_object_eta.at(id+k) ->Fill((*AK8JetEta)[pass_jet] ,factor);

              h_AK8_PUPPImass.at(idx+k) -> Fill((*AK8JetMass)[pass_jet] ,factor);

              // h_AK8_PUPPISDmass.at(idx) -> Fill((*AK8puppiSDMass)[pass_jet] ,factor);
              h_AK8_PUPPISDmass.at(idx+k) -> Fill(Higgs_SDMassCorr ,factor);

              // h_AK8_PUPPIvsmass.at(idx) -> Fill((*AK8puppiSDMass)[pass_jet],(*AK8JetMass)[pass_jet] ,factor);
              // h_AK8_PUPPIvsmass.at(idx+k) -> Fill( Higgs_SDMassCorr ,(*AK8JetMass)[pass_jet] ,factor);

              h_AK8_PUPPIvsmass.at(idx+k) -> Fill( (*AK8JetPt)[pass_jet] ,Higgs_SDMassCorr ,factor);


              ptau1 = ((*AK8puppiTau2)[pass_jet]/(*AK8puppiTau1)[pass_jet]) ;
              h_AK8_PUPPItau21.at(idx+k) -> Fill(ptau1 ,factor);
              ptau1 = ((*AK8puppiTau3)[pass_jet]/(*AK8puppiTau2)[pass_jet]) ;
              h_AK8_PUPPItau32.at(idx+k) -> Fill(ptau1 ,factor);
              ptau1 = ((*AK8puppiTau3)[pass_jet]/(*AK8puppiTau1)[pass_jet]) ;
              h_AK8_PUPPItau31.at(idx+k) -> Fill(ptau1 ,factor);

              ptau1 = ((*AK8puppiTau4)[pass_jet]/(*AK8puppiTau1)[pass_jet]) ;
              h_AK8_PUPPItau41.at(idx+k) -> Fill(ptau1 ,factor);
              ptau1 = ((*AK8puppiTau4)[pass_jet]/(*AK8puppiTau2)[pass_jet]) ;
              h_AK8_PUPPItau42.at(idx+k) -> Fill(ptau1 ,factor);
              dPt_dR_muqjet->Fill( ptau1,(*AK8puppiSDMass)[pass_jet],factor);

              ptau1 = ((*AK8puppiTau4)[pass_jet]/(*AK8puppiTau3)[pass_jet]) ;
              h_AK8_PUPPItau43.at(idx+k) -> Fill(ptau1 ,factor);

              dRPlots_ak4_ak8Jet_v2( pass_jet, k) ;
         }


             
}



std::map<std::string,TString> Sample_Type_Muon = {  // to check whether muon is from signal or from background
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  "PromptLepton"   },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  "PromptLepton"   },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  "PromptLepton"   },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "PromptLepton"   }, 
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   "FakeLepton"     },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  "FakeLepton"     },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  "FakeLepton"     },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  "FakeLepton"     },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  "FakeLepton"     },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  "FakeLepton"     },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 "FakeLepton"     },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  "FakeLepton"     } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            "FakeLepton"     } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           "FakeLepton"     } ,                                                                
                                                               { "list_of_Bkgfiles/ST_s-channel_4f_leptonDecays_v3_",               "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays_v3_",    "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_t-channel_top_4f_inclusiveDecays_v3_",        "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_tW_antitop_5f_inclusiveDecays_v3_",           "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_tW_top_5f_inclusiveDecays_v3_",               "FakeLepton"     }
                                                 } ;   



bool   Muon_Gen_Match (int c_muon) {

   bool match = true ;

   if ( (*muCharge)[c_muon] != ((*mcPID)[top_Mu] / (-13) )) match = false ;

   float eta1       = (*muEta)[c_muon];
   float phi1       = (*muPhi)[c_muon];
   float pT1        = (*muPt) [c_muon];

   float eta2       = (*mcEta)[top_Mu];
   float phi2       = (*mcPhi)[top_Mu];
   float pT2        = (*mcPt) [top_Mu];

   float dpT        = (fabs( pT1 - pT2) / pT2 );
   float dR_min        = dR_Calculator(eta1, phi1, eta2, phi2) ;
   dPt_dR_muqjet->Fill( dpT,dR_min);

   if( dR_min > 0.1 ) match = false ;
   if( dpT > 0.3 ) match = false ; 

   // if(match == true) {
   // cout << " We have mucharge = " << (*muCharge)[c_muon] << "  and gen muCharge = " << ((*mcPID)[top_Mu] / (-13) ) << " and rel. pT = " << dpT << " and deltaR = " << dR <<endl ;
   // }

   return match ;
}

void   Fill_Gen_Matched_Muon(int mu){

  
  Match_Muon_Eta       ->Fill((*muEta)[mu]);
  Match_Muon_Pt300     ->Fill((*muPt)[mu]);
  // Match_Muon_Pt1000    ->Fill((*muHighpTID_BestTrkPt)[mu]);
     
  Match_Muon_Phi       ->Fill((*muPhi)[mu]);
  Match_Primary_Vertex ->Fill( nGoodVtx) ;

}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// for Plotting of Histograms==============================
////////////////////////////////////////////////////////////////////////////////////////////////////////


void Fill_RecoObject(int mu , TString fill ) {
   //   id for defining particle type, MET = 0, mu= 1, AK4bjet = 2, AK4qjet = 4, AK4forwjet = 6, puppibjet = 7, puppiqjet = 9, puppiforwjet = 11
   //   AK8jet= 12(W) , 
   int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
   int Asize   = ( n_AK8Jet.size() >= 3) ? 3 : n_AK8Jet.size() ;    
   int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
   int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
   int Qsize   = ( q_jet.size() >= 2 ) ?  2 : q_jet.size() ;
   int Nsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;

   // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
   // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
   // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ; 

   int b2 = -1 ;

   Fill_NPtEta_Histo(0, 0, 0) ;                                     // for MET & object population


   if( fill == "After topmu") {
     
     b2 = mu ;
     Fill_NPtEta_Histo(1, b2, 0) ;        // for particularly selected muon after Lepton Isoaltion
     // RecoPlots_dRHisto_v2(b2) ;  


   }

   // if( fill == "Before topmu" ) { }
    // for standard filling of muon. Change string value for this options
    for ( int i = 0; i < Msize; i ++)
    {    b2 = n_Mu[i] ;
         Fill_NPtEta_Histo(1, b2, i) ;
         // Match_Muon_Pt300     ->Fill((*muPt)[b2], factor);  // for cut selections
    }
   
   
   for ( int i = 0; i < Bsize; i ++)
   {    b2 = b_jet[i] ;
        Fill_NPtEta_Histo(2, b2, i) ;
   }

   if ( fill == "Before Higgs"){
   for ( int i = 0; i < Asize; i ++) {
        b2 = n_AK8Jet[i] ;
//      if ( WtagMatch(b2) == -1) ;
        if ( (*AK8JetPt)[b2] > 20.0)Fill_NPtEta_Histo(12,b2,i) ;
   }
   }

   for ( int i = 0; i < Fsize; i ++)
   {    b2 = n_forwjet[i] ;
        Fill_NPtEta_Histo(6, b2, i) ;
   }

   for ( int i = 0; i < Qsize; i ++)
   {    
;
        b2 = q_jet[i] ;
        Fill_NPtEta_Histo(8, b2, i) ;
   }


   for ( int i = 0; i < Nsize; i ++)
   {   
        b2 = n_jet[i] ;
        Fill_NPtEta_Histo(4, b2, i) ;
   }

   // for ( int i = 0; i < P_qsize; i ++)
   // {    b2 = puppin_jet[i] ;
   //      Fill_NPtEta_Histo(9, b2, i) ;
   // }

   // for ( int i = 0; i < P_fsize; i ++)
   // {    b2 = puppin_forwjet[i] ;
   // {    b2 = puppin_forwjet[i] ;
   //      Fill_NPtEta_Histo(11, b2, i) ;
   // }

   // RecoPlots_dRHisto_v2(0) ;  //skip for just delta r distribution
   RecoPlots_dRHisto() ;     // skip it for dR_Check_step2
}


void   Fill_NPtEta_Histo(int id, int en, int idx)
   {
      float ptau1 = 0.0 ;
      float puppi_mass = 0.0 , CHS_mass = 0.0 ; 

      double muon_scale_factor = muon_ID_factor * factor ;
      //   id for defining particle type, MET = 0, mu= 1, AK4bjet = 2, AK4qjet = 4, AK4forwjet = 6, puppibjet = 7, puppiqjet = 9, puppiforwjet = 11
      //   AK8jet= 12(W) , 
      if (id == 0) {
        h_object_no.at(0) ->Fill(n_Mu.size() ,factor);
        h_object_no.at(1) ->Fill(b_jet.size() ,factor);
        // h_object_no.at(2) ->Fill(n_AK8Jet.size() ,factor) ;
        h_object_no.at(3) ->Fill(n_jet.size() ,factor) ;
        h_object_no.at(4) ->Fill(n_forwjet.size() ,factor) ;
        h_object_no.at(5) ->Fill(q_jet.size() ,factor) ;
        // h_object_no.at(6) ->Fill(puppib_jet.size() ,factor) ;
        // h_object_no.at(7) ->Fill(puppin_forwjet.size() ,factor) ;

        h_object_pt.at(0) ->Fill( pfMET ,factor); 
      }

   if ( id == 1){
        h_object_pt.at(idx+id)    ->Fill((*muPt)[en] ,muon_scale_factor); 
        // h_object_pt.at(idx+id)    ->Fill((*muIsoTrk)[en] ,factor); 
        h_object_eta.at(idx+id)   ->Fill((*muEta)[en] ,muon_scale_factor);
   }

   if( id == 2) {
      h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4bjet
      h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
   }

   if( id == 4){
      h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4qjet
      h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
   }

   if( id == 6){
      h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4forwjet
      h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
   }

   if( id == 8){
      h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4forwjet
      h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
   }

       // if( id == 7){
          // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppibjet
          // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
       // }
    
       // if( id == 9){
          // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppiqjet
          // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
       // }
     
       // if( id == 11){
          // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppibjet
          // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
       // }

   if (id == 12 ) {
         
         // for AK8jet       
         h_object_pt.at(idx+id) ->Fill((*AK8JetPt)[en] ,factor); 
         h_object_eta.at(idx+id) ->Fill((*AK8JetEta)[en] ,factor);

         h_AK8_Jetmass.at(idx) -> Fill((*AK8JetCHSMass)[en] ,factor) ;
         h_AK8_PUPPImass.at(idx) -> Fill((*AK8JetMass)[en] ,factor);

         h_AK8_PUPPISDmass.at(idx) -> Fill((*AK8puppiSDMass)[en] ,factor);
         h_AK8_CHSmass.at(idx) -> Fill((*AK8JetCHSMass)[en] ,factor) ;     

         //h_AK8_PUPPIvsmass.at(idx) -> Fill(puppi_mass,(*AK8_puppiMass)[en]) ;
         //h_AK8_CHSvsmass.at(idx) -> Fill(CHS_mass,(*AK8_JetMass)[en]) ;

         ptau1 = ((*AK8puppiTau2)[en]/(*AK8puppiTau1)[en]) ;
         h_AK8_PUPPItau21.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8puppiTau3)[en]/(*AK8puppiTau2)[en]) ;
         h_AK8_PUPPItau32.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8puppiTau3)[en]/(*AK8puppiTau1)[en]) ;
         h_AK8_PUPPItau31.at(idx) -> Fill(ptau1 ,factor);

         ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau1)[en]) ;
         h_AK8_PUPPItau41.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau2)[en]) ;
         h_AK8_PUPPItau42.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau3)[en]) ;
         h_AK8_PUPPItau43.at(idx) -> Fill(ptau1 ,factor);

         ptau1 = ((*AK8Jet_tau2)[en]/(*AK8Jet_tau1)[en]) ;
         h_AK8_tau21.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8Jet_tau3)[en]/(*AK8Jet_tau2)[en]) ;
         h_AK8_tau32.at(idx) -> Fill(ptau1 ,factor);
         ptau1 = ((*AK8Jet_tau4)[en]/(*AK8Jet_tau2)[en]) ;
         h_AK8_CHStau42.at(idx) -> Fill(ptau1 ,factor);
      

   }  

}


void RecoPlots_dRHisto()
{
   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt;
   int b1 = -1, b2 =-1 ;
    //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
    //   AK8jet= 11(W) , 
      int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
      int Asize   = ( n_AK8Jet.size() >= 2) ? 2 : n_AK8Jet.size() ;    // focussing only on first 2 ak8Jet
      int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
      int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
      int Qsize   = ( q_jet.size() >= 2 ) ?  2 : q_jet.size() ;
      int Nsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;


      // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
      // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ;           

    TVector3 vec_lep, vec_jet;
      int id ; 
      
       // for muon w.r.t other jets dR plots
       for ( int h = 0 ; h < Msize ; h ++ ) {

          b1    = n_Mu[h];   
          eta1  = (*muEta)[b1];
          phi1  = (*muPhi)[b1];
          vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;

          // cout <<"\n check1";

          id = 1 ; // for AK4bjet
          for( int g = 0 ; g < Bsize ; g ++ ) {

             b2   = b_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check2";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.  at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);


          }

          id = 3; // for ak4jet
               for( int g = 0 ; g < Nsize ; g ++ ) {

             b2   = n_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check3";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);

          }

          id = 5; // for forw jet      
          for( int g = 0 ; g < Fsize ; g ++ ) {
             
             b2 = n_forwjet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check4";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);

          }


          id = 7; // for qjet collection
          for( int g = 0 ; g < Qsize ; g ++ ) {
             
             b2 = q_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);
             // cout <<"\n checkqjet";

          }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
             
             b2 = n_AK8Jet[g];         
             eta2 = (*AK8JetEta)[b2] ;
             phi2 = (*AK8JetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*AK8JetPt)[b2], (*AK8JetEta)[b2], (*AK8JetPhi)[b2] ) ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->
             Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);
             // cout <<"\n checkAk8jet";

          }  
       }

       // for ak4 bjet w.r.t other ak4jets and AK8jets

       // id = 1 ; // for AK4bjet
       for( int h = 0 ; h < Bsize ; h ++ ) {

              b1    = b_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;
              // cout <<"\n checkbjet  == " << b1;
              // cout <<"\nBsize = " << Bsize << endl ;
            if(h == 0 && Bsize == 2  ){
             b2   = b_jet[h+1];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1).at(h+2)->Fill(dR);
             h_dEta_Reco.at(h+1).at(h+2)->Fill(dEta);


            }

          id = 3; // for ak4jet
          for( int g = 0 ; g < Nsize ; g ++ ) {

             b2   = n_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1)  .at(g+id)->Fill(dR);
             h_dEta_Reco.at(h+1)  .at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h+1)  .at(g+id)->Fill(dPhi);

             // cout <<"\n checkbjetnjet";

            }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
             
             b2 = n_AK8Jet[g];
             eta2 = (*AK8JetEta)[b2] ;
             phi2 = (*AK8JetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h+1).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h+1).at(g+id)->Fill(dPhi);

             // cout <<"\n checkbjetak8jet";

          }


       }


      // for ak4  w.r.t  AK8jets
          
          id = 11 ; // for AK8jet
          for( int h = 0 ; h < Nsize ; h ++ ) {

              b1    = n_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;

              for( int g = 0 ; g < Asize ; g ++ ) {
               
               b2   = n_AK8Jet[g];
               eta2 = (*AK8JetEta)[b2] ;
               phi2 = (*AK8JetPhi)[b2] ;


               dR_Calculator(eta1, phi1, eta2, phi2) ;
               h_dR_Reco  .at(h+3).at(g+id)->Fill(dR , factor);
               h_dEta_Reco.at(h+3).at(g+id)->Fill(dEta , factor);
               h_dPhi_Reco.at(h+3).at(g+id)->Fill(dPhi , factor);
               // cout <<"\n checkak4jetak8jet";

              }
              
          }

          // for qjet  w.r.t  AK8jets
          
          id = 11 ; // for AK8jet
          for( int h = 0 ; h < Qsize ; h ++ ) {

              b1    = q_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;

              for( int g = 0 ; g < Asize ; g ++ ) {
               
               b2   = n_AK8Jet[g];
               eta2 = (*AK8JetEta)[b2] ;
               phi2 = (*AK8JetPhi)[b2] ;

               dR_Calculator(eta1, phi1, eta2, phi2) ;
               h_dR_Reco  .at(h+7).at(g+id)->Fill(dR , factor);
               h_dEta_Reco.at(h+7).at(g+id)->Fill(dEta , factor);
               h_dPhi_Reco.at(h+7).at(g+id)->Fill(dPhi , factor);
               // cout <<"\n checkqjetak8jet";

              }
              
          }

}


void RecoPlots_dRHisto_v2(int mu)
{
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt;
      int b1 = -1, b2 =-1 ;
      //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
      //   AK8jet= 11(W) , 
      int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
      int Asize   = ( n_AK8Jet.size() >= 2) ? 2 : n_AK8Jet.size() ;    // focussing only on first 2 ak8Jet
      int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
      int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
      int Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;

      // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
      // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ;           

      TVector3 vec_lep, vec_jet;
      int id ; 
      // cout << "\n Check 1 ";
      // for muon w.r.t other jets dR plots


      b1    = mu;   
      eta1  = (*muEta)[b1];
      phi1  = (*muPhi)[b1];
      vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;
      int h = 0 ;
      id = 1 ; // for AK4bjet
      for( int g = 0 ; g < Bsize ; g ++ ) {

         b2   = b_jet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor );


      } // end loop for bjets

      id = 3; // for ak4qjet
      for( int g = 0 ; g < Qsize ; g ++ ) {

         b2   = n_jet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      } // end loop for qjets

      id = 5; // for forw jet      
      for( int g = 0 ; g < Fsize ; g ++ ) {
         
         b2 = n_forwjet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      } //end loop for forwjets


      id = 11 ; // for AK8jet
      for( int g = 0 ; g < Asize ; g ++ ) {
         
         b2 = n_AK8Jet[g];         
         eta2 = (*AK8JetEta)[b2] ;
         phi2 = (*AK8JetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*AK8JetPt)[b2], (*AK8JetEta)[b2], (*AK8JetPhi)[b2] ) ;


         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      }  // end loop for AK8jets

      // for ak4 bjet w.r.t other ak4jets and AK8jets
      
      id = 1 ; // for AK4bjet
      for( h = 0 ; h < Bsize ; h ++ ) {

          b1    = b_jet[h];
          eta1  = (*jetEta)[b1] ;
          phi1  = (*jetPhi)[b1] ;

          if(h == 0 && Bsize == 2){
           b2   = b_jet[h+1];
           eta2 = (*jetEta)[b2] ;
           phi2 = (*jetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco.at(h+id).at(h+id+1)  ->Fill(dR , factor);
           h_dEta_Reco.at(h+id).at(h+id+1)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+id).at(h+id+1)->Fill(dPhi , factor);
          }

          
          id = 3; // for ak4qjet
          for( int g = 0 ; g < Qsize ; g ++ ) {

           b2   = n_jet[g];
           eta2 = (*jetEta)[b2] ;
           phi2 = (*jetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco  .at(h+1) .at(g+id)->Fill(dR , factor);
           h_dEta_Reco.at(h+1)  .at(g+id)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+1)  .at(g+id)->Fill(dPhi , factor);

          }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
           
           b2 = n_AK8Jet[g];
           eta2 = (*AK8JetEta)[b2] ;
           phi2 = (*AK8JetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco  .at(h+1).at(g+id)->Fill(dR , factor);
           h_dEta_Reco.at(h+1).at(g+id)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+1).at(g+id)->Fill(dPhi , factor);

          }
          

      }
      


}


float dRPlots_ak4_ak8Jet( int b1, int b2, int idx) {
  // Temporary function to plot dR b/w ak8jet(b2) and ak4Jet(b1) and in histo of index idx 

   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;
   int id = 11; // id = 11 for ak8Jet

          eta1  = (*jetEta)[b1] ;
          phi1  = (*jetPhi)[b1] ;
           
          eta2 = (*AK8JetEta)[b2] ;
          phi2 = (*AK8JetPhi)[b2] ;

          dR_Calculator(eta1, phi1, eta2, phi2) ;

          return dR ;

}      

void dRPlots_ak4_ak8Jet_v2( int b2 , int idx) {
  // Temporary function to plot dR b/w ak8jet(b2) and ak4Jet(b1) and in histo of index idx 

   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;
   int b1 = -1 ;

   eta2 = (*AK8JetEta)[b2] ;
   phi2 = (*AK8JetPhi)[b2] ;
   int Bsize   = ( b_jet.size() >= 3 ) ?  3 : b_jet.size() ;
   // int Qsize   = ( q_jet.size() >= 3 ) ?  3 : q_jet.size() ;
   // int Qsize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

        for( int h = 0 ; h < Bsize ; h ++ ) {

          // b1    = n_jet[h];
          // b1    = q_jet[h];          
          b1    = b_jet[h];          
          eta1  = (*jetEta)[b1] ;
          phi1  = (*jetPhi)[b1] ;

          dR_Calculator(eta1, phi1, eta2, phi2) ;

          // h_dR_ak41_ak8Jet1 ->Fill(dR , factor);
          // cout << "\n dR_check2 = " << dR << " for jet index = " << b1;

          // continue ;

          if ( idx == 0) {
             // if(h == 0)h_dR_ak41_ak8Jet1 ->Fill(dR , factor);
             if(h == 1)h_dR_ak42_ak8Jet1 ->Fill(dR , factor);
             if(h == 2)h_dR_ak43_ak8Jet1 ->Fill(dR , factor);
          }
      
          if ( idx == 1) {
             if(h == 0) h_dR_ak41_ak8Jet2 ->Fill(dR , factor);
             if(h == 1) h_dR_ak42_ak8Jet2 ->Fill(dR , factor);
             if(h == 2) h_dR_ak43_ak8Jet2 ->Fill(dR , factor);
          }
        }  
}       


void ak4jet_Higgs_dR_check(int Higgs, int var){
  
  // After this step only those ak4jet are remained for those, dR(ak4jet, Higgjet) >1.2 and stored into q_jet collection
  // Then bjets are selected from them into b_jet collection

  int ak4jet = -1 ;
  float  DeltaR = 0.0 ;

  for ( int j = 0 ; j <  n_jet.size() ; j ++) {

        ak4jet =  n_jet[j];
        DeltaR =  dRPlots_ak4_ak8Jet( ak4jet, Higgs, j)  ;          
        if ( DeltaR > 1.200 )  {
             q_jet.push_back(ak4jet)  ; 
             Cut_bjet_After_drCheck(ak4jet, var) ;         ;
             // cout << "\n dR_check1 = " << DeltaR << " for jet index = " << ak4jet;
        }     
  }

}

void bjet_Higgs_dR_check(int Higgs){
  
  // After this step only those ak4jet are remained for those, dR(ak4jet, Higgjet) >1.2 and stored into q_jet collection
  // Then bjets are selected from them into b_jet collection

  int ak4jet = -1 ;
  float  DeltaR = 0.0 ;
  Tprime_bjet = -1 ;

  for ( int j = 0 ; j <  b_jet.size() ; j ++) {

        if ( Tprime_bjet != -1 ) continue ;
        ak4jet =  b_jet[j];
        DeltaR =  dRPlots_ak4_ak8Jet( ak4jet, Higgs, j)  ;          
        if ( DeltaR < 1.200 ) continue ;
        Tprime_bjet = ak4jet ;
        h_dR_ak41_ak8Jet1 ->Fill(DeltaR , factor);
             // cout << "\n dR_check1 = " << DeltaR << " for jet index = " << ak4jet;    
  }

}
//////////////////////////////////////////////////////////////////////////////////////////
// filling of histograms for tagged jets =================================================
///////////////////////////////////////////////////////////////////////////////////////////

void  Higgsjet_Plots( ) 
{
   int j = -1 ;
   int fill = -1 ;
   int Pt_idx = 3; //for dPt w.r.t muon plots
   int t2 = -1 ;
   int t3 = -1 ;     
   float  tau = 0.0 ;
   float  tau1 = 0.0 ;
   float mass_puppi = 0.0;
   float max = 0.0 ;
   float min = 0.0 ;
   // double SD_mass  = 0.0 ;        
   // double corr_SD  = 0.0 ;        

   TLorentzVector  Ws ;
   int Hsize        =   Higgsjets.size()  ;
   if ( Hsize != 0 )  h_tag_N.at(2)     ->Fill(Hsize ,factor) ;

    Hsize  = ( Higgsjets.size() >= 1) ? 1 : Higgsjets.size() ;
   for (int k = 0 ; k < Hsize ; k ++ ) {

              t2   =   Higgsjets[k] ;
              h_tag_Pt.at(k+3)  -> Fill((*AK8JetPt)[t2]  ,factor) ;
              h_tag_Eta.at(k+3) -> Fill((*AK8JetEta)[t2] ,factor) ; 
        
              h_tag_Pruned.at(k+3)     ->Fill((*AK8JetCHSPrunedMass)[t2] ,factor) ;


              h_tag_SD.at(k+3)         ->Fill(Higgs_SDMassCorr ,factor) ;

              h_AK8_PUPPIvsmass.at(k)  -> Fill( (*AK8JetPt)[t2] ,Higgs_SDMassCorr ,factor);


              tau =  ((*AK8puppiTau2)[t2]/(*AK8puppiTau1)[t2]) ;
              h_tag_Puppitau21.at(k+3) -> Fill(tau ,factor) ;
              tau =  ((*AK8puppiTau3)[t2]/(*AK8puppiTau2)[t2]) ;
              h_tag_Puppitau32.at(k+3) -> Fill(tau ,factor) ;
              tau =  ((*AK8puppiTau4)[t2]/(*AK8puppiTau2)[t2]) ;
              h_tag_Puppitau42.at(k+3) -> Fill(tau ,factor) ;
        
              tau =  ((*AK8puppiTau2)[t2]/(*AK8puppiTau1)[t2]) ;
              h_tag_tau21.at(k+3)  -> Fill(tau ,factor ) ;
              tau =  ((*AK8puppiTau3)[t2]/(*AK8puppiTau2)[t2]) ;
              h_tag_tau32.at(k+3)  -> Fill(tau ,factor) ;

              // tau =  ((*AK8Jet_tau4)[t2]/(*AK8Jet_tau4)[t2]) ;
              // h_tag_CHStau42.at(k+3)  -> Fill(tau ,factor) ;
        
              mass_puppi = (*AK8JetMass)[t2];
              h_tag_PUPPImass.at(k+3) ->Fill(mass_puppi ,factor);
        
              //Ws.SetPtEtaPhiE((*AK8_JetPt)[t2],(*AK8_JetEta)[t2],(*AK8_JetPhi)[t2],(*AK8_JetEn)[t2]);
              // mass_puppi = (*AK8JetCHSMass)[t2] ;
              mass_puppi    = Ws.M(); 
              h_tag_Mass.at(k+3) ->Fill(mass_puppi ,factor);
     }



         // h_AK8_PUPPISDmass.at(idx) -> Fill((*AK8puppiSDMass)[pass_jet] ,factor);

         // h_AK8_PUPPIvsmass.at(idx) -> Fill((*AK8puppiSDMass)[pass_jet],(*AK8JetMass)[pass_jet] ,factor);
} 


void  Wjet_Plots( int bjet)
{
   
   int   j = -1 ;
   int   t2 = -1 ;
   int   t3 = -1 ;
   float tau = 0.0 ;
   float tau1 = 0.0 ;
   float mass_puppi = 0.0 ;
   float max = 0.0 ;
   float min = 0.0 ;
   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0;
   TLorentzVector  Ws ;

   int Wsize        =   W_boson.size()  ;
   if ( Wsize != 0 )  h_tag_N.at(0)    ->Fill(Wsize) ;


   Wsize  = ( W_boson.size() >= 2) ? 2 : W_boson.size() ;

   for (int k = 0 ; k < Wsize ; k ++ ) {


      t2    =     W_boson[k] ;

      h_tag_Pt.at(k)  -> Fill((*AK8JetPt)[t2]) ;
      h_tag_Eta.at(k) -> Fill((*AK8JetEta)[t2]) ; 

      h_tag_Pruned.at(k)     ->Fill((*AK8JetCHSPrunedMass)[t2]);
      h_tag_SD.at(k)         ->Fill((*AK8puppiSDMassL2L3Corr)[t2]);

      tau =  ((*AK8puppiTau2)[t2]/(*AK8puppiTau1)[t2]) ;
      h_tag_Puppitau21.at(k) -> Fill(tau) ;
      tau =  ((*AK8puppiTau3)[t2]/(*AK8puppiTau2)[t2]) ;
      h_tag_Puppitau32.at(k) -> Fill(tau) ;
      tau =  ((*AK8puppiTau4)[t2]/(*AK8puppiTau2)[t2]) ;
      h_tag_Puppitau42.at(k) -> Fill(tau) ;

      tau =  ((*AK8Jet_tau2)[t2]/(*AK8Jet_tau1)[t2]) ;
      h_tag_tau21.at(k)  -> Fill(tau) ;
      tau =  ((*AK8Jet_tau3)[t2]/(*AK8Jet_tau2)[t2]) ;
      h_tag_tau32.at(k)  -> Fill(tau) ;

      tau =  ((*AK8Jet_tau4)[t2]/(*AK8Jet_tau4)[t2]) ;
      h_tag_CHStau42.at(k)  -> Fill(tau) ;

      mass_puppi = (*AK8JetMass)[t2];
      h_tag_PUPPImass.at(k) ->Fill(mass_puppi);

      //Ws.SetPtEtaPhiE((*AK8_JetPt)[t2],(*AK8_JetEta)[t2],(*AK8_JetPhi)[t2],(*AK8_JetEn)[t2]);
      mass_puppi = (*AK8JetCHSMass)[t2] ;
      h_tag_Mass.at(k) ->Fill(mass_puppi);
   

   // for dR plots in Wjets
     if (k == 1){

     eta1  = (*AK8JetEta)[t2] ;
      phi1  = (*AK8JetPhi)[t2];
     
     t3    = W_boson[k-1];
     eta2  = (*AK8JetEta)[t3] ;
      phi2  = (*AK8JetPhi)[t3];
      
      dR_Calculator(eta1, phi1, eta2, phi2) ;
      h_dR_tagjet.at(k-1).at(k) ->Fill(dR) ;

      }  
   }
}

// Generalised function to sort Higgs jet collection 
void Jet_Sorting( TString jet)
{

    int   j   = -1 ;
    int   t2  = -1 ;
    int   t3  = -1 ;     
    float max = 0.0 ;
    float min = 0.0 ;
    int   Jetsize = 0 ;

    if ( jet == "Higgs"){
    
      Jetsize        =   Higgsjets.size()  ;
        for (int k = 0 ; k < Jetsize ; k ++ ){
         for ( int h = k+1 ; h < Jetsize ; h++)
         {
             t2      =     Higgsjets[k] ;
             j       =     t2  ;
             min     =     fabs((*AK8puppiSDMassL2L3Corr)[t2] - 125.0 ); 
             t3      =     Higgsjets[h] ;
             max     =     fabs((*AK8puppiSDMassL2L3Corr)[t3]- 125.0 ) ; 
             if(min > max){
                  Higgsjets[k] = t3 ;
                  Higgsjets[h] = t2 ;
             }
         }
      
      }
    }


}

// DeltaR calculation and plotting for muon & bjet w.r.t to heavy jets

void dR_TagJets_objects( ) 
{
    float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt;
    int b1 = -1, b2 =-1 ;
     //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
    //   AK8jet= 11(W) , 
       int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
       int Hsize   = (Higgsjets.size() >= 1) ? 1 : Higgsjets.size() ;    
       int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
       int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      

    TVector3 vec_lep, vec_jet;
         int id, leadH ; 
       
    // for muon w.r.t other jets dR plots
    for ( int h = 0 ; h < Msize ; h ++ ){

      b1    = n_Mu[h];   
      eta1  = (*muEta)[b1];
      phi1  = (*muPhi)[b1];
      vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;

      if (Hsize == 1 ){
        leadH = Higgsjets[0];
        eta2  = (*AK8JetEta)[leadH] ;
        phi2  = (*AK8JetPhi)[leadH] ;
        vec_jet.SetPtEtaPhi((*AK8JetPt)[leadH],(*AK8JetEta)[leadH], (*AK8JetPhi)[leadH]) ;
       
        dR_Calculator(eta1, phi1, eta2, phi2) ;
        h_dR_Recomu_tagjet.at(h+3) ->Fill(dR , factor);
        h_dEta_Recomu_tagjet.at(h+3) ->Fill(dEta , factor);
        h_dPhi_Recomu_tagjet.at(h+3) ->Fill(dPhi , factor);
        dpt = dPt_Calculator(vec_lep, vec_jet) ;
        h_dPt_lep_tagjet.at(h+3) ->Fill(dpt , factor);
      }
     // Similarly repeat for W and top jets

    }

    // With bjets w.r.t to Higgs & other jets
    for( int h = 0 ; h < Bsize ; h ++ ) {

      b1    = b_jet[h];
      eta1  = (*jetEta)[b1] ;
      phi1  = (*jetPhi)[b1] ;

      // for Higgsjet  
      if (Hsize == 1 ){
        leadH = Higgsjets[0];
        eta2  = (*AK8JetEta)[leadH] ;
        phi2  = (*AK8JetPhi)[leadH] ;

        dR_Calculator(eta1, phi1, eta2, phi2) ;
        if (h == 0) {        
          h_dR_Recob1_tagjet  .at(h+3) ->Fill(dR , factor);
          h_dEta_Recob1_tagjet.at(h+3) ->Fill(dEta , factor);
          h_dPhi_Recob1_tagjet.at(h+3) ->Fill(dPhi , factor);
        }

        if (h == 1) {        
          h_dR_Recob2_tagjet  .at(3)   ->Fill(dR , factor);         // 3 indices for Higgs jets
          h_dEta_Recob2_tagjet.at(3) ->Fill(dEta , factor);
          h_dPhi_Recob2_tagjet.at(3) ->Fill(dPhi , factor);
        }
      } 
    }
}


/// to check deltaR explicitly for Higgs & muon

void dR_TagJets_objects_v2(int muon) 
{
   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt, eta3= 0.0 , phi3 = 0.0;
   int b1 = -1, b2 =-1 ;
    //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
   //   AK8jet= 11(W) , 

      int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
      int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      float dRHbjet = -99.0;
      float dRlbjet = -99.0;

   TVector3 vec_lep, vec_jet;
        int id = 1 ; 
      
   // for muon w.r.t other jets dR plots

      eta1  = (*muEta)[muon];
      phi1  = (*muPhi)[muon];
      vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;

      int leadH = Higgsjets[0];
      eta2  = (*AK8JetEta)[leadH] ;
      phi2  = (*AK8JetPhi)[leadH] ;
      vec_jet.SetPtEtaPhi((*AK8JetPt)[leadH],(*AK8JetEta)[leadH], (*AK8JetPhi)[leadH]) ;
     
      dR_Calculator(eta1, phi1, eta2, phi2) ;
      h_dR_Recomu_tagjet.at(3) ->Fill(dR);
      h_dEta_Recomu_tagjet.at(3) ->Fill(dEta);
      h_dPhi_Recomu_tagjet.at(3) ->Fill(dPhi);
      dpt = dPt_Calculator(vec_lep, vec_jet) ;
      h_dPt_lep_tagjet.at(3) ->Fill(dpt);

     // Similarly repeat for W and top jets


    // With bjets w.r.t to Higgs & other jets
    for( int h = 0 ; h < Bsize ; h ++ ) {

     b1    = b_jet[h];
     eta3  = (*jetEta)[b1] ;
     phi3  = (*jetPhi)[b1] ;


      dRHbjet = dR_Calculator(eta3, phi3, eta2, phi2) ;
      if (h == 0)
      {        
        h_dR_Recob1_tagjet  .at(h+3) ->Fill(dR);
        h_dEta_Recob1_tagjet.at(h+3) ->Fill(dEta);
        h_dPhi_Recob1_tagjet.at(h+3) ->Fill(dPhi);
     }

       if (h == 1)
      {        
        h_dR_Recob2_tagjet  .at(3)   ->Fill(dR);         // 3 indices for Higgs jets
        h_dEta_Recob2_tagjet.at(3) ->Fill(dEta);
        h_dPhi_Recob2_tagjet.at(3) ->Fill(dPhi);
     }


     dRlbjet = dR_Calculator(eta1, phi1, eta3, phi3) ;
     h_dR_Reco  .at(0).at(h+id)->Fill(dR);
     h_dEta_Reco.at(0).at(h+id)->Fill(dEta);
     h_dPhi_Reco.at(0).at(h+id)->Fill(dPhi);
     dpt = dPt_Calculator(vec_lep, vec_jet) ;
     h_dPt_Reco.at(h+id)->Fill(dpt);

     if (h == 0) dRHbjet_dRlbjet->Fill( dRlbjet, dRHbjet ) ;
     
    } 
 }

//////////////////////////////////////////////////////////////////////////////////////////////
// filling for histograms for selected category===============================================
//////////////////////////////////////////////////////////////////////////////////////////////

void CatI_Objects_Plots()
{
   int prtcl = -1, b2 = -1, j = -1 ;     
   float  tau = 0.0 ;      
   float  Et_top = 0.0 ;
   TLorentzVector  Ws ;
   float mass_puppi = 0.0;              
   
   h_Histo_Pt.at(0).at(4)  -> Fill( pfMET) ;    // for MET being  global & [cat).at(histono.]               

   for(int g = 1 ; g < CatI_Objects.size(); g ++ )
   {   
      prtcl = CatI_Objects[g] ;
      if (g == 1)   {


           Ws.SetPtEtaPhiE((*AK8JetPt)[prtcl],(*AK8JetEta)[prtcl],(*AK8JetPhi)[prtcl],(*AK8JetEn)[prtcl]);
           h_Histo_Pt.at(0).at(g)  ->  Fill((*AK8JetPt)[prtcl]);
           h_Histo_Eta.at(0).at(g) ->  Fill((*AK8JetEta)[prtcl]); 
           h_Histo_Phi.at(0).at(g) ->  Fill((*AK8JetPhi)[prtcl]); 
           h_Histo_SD.at(0).at(g)  ->  Fill((*AK8JetMass)[prtcl]);   
           tau                      =  ((*AK8puppiTau4)[prtcl]/(*AK8puppiTau2)[prtcl]) ;            
           h_Histo_tau.at(0).at(g) ->  Fill(tau) ;

           Et_top                     =   Ws.Et() ;  
           mass_puppi              =   Sqrt (fabs ((Et_top * Et_top) - ((*AK8JetPt)[prtcl] * (*AK8JetPt)[prtcl]) ) );    
           h_Histo_Mass.at(0).at(g)->  Fill(mass_puppi);      

      }
      

      if (g == 2)    {
         h_Histo_Pt.at(0).at(g)  -> Fill((*jetPt)[prtcl]) ;
         h_Histo_Eta.at(0).at(g) -> Fill((*jetEta)[prtcl]) ; 
         h_Histo_Phi.at(0).at(g) -> Fill((*jetPhi)[prtcl]) ; 
      }

      if (g == 3)  {
         h_Histo_Pt.at(0).at(g)  -> Fill((*muPt)[prtcl]) ;
         h_Histo_Eta.at(0).at(g) -> Fill((*muEta)[prtcl]) ; 
         h_Histo_Phi.at(0).at(g) -> Fill((*muPhi)[prtcl]) ; 
      }

   }   
   

// Higgstag_MTCalculation() ;
   //          genlvl_MTCalculation(-1) ;  // for muon from top decayed W type
 
}


// for Dr plots 

void CatI_Objects_dR_Plots() 
{

  float eta1 = 0.0 ,phi1 = 0.0 ,eta2 = 0.0 ,phi2 = 0.0 ,eta3 = 0.0 ,phi3 = 3 ;
   TVector3 vec_lep, vec_Hjet, vec_jet ;

   int higgsjet = CatI_Objects[1] ;
   int bjet     = CatI_Objects[2] ;
   int muon     = CatI_Objects[3] ;


    eta1  = (*AK8JetEta)[higgsjet] ;   // for higgs jets
    phi1  = (*AK8JetPhi)[higgsjet] ;
    vec_Hjet.SetPtEtaPhi((*AK8JetPt)[higgsjet],(*AK8JetEta)[higgsjet], (*AK8JetPhi)[higgsjet]) ;    

    eta2  = (*jetEta)[bjet] ;          // for bjet
    phi2  = (*jetPhi)[bjet] ;
    vec_jet.SetPtEtaPhi((*jetPt)[bjet], (*jetEta)[bjet], (*jetPhi)[bjet]) ;

    eta3  = (*muEta)[muon];           // for muon  
    phi3  = (*muPhi)[muon];
    vec_lep.SetPtEtaPhi( (*muPt)[muon], (*muEta)[muon] , (*muPhi)[muon] ) ;


// for dR b/w Higgs & bjet 
    dR_Calculator(eta1, phi1, eta2, phi2) ;
    h_Histo_dR  .at(0).at(0)    ->Fill(dR) ;

// for dR b/w Higgs & muon 
    dR_Calculator(eta1, phi1, eta3, phi3) ;
    h_Histo_dR  .at(0).at(1)    ->Fill(dR) ;
    float dpt  = dPt_Calculator(vec_lep, vec_Hjet) ;    
    h_Histo_dPt.at(0).at(1) ->Fill(dpt) ;       

//  for dR b/w bjet & muon 
    dR_Calculator(eta2, phi2, eta3, phi3) ;
    h_Histo_dR  .at(0).at(2)    ->Fill(dR) ;
    dpt   = dPt_Calculator(vec_lep, vec_jet) ;    
    h_Histo_dPt.at(0).at(2) ->Fill(dpt) ;       

  
}  

// for Mt calculation ==========================


void  CatI_Objects_MTCalculation() 
{
   int higgs    = -1 ;  
   int topbjet  = -1 ;     
   int topmu       = -1 ; 
   TLorentzVector v_higgs, v_mu, v_topbjet ;

   higgs       = CatI_Objects[1] ;  
   topbjet     = CatI_Objects[2] ;     
   topmu        = CatI_Objects[3] ;  

   v_topbjet.SetPtEtaPhiE((*jetPt)[topbjet], (*jetEta)[topbjet], (*jetPhi)[topbjet], (*jetEn)[topbjet] ) ;
   v_mu.SetPtEtaPhiE( (*muPt)[topmu], (*muEta)[topmu], (*muPhi)[topmu], (*muEn)[topmu]);
   v_higgs.SetPtEtaPhiE((*AK8JetPt)[higgs],(*AK8JetEta)[higgs], (*AK8JetPhi)[higgs],(*AK8JetEn)[higgs]);




   float Et_higgs         =  v_higgs.Et() ;
   float Et_bjet          = v_topbjet.Et() ;
   float Et_mu            = v_mu.Et() ;
   double Et_sum          = 0.0 ;

   float pT_higgs         =  (*AK8JetPt)[higgs]; 
   float pT_bjet          =  (*jetPt)[topbjet] ;
   float pT_mu            =  (*muPt)[topmu] ;
   double pT_sum          =  0.0 ;

   double  W_Trans                = 0.0 ;
   double  top_Trans                = 0.0 ;  
   double  Higgs_Trans            = 0.0 ;
   double  TprimEt_Trans        = 0.0 ;
   double  trans_mass             = 0.0 ;

   // for cos(deltaPhi) calculation  
   float  dPhi           =  delta_phi((*muPhi)[topmu] ,  pfMETPhi) ;   // for muon & MET dphi
   float  MET_phi        =   pfMET * Cos(dPhi) ;

   dPhi                   =  delta_phi((*jetPhi)[topbjet] ,  pfMETPhi)  ;   //  for topbjet & MET dphi
   float  MET2_phi        =   pfMET * Cos(dPhi) ;

   dPhi                   =  delta_phi((*AK8JetPhi)[higgs] ,  pfMETPhi)  ;   //  for higgs & MET dphi
   float  MET3_phi        =   pfMET * Cos(dPhi) ;

   dPhi                   =  delta_phi((*jetPhi)[topbjet], (*muPhi)[topmu])  ;   //  for topbjet & muon dphi
   float   muphi       =   pT_mu * Cos(dPhi) ;

   dPhi                   =  delta_phi((*AK8JetPhi)[higgs], (*muPhi)[topmu]) ; //  for higgs & muon dphi
   float  mu2_phi       =   pT_mu * Cos(dPhi) ;

   dPhi                   =  delta_phi((*jetPhi)[topbjet], (*AK8JetPhi)[higgs])  ; //  for W & higgs dphi
   float  bjetphi       =   pT_bjet * Cos(dPhi) ;

   float  Dot_prod = 0.0   ;
   //  for W transverse mass    
   Et_sum               = Et_sum + Et_mu  +  pfMET  ;
   pT_sum            = pT_sum + (  pfMET *  pfMET ) + (pT_mu * pT_mu) ;  
   Dot_prod             =  Dot_prod +  2.0 * pT_mu * MET_phi ;
   W_Trans           = fabs (( Et_sum * Et_sum) - ( pT_sum + Dot_prod) ) ;
   trans_mass           = Sqrt ( W_Trans) ;
   float St_sum         =   pfMETPhi + pT_higgs + pT_bjet + pT_mu ;
   h_Histo_Mt.at(0).at(3) -> Fill( St_sum) ;

   //  for Top transverse mass 
   Et_sum                  = Et_sum +   Et_bjet ;
   pT_sum                  = pT_sum + ( pT_bjet* pT_bjet ) ;
   Dot_prod                = Dot_prod + 2.0 * pT_bjet *( MET2_phi +  muphi ) ;
   top_Trans               = fabs (( Et_sum * Et_sum)  - ( pT_sum + Dot_prod) )  ;
   trans_mass              = Sqrt ( top_Trans) ;
   h_Histo_Mt.at(0).at(2) -> Fill( trans_mass) ;

   // for Tprime Transverse mass
   Et_sum               = Et_sum + Et_higgs ;
   pT_sum                  = pT_sum + (pT_higgs * pT_higgs) ;    
   Dot_prod             = Dot_prod + 2.0 * pT_higgs * ( MET3_phi + mu2_phi + bjetphi ) ;
   TprimEt_Trans           = fabs(( Et_sum * Et_sum)  - ( pT_sum + Dot_prod) ) ;
   trans_mass              = Sqrt ( TprimEt_Trans ) ;

   h_Histo_Mt.at(0).at(1) -> Fill( trans_mass) ;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// function definitions for histogram detailing ==========================================
//Defaults Histograms for root =================================

// function definitions for histogram detailing 

// Histograms for muon studying ===================================

void Histo_Muon_ID_Study() {

    //   New defination of histogram
    char   pT_name[100] , pT_title[100] ; 
    string reco_object = {"Gen_Matched_muon_reco"};
    string variable[5] = {"pT300", "pT1000", "eta","phi", "N(Primary Vertex)"} ;
    string ar;
    //cout << "\nFunc 4" ;
    int s = -1;
    const int nBin = 29;
    const double Bin_value[nBin+1] =  {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0 } ;
   
    // for object pT histograms
    for(Int_t k = 0 ; k <  5; k++) {
     
 
        sprintf( pT_name , "%s_%s_" , variable[k].c_str(), reco_object.c_str() ) ;
        sprintf( pT_title , "%s(%s) Distribution" , variable[k].c_str(), reco_object.c_str() ) ;     
   
        if ( k == 0) {
          Match_Muon_Pt300  = new TH1D(pT_name,pT_title, nBin, Bin_value);
          Match_Muon_Pt300 ->GetYaxis()->SetTitle("Events");
        }

        if ( k == 1) {
          Match_Muon_Pt1000 = new TH1D(pT_name,pT_title, nBin, Bin_value);
          Match_Muon_Pt1000 ->GetYaxis()->SetTitle("Events");
          //cout<< " h_object_eta["<<k<<"].name() : "<< h_object_eta.at(k) ->GetName()<<endl;   
        }

        if( k == 2) {
          
          Match_Muon_Eta =  new TH1D(pT_name,pT_title, 200, -5.0,  5.0);
          Match_Muon_Eta -> GetYaxis()->SetTitle("Events");
        }

        if( k == 3) {
          
          Match_Muon_Phi =  new TH1D(pT_name,pT_title, 200, -5.0,  5.0);
          Match_Muon_Phi -> GetYaxis()->SetTitle("Events");
          
        }
   
        if( k == 4) {
          
          Match_Primary_Vertex =  new TH1D(pT_name,pT_title, 60, 0, 60) ;
          Match_Primary_Vertex -> GetYaxis()->SetTitle("Events");
          
        }  
   
    } // End loop of K

          Muon_Pt_ratio =  new TH1D("Muon_Pt_ratio","Muon_Pt_ratio Distribution", 20000.0, 0.0, 1000.0) ;
          Muon_Pt_ratio -> GetYaxis()->SetTitle("Events");

}

// Histograms for Cut flow 
     void Histo_Cut_Efficiency_Flow() 
    {
       Good_PV_Histo    = new TH1D("Good_PV_Histo", "Good Primary Vertex Distribution", 100, 0.0, 100);

       Good_PV_Pr_Histo = new TH1D("Good_PV_Pr_Histo", "Good Primary Vertex (after Pre-Sel) Distribution", 100, 0.0, 100);

       h_Parent_Mass    = new TH1D("h_Parent_Mass", "Parent Mass Distribution", 250, 0.0, 500.0);

       h_leadjetPt_before_after  = new TH2D( "h_leadjetPt_before_after", "lead jetpT after and before cleaning", 150, 0, 1500, 150, 0, 1500);
       h_leadjetPt_before_after  ->GetYaxis()->SetTitle("P_{T}(ak4jet1)(GeV)[before cleaning]");
       h_leadjetPt_before_after  ->GetXaxis()->SetTitle("P_{T}(ak4jet1)(GeV)[after cleaning]");

       h_subleadjetPt_before_after  = new TH2D( "h_subleadjetPt_before_after", "sublead jetpT after and before cleaning", 150, 0, 1500, 150, 0, 1500);
       h_subleadjetPt_before_after  ->GetYaxis()->SetTitle("P_{T}(ak4jet2)(GeV)[before cleaning]");
       h_subleadjetPt_before_after  ->GetXaxis()->SetTitle("P_{T}(ak4jet2)(GeV)[after cleaning]");       

       // h_jetPt_after_jetclean   = new TH1D( "h_jetPt_after_jetclean", "Leading jetPt after jet clean", 2000, 0, 2000);

       // h_jetPt_corr_factors     = new TH1D( "h_jetPt_corr_factors", "Jet cleaning correction factors per events", 2000, 0, 2000);

       h_leadjetPt_factors             = new TH2D( "h_leadjetPt_factors", "Corr factors w.r.t lead jetpT", 150, 0, 1500, 40, 0, 2);
       h_subleadjetPt_factors          = new TH2D( "h_subleadjetPt_factors", "Corr factors w.r.t sublead jetpT", 150, 0, 1500, 40, 0, 2);

       h_leadjetEta_factors             = new TH2D( "h_leadjetEta_factors", "Corr factors w.r.t lead jetEta", 200, -5.0, 5.0, 40, 0, 2);
       h_subleadjetEta_factors          = new TH2D( "h_subleadjetEta_factors", "Corr factors w.r.t sublead jetEta", 200, -5.0, 5.0, 40, 0, 2);

       h_leadjetPhi_factors             = new TH2D( "h_leadjetPhi_factors", "Corr factors w.r.t lead jetPhi", 200, -5.0, 5.0, 40, 0, 2);
       h_subleadjetPhi_factors          = new TH2D( "h_subleadjetPhi_factors", "Corr factors w.r.t sublead jetPhi", 200, -5.0, 5.0, 40, 0, 2);

      const int    nBin = 16;
      const double Bin_value[nBin+1] =  {0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1200.0, 1400.0, 1600.0 } ;

      // Gen_Match_Jet_Pt = new TH1D("Gen_Match_Jet_Pt", "Gen Matched ak8Jet Pt Distribution",  60, 0.0, 2400.0);
      Gen_Match_Jet_Pt = new TH1D("Gen_Match_Jet_Pt", "Gen Matched ak8Jet Pt Distribution",  nBin, Bin_value);

       Int_t i;
       const Int_t nx = 14;
       const char *cut_pass[nx] = { "Total Events",                //0                                      
                                    "HLT_Mu50 Trigger",           //1
                                    "Muon Cut",           //2
                                    "AK8 jet Cut" ,            //3
                                    "jet Tag",           //4           
                                    "for_jet Tag"  ,     //5         
                                    "Higgs Tag",               //8                                                                                                      
                                    "Higgs_Pt Cut",             //12   
                                    // "bjet tag",                                      
                                    // "dR check",                                    
                                    "MET Cut" ,          //5                                         
                                    "St Cut"  ,                //7   
                                    "Lep Iso",            //6                                                                                                                             
                                    // "bjet Tag" ,                                                       
                                    // "HiggspT > 300",                                    // "dR(Higgs, bjet) Cut" ,    //9
                                    // "dR(mu, bjet) Cut" ,       //10
                                    // "Pt Bjet Cut" ,            // 11                       
                                   };

       dPt_dR_mubjet   = new TH2F("dPt_dR_mubjet", "dPt & dR for mu,bjet Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);

       // dPt_dR_muqjet   = new TH2F("dPt_dR_muqjet", "dPt & dR for mu,qjet Distribution", 100, -1.0, 1.0, 500, 0.0, 1000.0);  // for tau42 study
       dPt_dR_muqjet   = new TH2F("dPt_dR_muqjet", "dPt & dR for mu,qjet Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);   // for standard use

       // dPt_dR_mubjet         ->GetYaxis()->SetTitle("dPT(mu,jet)");
       // dPt_dR_mubjet         ->GetXaxis()->SetTitle("dR(mu,jet)");


       dRHbjet_dRlbjet  = new TH2F("dRHbjet_dRlbjet","dRHbjet v/s dRlbjet", 50, 0.0, 5.0, 50, 0.0, 5.0) ;

       Cut_Efficiency_Flow = new TH1D("Cut_Efficiency_Flow","Cut Efficiency Flow",nx,0,nx);
       Cut_Efficiency_Flow->SetFillColor(38);


       for (i=1;i<=nx;i++) {
        Cut_Efficiency_Flow->GetXaxis()->SetBinLabel(i,cut_pass[i-1]);
      }

      const Int_t tx = 9 ;

      const char *cut_pt[tx] = {"dPt=10GeV", 
                                "dPt=15GeV", 
                                "dPt=20GeV", 
                                "dPt=25GeV", 
                                "dPt=30GeV", 
                                "dPt=35GeV", 
                                "dPt=40GeV", 
                                "dPt=45GeV", 
                                "dPt=50GeV"
                               };
    
      Cut_LepIso_dPt_Flow = new TH1D("Cut_LepIso_dPt_Flow", "Cut LepIso dPt Flow", tx, 0, tx);
      Cut_LepIso_dPt_Flow->SetFillColor(35) ;
      for (int i = 1; i <= tx; i++)
      {
        Cut_LepIso_dPt_Flow->GetXaxis()->SetBinLabel(i,cut_pt[i-1]);
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

      const Int_t taux = 21 ;

      const char *cut_tau[taux] = {"No cut on tau42", 
                                   "tau42 < 1.00",
                                   "tau42 < 0.95",
                                   "tau42 < 0.90",                                                                      
                                   "tau42 < 0.85",
                                   "tau42 < 0.80",                                   
                                   "tau42 < 0.75", 
                                   "tau42 < 0.70",                                   
                                   "tau42 < 0.65",
                                   "tau42 < 0.60",
                                   "tau42 < 0.55",   
                                   "tau42 < 0.50",                                                                                                        
                                   "tau42 < 0.45", 
                                   "tau42 < 0.40",                                   
                                   "tau42 < 0.35",
                                   "tau42 < 0.30",                                   
                                   "tau42 < 0.25",                                   
                                   "tau42 < 0.20",                                   
                                   "tau42 < 0.15",                                   
                                   "tau42 < 0.10", 
                                   "tau42 < 0.05",                                   
                                  };
    
      Cut_Tau42_Flow = new TH1D("Cut_Tau42_Flow", "Cut Tau42 Flow", taux, 0, taux);
      Cut_Tau42_Flow->SetFillColor(35) ;
      for (int i = 1; i <= taux; i++)
      {
        Cut_Tau42_Flow->GetXaxis()->SetBinLabel(i,cut_tau[i-1]);
      }




       const Int_t Higgsx = 5;
       const char *cut_Higgs[Higgsx] = { 
                                    "Total Events",
                                    "Events with Parent",                //0                                      
                                    "Events with matched AK8Jet",           //1
                                    "SDmass passed",           //2
                                    "Tau42 passed" ,            //3                   
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



    ST_Sum_Presel = new TH1D("ST_Sum_Presel", "ST Sum Distribution(Preselection)", 100, 0.0, 5000.0 );
    ST_Sum_Presel ->GetYaxis()->SetTitle("Events") ;

    ST_Sum_Evesel = new TH1D( "ST_Sum_Evesel", "ST Sum Distribution(Event selection)", 100, 0.0, 5000.0 );
    ST_Sum_Evesel ->GetYaxis()->SetTitle("Events") ;

    ST_Sum_LeadObj = new TH1D( "ST_Sum_LeadObj", "ST Sum Distribution(Leading objects)", 100, 0.0, 5000.0 );
    ST_Sum_LeadObj ->GetYaxis()->SetTitle("Events") ;

    // New sets of histogram defined for ak4 and ak8 jet distributions:

     h_dR_ak41_ak8Jet1 = new TH1D ("h_dR_ak41_ak8Jet1", "dR_ak41_ak8Jet1", 100, 0.0, 5.0 );
     h_dR_ak42_ak8Jet1 = new TH1D ("h_dR_ak42_ak8Jet1", "dR_ak42_ak8Jet1", 1000, 0.0, 10.0 );
     h_dR_ak43_ak8Jet1 = new TH1D ("h_dR_ak43_ak8Jet1", "dR_ak43_ak8Jet1", 1000, 0.0, 10.0 );
     h_dR_ak41_ak8Jet2 = new TH1D ("h_dR_ak41_ak8Jet2", "dR_ak41_ak8Jet2", 1000, 0.0, 10.0 );
     h_dR_ak42_ak8Jet2 = new TH1D ("h_dR_ak42_ak8Jet2", "dR_ak42_ak8Jet2", 1000, 0.0, 10.0 );
     h_dR_ak43_ak8Jet2 = new TH1D ("h_dR_ak43_ak8Jet2", "dR_ak43_ak8Jet2", 1000, 0.0, 10.0 );

    } 
    
    
    void Define_Mt_Histo()
    {
      //   New defination of histogram
      char  dr_MTname[100] , dr_MTtitle[100] ;
    
      int s = -1;
      int rk = -1 ;
      string MT_comp[9] = {"Mt_muMeT", "Mt_WmuMeT", "Mt_Tprime", "Mt_topjet", "Mt_Wjet", "Mt_Wmc", "MT_HiggsMC", "MT_topmc", "MT_Tmc"} ;
      //cout<<"\nFunc 1" ;
      // for Transverse mass plots, we have 6 combinations for objects
      for( int Sk = 0 ; Sk < 9 ; Sk ++ )
      {
        sprintf( dr_MTname, "%s",  MT_comp[Sk].c_str() ) ;
        sprintf( dr_MTtitle, "%s Distribution",  MT_comp[Sk].c_str() ) ;    
        h_object_MT.at(Sk) = new TH1D(dr_MTname,dr_MTtitle,  600, 0.0 , 3000.0 );
        h_object_MT.at(Sk)->GetYaxis()->SetTitle("Events");
        //cout<< " , h_object_Mt["<<Sk<<"].name() : "<< h_object_MT.at(Sk) ->GetName()<<endl; 
      }      
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------mc level objects ----------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  DefineMC_NPtEta_Histo()
{
  //   New defination of histogram
  //        TString   mc_pT , mc_pT_title, gh_name, gh_title;
  char mc_pT[100], mc_pT_title[100], gh_name[100], gh_title[100] ;

  std::string mc_objectI[7] = {"topb", "topWl","higgWq1", "higgWq2", "higgWl", "assob", "forwq" };
  //std::string mc_objectI[3] = {"topb", "topWl","higgWq1"};
  // for object pT histograms
  //cout << "\nFunc 2" ;
  for(Int_t k = 0 ; k < 7; ++k) {
    sprintf (mc_pT, "Pt(%s)", mc_objectI[k].c_str() )  ;
    sprintf (mc_pT_title, "Pt(%s) Distribution", mc_objectI[k].c_str() )  ;               
    h_mcobject_pt.at(k) = new TH1D(mc_pT,mc_pT_title, 24, 0, 1200.0);
    h_mcobject_pt.at(k) ->GetYaxis()->SetTitle("Events");        
    //  cout<< " , h_mcobject_pt["<<k<<"].name() : "<< h_mcobject_pt.at(k) ->GetName()<<endl;   
  }


  for(Int_t h = 0 ; h < 7; ++h) {
    sprintf (gh_name, "Eta(%s)", mc_objectI[h].c_str() )  ;
    sprintf (gh_title, "Eta(%s) Distribution", mc_objectI[h].c_str() )  ;                            
    h_mcobject_eta.at(h) = new  TH1D(gh_name,gh_title, 100, -5.0, 5.0);
    h_mcobject_eta.at(h) ->GetYaxis()->SetTitle("Events");
    //cout<<" , h_mcobject_eta["<<h<<"].name() : "<< h_mcobject_eta.at(h) ->GetName()<<endl; 
  }

  for(Int_t h = 0 ; h < 7; ++h) {
    sprintf (gh_name, "Mass(%s)", mc_objectI[h].c_str() )  ;
    sprintf (gh_title, "Mass(%s) Distribution", mc_objectI[h].c_str() )  ;                            
    h_mcobject_mass.at(h) = new  TH1D(gh_name,gh_title, 300, 0.0, 3000.0);
    h_mcobject_mass.at(h) ->GetYaxis()->SetTitle("Events");
    // cout<<" , h_mcobject_eta["<<h<<"].name() : "<< h_mcobject_eta.at(h) ->GetName()<<endl; 
  }
}



void  dRHisto_MCObject()
{
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ;
  string mc_object[7] = {"topb", "topWl","higgWq1", "higgWq2", "higgWl", "assob", "forwq" };
  // Here, i = 0-1 top decayed, i = 2-4 Higgs decayed, i = 5 assob, i = 6 forwq
  Int_t s = -1;
  //cout << "\nFunc 3" ;  
  for (Int_t i = 0; i < 7; i++) {     
    for (Int_t k = i+1; k < 7; k++) {
      // for mc  objects dR histograms
      sprintf(dR_name, "DeltaR_%s_%s_", mc_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf(dR_title, "DeltaR(%s_%s) Distribution", mc_object[i].c_str(), mc_object[k].c_str()) ;
      h_dR_MC.at(i).at(k) = new TH1D(dR_name,dR_title, 50, 0, 5.0);
      h_dR_MC.at(i).at(k) ->GetYaxis()->SetTitle("Events");     
      //cout<<" , h_dR_MC["<<i<<"]["<<k<<"].name() : "<< h_dR_MC.at(i).at(k) ->GetName()<<endl; 
      // for mc Object dPt histograms     
      sprintf(dPt_name, "DeltaPt_%s_%s_", mc_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf(dPt_title, "DeltaPt(%s_%s) Distribution", mc_object[i].c_str(), mc_object[k].c_str()) ;
      h_dPt_MC.at(i).at(k) = new TH1D(dPt_name,dPt_title, 100, 0, 500.0);
      h_dPt_MC.at(i).at(k) ->GetYaxis()->SetTitle("Events");      
      //cout<<" h_dPt_MC["<<i<<"]["<<k<<"].name() : "<< h_dPt_MC.at(i).at(k) ->GetName()<<endl;     
    }
  }
}     


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------reco level objects - Preselection--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   void  Define_2DMass_Histo()
   {
    //   New defination of histogram
    char   mass[100] , massT[100] ; 
    string object_no[4] = {"Higgs", "WHiggs","Top","WTop"};
    string reco_object[3] = {"AK8jet1", "AK8jet2","AK8jet3"};
   
    for(Int_t k = 0 ; k <  3; k++) {
      for(Int_t j = 0; j < 4; j++) {
   
        sprintf( mass , "%svs%s_Mass" , reco_object[k].c_str(),  object_no[j].c_str()  ) ;
        sprintf( massT , "%svs%s_Mass Distribution" , reco_object[k].c_str(),  object_no[j].c_str()) ;      
   
        if ( k == 0) {
          h_AK81vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK81vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
          
        }
   
        if ( k == 1) {
          h_AK82vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK82vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
        }
   
        if ( k == 2) {
          h_AK83vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK83vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
        }
   
      }
    }
   }
   
   
   void  Define_NPtEta_Histo()
   {
    //   New defination of histogram
    char   pT_name[100] , pT_title[100] ; 
    string object_no[8] = {"mu", "bjet", "AK8jet","jet","forwjet","qjet","puppi_bjet","puppi_forwjet"};
    string reco_object[15] = {"MET", "mu1", "bjet1", "bjet2","jet1","jet2","fjet1", "fjet2","qjet1","qjet2","puppiqjet2","puppifjet1", "AK8jet1", "AK8jet2","AK8jet3"};
    string variable[18] = {"pt", "eta", "puppimass", "chsprunedmass", "puppitau21", "puppitau32","tau21", "tau32", "chstau42","puppisdvsmass", "chsprunedvsmass","jetmass","puppisdmass","puppitau42","puppitau41", "puppitau43","puppitau31", "phi"} ;
    string ar;
    //cout << "\nFunc 4" ;
    int s = -1;
   
    // for object pT histograms
    for(Int_t k = 0 ; k <  15; k++) {
      for(Int_t j = 0; j < 18; j++) {
   
        sprintf( pT_name , "%s_%s_" , variable[j].c_str(), reco_object[k].c_str() ) ;
        sprintf( pT_title , "%s(%s) Distribution" , variable[j].c_str(), reco_object[k].c_str() ) ;     
        
        if( k < 12 && k > 9) continue ;
        if ( j == 0) {
          h_object_pt.at(k) = new TH1D(pT_name,pT_title,120, 0, 1200.0);
          h_object_pt.at(k) ->GetYaxis()->SetTitle("Events");
          // cout<< " h_object_pt["<<k<<"].name() : "<< h_object_pt.at(k) ->GetName()<<endl;   

        }
        if ( j == 1) {
          h_object_eta.at(k) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
          h_object_eta.at(k) ->GetYaxis()->SetTitle("Events");
        }
        if ( j == 17) {
          h_object_phi.at(k) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
          h_object_phi.at(k) ->GetYaxis()->SetTitle("Events");
        }

        if(!( k > 11) ) continue ;
        if( j == 2) {
          s = k +j - 14 ;
          h_AK8_PUPPImass.at(s) =  new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
          h_AK8_PUPPImass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_PUPPImass.at(s)->GetName()<<endl;  
        }
        if( j == 3) {
          s = k +j - 15 ;
          h_AK8_CHSmass.at(s) =  new TH1D(pT_name,pT_title, 50, 0.0, 500.0);
          h_AK8_CHSmass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_CHSmass["<<s<<"].name() : "<< h_AK8_CHSmass.at(s)->GetName()<<endl;  
        }
   
        if( j == 4) {
          s = k +j - 16;
          h_AK8_PUPPItau21.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau21.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau21["<<s<<"].name() : "<< h_AK8_PUPPItau21.at(s)->GetName()<<endl;          
        }
        if( j == 5) {
          s = k +j - 17 ;
          h_AK8_PUPPItau32.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau32.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau32["<<s<<"].name() : "<< h_AK8_PUPPItau32.at(s)->GetName()<<endl;                  
        }
        if( j == 6) {
          s = k +j - 18 ;
          h_AK8_tau21.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_tau21.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_tau21["<<s<<"].name() : "<< h_AK8_tau21.at(s)->GetName()<<endl;          
        }
        if( j == 7) {
          s = k +j - 19 ;
          h_AK8_tau32.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_tau32.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_tau32["<<s<<"].name() : "<< h_AK8_tau32.at(s)->GetName()<<endl;                  
        }
   
        if( j == 8) {
          s = k +j - 20 ;
          h_AK8_CHStau42.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_CHStau42.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_CHStau42["<<s<<"].name() : "<< h_AK8_CHStau42.at(s)->GetName()<<endl;                  
        }
        if( j == 9) {
          s = k +j - 21 ;
          h_AK8_PUPPIvsmass.at(s) =  new TH2F(pT_name,pT_title, 160, 0.0, 1600.0, 320, 0.0, 1600.0) ;
          h_AK8_PUPPIvsmass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_Puppivsmass["<<s<<"].name() : "<< h_AK8_PUPPIvsmass.at(s)->GetName()<<endl;                  
        }
        if( j == 10) {
          s = k +j - 22 ;
          h_AK8_CHSvsmass.at(s) =  new TH2F(pT_name,pT_title, 202, -10.0, 1000.0, 202, -10.0, 1000.0) ;
          h_AK8_CHSvsmass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_CHSvsmass["<<s<<"].name() : "<< h_AK8_CHSvsmass.at(s)->GetName()<<endl;                  
        }
   
        if( j == 11) {
          s = k +j - 23 ;
          h_AK8_Jetmass.at(s) =  new TH1D(pT_name,pT_title, 100, 0.0, 1000.0);
          h_AK8_Jetmass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_Jetmass.at(s)->GetName()<<endl;  
        }
   
        if( j == 12) {
          s = k +j - 24 ;
          h_AK8_PUPPISDmass.at(s) =  new TH1D(pT_name,pT_title, 50,  0.0, 500.0) ;
          h_AK8_PUPPISDmass.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_PUPPImass.at(s)->GetName()<<endl;  
        }
        if( j == 13) {
          s = k +j - 25 ;
          h_AK8_PUPPItau42.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau42.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
        }
        if( j == 14) {
          s = k +j - 26;
          h_AK8_PUPPItau41.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau41.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
        }
        if( j == 15) {
          s = k +j - 27;
          h_AK8_PUPPItau43.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau43.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
        }
        if( j == 16) {
          s = k +j - 28;
          h_AK8_PUPPItau31.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
          h_AK8_PUPPItau31.at(s) -> GetYaxis()->SetTitle("Events");
          //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
        }
   
      }  //end loop for J
    }  // end loop for K
   
    // for No. object  histograms
    for(Int_t j = 0; j < 6; j++) {  
      sprintf( pT_name , "N(%s)" , object_no[j].c_str() ) ;
      sprintf( pT_title , "N(%s) Distribution" , object_no[j].c_str() ) ; 
      h_object_no.at(j) = new TH1D(pT_name,pT_title, 10, 0, 10);  
      h_object_no.at(j) ->GetYaxis()->SetTitle("Events");
      // cout<<"h_object_no["<<j<<"].name() : "<< h_object_no.at(j)->GetName()<<endl;      
    }



   
   }
   
   
   void  dRHisto_RecoObject() 
   {
        // New defination of histogram for reco level at Preselection 
        char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ,dEta_title[100], dEta_name[100], dPhi_name[100], dPhi_title[100];
        string reco_object[14] = {"mu1", "bjet1", "bjet2","jet1","jet2","fjet1", "fjet2","qjet1","qjet2","puppiqjet2","puppifjet1", "AK8jet1", "AK8jet2","AK8jet3"};
        
        // Here i -> 0 muon, i -> 1-2 bjet & i -> 3-4 forwjet, i -> 5-6 AK8jet
        //cout<<"\nFunc 5" ;  
        int j = -1;
        for (Int_t i = 0; i < 14; i++) {      
    
          if (( i >= 9 && i <= 10) ) continue ;  
          for (Int_t k = i+1; k < 14; k++) {      
      
            if (( k >= 9 && k <= 10 ) )continue ;    
    
            // for reco preselected objects dR histograms
            sprintf( dR_name , "DeltaR_%s_%s_" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dR_title ,"DeltaR_%s_%s_ Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dR_Reco.at(i).at(k) = new TH1D(dR_name,dR_title, 1000, 0, 10.0);
            h_dR_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dR_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dR_Reco.at(i).at(k)->GetName()<<endl;                  
      
            // for reco preselected objects dEta histograms
            sprintf( dEta_name , "DeltaEta(%s_%s)" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dEta_title ,"DeltaEta(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dEta_Reco.at(i).at(k) = new TH1D(dEta_name,dEta_title, 100, 0, 10.0);
            h_dEta_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dEta_Reco" <<i<<"]["<<k<<"].name() : "<< h_dEta_Reco.at(i).at(k)->GetName()<<endl;                  
      
      
            // for reco preselected objects dPhi histograms
            sprintf( dPhi_name , "DeltaPhi(%s_%s)" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPhi_title ,"DeltaPhi(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dPhi_Reco.at(i).at(k) = new TH1D(dPhi_name,dPhi_title, 100, 0, 10.0);
            h_dPhi_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dPhi_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dPhi_Reco.at(i).at(k)->GetName()<<endl;                  
      
      
            // for lep-bjet dPt histograms  
            if(i == 0){
            sprintf( dPt_name , "DeltaPt_%s_%s_" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco.at(k) = new TH1D(dPt_name,dPt_title, 500, 0, 500.0);
            h_dPt_Reco.at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dPt_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dPt_Reco.at(k)->GetName()<<endl;                   
            } // if loop 

            if ( (reco_object[i] == "mu1") && ( reco_object[k] == "bjet1" || reco_object[k] == "qjet1" )) {

            if ( reco_object[k] == "bjet1" ) j = 0 ;
            if ( reco_object[k] == "qjet1" ) j = 1 ;

            // cout << "\ni = " << i <<" and j = " << reco_object[k] ;
            sprintf( dR_name , "DeltaR_%s_%s__lt04" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dR_title ,"DeltaR(%s_%s)_lt04 Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dR_Reco_lt04.at(i).at(j) = new TH1D(dR_name,dR_title, 100, 0.0, 0.50);
            h_dR_Reco_lt04.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            sprintf( dPt_name , "DeltaPt_%s_%s__lt10" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt_%s_%s__lt10 Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco_lt10.at(i).at(j) = new TH1D(dPt_name,dPt_title,20, 0, 20.0);
            h_dPt_Reco_lt10.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            sprintf( dPt_name , "DeltaPt_%s_%s__lt15" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt_%s_%s__lt15 Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco_lt15.at(i).at(j) = new TH1D(dPt_name,dPt_title,20, 0, 20.0);
            h_dPt_Reco_lt15.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            }
          }
        }
   }     

/////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------mc-Reco dR Histogram--------------------------------------


void  dRHisto_MCRecoObject()
{
  // New defination of histogram
  char dR_name[100], dR_title[100];
  string mc_object[4] = {"Higgs","W_Higgs", "Top", "W_Top"};
  string reco_object[3] = {"AK8jet1", "AK8jet2","AK8jet3"};
  //cout<<"\nFunc 6" ;
  for (Int_t i = 0; i < 3; i++) {          
    for (Int_t k = 0; k < 4; k++) {
      // for mc  objects dR histograms
      sprintf( dR_name, "DeltaR_%s_%s_" ,reco_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf( dR_title,"DeltaR(%s_%s) Distribution" , reco_object[i].c_str(), mc_object[k].c_str()) ;
      h_dR_MCReco.at(i).at(k) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
      h_dR_MCReco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
      //cout<<"h_dR_MCReco[" <<i<<"]["<<k<<"].name() : "<< h_dR_MCReco.at(i).at(k)->GetName()<<endl;      
    }
  }     
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------Tagged jets Histogram ---------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////

void   Define_Tag_Jet_Histo()
   {
      char tag_name[100] , tag_title[100] ;
      int x1 = -1 ;
      int rk = -1 ;
    
      string jet_tag[4] = { "Wjet", "topjet", "Higgsjet", "fatjet" } ; 
      string  Wjet_var[12]  = { "Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      string   top_var[12]  = { "Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      string Higgs_var[12]  = {"Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      //cout<<"\nFunc 7" ;
      for( int h =0 ; h < 3 ; h ++) {       
        // neglecting fatjet objetcs
        sprintf( tag_name, "N(%s)" , jet_tag[h].c_str() ) ;
        sprintf( tag_title, "N(%s) Distribution" , jet_tag[h].c_str() ) ;
        h_tag_N.at(h)  =  new TH1D(tag_name,tag_title, 10, 0, 10);
        h_tag_N.at(h)  -> GetYaxis()->SetTitle("Events");
        //cout<<"h_tag_N[" <<h<<"].name() : "<< h_tag_N.at(h)->GetName()<<endl;     
      }
    
      // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5  fatjet,Use this index cycle for filling plots  
      for(     int Sj = 0 ; Sj <  4; Sj ++) {


        for( int Tk = 0 ; Tk < 12; Tk ++ ) {
    

          if ( Sj < 2  ) {
            x1 = Sj + 1 ;                // for Wjets index   0-1     
            sprintf( tag_name, "%s(%s%d)",  Wjet_var[Tk].c_str(), jet_tag[0].c_str(), x1 ) ;  
            sprintf( tag_title,"%s(%s%d) Distribution", Wjet_var[Tk].c_str(), jet_tag[0].c_str(), x1);        
          }
          if ( Sj == 2 ) {
            x1 = Sj - 1 ;           // for topjet index  2
            sprintf( tag_name, "%s(%s%d)",  top_var[Tk].c_str(), jet_tag[1].c_str(), x1 ) ;  
            sprintf( tag_title,"%s(%s%d) Distribution", top_var[Tk].c_str(), jet_tag[1].c_str(), x1); 
          }
          if ( Sj == 3 ) {
            x1 = Sj - 2 ;           // for Higgsjet index   3 
            sprintf( tag_name, "%s(%s%d)",  Higgs_var[Tk].c_str(), jet_tag[2].c_str(), x1 ) ;       
            sprintf( tag_title,"%s(%s%d) Distribution", Higgs_var[Tk].c_str(), jet_tag[2].c_str(), x1);   
          }          
          if ( Sj > 3)      {
            x1 = Sj - 3 ;            // for fatjet index 4-5
            sprintf( tag_name, "%s(%s%d)",  Wjet_var[Tk].c_str(), jet_tag[3].c_str(), x1 ) ;      
            sprintf( tag_title,"%s(%s%d) Distribution", Wjet_var[Tk].c_str(), jet_tag[3].c_str(), x1);  
          }         
    
          if(Tk == 0 ) {
            h_tag_Pt.at(Sj)             = new TH1D(tag_name,tag_title, 40, 0, 1600.0);
            h_tag_Pt.at(Sj)             ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Pt[" <<Sj<<"].name() : "<< h_tag_Pt.at(Sj)->GetName()<<endl;             
          }      
          if(Tk == 1 )  {
            h_tag_Eta.at(Sj)           = new TH1D(tag_name,tag_title, 200, -5.0, 5.0);                   
            h_tag_Eta.at(Sj)            ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Eta[" <<Sj<<"].name() : "<< h_tag_Eta.at(Sj)->GetName()<<endl;       
          }      
          if(Tk == 2 ) {
            h_tag_Mass.at(Sj)         = new TH1D(tag_name,tag_title, 100, 0, 1000.0);         
            h_tag_Mass.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Mass[" <<Sj<<"].name() : "<< h_tag_Mass.at(Sj)->GetName()<<endl;             
          }                                
          if(Tk == 3  )  {
            h_tag_SD.at(Sj)           = new TH1D(tag_name,tag_title, 50, 0.0, 500.0);       
            h_tag_SD.at(Sj)       ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_SD[" <<Sj<<"].name() : "<< h_tag_SD.at(Sj)->GetName()<<endl;       
          }            
          if( Tk == 4 )  {
            h_tag_Pruned.at(Sj)        = new TH1D(tag_name,tag_title, 50, 0.0, 500.0);        
            h_tag_Pruned.at(Sj)       ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_SD[" <<Sj<<"].name() : "<< h_tag_SD.at(Sj)->GetName()<<endl;       
          }            
    
          if(Tk == 5 )  {
            h_tag_tau21.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_tau21.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_tau21.at(Sj)->GetName()<<endl;       
          }                        
          if(Tk == 6 )  {
            h_tag_tau32.at(Sj)         = new TH1D(tag_name,tag_title,200, -1.0, 1.0);               
            h_tag_tau32.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_tau32.at(Sj)->GetName()<<endl;       
          }   
          if(Tk == 7 )  {
            h_tag_Puppitau21.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau21.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau21.at(Sj)->GetName()<<endl;        
          }   
          if(Tk == 8 )  {
            h_tag_Puppitau32.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau32.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau32.at(Sj)->GetName()<<endl;        
          }   
          if(Tk == 9 )  {
            h_tag_CHStau42.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_CHStau42.at(Sj)         ->GetYaxis()->SetTitle("Events");
          } 
          if(Tk == 10){ 
            h_tag_PUPPImass.at(Sj)         = new TH1D(tag_name,tag_title, 100, 0, 1000.0);       
            h_tag_PUPPImass.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_PUPPImass[" <<Sj<<"].name() : "<< h_tag_PUPPImass.at(Sj)->GetName()<<endl;       
          } 
          if(Tk == 11 )  {
            h_tag_Puppitau42.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau42.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau32.at(Sj)->GetName()<<endl;        
          }   
    
    
        }      
      }
 }
       
       
void  dR_tagjetHisto() {
  
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ;
  string tag_jet[6] = {"Wjet1", "Wjet2", "topjet1",  "Higgsjet1", "fatjet1", "fatjet2"} ;                   
  //for tag jet   dR histograms
  // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5 fatjet, Use this index cycle for illing plots
  //cout<<"\nFunc 8" ;
  for (int i = 0; i < 4; i++) {
    for(int j = i+1; j < 4; j++) {
      // neglecting fatjets objects

      sprintf(dR_name,"DeltaR_%s_%s_" , tag_jet[i].c_str(), tag_jet[j].c_str() ) ;
      sprintf(dR_title,"DeltaR(%s_%s) Distribution", tag_jet[i].c_str(), tag_jet[j].c_str() ) ; 
      h_dR_tagjet.at(i).at(j)   =    new TH1D(dR_name,dR_title, 50, 0, 5.0);
      h_dR_tagjet.at(i).at(j)   ->   GetYaxis()->SetTitle("Events");         
      //cout<<"h_dR_tagjet["<<i<<"]["<<j<<"].name() : "<< h_dR_tagjet.at(i).at(j)->GetName()<<endl;     
    }
  }

}
       
       
void  Define_Reco_tagjetHisto()  {
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ,dEta_title[100], dEta_name[100], dPhi_name[100], dPhi_title[100];
  string reco_object[3]  =  {"muon","bjet1", "bjet2"} ;
  string tag_jet[6] = {"Wjet1", "Wjet2", "topjet1", "Higgsjet1", "fatjet1", "fatjet2" } ;  

  //for tag jet - muon  dR histograms
  // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5 fatjet, Use this index cycle for illing plots
  //cout<<"\nFunc 9" ;  
  int s = -1 ;
  for (Int_t i = 0; i < 3; i++) {
    for(Int_t j = 0; j < 4; j++) {
      // neglecting fatjets objects
      //cout << "\n value i = " << i << " && value j << " << j ;        
      if (tag_jet[j] != "Higgsjet1") continue ;   
      if( i == 0){      
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR_%s_%s_ Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dR_Recomu_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");
        //cout<<"h_dR_Recomu_tagjet]"<<j<<"].name() : "<< h_dR_Recomu_tagjet.at(j)->GetName()<<endl;          

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recomu_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recomu_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPt_name,"DeltaPt_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPt_title,"DeltaPt(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str());
        h_dPt_lep_tagjet.at(j)= new TH1D(dPt_name,dPt_title, 100, 0, 500.0);
        h_dPt_lep_tagjet.at(j)->GetYaxis()->SetTitle("Events");       
        //cout<<"h_dPt_lep_tagjet]"<<j<<"].name() : "<< h_dPt_lep_tagjet.at(j)->GetName()<<endl;            
      }

      if( i == 1){
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str());  
        h_dR_Recob1_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");      
        //cout<<"h_dR_Recob1_tagjet]"<<j<<"].name() : "<< h_dR_Recob1_tagjet.at(j)->GetName()<<endl;                    

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recob1_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recob1_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");
      }

      if( i == 2){
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR_%s_%s_ Distribution", reco_object[i].c_str(), tag_jet[j].c_str() );
        h_dR_Recob2_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");
        //cout<<"h_dR_Recob2_tagjet]"<<j<<"].name() : "<< h_dR_Recob2_tagjet.at(j)->GetName()<<endl;  

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recob2_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recob2_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");     

      }
    }//END OF J
  }// END OF I

} // END OF FUNC


///////////////////////////////////////////////////////////////////////////////////////////////////////
//================Signal Category Objects Histogram==================
////////////////////////////////////////////////////////////////////////////////////////////////////////

    void  Category_Object_Histo() {
      char Histo_name[100], Histo_title[100] ;
      string  obj[5], var  ;
      string  reco_var [3] = { "Pt", "Eta", "Phi" } ;
      string  Wjet_var [6] = { "Pt", "Eta","Phi", "TransMass", "PuppiSDMass",  "PUPPItau21"} ;
      string  top_var  [6] = { "Pt", "Eta","Phi", "TransMass", "PuppiSDMass",  "PUPPItau32"} ;
      string  Higgs_var[6] = { "Pt", "Eta","Phi", "TransMass", "PuppiSDMass",  "PUPPItau42"} ;
      int x ;
      int f = 0 ;
      //cout<<"\nFunc 10" ; 
      //For category  plots
      for ( int u = 0 ; u < 1 ; u ++ ) 
      { 
    
        // focussing only Higgs Category Plots by using u = 5
        x = u +1 ;
        // Category Decision
        if ( u == 5 ) {
          obj[0] = "Topjet" ; obj[1] = "HWjet"; obj[2] = "muon" ; obj[3] = "MET";
          f = 4;
        }
        if ( u == 1 )  {
          obj[0] = "Topjet" ; obj[1] = "HFatjet"; obj[2] = "muon" ; obj[3] = "MET";
          f =4 ;
        }
        if ( u == 2 )  {
          obj[0] = "TWjet" ; obj[1] = "HFatjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 3 )  {
          obj[0] = "TWjet" ; obj[1] = "HWjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 4 )  {
          obj[0] = "HWjet" ; obj[1] = "HFatjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 0 ) {
          obj[0] = "no" ; obj[1] = "Higgsjet" ; obj[2] = "bjet"; obj[3] = "muon" ; obj[4] = "MET";
          f = 5;
        }
    
        for ( int j = 0; j < f; j ++ )
        {
          if ( obj[j] == "no" ) continue;
          for ( int k = 0; k < 6 ; k++) 
          {
            if ( j > 1 && k > 2) continue ;
    
            if( obj[j] == "Topjet" )                                 var =  top_var[k]  ;
            if( obj[j] == "Higgsjet")                                var =  Higgs_var[k]  ;
            if( obj[j] == "muon" )                                   var =  reco_var[k]  ;
            if( obj[j] == "MET" )                                    var =  reco_var[k]  ;
            if( obj[j] == "bjet" )                                   var =  reco_var[k] ;
            if( obj[j] == "TWjet" || obj[j] == "HWjet" )     var =  Wjet_var[k]  ;        
            if( obj[j] == "TFatjet" || obj[j] == "HFatjet")          var =  Wjet_var[k]  ;        
    
            sprintf( Histo_name, "Category%d_%s_%s_", x, obj[j].c_str(), var.c_str() ) ; 
            sprintf( Histo_title, "Category%d_%s(%s) Distribution", x, obj[j].c_str(), var.c_str() ) ;        
            if(k == 0 ) {
              h_Histo_Pt.at(u).at(j)       = new TH1D(Histo_name,Histo_title, 40, 0, 1600.0);
              h_Histo_Pt.at(u).at(j)             ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_Pt["<<u<<"]["<<j<<"].name() : "<< h_Histo_Pt.at(u).at(j)->GetName()<<endl;             
            }      
            if(k == 1 )  {
              h_Histo_Eta.at(u).at(j)      = new TH1D(Histo_name,Histo_title, 200, -5.0, 5.0);    
              h_Histo_Eta.at(u).at(j)      ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_Eta["<<u<<"]["<<j<<"].name() : "<< h_Histo_Eta.at(u).at(j)->GetName()<<endl;         
            }   
            if(k == 2 )  {
              h_Histo_Phi.at(u).at(j)      = new TH1D(Histo_name,Histo_title, 100, -5.0, 5.0);    
              h_Histo_Phi.at(u).at(j)      ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_Eta["<<u<<"]["<<j<<"].name() : "<< h_Histo_Eta.at(u).at(j)->GetName()<<endl;         
            }       
            if(k == 3 ) {
              h_Histo_Mass.at(u).at(j)     = new TH1D(Histo_name,Histo_title, 100, 0, 1000.0);   
              h_Histo_Mass.at(u).at(j)      ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_Mass["<<u<<"]["<<j<<"].name() : "<< h_Histo_Mass.at(u).at(j)->GetName()<<endl;           
            }                                
            if(k == 4 )  {
              h_Histo_SD.at(u).at(j)        = new TH1D(Histo_name,Histo_title, 100, 0, 1000.0);
              h_Histo_SD.at(u).at(j)        ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_SD["<<u<<"]["<<j<<"].name() : "<< h_Histo_SD.at(u).at(j)->GetName()<<endl;           
            }            
            if(k == 5 )  {
              h_Histo_tau.at(u).at(j)         = new TH1D(Histo_name,Histo_title, 200, 0, 1.0);  
              h_Histo_tau.at(u).at(j)         ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_tau["<<u<<"]["<<j<<"].name() : "<< h_Histo_tau.at(u).at(j)->GetName()<<endl;
            }  // end of k ==4                       
    
          }  //end of kth loop
        }    //end of jth loop
    
      }    // end of uth loop
    }  //  end of function
    
    
    void  Category_Object_MtHisto()
    {
      char Histo_name[100], Histo_title[100];
      string TransM, transM1 , transM2 ;
      string  obj[5]  ;
      int x ;
      int f = 0 ;
      //cout<<"\nFunc 11" ;   
      //For category  plots
      for ( int u = 0 ; u < 1 ; u ++ ) 
      { 
        x = u +1 ;
        // Category Decision
        // focussing only Higgs Category Plots by using u = 0
    
        if ( u == 5 ) {
          obj[0] = "Top" ; obj[1] = "HW"; obj[2] = "mu" ; obj[3] = "MET";
          f = 4;
        }
        if ( u == 1 )  {
          obj[0] = "Top" ; obj[1] = "HFat"; obj[2] = "mu" ; obj[3] = "MET";
          f =4 ;
        }
        if ( u == 2 )  {
          obj[0] = "TW" ; obj[1] = "b"; obj[2] = "HFat" ; obj[3] = "mu" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 3 )  {
          obj[0] = "TW" ; obj[1] = "b"; obj[2] = "HW" ; obj[3] = "mu" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 4 )  {
          obj[0] = "HW" ; obj[1] = "HFat"; obj[2] = "b" ; obj[3] = "mu" ; obj[4] = "MET";
          f = 5;
        }
        if ( u == 0 ) {
          obj[0] = "no" ; obj[1] = "Higgs" ; obj[2] = "b"; obj[3] = "mu" ; obj[4] = "MET";
          f = 5;
        }
    
        TransM = TransM + "MET" ;
        for ( int j = f-2; j > -1; j -- )
        {
          transM1 = "" ;    
          transM2 = "" ;                   
          if ( obj[j] == "no" )                                continue;    
          if( obj[j] == "Top" )                               TransM = TransM + obj[j] ;
          if(obj[j] == "Higgs")                               TransM = TransM + obj[j] ;
          if( obj[j] == "mu" )                                TransM = TransM + obj[j] ;   
          if(  obj[j] == "b" )                                 TransM = TransM + obj[j] ;
          if(  obj[j] == "HFat" )                             TransM = TransM + obj[j] ;     
          if( obj[j] == "TW" || obj[j] == "HW" ) {
            if ( u == 2 || u == 3 || u == 4 )   TransM = TransM + obj[j+1] + obj[j];
            else {
              TransM = TransM + obj[j] ;
            }
          }
          transM2 = TransM ;
          if(  obj[j] == "b" && ( u == 2 || u == 3)  )  transM2 = obj[j] + obj[j-1]; 
          if( obj[j] == "HFat" && u == 4 )               transM2 = obj[j] + obj[j-1];    
    
          if( j == f-2 ){
          sprintf( Histo_name, "Cat%d_St(%s)", x , transM2.c_str() ) ;
          sprintf( Histo_title, "Cat%d_St(%s) Distribution", x , transM2.c_str() ) ;      
          }
    
          if (j != f-2 ){
          sprintf( Histo_name, "Cat%d_Mt(%s)", x , transM2.c_str() ) ;
          sprintf( Histo_title, "Cat%d_Mt(%s) Distribution", x , transM2.c_str() ) ;              
          }
    
          if(u <= 4){
            if ( j == 0 ) h_Histo_Mt.at(u).at(j)         = new TH1D(Histo_name,Histo_title, 30, 0, 3000.0);
            if ( j != 0 ) h_Histo_Mt.at(u).at(j)         = new TH1D(Histo_name,Histo_title, 30, 0, 3000.0);
          }
          if(u == 5 ) { 
            if ( j == 1 ) h_Histo_Mt.at(u).at(j)         = new TH1D(Histo_name,Histo_title, 30, 0, 3000.0);
            if ( j != 1 ) h_Histo_Mt.at(u).at(j)         = new TH1D(Histo_name,Histo_title, 30, 0, 3000.0);
          }
          h_Histo_Mt      .at(u).at(j)         ->GetYaxis()->SetTitle("Events");   
          //  cout<<"h_Histo_Mt["<<u<<"]["<<j<<"].name() : "<< h_Histo_Mt.at(u).at(j)->GetName()<<endl;     
        } 
        TransM = "" ;
      }
    }
    
    
    void  Category_Object_dRHisto()
    {
      char Histo_name[100], Histo_title[100] , dp_name[100], dp_title[100], dEta_name[100], dEta_title[100], dPhi_name[100], dPhi_title[100];
      string  obj[5]  ;
      int x ;
      int f = 0 , g  ;
      //cout<<"\nFunc 12" ;   
      //For category  plots
      for ( int u = 0 ; u < 1 ; u ++ ) 
      { 
        g = -1 ; 
        x = u +1 ;
        // Category Decision
        // focussing only Higgs Category Plots by using u = 0
    
        if ( u == 5 ) {
          obj[0] = "Topjet" ; obj[1] = "HWjet"; obj[2] = "muon" ; obj[3] = "MET";
          f = 3;
        }
        if ( u == 1 )  {
          obj[0] = "Topjet" ; obj[1] = "HFatjet"; obj[2] = "muon" ; obj[3] = "MET";
          f =3 ;
        }
        if ( u == 2 )  {
          obj[0] = "TWjet" ; obj[1] = "HFatjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 4;
        }
        if ( u == 3 )  {
          obj[0] = "TWjet" ; obj[1] = "HWjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 4;
        }
        if ( u == 4 )  {
          obj[0] = "HWjet" ; obj[1] = "HFatjet"; obj[2] = "bjet" ; obj[3] = "muon" ; obj[4] = "MET";
          f = 4;
        }
        if ( u == 0 ) {
          obj[0] = "no" ; obj[1] = "Higgsjet" ; obj[2] = "bjet"; obj[3] = "muon" ; obj[4] = "MET";
          f = 4;
        }
    
        for ( int j = 0; j < f; j ++ )
        {
          if ( obj[j] == "no" ) continue;
          for ( int k = j+1; k < f ; k++) 
          {
            g ++ ;
            if( obj[j] == "Topjet" ){
              sprintf( Histo_name, "Category%d_dR(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dEta_name, "Category%d_dEta(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dPhi_name, "Category%d_dPhi(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dp_name, "Category%d_dPt(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;   
            }
            if(obj[j] == "Higgsjet") {
              sprintf( Histo_name, "Category%d_dR(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dp_name, "Category%d_dPt(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;   
              sprintf( dEta_name, "Category%d_dEta(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dPhi_name, "Category%d_dPhi(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;          
            }
            if( obj[j] == "bjet" ) {
              sprintf( Histo_name, "Category%d_dR(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dp_name, "Category%d_dPt(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;   
              sprintf( dEta_name, "Category%d_dEta(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dPhi_name, "Category%d_dPhi(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;          
            }
            if( obj[j] == "TWjet" || obj[j] == "HWjet" ){
              sprintf( Histo_name, "Category%d_dR(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dp_name, "Category%d_dPt(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;   
              sprintf( dEta_name, "Category%d_dEta(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dPhi_name, "Category%d_dPhi(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;          
            }
            if( obj[j] == "TFatjet" || obj[j] == "HFatjet"){
              sprintf( Histo_name, "Category%d_dR(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dp_name, "Category%d_dPt(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;   
              sprintf( dEta_name, "Category%d_dEta(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;
              sprintf( dPhi_name, "Category%d_dPhi(%s_%s)",x ,obj[j].c_str(), obj[k].c_str() ) ;          
            } 
    
            sprintf(Histo_title,"Category%d_dR(%s_%s) Distribution",x ,obj[j].c_str(), obj[k].c_str() );
            sprintf(dp_title, "Category%d_dPt(%s_%s) Distribution",x ,obj[j].c_str(), obj[k].c_str() ) ;
            sprintf(dEta_title, "Category%d_dEta(%s_%s) Distribution",x ,obj[j].c_str(), obj[k].c_str() ) ;
            sprintf(dPhi_title, "Category%d_dPhi(%s_%s) Distribution",x ,obj[j].c_str(), obj[k].c_str() ) ;
    
            h_Histo_dR.at(u).at(g)             = new TH1D(Histo_name,Histo_title, 50, 0, 5.0);
            h_Histo_dR.at(u).at(g)             ->GetYaxis()->SetTitle("Events");
    
            h_Histo_dEta.at(u).at(g)             = new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
            h_Histo_dEta.at(u).at(g)             ->GetYaxis()->SetTitle("Events");
    
            h_Histo_dPhi.at(u).at(g)             = new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
            h_Histo_dPhi.at(u).at(g)             ->GetYaxis()->SetTitle("Events");
    
            //cout<<"h_Histo_dR["<<u<<"]["<<g<<"].name() : "<< h_Histo_dR.at(u).at(g)->GetName()<<endl;       
    
            if( obj[k] == "muon"){
              h_Histo_dPt.at(u).at(g)        = new TH1D(dp_name,dp_title, 500, 0.0, 500.0);
              h_Histo_dPt.at(u).at(g)        ->GetYaxis()->SetTitle("Events");
              //cout<<"h_Histo_dPt["<<u<<"]["<<g<<"].name() : "<< h_Histo_dPt.at(u).at(g)->GetName()<<endl;         
            }
    
          } // end of kth loop 
        } // end of jth loop
      }  //  end of uth loop
    }
    
    //============================================================
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////




// Category Selections 
// void  CategoryI_Check(int vr) {

//     TString Cat_pass  = "no" ;
//     int   jet1  = Higgsjets[0] ;
//     int   jet2  = -1 ; 
//     int   b2    = -1 ;
//     int   j     = n_Mu[0] ;
//     bool  pass  = false ;
//     int   mu    = -1 , top = -1, higg = -1 , bjet = -1 ;
//     float dPt   = 0.0 ;
//      float eta1  = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, eta3 = 0.0, phi3 = 0.0;
//      float ptcut   = Pt_Cut[vr - 1] ; 
//      float MeT_cut = METCut[vr - 1] ;
//      float jetPt = (*AK8JetPt)[jet1] ;
 
//      TVector3 vec_lep, vec_jet;

//     eta1  = (*muEta)[j];
//     phi1  = (*muPhi)[j];
//     vec_lep.SetPtEtaPhi( (*muPt)[j], (*muEta)[j] , (*muPhi)[j] ) ;

//     eta3  = (*AK8JetEta)[jet1] ;
//     phi3  = (*AK8JetPhi)[jet1] ;
//     dR_Calculator(eta1, phi1, eta3, phi3) ;

//    if ( dR  > 2.0 ) {
//       pass  = true ;
//       Cut_Efficiency_Flow->Fill(7);    // for dR(Higgs, muon) Cut bin 
//       }

//    int size4  = ( b_jet.size() >= 3) ? 3 : b_jet.size() ;
//    for( int h =0 ; h < size4 ; h ++ ){
//       if ( jet2 != -1 ) continue ;

//       b2    =  b_jet[h] ;          
//       if ( (*jetPt)[b2] < 50.0 ) continue ;

//         mu    = -1;
//         top   = -1;
//         higg  = -1;

//         eta2  = (*jetEta)[b2] ;
//         phi2  = (*jetPhi)[b2] ;    
//         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

//         dR_Calculator(eta1, phi1, eta2, phi2) ;
//         dPt  = dPt_Calculator(vec_lep, vec_jet) ;
//       if ( dR < 1.5 && dR > 0.1) top = 1  ;    
//       if(((dR > 0.4 && dR < 1.5)  || dPt > 40.0))  mu = 1 ;   

//        dR_Calculator(eta3, phi3, eta2, phi2) ;
                                   
//       if ( dR > 2.0 )  higg = 1 ;           

//       if ( top == 1&& mu == 1 && higg == 1 )  jet2  = b2 ;


//    }    

//    if ( pass == true && jet2 != -1 && (*muPt)[j] >= 40.0 ) {

//       Cut_Efficiency_Flow->Fill(8);    // for Lep Iso Cut bin 

//       if ( pfMET > MeT_cut ) {        //continue ;

//       Cut_Efficiency_Flow->Fill(9);     // for MET Cut bin 
//       if (jetPt > ptcut )    {

//       //   Cut_Efficiency_Flow->Fill(9);    // for Higgs Pt Cut bin 
//          CatI_Objects.push_back(-1);    //vague value as all histogram defined from index =1                 
//          CatI_Objects.push_back(jet1);               // Higgsjet at 0th place
//          CatI_Objects.push_back(jet2);         //  bjet at 1st place 
//          CatI_Objects.push_back(j);            //  muon at 2nd place & MET is global
     
//       }
//    }
//   }
// }