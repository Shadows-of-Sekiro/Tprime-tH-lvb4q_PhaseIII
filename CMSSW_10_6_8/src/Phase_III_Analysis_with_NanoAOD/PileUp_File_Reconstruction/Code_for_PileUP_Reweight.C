// for pileup reweight calculations

#include "TROOT.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"
#include "TGraph.h"
#include "TPad.h"
#include "TFile.h"
#include "TVirtualPad.h"
#include "TH1F.h"
#include "TPaveStats.h"
#include <iostream>
#include <fstream>
#include "THStack.h"
#include "TPaveLabel.h"

using namespace std ;

void PileUP_Cal()
	{
			// TFile *f2	 = new TFile("PileUp_ScalefactorsUL2017_16Mar21_66.root","recreate");
			TFile *f2	 = new TFile("PileUp_ScalefactorsUL2017_24Mar21_724.root","recreate");

			TCanvas *C = new TCanvas("C","Sig/Bkg",1000,400) ; 

			// TString Local_Path  = "/home/weapon-x/Ubuntu_VLQ_Analysis_VMWARE/Phase_II_Analysis/PileUP_Cal2016/TTbar_PileUp_Files/" ;
			TString Lpc_Path	= "/afs/cern.ch/work/a/achhetri/NANO_AOD/CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/PileUp_File_Reconstruction/";

    		char input  = 'N';

			// cout << "Where are you now Local(Y/y) or on lpc(N/n) = " <<endl ;
			// cin  >>  input ;

			TString path_data, path_MC ;
			//TString path_Signal = "/home/logan/VLQAnalysis/New_Method/PUPPI_files/Tb_tH_LH_MiniAoDv2/MET_Test_060519/" ;
			// if ( input=='Y' || input=='y'){
		
			// path_data 	 = Local_Path + "PileupHistogram-goldenJSON-13tev-2016-69200ub.root" ;
			// path_MC		 = Local_Path + "TTbar_v3_PileUp_1.root" ;
		
			//  }
		
			if ( input=='N' || input=='n'){
		
			// path_data 	 = Lpc_Path + "PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root" ;
			// path_data 	 = Lpc_Path + "PileupHistogram-goldenJSON-13tev-2017-66000ub-99bins.root" ;
			path_data 	 = Lpc_Path + "PileupHistogram-goldenJSON-13tev-2017-72400ub-99bins.root" ;
			// path_MC		 = Lpc_Path + "TTbar_Incl_UL17_PileUp_16-Mar-21.root" ;
			path_MC		 = Lpc_Path + "TTbar_Incl_UL17_PileUp_24-Mar-21.root" ;

 			}

 			TFile *file_data , *file_MC ;

 			file_data = new TFile(path_data) ; 
 			file_MC   = new TFile(path_MC)	;


 			TH1D  *h_data , *h_MC , *h_dataPU ,*h_MCPU , *h_PUScaleFactor ;	

 			h_data 	= (TH1D*) file_data 	->Get("pileup")  ;
 			h_MC    = (TH1D*) file_MC       ->Get("h_MC") ;

 			//h_MC   ->Rebin(5); //because "hPUTrue" has binning of width 0.2 (1000, 0, 200), that is 1000 bins in the range of 0 to 200.

 			// h_data -> DrawNormalized();
 			// h_MC   -> DrawNormalized("same");

 			h_dataPU 				 = new TH1D("h_dataPU", "Data PileUp Distribution", 80, 0, 80);
 			h_MCPU 					 = new TH1D("h_MCPileUp", "MC PileUp Distribution", 80, 0, 80);
 			h_PUScaleFactor			 = new TH1D("h_PUScaleFactor", "PileUp Scale Factor Distribution", 80, 0, 80);

 			 for(Int_t ibin = 0; ibin < 80; ibin++){

				   h_dataPU			->SetBinContent(ibin , h_data->GetBinContent(ibin)); 
				   h_PUScaleFactor	->SetBinContent(ibin , h_data->GetBinContent(ibin));
				   h_MCPU			->SetBinContent(ibin , h_MC  ->GetBinContent(ibin));

				 }

		    f2->cd();

			 h_dataPU 				->Scale(1.0/h_dataPU		->Integral());
 		     h_MCPU 				->Scale(1.0/h_MCPU			->Integral());	

		    // for (int ibin = 0; ibin < 60; ibin++)
		    // {
		    // 	h_PUScaleFactor	->SetBinContent(ibin+1, h_dataPU->GetBinContent(ibin+1)/h_MCPU  ->GetBinContent(ibin+1) );
		    // }
		
 		    h_PUScaleFactor 	->Scale(1.0/h_PUScaleFactor ->Integral());	   
	  		   
		   
 		    h_PUScaleFactor->Divide(h_MCPU);					 
			// h_PUScaleFactor ->Draw();
			// h_dataPU ->Draw("same");
			// h_MCPU	 ->Draw("same"); 	


			h_PUScaleFactor -> Write() ; 
			h_dataPU 		-> Write() ; 
			h_MCPU	 		-> Write() ;  	
 			h_data          -> Write() ; 
 			h_MC            -> Write() ; 
	    

			f2->Write();
	}

void Code_for_PileUP_Reweight()
{
	gROOT->ProcessLine("#include <vector>");
	gROOT->ProcessLine("#include <map>");
	PileUP_Cal();

}