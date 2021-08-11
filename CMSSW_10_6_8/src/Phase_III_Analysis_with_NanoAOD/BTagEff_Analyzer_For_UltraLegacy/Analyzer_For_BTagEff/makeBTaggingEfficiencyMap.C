// Use this one as a standard one for other files okay.


#include "TCanvas.h"
#include "TDirectory.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "Math/ProbFunc.h"
#include "TProfile.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TEfficiency.h"
#include "TArrow.h"
#include "TLine.h"
#include "TPad.h"
#include "TVirtualFitter.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <map>

#include "makeBTaggingEfficiencyMap.h"

using namespace ROOT;
using namespace ROOT::Math;

using namespace std ;




void makeBTaggingEfficiency(TString InputFileName )

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

  



   // Output root file is declared and named ============================

   TFile* input_file = new TFile(InputFileName);

   TString OutputFileName = InputFileName.ReplaceAll(".root","");

   OutputFileName  = OutputFileName + "_Map.root";
   
   TFile* output_file = new TFile(OutputFileName.Data(),"recreate");  


   // Output root file is declared and named ============================



   cout <<"\n Yo man It works for OutputFileName " << OutputFileName << endl;

// ================================Histograms are defined and declared for the root files ===========================


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
   TString  MET  = "MET" ;
   TString  IsTopbjet = "No";


        vector<Person> parr1 = {{"John", "Cooper", 32},
                                {"Theo", "Parrot", 23},
                                {"Aun", "Chao", 43},
                                {"Vivien", "Bardot", 67}};



    for (const auto &arr : parr1) {
        cout << "Name: " << arr.name << endl
             << "Surname: " << arr.surname << endl
             << "Age: " << arr.age << endl;
    }                                

//---------------------------------------BTagging Scalefactors------------------------------

   // BTagCalibrationReader reader_up(BTagEntry::OP_LOOSE, "up");  // sys up

   // BTagEntry::OperatingPoint DeepCSV_OP = BTagEntry::OP_LOOSE; // required for SF calculation

   // BTagEntry::JetFlavor jet_Flavor  =  BTagEntry::FLAV_B ; // required for SF calculation
// Event Loop started here and main analyzing code starts ==============================================================================





   output_file->Write();   // output file is written here and closed
   output_file->Close();

}


int main(int argc, char **argv)
{
       if (argc < 2){ 
                std::cout<<"pass the text file containing root file names "<<std::endl;
                exit(0);
        }

        gROOT->ProcessLine("#include <vector>");
        gROOT->ProcessLine("#include <map>");

        // UL17_Analyzer_NANO_AOD a(argv[1]);


        TString InputFile = argv[1];
      
        // for running test in Loops 

        makeBTaggingEfficiency(InputFile); 



} 