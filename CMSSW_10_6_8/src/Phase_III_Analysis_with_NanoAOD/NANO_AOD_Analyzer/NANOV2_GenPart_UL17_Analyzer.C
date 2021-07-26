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



        TString Higgs_Working_Point2[13] = {
                                           "No" ,
                                           "PT300SD70-160",
                                           "PT300SD80-160",
                                           "PT300SD90-160",
                                           "PT350SD70-160",
                                           "PT350SD80-160",
                                           "PT350SD90-160",
                                           "PT400SD70-160",
                                           "PT400SD80-160",
                                           "PT400SD90-160",
                                           "PT450SD70-160",
                                           "PT450SD80-160",
                                           "PT450SD90-160",
                           } ;              

         for (int ji = 0; ji < 1; ++ji)
         { // Loop over Higgs working point
              // if ( ji != 0 ) a.Loop(OutputFileName.Data(), "Yes" , "No" , "GenStudyHiggs" + Higgs_Working_Point2[ji] );                     
              // else  a.Loop(OutputFileName.Data(), "Yes" ,  "GenStudyMuonWithPT" ,"No"); 
         }
        // Another sets of run
        // For General Run Put this
        // a.Loop( OutputFileName.Data(), "Yes", "GenStudyMuonWithPT", "No" ); 
        // a.Loop( OutputFileName.Data(), "Yes", "GenStudyMuonWithoutPT",  "GenStudyHiggs"); 

        // a.Loop(OutputFileName.Data(), "Yes" , "No" , "GenStudyHiggsWW" );                     
        // a.Loop(OutputFileName.Data(), "Yes" , "No" , "GenStudyHiggs4q" );  

        // a.Loop(OutputFileName.Data(), "Yes" , "No" , "GenStudyHiggswithPtSD"  );                     

        a.Loop(OutputFileName.Data(), "Yes" , "GenStudyElectron" , "No"  );                     
                           

} 







// void UL17_Analyzer_NANO_AOD::Loop(TString OutputFileName)

void UL17_Analyzer_NANO_AOD_with_LepJetClean::Loop(TString OutputFileName, TString Channel, TString LeptonIsolation , TString Higgs_WP)
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
   
   // Output root file is declared and named ============================

   // if ( JetforIsolation.Contains("Yes")) OutputFileName = OutputFileName + "_Higgs90-160_12-01-21.root";
   // if ( JetforIsolation.Contains("No")) OutputFileName = OutputFileName + "_Full_Selection_Check_12-01-21.root";

   if ( Higgs_WP.Contains("GenStudyHiggs"))  OutputFileName = OutputFileName + Higgs_WP ;
   if ( LeptonIsolation.Contains("GenStudyMuon")) OutputFileName  = OutputFileName + "_" + LeptonIsolation + "_10-02-21.root";
   if ( LeptonIsolation.Contains("GenStudyElectron")) OutputFileName  = OutputFileName + "_" + LeptonIsolation + "_10-02-21.root";
   if ( LeptonIsolation.Contains("No")) OutputFileName  = OutputFileName + "_10-02-21.root";


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
   // Define_Kinematic_Histo_for_HiggsJet() ;
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
   TString  UseSortedJets = "Sorting" ;
   TString  Filling_at_Preselection = Channel ; // Put it Yes for preselection filling
   TString  MET  = "MET" ;
   TString  IsTopbjet = "No";

// Event Loop started here and main analyzing code starts ==============================================================================

   Luminosity_Normalization(OutputFileName) ;

   Find_Object_type_From_Sample(OutputFileName) ;

   for (Long64_t jentry= 0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 421) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Cut_Efficiency_Flow->Fill(0.5, factor);     // for Total events in MC sample





      Clear_Vector() ;

      //========= Preselection of event requiring atleast of lepton and jet =====================================================================
      if ( PV_npvsGood == 0 ) continue;


      Cut_Efficiency_Flow->Fill(1.5, factor);     // for Primary Vertex Passed events
      Cut_Efficiency_Flow->Fill(2.5, factor);     // for MuTrigger Passed events

      Good_PV_Histo ->Fill( PV_npvsGood,factor);

      
      nLepton = nElectron + nMuon ;

      top_muon = -1 ;
      top_electron = -1 ;

      IsTopbjet = "No";

	    // if (!( nFatJet > 0  ))   continue ;


      Cut_Higgs_Tagging_Flow -> Fill(0.5, factor);


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

      //=============================== Generator Fat Jet Selection =====================================================================================================

      // cout << "\n No. of fatjet = " << nFatJet << endl;

      if ( Higgs_WP.Contains("GenStudyHiggs") ) {

          Study_of_Higgs_GenPart_Information(Higgs_WP) ;

          if ( gen_udscquark.size() != 0 ) {
                  Loop_Over_FatJet(Filling_at_Preselection + "FatJetSorting" + Higgs_WP) ;
                  Cut_Higgs_Tagging_Flow -> Fill(1.5, factor);
          }

          if ( n_AK8Jet.size() > 0 )FatJet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection);      // PASS "NO" FOR NO FILLING    Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet 

          // Whether you sort or not this line happens

          n_AK8Jet = fatjet_sort ;

          if ( Filling_at_Preselection.Contains("Yes") && ( n_AK8Jet.size() > 0 )   ) {   
           
                      Cut_Higgs_Tagging_Flow -> Fill(2.5, factor);
                      Selection_Comparison_HiggsTagging( Higgs_WP ) ;

          } 

          if ( Filling_at_Preselection.Contains("No") ) HiggsTagging_Using_PT_SD_Tau_N_Deep( Higgs_WP ) ; 


      }
      //===================================== Generator Level Muon Selection ==============================================================================

      // cout << "\n No. of muon = " << nMuon ;

	    if ( LeptonIsolation.Contains("GenStudyMuon") ) {

            Study_of_Muon_GenPart_Information() ;

            if ( gen_Tmuon_idx != -1 ) Loop_Over_Muon( Filling_at_Preselection + "Muon" + LeptonIsolation) ;

            Check_CleanFatJet_For_Event_N_Fill( Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet

            h_object_no.at(4) ->Fill(n_AK8Jet.size(), factor );       //  index 4   for nFatJet  Filling Population Plot    


            //============================== Jet Selection =======================================================================

            // cout << "\n No. of jet = " << nJet ;

            Check_CLeanedJet_For_Event_N_Fill( Filling_at_Preselection) ;  /// PUT "Yes" for filling 


            h_object_no.at(3) ->Fill(n_jet.size(), factor );      //  index 3   for nJet  Filling Population Plot
            h_object_no.at(5) ->Fill(n_forwjet.size(), factor );  //  index 5   for nForwJet  Filling Population Plot


            // if you want to continue with the sorted jets Put "Sorting" or else "No"


            Jet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection); 


            FatJet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection);      // PASS "NO" FOR NO FILLING    Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet 

            // Whether you sort or not this line happens
            n_jet = jet_sort ;
            n_AK8Jet = fatjet_sort ;


            // ==================== Generate Clean Jet from fatJet using dR > 1.2 and Check is for deltaR plots ======================///////////////////

            // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots

            if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet(Filling_at_Preselection +"CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots


            h_object_no.at(6) ->Fill(n_cleanjet.size(), factor );   //  index 6   for nCleanJet  Filling Population Plot


	         //====== Jet Selection Ends=====================================================================================================
	  

            jet_copy = n_cleanjet;  


            if ( n_Mu.size() > 0  && (!LeptonIsolation.Contains("No")) ) {

             if ( Filling_at_Preselection.Contains("Yes") )  top_muon =  Lepton_Isolation_Study_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
             if ( Filling_at_Preselection.Contains("No") )   top_muon =  Selection_Lepton_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
             
             top_muon =   n_Mu[0];

             // cout << "\n\n For Event,   " << jentry ;
             // Check_DeltaR_N_Pt_for_Closest_Jet_to_Muon(top_muon ) ;
            }   

      } 
      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      


      //================================Generator Level Electron Selection==========================

      if ( LeptonIsolation.Contains("GenStudyElectron") ) {

            Study_of_Electron_GenPart_Information() ;

            // cout << "\n gen_Tele_idx = "  << gen_Tele_idx ;

            if ( gen_Tele_idx != -1 ) Loop_Over_Electron( Filling_at_Preselection + "Electron" + LeptonIsolation) ;

            Check_CleanFatJet_For_Event_N_Fill( Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet

            h_object_no.at(4) ->Fill(n_AK8Jet.size(), factor );       //  index 4   for nFatJet  Filling Population Plot    


            //============================== Jet Selection =======================================================================

            // cout << "\n No. of jet = " << nJet ;

            Check_CLeanedJet_For_Event_N_Fill( Filling_at_Preselection) ;  /// PUT "Yes" for filling 


            h_object_no.at(3) ->Fill(n_jet.size(), factor );      //  index 3   for nJet  Filling Population Plot
            h_object_no.at(5) ->Fill(n_forwjet.size(), factor );  //  index 5   for nForwJet  Filling Population Plot


            // if you want to continue with the sorted jets Put "Sorting" or else "No"


            Jet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection); 


            FatJet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection);      // PASS "NO" FOR NO FILLING    Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet 

            // Whether you sort or not this line happens
            n_jet = jet_sort ;
            n_AK8Jet = fatjet_sort ;


            // ==================== Generate Clean Jet from fatJet using dR > 1.2 and Check is for deltaR plots ======================///////////////////

            // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots

            if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet(Filling_at_Preselection +"CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots


            h_object_no.at(6) ->Fill(n_cleanjet.size(), factor );   //  index 6   for nCleanJet  Filling Population Plot


           //====== Jet Selection Ends=====================================================================================================
    

            jet_copy = n_cleanjet;  


            if ( n_ele.size() > 0  && (!LeptonIsolation.Contains("No")) ) {

             if ( Filling_at_Preselection.Contains("Yes") )  top_electron =  Electron_Isolation_Study_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
             if ( Filling_at_Preselection.Contains("No") )   top_electron =  Selection_Electron_Isolation_Using_MiniIso_2DLepIso (LeptonIsolation, Filling_at_Preselection);
             
             top_electron =   n_ele[0];

             // cout << "\n\n For Event,   " << jentry ;
             Check_DeltaR_N_Pt_for_Closest_Jet_to_Electron(top_electron ) ;
            }   

      }            


      // if ( Filling_at_Preselection.Contains("Yes") )  continue ;
      // If only test are running then Filling_at_Preselection = "Yes" Otherwise No for full run


   }  // EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

    
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();

   cout << "\n Total muon events      = " << passed_total_events ;
   cout <<"\n passed_dR               = " << passed_dR  
        << " \n && passed_dPt         = "   << passed_dPt  
        << " \n && passed_only_dRdPt  = " << passed_only_dRdPt
        << " \n && No pass            = " <<passed_no_dRdPt 
        << " \n && passed_both_dRdPt  = " << passed_both_dRdPt
        << " \n Also noclosejet       = " << passed_nojet
        << " \n && factor             = "   << factor ;
}


// "Total Events",                //0 
// "Primary_Vertex",              //1 
// "HLT_Mu50 Trigger",            //2 
// "Forward Jet Tag"    ,         //3 
// "MET Cut" ,                    //4 
// "Muon Cut",                    //5 
// "AK8 Jet Tag" ,                //6 
// "Clean Jet Tag",               //7 
// "Higgs Tag",                   //8 
// "Lep Iso",                     //9 
// "dR check(mu, H)",             //10
// "Higgs_Pt Cut",                //11
// "bjet tag",                    //12
// "dR check(bjet)" ,             //13
// "St Cut"  ,                    //14


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


 // For Sample = Tprime_M1500_UL17   Xsections = 10.64 && Events = 400000

 // For Sample = Tprime_M1500_UL17   Type of Muon = PromptLepton  &&& Type of Jet = Higgs


 // Total muon events      = 6911
 // passed_dR               = 5838 
 // && passed_dPt         = 6166 
 // && passed_only_dRdPt  = 5697 
 // && No pass            = 319 
 // && passed_both_dRdPt  = 6307 
 // Also noclosejet       = 285 
 // && factor             = 0.0011047