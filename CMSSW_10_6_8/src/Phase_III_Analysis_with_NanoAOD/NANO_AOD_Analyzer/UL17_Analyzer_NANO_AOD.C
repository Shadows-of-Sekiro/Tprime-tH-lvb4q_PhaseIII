////////////////////////////////////////////////////////////
// This class has been automatically generated on         //
// Wed Jan 20 12:51:00 2021 by ROOT version 6.14/06       // 
// from TTree Events/Events                               //
// found on file: tree_4.root                             // 
////////////////////////////////////////////////////////////

// #define UL17_Analyzer_NANO_AOD_cxx
// #include "UL17_Analyzer_NANO_AOD.h"

#define UL17_Analyzer_NANO_AOD_with_LepJetClean_cxx
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


          a.Loop(OutputFileName.Data(), "Lep" , "No" ,Higgs_Working_Point2[ji],"MCSample"); 

         }
        // Another sets of run
        // For General Run Put this
        // a.Loop( OutputFileName.Data(), "No", "dR>0.2_OR_dPt>20GeV",  "PT300SD70-160Tau80"); 
      // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp"); 

      a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleEvntW"); 

      // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleNoPU"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleNoPU"); 

      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp660"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp692"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithPileUp724"); 

      // a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithL1VFP"); 
      // a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleWithL1VFP"); 
} 







// void UL17_Analyzer_NANO_AOD::Loop(TString OutputFileName)

void UL17_Analyzer_NANO_AOD_with_LepJetClean::Loop(TString OutputFileName, TString Channel, TString LeptonIsolation , TString Higgs_WP, TString IsData)
{
// For Run put No, For Check Put Yes ....... Remember !!!!   
//======================================================================================================================================//
//   In a ROOT session, you can do:	
//      root> .L UL17_Analyzer_NANO_AOD.C
//      root> UL17_Analyzer_NANO_AOD t
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
  
   TString xsec_str = OutputFileName ;

   Trigger_Check = IsData  ;

   MC_Channel  =  Channel ;
   
   // Output root file is declared and named ============================

   // if ( JetforIsolation.Contains("Yes")) OutputFileName = OutputFileName + "_Higgs90-160_12-01-21.root";
   // if ( JetforIsolation.Contains("No")) OutputFileName = OutputFileName + "_Full_Selection_Check_12-01-21.root";

   OutputFileName = OutputFileName + "_"  + Channel ;

   if ( Higgs_WP.Contains("PT") || Higgs_WP.Contains("SD"))  OutputFileName = OutputFileName + "_Higgs" + Higgs_WP ;
   // if ( LeptonIsolation.Contains("MiniIso")) OutputFileName  = OutputFileName + "MuIso_" + LeptonIsolation + "_03-Feb-21.root";
   if ( LeptonIsolation.Contains("MiniIso")) OutputFileName  = OutputFileName + "_LepIso" ;
   if ( LeptonIsolation.Contains("dR")) OutputFileName  = OutputFileName + "_2DLepIso_" + LeptonIsolation ;   
   if ( LeptonIsolation.Contains("No")) OutputFileName  = OutputFileName ;
   if ( IsData.Contains("L1VFP"))  OutputFileName  = OutputFileName + "_L1VFP_22-Mar-21.root";
   if ( IsData.Contains("PileUp"))  OutputFileName  = OutputFileName + "_"+ IsData +"_22-Mar-21.root";
   if ( IsData.Contains("NoPU"))    OutputFileName  = OutputFileName + "_EvntLvlChck_14-Apr-21.root";

   // OutputFileName = OutputFileName + "_NoMatchLep_11-12-20.root";

   
   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

   // Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works";

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
   bool Lepton_Trigger = false ;

   int   top_lepton = -1 ;

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


//..................... Luminosity Weight ........................................

    Luminosity_Normalization(OutputFileName) ;
 
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



// Event Loop started here and main analyzing code starts ==============================================================================


   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 1000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Cut_Efficiency_Flow->Fill(0.5, factor);     // for Total events in MC sample

	    // cout << "\n\n For Event,   " << jentry ;
      Clear_Vector() ;

      //========= Preselection of event requiring atleast of lepton and jet =====================================================================
      if ( PV_npvsGood == 0 ) continue;

      if (IsData.Contains("PileUp")) {
          
          PU_factor   = PUWeights(Pileup_nTrueInt)    ;       // factor from PileUp root file store locally
          // factor      = lumi_factor * PU_factor * L1PreFiringWeight_Nom ;
          factor      = lumi_factor * PU_factor  ;

          // cout << "\n   Pile Up factor = " << PU_factor <<"  for pu True = " << Pileup_nTrueInt ;
      }


      if (IsData.Contains("L1VFP")) {

        factor = lumi_factor * L1PreFiringWeight_Nom ;

      }  


      Cut_Efficiency_Flow->Fill(1.5, factor);     // for Primary Vertex Passed events

      Good_PV_Histo ->Fill( PV_npvsGood,factor);


      Lepton_Trigger = false ;

      Lepton_Trigger = Lepton_Trigger_Check() ;

      if ( Lepton_Trigger == 0 ) continue ;

      Cut_Efficiency_Flow->Fill(2.5, factor);     // for MuTrigger Passed events


      
      nLepton = nElectron + nMuon ;

      top_muon = -1 ;

      top_electron  = -1 ;

      top_lepton    = -1 ;


      IsTopbjet = "No";

	  // if (!( nLepton > 0  && nFatJet > 0  ))   continue ;

      Filling_at_Preselection = "No" ;
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

      // // ========================Study Jet Lepton Cleaning =============================================
    
      // Study_JetLepton_Cleaning_Effect() ;

      // continue ;

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



      Check_Cleaned_Bjet_After_Muon_Isolation( "loose");


	    //====== Jet Selection Ends=====================================================================================================
	  





      // If only test are running then Filling_at_Preselection = "Yes" Otherwise No for full run
      Filling_at_Preselection = "No" ;
      ///////-========-HERE WE AFTER SELECTION OF EACH PBJECTS AND TEST WE CHECK SELECTIONS AND FILL SELECTION FLOW HISTOGRAMS  =====---/////////////////////////
      //////====================== ALSO FILL EACH OBJECT AT THIS TIME BUDDY ============================//////////////////////////



      if ( n_forwjet.size() == 0)  continue ; 

      Cut_Efficiency_Flow -> Fill( 3.5, factor);   // Forward Jet tag
      
      // Fill_Lepton_Hist_Preselction_LvL( "YesMET"  , 0 , 0) ; // both entries 0 for YesMET to Fill or NoMET  

      if ( MET_pt < 50.0 )   continue ;

      Cut_Efficiency_Flow -> Fill( 4.5, factor);    // METcut 

      if ( ( n_Mu.size() + n_ele.size() ) == 0 )  continue ;

      Cut_Efficiency_Flow -> Fill ( 5.5, factor);   // Lepton tag in the event

      Lepton_Scale_Factor_ID =  factor ;  // KEEPING LEPTON SCALE ID FACTOR SAME AS OTHER EVENT FACTORS, UNTILL CALCULATED


      if ( n_AK8Jet.size() == 0) continue ;  

      Cut_Efficiency_Flow -> Fill (6.5, factor);   // Fatjet tag

      if ( n_cleanjet.size() == 0 ) continue ;


      //=== PRESELECTION LEVEL CLEARED ================///////////////////

      Cut_Efficiency_Flow -> Fill ( 7.5, factor);  // Clean jet tag

      Scalar_Sum_pT_Function( Channel) ; // Fiiled and calculated after preselection 

      if (Filling_at_Preselection.Contains("No")) ST_Sum_Presel -> Fill(Scalar_Sum_pT, factor) ;
      // Fill_Object_Hist_After_Preselction_LvL( "Yes" ) ;

      if( b_jet.size() == 0 ) continue ;
    
      Cut_Efficiency_Flow -> Fill ( 8.5, factor); // bjet tag     


      // ST Selection cut  
      ST_Sum_LeadObj -> Fill( Scalar_Sum_pT, factor) ;

      if ( Scalar_Sum_pT < 600.0) continue ;


      Cut_Efficiency_Flow -> Fill ( 9.5, factor); // ST cut  

      //////============= Higgs Tagging Selections and Some Fucking Test ======================================///////////////////////////////////////////////

      if ( Filling_at_Preselection.Contains("Yes") && (!Higgs_WP.Contains("No"))) Selection_Comparison_HiggsTagging( Higgs_WP ) ;


      if ( Filling_at_Preselection.Contains("No") && (!Higgs_WP.Contains("No")) ) HiggsTagging_Using_PT_SD_Tau_N_Deep( Higgs_WP ) ;

      Hist_for_Leading_HiggsJet.at(16) ->Fill( Higgsjets.size(), factor );

      if ( Higgsjets.size() == 0 ) continue ;

      Cut_Efficiency_Flow -> Fill ( 10.5, factor); // Higgjet Tag


      Check_DeltaR_of_Higgs_wrt_Top_Lepton( Channel, "Mass" );

      Hist_for_Leading_HiggsJet.at(22) ->Fill( DeltaR_Cleared_Higgsjet.size(), factor );


      if ( DeltaR_Cleared_Higgsjet.size() != 0 ) Cut_Higgs_Tagging_Flow -> Fill(2.5, factor) ;

      Cut_Efficiency_Flow -> Fill ( 11.5, factor); // Mas and  DeltaR check for H, mu > 1.2       
      // ========================Check and Test Muon N Electron Isolation Methods =============================================

      // cout << "\n For Event,   " << jentry ;


     //-----------------For Muon Channel -------------------------------
      if ( n_Mu.size() > 0  && (!LeptonIsolation.Contains("No")) && Channel.Contains("Muonic") ) {

            jet_copy = n_cleanjet;  

            if ( Filling_at_Preselection.Contains("Yes") )  top_muon =  Lepton_Isolation_Study_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
            if ( Filling_at_Preselection.Contains("No") )   top_muon =  Selection_Lepton_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
      
            // top_muon =   n_Mu[0];

            // cout << "\n Pt_muon = " << Muon_pt[top_muon] ;    
    
            // cout << "\n Muon = " <<  top_muon ;
            // cout << "\n\n For Event,   " << jentry ;
            // Check_DeltaR_N_Pt_for_Closest_Jet_to_Muon(top_muon ) ;      

            // cout << "\n In main Lepton_Pt = "  << Muon_pt[top_muon]  << "   for Muon = "  << top_muon; 

            // W_mass_constraint_V2(top_muon, Channel) ;
            // W_mass_constraint(top_muon, Channel) ;


            top_lepton    =   top_muon ;                     
            // top_lepton    =   n_Mu[0];

            if ( top_lepton != -1 )   Lepton_Scale_Factor_ID = Muon_ID_ScaleFactor_UL2017( Muon_pt[top_lepton], Muon_eta[top_lepton]) ;

            // if ( top_lepton != -1 )            W_mass_constraint_V2(top_lepton, Channel) ;
            
            // if ( top_lepton != -1 )            Top_Candidate_Check(top_lepton, Channel) ;
      }   

      //-----------------For Electron Channel-------------------------------
      if ( n_ele.size() > 0  && (!LeptonIsolation.Contains("No")) && Channel.Contains("Electronic") ) {

            jet_copy = n_cleanjet;  

            if ( Filling_at_Preselection.Contains("Yes") )  top_electron =  Electron_Isolation_Study_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
            if ( Filling_at_Preselection.Contains("No") )   top_electron =  Selection_Electron_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
       

            // cout << "\n Pt_ele = " << Electron_pt[top_electron] ;

            // cout << "\n Ele = " <<  top_electron ;            
            // cout << "\n\n For Event,   " << jentry ;
            // Check_DeltaR_N_Pt_for_Closest_Jet_to_Electron(top_electron ) ;

            // W_mass_constraint(top_electron, Channel) ;

            top_lepton    =   top_electron ;                     
            // top_lepton    =   n_ele[0];

            // if ( top_lepton != -1 )            W_mass_constraint_V2(top_lepton, Channel) ;
            
            // if ( top_lepton != -1 )            Top_Candidate_Check(top_lepton, Channel) ;
            
            if ( top_lepton != -1 )  Lepton_Scale_Factor_ID = Electron_ID_ScaleFactor_UL2017( Electron_pt[top_lepton], Electron_eta[top_lepton]) ;
            // if ( top_lepton != -1 )  Lepton_Scale_Factor_ID = Electron_ID_ScaleFactor_UL2017( Electron_pt[top_lepton], 1.0) ;



      }

      // top_muon =  Selection_Lepton_Isolation_Using_MiniIso_2DLepIso ("MiniIsoTight", "No");
      
      if ( top_lepton == -1 ) continue ; // lepton after passing Isolation is reffered now as top_lepton

      // Lepton_Scale_Factor_ID = Lepton_Scale_Factor_ID * factor ;
      if ( IsData.Contains("NoPU"))          Lepton_Scale_Factor_ID =  factor ;  // KEEPING LEPTON SCALE ID FACTOR SAME AS OTHER EVENT FACTORS, UNTILL CALCULATED      

      else       Lepton_Scale_Factor_ID = Lepton_Scale_Factor_ID * factor ;

      Cut_Efficiency_Flow -> Fill ( 12.5, factor); // Lep-Isolation Selection      

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      Fill_Object_Population() ;

      Fill_Object_Hist_After_Preselction_LvL( "Yes" , IsTopbjet, Channel ) ;

      Top_Candidate_Check(top_lepton, Channel) ;

      Tprime_Candidate_Reconstruction( ) ;

      Fill_HiggsJet_Hist_Preselction_LvL( "FillHiggsJet"  ) ; // Put DeltaR instring to pass DeltaR check for H, mu > 1.2 in plots  

      ST_Sum_Evesel -> Fill( Scalar_Sum_pT, factor) ;
      
      // if ( Filling_at_Preselection.Contains("Yes") )  


      continue ;

      

      ///////////////////////////////////Not concerned to this at this stage ///////////////////////////////////////////////////////


      // if ( Higgsjets.size() > 0 ) Fill_HiggsJet_Hist_Preselction_LvL( "CheckHiggsJet") ; // Put "CheckHiggsJet" string  for Delta R check wrt Muon 
      // Put "FillHiggsJet" string to only fill




 

      Cut_Efficiency_Flow -> Fill ( 13.5, factor); // Higgs pT cut


      if( b_jet.size() == 0 ) continue ;
    

      Cut_Efficiency_Flow -> Fill ( 12.5, factor); // bjet tag 

      Check_DeltaR_of_bjet_wrt_Top_Lepton_n_Higgs( Channel) ;

      if (top_bjet  == -1) continue ;

      IsTopbjet = "Topbjet";

      Cut_Efficiency_Flow -> Fill ( 14.5, factor); // DeltaR check for bjet tag 

      // Fill_Object_Hist_After_Preselction_LvL( "Yes" , IsTopbjet ) ;

      Fill_HiggsJet_Hist_Preselction_LvL( "FillDeltaRClearHiggsJet" + IsTopbjet ) ; // Put DeltaR instring to pass DeltaR check for H, mu > 1.2 in plots  

      ST_Sum_LeadObj -> Fill( Scalar_Sum_pT, factor) ;

      if ( Scalar_Sum_pT < 500.0) continue ;

      ST_Sum_Evesel -> Fill( Scalar_Sum_pT, factor) ;

      Cut_Efficiency_Flow -> Fill ( 14.5, factor); // ST cut

   }  // EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

    
   // Muon_Scale_file->Close();
   PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();

   cout << "\n Total muon events      = " << passed_total_events ;
   cout <<"\n passed_dR               = " << passed_dR  
        << " \n && passed_dPt         = " << passed_dPt  
        << " \n && passed_only_dRdPt  = " << passed_only_dRdPt
        << " \n && No pass            = " << passed_no_dRdPt 
        << " \n && passed_both_dRdPt  = " << passed_both_dRdPt
        << " \n Also noclosejet       = " << passed_nojet
        << " \n && factor             = " << factor ;   
}


// "Total Events",                //0 
// "Primary_Vertex",              //1 
// "HLT_Mu50 Trigger",            //2 
// "Forward Jet Tag"    ,         //3 
// "MET Cut" ,                    //4 
// "Muon Cut",                    //5 
// "AK8 Jet Tag" ,                //6 
// "Clean Jet Tag",               //7 
// "bjet tag",                    //8 
// "Lep Iso",                     //9 
// "St Cut"  ,                    //10
// "Higgs Tag",                   //11
// "dR check(mu, H)",             //12
// "Higgs_Pt Cut",                //13
// "dR check(bjet)" ,             //14


// fOR Muon Isolation study, Cut flow histogram
 // "No Isolation",             //0 
 // "MiniIsoLoose",             //1 
 // "MiniIsoMedium",            //2 
 // "MiniIsoTight",             //3 
 // "MiniIsoVeryTight",         //4 
 // "dR > 0.2 OR dPt > 20GeV",  //5 
 // "dR > 0.3 OR dPt > 20GeV",  //6 
 // "dR > 0.4 OR dPt > 20GeV",  //7 
 // "dR > 0.2 OR dPt > 40GeV",  //8 
 // "dR > 0.3 OR dPt > 40GeV",  //9 
 // "dR > 0.4 OR dPt > 40GeV"   //10