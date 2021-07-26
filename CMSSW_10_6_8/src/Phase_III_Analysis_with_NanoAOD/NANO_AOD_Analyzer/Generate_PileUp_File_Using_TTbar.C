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
        
        a.Loop(OutputFileName.Data(), "Muonic" ,     "dR_04_OR_dPt_40" ,"PT300SD90-160Deep10","MCSample"); 

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
   
   // Output root file is declared and named ============================

   OutputFileName = OutputFileName + "_PileUp_24-Mar-21.root"  ;

   
   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

   // Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works";

// ================================Histograms are defined and declared for the root files ===========================

   Define_Histo_For_Global_Var() ;


//=================================== Histograms are defined and declared for the root files =============================



   TString  UseSortedJets = "Sorting" ;
   TString  Filling_at_Preselection = Channel ; // Put it Yes for preselection filling
   TString  MET  = "MET" ;
   TString  IsTopbjet = "No";


// Event Loop started here and main analyzing code starts ==============================================================================

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 1000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;


	    // cout << "\n\n For Event,   " << jentry  << " PileUP True = " << Pileup_nTrueInt ;
      Clear_Vector() ;

      h_MC -> Fill ( Pileup_nTrueInt);

     

   }  // EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

    
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();


}
