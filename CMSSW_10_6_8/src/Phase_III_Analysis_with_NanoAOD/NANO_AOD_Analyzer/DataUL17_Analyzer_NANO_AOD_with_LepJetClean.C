// #define DataUL17_Analyzer_NANO_AOD_with_LepJetClean_cxx
// #include "DataUL17_Analyzer_NANO_AOD_with_LepJetClean.h"

#define  UL17_Analyzer_NANO_AOD_with_LepJetClean_cxx
#include "UL17_Analyzer_NANO_AOD_with_LepJetClean.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <stdio.h>


using namespace std;

int main(int argc, char **argv)
{
       if (argc < 2){ 
                std::cout<<"pass the text file containing root file names "<<std::endl;
                exit(0);
        }

        gROOT->ProcessLine("#include <vector>");
        gROOT->ProcessLine("#include <map>");

        // UL17_Analyzer_NANO_AOD a(argv[1]);



        UL17_Analyzer_NANO_AOD_with_LepJetClean  a(argv[1]);


        TString InputTxtFile = argv[1];
        TString OutputFileName = InputTxtFile.ReplaceAll(".txt","");
        
        // for running test in Loops 
        TString MuonIsolation[4] = {
                                       "MiniIsoTight",
                                       "MiniIsoVeryTight",                                              
                                       "dR_04_OR_dPt_20",
                                       "dR_04_OR_dPt_40"
                                     };

        TString Higgs_Working_Point[8] = {
                                           "PT350SD80-160Tau80",
                                           "PT350SD80-160Tau75",
                                           "PT350SD80-160Deep10",
                                           "PT350SD80-160Deep20",
                                           "PT400SD70-160Tau80",
                                           "PT400SD70-160Tau75",
                                           "PT400SD70-160Deep10",
                                           "PT400SD70-160Deep25",
                                         } ;                                      
        // For Loop for running test in combinations
        for (int i = 0; i < 4; ++i)
        { // Ist loop over Muon Isoaltion
          for (int ji = 0; ji < 8; ++ji)
          { // Loop over Higgs working point
               // a.Loop(OutputFileName.Data(), "No" , MuonIsolation[i] ,Higgs_Working_Point[ji]);                     
          }
             
        }  //  End of Loop 

        TString Higgs_Working_Point2[9] = {
                                           // "PT300SD70-160",
                                           // "PT300SD80-160",
                                           "PT300SD90-160",
                                           // "PT350SD70-160",
                                           "PT350SD80-160",
                                           "PT350SD90-160",
                                           "PT400SD70-160",
                                           // "PT400SD80-160",
                                           // "PT400SD90-160",
                           } ;              

         for (int ji = 0; ji < 0; ++ji)
         { // Loop over Higgs working point
              // if ( ji != 0 ) a.Loop(OutputFileName.Data(), "No" , "No" ,Higgs_Working_Point2[ji]);                     
              // else  a.Loop(OutputFileName.Data(), "No" , MuonIsolation[0] ,Higgs_Working_Point2[ji]); 

          // a.Loop(OutputFileName.Data(), "Lep" , "No" ,Higgs_Working_Point2[ji]);  
         }
        // Another sets of run
        // For General Run Put this
        // a.Loop( OutputFileName.Data(), "No", "dR>0.2_OR_dPt>20GeV",  "PT300SD70-160Tau80"); 
        // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10"); 
        // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10"); 


        if( (! OutputFileName.Contains("Electron")) && (! OutputFileName.Contains("Muon")) ) {

      a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleEvntW"); 

      a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleEvntW"); 

      // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleNoPU"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleNoPU"); 

      // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithL1VFP"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithL1VFP"); 

      // // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp660"); 02 Apr
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp692"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp724"); 

      // // a.Loop(OutputFileName.Data(), "Electronic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp660"); 
      // a.Loop(OutputFileName.Data(), "Electronic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp692"); 
      // a.Loop(OutputFileName.Data(), "Electronic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp724");              
        }


        if( OutputFileName.Contains("Muon"))     a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10", "MuonDataSample");
        if( OutputFileName.Contains("Electron")) a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10", "ElectronDataSample");   
} 







// void UL17_Analyzer_NANO_AOD::Loop(TString OutputFileName)

void UL17_Analyzer_NANO_AOD_with_LepJetClean::Loop(TString OutputFileName, TString Channel, TString LeptonIsolation , TString Higgs_WP, TString IsData)

// void DataUL17_Analyzer_NANO_AOD_with_LepJetClean::Loop()
{

// For Run put No, For Check Put Yes ....... Remember !!!!   
//======================================================================================================================================//

//   In a ROOT session, you can do:
//      root> .L DataUL17_Analyzer_NANO_AOD_with_LepJetClean.C
//      root> DataUL17_Analyzer_NANO_AOD_with_LepJetClean t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
//========================================================================================================================================//

   if (fChain == 0) return;
  
   Trigger_Check = IsData  ;

   factor = 1.0; 
   
   if ( Trigger_Check.Contains("MCSample")) {

      Luminosity_Normalization(OutputFileName) ; 
      
      factor      = lumi_factor ;

      Efficiency_Read_From_bTagEff_Root_Files(OutputFileName) ;

   }  

   MC_Channel  =  Channel ;



   cout <<"\n Factor for " << OutputFileName << " is = " << factor ;


   // Output root file is declared and named ============================

   // if ( JetforIsolation.Contains("Yes")) OutputFileName = OutputFileName + "_Higgs90-160_12-01-21.root";
   // if ( JetforIsolation.Contains("No")) OutputFileName = OutputFileName + "_Full_Selection_Check_12-01-21.root";

   OutputFileName = OutputFileName + "_"  + Channel ;

   // if ( Higgs_WP.Contains("PT") || Higgs_WP.Contains("SD"))  OutputFileName = OutputFileName + "_Higgs" + Higgs_WP ;
   if ( Higgs_WP.Contains("Deep") )  OutputFileName = OutputFileName + "_HiggsDeepMD";

   // if ( LeptonIsolation.Contains("MiniIso")) OutputFileName  = OutputFileName + "MuIso_" + LeptonIsolation + "_03-Feb-21.root";
   if ( LeptonIsolation.Contains("MiniIso")) OutputFileName  = OutputFileName + "_LepIso" + "_EvntLvL2_11-Aug-21.root";   
   if ( LeptonIsolation.Contains("dR")) OutputFileName  = OutputFileName + "_2DLepIso" ;   
   if ( LeptonIsolation.Contains("No")) OutputFileName  = OutputFileName + "_EvntLvL2_11-Aug-21.root";   
   
   if ( IsData.Contains("L1VFP"))  OutputFileName  = OutputFileName + "_L1VFP_11-Aug-21.root";
   if ( IsData.Contains("PileUp"))  OutputFileName  = OutputFileName + "_"+ IsData +"_11-Aug-21.root";
   if ( IsData.Contains("NoPU"))  OutputFileName  = OutputFileName + "_EvntLvlv2_11-Aug-21.root";

   if ( IsData.Contains("Data"))  OutputFileName  = OutputFileName + "EvntLvl_02-Sep-21.root";
   if ( IsData.Contains("MCSampleEvntW"))  OutputFileName  = OutputFileName + "_"+ "bweight_EvntW_02-Sep-21.root";
   // if ( IsData.Contains("MCSampleEvntW"))  OutputFileName  = OutputFileName + "_"+ "_EvntW_17-Aug-21.root";


   // OutputFileName = OutputFileName + "_NoMatchLep_11-12-20.root";

   
   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

   // Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works" << endl;

// ================================Histograms are defined and declared for the root files ===========================

   // Define_Mt_Histo() ;  
   // Histo_Cut_Efficiency_Flow() ;
   // Histo_Muon_ID_Study() ;

   // Define_2DMass_Histo();    // for gen level plots

   Define_Histo_For_Global_Var() ;
   Define_Kinematic_Histo_for_RecoObject();
   Define_DelatR_Histo_for_RecoObject() ;
   Define_Kinematic_Histo_for_HiggsJet() ;
   Define_Histograms_For_LeptonJet_Cleaning_Effect() ;

   Define_2DHistogram_For_BtagEff() ;


   // Define_Tag_Jet_Histo() ;    // for tagged jets plots at reco level
   // Define_Reco_tagjetHisto() ;   
   // dR_tagjetHisto() ;     

   // Category_Object_Histo() ;     // for category I plots
   // Category_Object_dRHisto() ;     
   // Category_Object_MtHisto() ; 

//=================================== Histograms are defined and declared for the root files =============================

   float Eta = 0.0 ; 	
   int count = -1 ;
   int id = -1 ;       //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
   int nLepton = 0 ;
   int check = -1 ;
   float  PU_factor = 1.0 ;

   float top_mass   = 0.0 ;

   bool Lepton_Trigger = false ;

   TString  UseSortedJets = "Sorting" ;
   TString  Filling_at_Preselection = Channel ; // Put it Yes for preselection filling
   TString  MET  = "MET" ;
   TString  IsTopbjet = "No";

   passed_total_events              = 0.0 ;
   passed_dR                        = 0.0 ;
   passed_dPt                       = 0.0 ;
   passed_only_dRdPt                = 0.0 ;
   passed_no_dRdPt                  = 0.0 ;
   passed_both_dRdPt                = 0.0 ;
   passed_nojet                     = 0.0 ;

//.....................PileUp ReWeighting.........................

        TString PileUp_file_name = "PileUp_ScalefactorsUL2017_24Mar21_724.root" ;
        
        if (IsData.Contains("PileUp660"))   PileUp_file_name = "PileUp_ScalefactorsUL2017_24Mar21_66.root" ;
        if (IsData.Contains("PileUp692"))   PileUp_file_name = "PileUp_ScalefactorsUL2017_24Mar21.root" ;
        if (IsData.Contains("PileUp724"))   PileUp_file_name = "PileUp_ScalefactorsUL2017_24Mar21_724.root" ;

        PileUp_file            = TFile::Open( PileUp_file_name,"READ");
        PieUp_ScaleFactor      = (TH1D*)PileUp_file->Get("h_PUScaleFactor");

//.....................Muon ID scale factor for 2016 ............................................     

   Muon_Scale_file             = TFile::Open( RunBCDEF_UL17_Muon_SF_ID_Root_File,"READ");

   Electron_Scale_file         = TFile::Open( Run2_UL17_Electron_SF_LooseID_Root_File,"READ");


   if(Channel.Contains("Muon"))     Lepton_histo_scale_factor   = (TH2F*) Muon_Scale_file->Get("NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta") ;
   if(Channel.Contains("Electron")) Lepton_histo_scale_factor   = (TH2F*) Electron_Scale_file->Get("EGamma_SF2D") ;

//---------------------------------------BTagging Scalefactors------------------------------

   // BTagCalibrationReader reader_up(BTagEntry::OP_LOOSE, "up");  // sys up

   // BTagEntry::OperatingPoint DeepCSV_OP = BTagEntry::OP_LOOSE; // required for SF calculation

   // BTagEntry::JetFlavor jet_Flavor  =  BTagEntry::FLAV_B ; // required for SF calculation
// Event Loop started here and main analyzing code starts ==============================================================================



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 1000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Cut_Efficiency_Flow->Fill(0.5, factor);     // for Total events in MC sample


      Clear_Vector() ;

      //========= Preselection of event requiring atleast of lepton and jet =====================================================================
      if ( PV_npvsGood == 0 ) continue;


      if (IsData.Contains("PileUp")) {
          
          PU_factor   = PUWeights(Pileup_nTrueInt)    ;       // factor from PileUp root file store locally
          // factor      = lumi_factor * PU_factor * L1PreFiringWeight_Nom ;
          factor      = lumi_factor * PU_factor  ;

          // cout << "\nlumi factor from calculation = " << lumi_factor  << "  &&  Pile Up factor = " << PU_factor <<"  for pu True = " << Pileup_nTrueInt ;
      }


      if (IsData.Contains("L1VFP")) {

        factor = lumi_factor * L1PreFiringWeight_Nom ;

      } 

      if ( IsData.Contains("MCSampleEvntW") ) {

          PU_factor   = PUWeights(Pileup_nTrueInt)    ;       // factor from PileUp root file store locally
          factor      = lumi_factor * PU_factor  * L1PreFiringWeight_Nom ;

      }


      Cut_Efficiency_Flow->Fill(1.5, factor);     // for Primary Vertex Passed events

      Lepton_Trigger = false ;

      // Lepton_Trigger = ( HLT_Mu50 != 0 || HLT_OldMu100 != 0 || HLT_TkMu100 != 0 ) ;

      // Lepton_Trigger = ( HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165 != 0 || HLT_Ele115_CaloIdVT_GsfTrkIdT != 0 ) ;

      Lepton_Trigger = Lepton_Trigger_Check() ;

      if ( Lepton_Trigger == 0 ) continue ;


      Cut_Efficiency_Flow->Fill(2.5, factor);     // for MuTrigger Passed events

      Good_PV_Histo ->Fill( PV_npvsGood,factor);

      

      top_muon = -1 ;

      top_electron  = -1 ;

      top_lepton    = -1 ;

      top_mass   = 0.0 ;

      IsTopbjet = "No";

	  // if (!( nLepton > 0  && nFatJet > 0  ))   continue ;

      Filling_at_Preselection = "No" ;
      //================================================= GENERAL SELECTION OF OBJECTS=================================================

      //================================================= GENERAL SELECTION OF OBJECTS=================================================
  	  
  	  ////////////////////////////////////////////////////
  	  //  0  for nMET"}, 
        //  index 1   for nElectron  Filling Population Plot
        //  index 2   for nMuon  Filling Population Plot
        //  index 3   for nJet  Filling Population Plot
        //  index 4   for nFatJet  Filling Population Plot
        //  index 5   for nForwJet  Filling Population Plot
        //  index 6   for nCleanJet  Filling Population Plot
        //  index 7   for nbjet  Filling Population Plot
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

      //===================================================== Electron Selection =======================================================================

      // cout << "\n No. of electron = " << nElectron ;

      Check_Electrons_For_Event_N_Fill(Filling_at_Preselection + "Electron") ;



      //===================================== Muon Selection ==============================================================================

      // cout << "\n No. of muon = " << nMuon ;

	    check = -1 ;

	    Check_Muons_For_Event_N_Fill( Filling_at_Preselection + "Muon") ;



      //===============================  Muon Selection Ends =======================================================================

      //=============================== Fat Jet Selection =====================================================================================================

      // cout << "\n No. of fatjet = " << nFatJet << endl;


      Check_CleanFatJet_For_Event_N_Fill( Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet



      //====== FatJet Selection Ends=====================================================================================================
      //====== MET  Selection =====================================================================================================
      
      // MET = Filling_at_Preselection + "MET" ;

      Fill_Lepton_Hist_Preselction_LvL( Filling_at_Preselection + "MET"  , 0 , 0) ; // both entries 0 for YesMET to Fill or NoMET  

      //====== MET Selection Ends=====================================================================================================
      //============================== Jet Selection =======================================================================

      // cout << "\n No. of jet = " << nJet ;

      Check_CLeanedJet_For_Event_N_Fill( Filling_at_Preselection) ;  /// PUT "Yes" for filling 


      // if you want to continue with the sorted jets Put "Sorting" or else "No"


      Jet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection); 


      FatJet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection);      // PASS "NO" FOR NO FILLING    Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet 

      // Whether you sort or not this line happens
      n_jet = jet_sort ;
      n_AK8Jet = fatjet_sort ;


      // ==================== Generate Clean Jet from fatJet using dR > 1.2 and Check is for deltaR plots ======================///////////////////

      // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots

      if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet(Filling_at_Preselection +"CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots


      Check_Cleaned_Bjet_After_Muon_Isolation( Filling_at_Preselection + "loose");


	  //====== Jet Selection Ends=====================================================================================================

      //////============= Higgs Tagging Selections and Some Fucking Test ======================================///////////////////////////////////////////////

      if ( Filling_at_Preselection.Contains("No") && (!Higgs_WP.Contains("No")) ) HiggsTagging_Using_PT_SD_Tau_N_Deep( Higgs_WP ) ;

      Hist_for_Leading_HiggsJet.at(16) ->Fill( Higgsjets.size(), factor );

    
      // Use @PreSelection or @EventSelection to define the selection level
      // Check_DeltaR_of_Higgs_wrt_Top_Lepton( Channel, "Mass@PreSelection" ); 

      // Hist_for_Leading_HiggsJet.at(22) ->Fill( DeltaR_Cleared_Higgsjet.size(), factor );

      // if ( DeltaR_Cleared_Higgsjet.size() != 0 ) Cut_Higgs_Tagging_Flow -> Fill(2.5, factor) ;


      ///////-========-HERE WE AFTER SELECTION OF EACH PBJECTS AND TEST WE CHECK SELECTIONS AND FILL SELECTION FLOW HISTOGRAMS  =====---/////////////////////////
      //////====================== ALSO FILL EACH OBJECT AT THIS TIME BUDDY ============================//////////////////////////

      if( Channel.Contains("Muon") )           nLepton = n_Mu.size() ;

      if( Channel.Contains("Electron") )       nLepton = n_ele.size() ;

      Lepton_Scale_Factor_ID  =  factor ;  // KEEPING LEPTON SCALE ID FACTOR SAME AS OTHER EVENT FACTORS, UNTILL CALCULATED     

      btag_weight  =  factor ;  // KEEPING LEPTON SCALE ID FACTOR SAME AS OTHER EVENT FACTORS, UNTILL CALCULATED     

      // Fill_Object_Population() ;    


      if ( n_forwjet.size() == 0)  continue ; 

      Cut_Efficiency_Flow -> Fill( 3.5, factor);   // Forward Jet tag
      
      // Fill_Lepton_Hist_Preselction_LvL( "YesMET"  , 0 , 0) ; // both entries 0 for YesMET to Fill or NoMET  

      if ( MET_pt < 50.0 )   continue ;

      Cut_Efficiency_Flow -> Fill( 4.5, factor);    // METcut 


      // if ( ( n_Mu.size() + n_ele.size() ) == 0 )  continue ;
      if ( ( nLepton ) == 0 )  continue ;

      Cut_Efficiency_Flow -> Fill ( 5.5, factor);   // Lepton tag in the event


      jet_copy = n_cleanjet;  

      if ( n_AK8Jet.size() == 0) continue ;  

      Cut_Efficiency_Flow -> Fill (6.5, factor);   // Fatjet tag

      if ( n_cleanjet.size() == 0 ) continue ;

      Cut_Efficiency_Flow -> Fill ( 7.5, factor);  // Clean jet tag


      // cout << "\n For Event,   " << jentry ;

      // cout << "\n Btag SF = " << SF  << endl ;


      //=== PRESELECTION LEVEL CLEARED ================///////////////////

      Scalar_Sum_pT_Function( Channel) ; // Fiiled and calculated after preselection 

      if (Filling_at_Preselection.Contains("No")) ST_Sum_Presel -> Fill(Scalar_Sum_pT, factor) ;

      // Fill_Object_Hist_After_Preselction_LvL( "Yes" ) ;

      //=== Event- SELECTION LEVEL Follows ================///////////////////


      if( b_jet.size() == 0 ) continue ;

      // cout << "\n\n For Event,   " << jentry ;

      Cut_Efficiency_Flow -> Fill ( 8.5, factor); // bjet tag     

      
      //--- top lepton selected using 2D Lepton Isolation------------

      if ( Channel.Contains("Muonic") )     top_lepton = Selection_Lepton_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);

      if ( Channel.Contains("Electronic") ) top_lepton = Selection_Electron_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);

      // cout << " \n top_lepton = " << top_lepton ;
   
      if ( top_lepton == -1 ) continue ; // lepton after passing Isolation is reffered now as top_lepton

      Cut_Efficiency_Flow -> Fill ( 9.5, factor); // Lep-Isolation Selection   


      //--------- Higgjet Tag --------

      if ( Higgsjets.size() == 0 ) continue ;

      Cut_Efficiency_Flow -> Fill ( 10.5, factor); // Higgjet Tag


      //--- DeltaRHiggjet Check --------------------
      //--- Use @PreSelection or @EventSelection to define the selection level -----

      Check_DeltaR_of_Higgs_wrt_Top_Lepton( Channel, "DeltaR@EventSelection" ); 


      if ( DeltaR_Cleared_Higgsjet.size() == 0 ) continue ;

      Cut_Efficiency_Flow -> Fill ( 11.5, factor); // Mass and  DeltaR check for H, top-lepton > 1.2   
  
      Cut_Efficiency_Flow -> Fill ( 12.5, factor); // Mass and  DeltaR check for H, top-b > 1.2  

 
      //--- ST Selection cut  ---------------

      ST_Sum_LeadObj -> Fill( Scalar_Sum_pT, factor) ;

      Scalar_Sum_pT_atEventSelection( top_lepton, Channel) ;

      if ( Scalar_Sum_pT < 500.0) continue ;

      Cut_Efficiency_Flow -> Fill ( 13.5, factor); // ST cut  



      //==== Object Reweights Calculations Follows -------------------------------


      if (IsData.Contains("MCSample")) Event_Reweighting_Using_SF_N_MC_btageff() ;  //Btag Weight Calculated for MC Sample

      factor =    btag_weight * factor ;

      
      if ( IsData.Contains("MCSample") && Channel.Contains("Muonic") )      Lepton_Scale_Factor_ID = Muon_ID_ScaleFactor_UL2017( Muon_pt[top_lepton], Muon_eta[top_lepton]) ;
      
      if ( IsData.Contains("MCSample") && Channel.Contains("Electronic"))   Lepton_Scale_Factor_ID = Electron_ID_ScaleFactor_UL2017( Electron_pt[top_lepton], Electron_eta[top_lepton]) ;


      // if ( IsData.Contains("NoPU"))          Lepton_Scale_Factor_ID =  factor ;  // KEEPING LEPTON SCALE ID FACTOR SAME AS OTHER EVENT FACTORS, UNTILL CALCULATED      

      // else       Lepton_Scale_Factor_ID = Lepton_Scale_Factor_ID * factor ;

      Lepton_Scale_Factor_ID = Lepton_Scale_Factor_ID * factor ;

      // cout << "\n Lepton_Scale_Factor_ID = "  << Lepton_Scale_Factor_ID  << "  for  Sample = " << IsData;



      // ======== Filling of Object Distributions ================================

      Fill_Object_Population() ;          

	  Fill_Object_Hist_After_Preselction_LvL( "Yes" , IsTopbjet, Channel ) ;      

      Fill_HiggsJet_Hist_Preselction_LvL( "FillHiggsJetDeltaRClear@Event", Channel  ) ; // Put DeltaR instring to fill DeltaRCleared Higgs  

      Hist_for_Leading_HiggsJet.at(22) ->Fill( DeltaR_Cleared_Higgsjet.size(), factor );


      Top_Candidate_Check(top_lepton, Channel) ;

      Tprime_Candidate_Reconstruction( ) ;


      ST_Sum_Evesel -> Fill( Scalar_Sum_pT, factor) ;    



   }// EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

   cout <<"\n Factor for " << OutputFileName << " is = " << factor ;
   cout <<"\n BtagFactor for " << OutputFileName << " is = " << btag_weight ;
   cout <<"\n LeptonFactor for " << OutputFileName << " is = " << Lepton_Scale_Factor_ID ;
   
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();

}
