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

        if( (! OutputFileName.Contains("Electron")) && (! OutputFileName.Contains("Muon")) ) {

              a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSampleEvntW"); 

        }


        if( OutputFileName.Contains("Muon"))     a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10", "MuonSampleData");
        if( OutputFileName.Contains("Electron")) a.Loop(OutputFileName.Data(), "Electronic" , "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10", "ElectronSampleData");   
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
   

   MC_Channel  =  Channel ;



   cout <<"\n Factor for " << OutputFileName << " is = " << factor ;


   // Output root file is declared and named ============================

   // OutputFileName = OutputFileName + "_"  + Channel ;

   // if ( Higgs_WP.Contains("PT") || Higgs_WP.Contains("SD"))  OutputFileName = OutputFileName + "_Higgs" + Higgs_WP ;
   // if ( Higgs_WP.Contains("Deep") )  OutputFileName = OutputFileName + "_HiggsDeepMD";


   if ( IsData.Contains("MCSampleEvntW"))  OutputFileName  = OutputFileName + "_BtagEff_2DPtEta_"+ "02-Aug-21.root";


   // OutputFileName = OutputFileName + "_NoMatchLep_11-12-20.root";

   
   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

   // Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works" << endl;

// ================================Histograms are defined and declared for the root files ===========================

   Define_Histo_For_Global_Var() ;
   Define_Kinematic_Histo_for_RecoObject();
   Define_2DHistogram_For_BtagEff() ;

//=================================== Histograms are defined and declared for the root files =============================

   float Eta = 0.0 ; 	
   int count = -1 ;
   int id = -1 ;       //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
   int nLepton = 0 ;
   int check = -1 ;
   float  PU_factor = 1.0 ;

   int   top_lepton = -1 ;
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


//---------------------------------------BTagging Scalefactors------------------------------

   // BTagCalibrationReader reader_up(BTagEntry::OP_LOOSE, "up");  // sys up

   // BTagEntry::OperatingPoint DeepCSV_OP = BTagEntry::OP_LOOSE; // required for SF calculation

   // BTagEntry::JetFlavor jet_Flavor  =  BTagEntry::FLAV_B ; // required for SF calculation
// Event Loop started here and main analyzing code starts ==============================================================================



   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 10000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Cut_Efficiency_Flow->Fill(0.5, factor);     // for Total events in MC sample

	  // cout << "\n\n For Event,   " << jentry ;

      factor  = 1.0 ;

      Clear_Vector() ;

      //========= Preselection of event requiring atleast of lepton and jet =====================================================================
      if ( PV_npvsGood == 0 ) continue;



      Cut_Efficiency_Flow->Fill(1.5, factor);     // for Primary Vertex Passed events


      Cut_Efficiency_Flow->Fill(2.5, factor);     // for MuTrigger Passed events

      Good_PV_Histo ->Fill( PV_npvsGood,factor);
    

      IsTopbjet = "No";

	  // if (!( nLepton > 0  && nFatJet > 0  ))   continue ;

      Filling_at_Preselection = "Yes" ;
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


      //============================== Jet Selection =======================================================================

      // cout << "\n No. of jet = " << nJet ;

      Check_CLeanedJet_For_Event_N_Fill( Filling_at_Preselection) ;  /// PUT "Yes" for filling 


      // if you want to continue with the sorted jets Put "Sorting" or else "No"


      Jet_sorting_pT_based_After_Cleaning(UseSortedJets + Filling_at_Preselection); 


      // Whether you sort or not this line happens
      n_jet = jet_sort ;

      // ==================== Generate Clean Jet from fatJet using dR > 1.2 and Check is for deltaR plots ======================///////////////////

      // cout << "\n For Event,   " << jentry ;

      Fill_BTaggingEff_2DHistogram( "loose") ;


      Check_Cleaned_Bjet_After_Muon_Isolation( Filling_at_Preselection + "loose");

	  //====== Jet Selection Ends=====================================================================================================


      ///////-========-HERE WE AFTER SELECTION OF EACH PBJECTS AND TEST WE CHECK SELECTIONS AND FILL SELECTION FLOW HISTOGRAMS  =====---/////////////////////////
      //////====================== ALSO FILL EACH OBJECT AT THIS TIME BUDDY ============================//////////////////////////


      Fill_Object_Population() ;    


      // Fill_Object_Hist_After_Preselction_LvL( "Yes" , IsTopbjet, Channel ) ; 


      Cut_Efficiency_Flow -> Fill( 3.5, factor);   // Forward Jet tag
      
      // Fill_Lepton_Hist_Preselction_LvL( "YesMET"  , 0 , 0) ; // both entries 0 for YesMET to Fill or NoMET  


      Cut_Efficiency_Flow -> Fill( 4.5, factor);    // METcut 


      Cut_Efficiency_Flow -> Fill ( 5.5, factor);   // Lepton tag in the event


      Cut_Efficiency_Flow -> Fill (6.5, factor);   // Fatjet tag

      if ( n_cleanjet.size() == 0 ) continue ;

      // double SF = DeepCSV2_bTag_SF_Calculator(DeepCSV_OP,  jet_Flavor, systype , Jet_pt_clean[0], 1.5); 


      // cout << "\n For Event,   " << jentry ;

      // cout << "\n Btag SF = " << SF  << endl ;


      //=== PRESELECTION LEVEL CLEARED ================///////////////////

      Cut_Efficiency_Flow -> Fill ( 7.5, factor);  // Clean jet tag


      if( b_jet.size() == 0 ) continue ;
    
      Cut_Efficiency_Flow -> Fill ( 8.5, factor); // bjet tag     


 
      Cut_Efficiency_Flow -> Fill ( 9.5, factor); // ST cut  

      // cout <<"\n Damn man!!";
      Cut_Efficiency_Flow -> Fill ( 10.5, factor); // Higgjet Tag

      Cut_Efficiency_Flow -> Fill ( 11.5, factor); // Mas and  DeltaR check for H, mu > 1.2   

      Cut_Efficiency_Flow -> Fill ( 12.5, factor); // Lep-Isolation Selection   

     



   }// EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

   // cout <<"\n Factor for " << OutputFileName << " is = " << factor ;
    
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();

}
