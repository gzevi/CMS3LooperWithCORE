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

      TString HLTTrigger("HLT_Ele22_WP75_Gsf_v1");
      if (!passHLTTrigger(HLTTrigger)) continue;
      int trigIdx = -1;
      vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
      vector<TString>::const_iterator end_it = hlt_trigNames().end();
      vector<TString>::const_iterator found_it = find(begin_it, end_it, HLTTrigger);
      if(found_it != end_it) trigIdx = found_it - begin_it;
      else {
	cout<<"not found"<<endl;
	return false; // trigger was not found
      }
      
      // get the vector of p4 passing this trigger
      std::vector<LorentzVector> trigObjs = hlt_trigObjs_p4()[trigIdx];
      std::vector<int> trigObjsID = hlt_trigObjs_id()[trigIdx];
    

      //cout << "hlt_trigObjs_passLast_branch "<<cms3.hlt_trigObjs_passLast_branch<<", hlt_trigObjs_passLast_isLoaded "<<cms3.hlt_trigObjs_passLast_isLoaded<<endl;
      //cout<<" tree->GetAlias(hlt_trigObjs_passLast) " <<tree->GetAlias("hlt_trigObjs_passLast") <<endl;
      if (tree->GetAlias("hlt_trigObjs_passLast")==0 ) cout<<"Did not find hlt_trigObjs_passLast"<<endl;
      else cout<<"Found hlt_trigObjs_passLast!!" <<endl;
      
      std::vector<bool> trigObjsPL = hlt_trigObjs_passLast()[trigIdx];
      std::vector<TString> trigObjsFilters = hlt_trigObjs_filters()[trigIdx];
      
      // if no trigger objects then fail
      if (trigObjs.size() == 0) {
	cout<<"trigObjs_p4 collection is empty"<<endl;
	return false; 
      }
      
      for (size_t i = 0; i < trigObjs.size(); ++i)
	{
	  cout<<"Trigger Object has pt, id, passLast "<<trigObjs[i].pt()<<" "<<trigObjsID[i]<<" "<<trigObjsPL[i]<<endl;
	  cout<<"It also has filters: "<<trigObjsFilters[i]<<endl;
	  if (trigObjsFilters[i].Contains("hltEle22WP75GsfTrackIsoFilter"))
	    cout<<"Found filter hltEle22WP75GsfTrackIsoFilter !!"<<endl;
	}



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


