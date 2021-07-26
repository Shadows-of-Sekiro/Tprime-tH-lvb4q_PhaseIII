#define MC_Analyzer_NANO_AOD_cxx
#include "MC_Analyzer_NANO_AOD.h"
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

        MC_Analyzer_NANO_AOD a(argv[1]);
        TString InputTxtFile = argv[1];
        TString OutputFileName = InputTxtFile.ReplaceAll(".txt","_");
        
        // a.Loop(OutputFileName.Data(), 2, 400.0  , 70.0  , "BeforeCleaning");
        a.Loop(OutputFileName.Data());

} 


void MC_Analyzer_NANO_AOD::Loop(TString OutputFileName)
{
//========================================================================================================================================	
//   In a ROOT session, you can do:
//      root> .L MC_Analyzer_NANO_AOD.C
//      root> MC_Analyzer_NANO_AOD t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//
//     This is the loop skeleton where: jentry is the global entry number in the chain ientry is the entry number in the current Tree
//     Note that the argument to GetEntry must be: jentry for TChain::GetEntry
//    										       ientry for TTree::GetEntry and TBranch::GetEntry
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
      // if (Cut(ientry) < 0) continue;
	
//========================================================================================================================================

   if (fChain == 0) return;

// Output root file is declared and named ============================

   OutputFileName = OutputFileName + "09-12-20.root";

   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

// Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works";

// Histograms are defined and declared for the root files ==============================================================================

   // Define_Mt_Histo() ;  
   Histo_Cut_Efficiency_Flow() ;
   // Histo_Muon_ID_Study() ;

   // Define_2DMass_Histo();    // for gen level plots

   Define_NPtEta_Histo();
   Define_NPtEta_Histo_v2();
   // dRHisto_RecoObject();


   // Define_Tag_Jet_Histo() ;    // for tagged jets plots at reco level
   // Define_Reco_tagjetHisto() ;   
   // dR_tagjetHisto() ;     

   // Category_Object_Histo() ;     // for category I plots
   // Category_Object_dRHisto() ;     
   // Category_Object_MtHisto() ; 

// Histograms are defined and declared for the root files ==============================================================================
   float Eta = 0.0 ; 
   int 	 Muon_ID  = -1;		
   int count = -1 ;
   int id = -1 ;       //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
   int nLepton = 0 ;
   int check = -1 ;
// Event Loop started here and main analyzing code starts ==============================================================================


   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      
      if (ientry > 1000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

	  // cout << "\n For Event,   " << jentry ;
      Clear_Vector() ;

      // Preselection of event requiring atleast of lepton and jet =====================================================================

      nLepton = nElectron + nMuon ;

	  if (!( nLepton > 0  && nFatJet > 0  ))   continue ;

	  // Muon_ID ++ ;
	  // if ( jentry   == nentries - 1)	  cout <<" \n With 1st check, count = " << count <<"   n 2nd check, id = " << id <<"   n 3rd check, Muon_ID = " <<	Muon_ID << endl;


      //================================================= GENERAL SELECTION OF OBJECTS=================================================

      //====== Electron Selection =====================================================================================================

      // cout << "\n No. of electron = " << nElectron ;

      id = 2 ; //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 

	  count = -1 ;

      for (int i = 0; i < nElectron; ++i)
      {

    
      	if (Electron_cutBased[i] < 2.0 ) 					continue ;
      	Eta = fabs (Electron_eta[i]) ;
      	// cout << "\n before Eta = " << Eta;
      	if ( Eta > 1.44 && (Eta < 1.56 || Eta > 2.5) ) 		continue ;        	
  		if (Electron_pt[i] < 40.0 ) 						continue ;	

		b_jet.push_back(i);
      	
      	count ++; 

      	if ( count >= 2) continue;
      	h_object_pt.at (count + id)    ->Fill(Electron_pt[i]);       // electron
        h_object_eta.at(count + id)   ->Fill(Electron_eta[i]);
        h_object_phi.at(count + id)   ->Fill(Electron_phi[i]);

		
      	// cout << "\n after selected, count = " << count ;

      }
      

      h_object_no.at(1) ->Fill(b_jet.size() );    // HERE FOR ELECTRON.... MAN!!!!

	  //====== Electron Selection Ends =====================================================================================================
      //====== Muon Selection =====================================================================================================

      // cout << "\n No. of muon = " << nMuon ;

      id = 0 ; //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
	  count = -1 ;
	  check = -1 ;

      for (int ki = 0; ki < nMuon; ++ki)
      {

      	Muon_ID = Muon_highPtId[ki] ;
 
      	// cout << "\n\n Before Selection, muon have pT = " << Muon_pt[ki] << "  n eta = " << Muon_eta[ki] << "  n HighpTID = " << Muon_ID ;
      	// printf("Muon_highPtId = %d", Muon_highPtId[ki] )  ;

      	if ( fabs(Muon_eta[ki]) > 2.1 ) 			continue ;
      	if ( Muon_ID < 1  ) 						continue ;
      	if ( Muon_pt[ki] < 40.0 ) 					continue ;
		
		n_Mu.push_back(ki);

		count ++; 

      	if ( count >= 2) continue;
      	h_object_pt.at (count + id)   ->Fill(Muon_pt[ki]);       // muon
        h_object_eta.at(count + id)   ->Fill(Muon_eta[ki]);
        h_object_phi.at(count + id)   ->Fill(Muon_phi[ki]);

      	// cout << "\n\n After Selection, muon have pT = " << Muon_pt[ki] << "  n eta = " << Muon_eta[ki] << "  n HighpTID = " << Muon_ID ;

      }

	  h_object_no.at(0) ->Fill(n_Mu.size() );


      //====== Muon Selection Ends =====================================================================================================
      //====== Jet Selection =====================================================================================================
      // cout << "\n No. of jet = " << nJet ;

      id = 4 ; //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
	  count = -1 ;      

      for (int ji = 0; ji < nJet; ++ji)
      {
      	if ( Jet_pt[ji] < 30.0 ) 				continue ;
      	if ( fabs(Jet_eta[ji]) > 2.4 )			continue ;
      	if ( Jet_jetId[ji] < 1 ) 				continue ;

        n_jet.push_back(ji);

		count ++; 

      	if ( count >= 2) continue;
      	h_object_pt.at (count + id)   ->Fill(Jet_pt[ji]);       // ak4jet
        h_object_eta.at(count + id)   ->Fill(Jet_eta[ji]);
        h_object_phi.at(count + id)   ->Fill(Jet_phi[ji]);

      }


      h_object_no.at(3) ->Fill(n_jet.size()) ;

      //====== Jet Selection Ends=====================================================================================================
      //====== Fat Jet Selection =====================================================================================================

      // cout << "\n No. of fatjet = " << nFatJet << endl;

      id = 12 ; //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
	  count = -1 ;      

      for (int fi = 0; fi < nFatJet; ++fi)
      {
      	if ( FatJet_pt[fi] < 200.0 ) 				continue ;
      	if ( fabs(FatJet_eta[fi]) > 2.4 )			continue ;
      	if ( FatJet_jetId[fi] < 1 ) 				continue ;   // for 2016, < 1, 2017/18 < 2

        n_AK8Jet.push_back(fi);

		count ++; 

      	if ( count >= 2) continue;
      	h_object_pt.at (count + id)   ->Fill(FatJet_pt[fi]);       // AK8jet
        h_object_eta.at(count + id)   ->Fill(FatJet_eta[fi]);
        h_object_phi.at(count + id)   ->Fill(FatJet_phi[fi]);

        h_AK8_PUPPISDmass.at(count)   -> Fill(FatJet_msoftdrop[fi]);
        h_AK8_PUPPItau42.at(count) 	  -> Fill((FatJet_tau4[fi] / FatJet_tau2[fi]));

        h_AK8_CHStau42.at(count) 	  -> Fill(FatJet_deepTagMD_H4qvsQCD[fi]);
        h_AK8_tau32.at(count) 		  -> Fill(FatJet_deepTag_H[fi]);        

      }

      h_object_no.at(2) ->Fill(n_AK8Jet.size() ) ;

   }

// Event Loop ended here and main analyzing code ends =================================================================================

 
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();
}
