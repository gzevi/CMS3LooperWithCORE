#include "ScanChain.h" 


//Switches
bool verbose = 0;
unsigned int evt_cut = 74994186;


//Main function
int ScanChain::looper(TChain* chain, TString output_name, int nEvents){

  //Print warning!
  cout << "Careful!! Path is " << path << endl;

  createAndInitMVA("CORE");

  //readMVA* localEleMVAreader = new readMVA();
  //localEleMVAreader->InitMVA("CORE"); 

  //Set up loop over chain
  unsigned int nEventsDone = 0;
  unsigned int nEventsToDo = chain->GetEntries();
  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  std::map<std::string, TH1*> h_1d;

  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 

    // Get File Content
    if(nEventsDone >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    cms3.Init(tree);
  
    // Loop over Events in current file
    unsigned int nEventsTree = tree->GetEntriesFast();
    for(unsigned int evt = 0; evt < nEventsTree; evt++){
	  
      //cout<<"\nEvent loop again"<<endl;	  

      // Get Event Content
      if(nEventsDone >= nEventsToDo) continue;   
      cms3.GetEntry(evt);
      nEventsDone++;


      //Debug mode
      if (verbose && tas::evt_event() != evt_cut) continue;
      if (verbose) cout << "file name is " << file->GetName() << endl;

     
      // Progress
      CMS3::progress(nEventsDone, nEventsToDo);


      for (unsigned int iel = 0; iel < els_p4().size(); ++iel) {
	LorentzVector el_p4 = els_p4().at(iel);
	float pt = el_p4.pt();
	plot1D("h_pt", pt,  1, h_1d, "pT [GeV]", 150, 0, 150);
      }
      
    }// end of event loop
    
    file->Close();
    delete file;
    //delete tree;
    cout<<"\nFile done"<<endl;

  }//end of  file loop
  
  cout<<"\nWriting file"<<endl;
  savePlots(h_1d, output_name+".root");
  
  return 0;  
  
}


