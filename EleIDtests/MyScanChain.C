#include "ScanChain.h" 


//Switches
bool verbose = 0;
unsigned int evt_cut = 74994186;
readMVA* localEleMVAreader74;
readMVA* localEleMVAreader80;

void makePlots(std::map<std::string, TH1*> & h_1, TString sel, int iel, float weight = 1) {
  
  float pt = els_p4().at(iel).pt();
  float phi = els_p4().at(iel).phi();
  float eta = els_etaSC().at(iel);


 
   TString EBEE = "";
   TString EBsplitEE = "";
  
  if (fabs(eta) > 1.57) {
    EBEE = "EE";
    EBsplitEE = "EEtest"; // just have a "test" to avoid overlaying the EE plot
  }
  else if (fabs(eta)<1.44){
    EBEE = "EB";
    if (fabs(eta)<0.8)   EBsplitEE = "EB1";
    else   EBsplitEE = "EB2";
  }

  plot1D(("h"+sel+"_pt"+EBEE).Data(), pt,  weight, h_1, "pt", 40, 0, 100);
  plot1D(("h"+sel+"_pt"+EBsplitEE).Data(), pt,  weight, h_1, "pt", 40, 0, 100);
  plot1D(("h"+sel+"_eta").Data(), eta,  weight, h_1, "eta", 50, -2.5, 2.5);
  if (pt>20) plot1D(("h"+sel+"_etaPT20").Data(), eta,  weight, h_1, "eta", 50, -2.5, 2.5);


  return;
}

//Main function
int ScanChain::looper(TChain* chain, TString output_name, int nEvents){

  //Print warning!
  cout << "Careful!! Path is " << path << endl;

  //Create and init electron MVA
  createAndInitMVA("CORE",true, false, 80);
  localEleMVAreader74 = new readMVA();
  localEleMVAreader74->InitMVA("CORE",true, false, 74);
  localEleMVAreader80 = new readMVA();
  localEleMVAreader80->InitMVA("CORE",true, false, 80);

  //Set up loop over chain
  unsigned int nEventsDone = 0;
  unsigned int nEventsToDo = chain->GetEntries();
  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;
  std::map<std::string, TH1*> h_1d;
  //std::map<std::string, TH2*> h_2d;



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

      bool isData = false;

      for (unsigned int iel = 0; iel < els_p4().size(); ++iel) {
	LorentzVector el_p4 = els_p4().at(iel);
	float pt = el_p4.pt();
	float eta = els_etaSC().at(iel);
	if (pt<5) continue;
	if (fabs(eta)>2.5) continue;
	if (fabs(eta)>1.44 && fabs(eta)<1.57) continue;

	// Gen Matching
	bool prompt = false;
	bool fake = false;
	bool tau = false;
	//cout<<pt<<" "<< els_mc3dr().at(iel)<<" "<<els_mc3idx().at(iel)<<" "<<els_mc3_id().at(iel)<<endl;
        if (!isData && els_mc3dr().size() > 0 && els_mc3dr().at(iel) < 0.1 
	    && els_mc3idx().at(iel) != -9999 && ( abs(els_mc3_id().at(iel)) == 11 ||  abs(els_mc3_id().at(iel)) == 22)) { // matched to a prunedGenParticle electron
	  //cout<<"prompt: "<<genps_isPromptFinalState().at( els_mc3idx().at(iel))<<" hard "<< genps_isHardProcess().at( els_mc3idx().at(iel) ) <<endl;
	  prompt = genps_isPromptFinalState().at( els_mc3idx().at(iel) ) || genps_isHardProcess().at( els_mc3idx().at(iel) );
	  tau = genps_isDirectPromptTauDecayProductFinalState().at( els_mc3idx().at(iel) );
	  //cout<<"tau: "<<tau<<endl;
	  
          int momid =  abs(genps_id_simplemother().at(cms3.els_mc3idx().at(iel)));
          int grandmomid =  abs(genps_id_simplegrandma().at(cms3.els_mc3idx().at(iel)));
	  if (momid == 23 || grandmomid == 23) prompt = true;
	  if (momid == 11 || grandmomid < 50) prompt = true;
        }
	else fake = true; // only fake if it is not matched to an electron
	//cout<<"isFromZ "<<isFromZ(11, iel)<<endl;
	TString Prompt;
	if (prompt && !tau) Prompt = "T_";
	else if (!tau) Prompt = "F_";
	//else if (fake) Prompt = "F_";
	//else continue; // don't bother with non-prompt electrons

	//float mva = localEleMVAreader74->MVA(iel);

        makePlots(h_1d, Prompt+"All", iel);
	bool passV = electronID(iel,id_level_t::HAD_veto_noiso_v4);
	bool passL = electronID(iel,id_level_t::HAD_loose_noiso_v4);
	bool passM = electronID(iel,id_level_t::HAD_medium_noiso_v4);
	bool passT = electronID(iel,id_level_t::HAD_tight_noiso_v4);
	bool passSSVLooseFOIDEmu = electronID(iel,id_level_t::SS_fo_looseMVA_noiso_noip_no3chg_v5);
	if (passV) makePlots(h_1d, Prompt+"passV74", iel);
	if (passL) makePlots(h_1d, Prompt+"passL74", iel);
	if (passM) makePlots(h_1d, Prompt+"passM74", iel);
	if (passT) makePlots(h_1d, Prompt+"passT74", iel);
	//passV = electronID(iel,id_level_t::HAD_veto_noiso_v5);
	//passL = electronID(iel,id_level_t::HAD_loose_noiso_v5);
	//passM = electronID(iel,id_level_t::HAD_medium_noiso_v5);
	//passT = electronID(iel,id_level_t::HAD_tight_noiso_v5);
	//if (passV) makePlots(h_1d, Prompt+"passV80", iel);
	//if (passL) makePlots(h_1d, Prompt+"passL80", iel);
	//if (passM) makePlots(h_1d, Prompt+"passM80", iel);
	//if (passT) makePlots(h_1d, Prompt+"passT80", iel);
	//cout<<"prompt "<<prompt<<", pt "<<pt<<",  passVeto "<<passV<<", MVA "<<mva<<endl;	  

	float mva74 = localEleMVAreader74->MVA(iel);
	float mva80 = localEleMVAreader80->MVA(iel);

	cout<<mva74<<" "<<mva80<<" "<<els_VIDSpring16GPMvaValue().at(iel)<<" "<<mva80-els_VIDSpring16GPMvaValue().at(iel)<<endl;


	TString EBEE = "";
	if (fabs(eta) > 1.57) EBEE = "EE";
	else if (fabs(eta)<0.8)  EBEE = "EB1";
	else if (fabs(eta)<1.44) EBEE = "EB2";
	plot1D(("h_"+Prompt+"mva74_"+EBEE).Data(), mva74,  1, h_1d, "MVA", 200, -1, 1);
	plot1D(("h_"+Prompt+"mva80_"+EBEE).Data(), mva80,  1, h_1d, "MVA", 200, -1, 1);
	if (pt<10) {
	  plot1D(("h_"+Prompt+"mva74_10"+EBEE).Data(), mva74,  1, h_1d, "MVA", 200, -1, 1);
	  plot1D(("h_"+Prompt+"mva80_10"+EBEE).Data(), mva80,  1, h_1d, "MVA", 200, -1, 1);
	}
	else if (pt<20) {
	  plot1D(("h_"+Prompt+"mva74_1020"+EBEE).Data(), mva74,  1, h_1d, "MVA", 200, -1, 1);
	  plot1D(("h_"+Prompt+"mva80_1020"+EBEE).Data(), mva80,  1, h_1d, "MVA", 200, -1, 1);
	}
	else {
	  plot1D(("h_"+Prompt+"mva74_20"+EBEE).Data(), mva74,  1, h_1d, "MVA", 200, -1, 1);
	  plot1D(("h_"+Prompt+"mva80_20"+EBEE).Data(), mva80,  1, h_1d, "MVA", 200, -1, 1);
	}
	float cut80 = 0, cut74 = 0, cutEGM = 0;
	float cut80cont = 0;
	float cut80_1020 = 0, cut80_20 = 0, slope = 0;
	//if (fabs(eta) > 1.57)    { cut80 = 0.09; cut74 = 0.17; cutEGM = 0.35; }//EE 
	//else if (fabs(eta)<0.8)  { cut80 = 0.56; cut74 = 0.87; cutEGM = 0.83; }//EB1
	//else if (fabs(eta)<1.44) { cut80 = 0.20; cut74 = 0.60; cutEGM = 0.71; }//EB2

	if (fabs(eta) > 1.57)    { cut80_1020 = 0.48; cut80_20 =-0.01; cut74 = 0.17; cutEGM = 0.35; }//EE
	else if (fabs(eta)<0.8)  { cut80_1020 = 0.77; cut80_20 = 0.51; cut74 = 0.87; cutEGM = 0.83; }//EB1
	else if (fabs(eta)<1.44) { cut80_1020 = 0.55; cut80_20 = 0.10; cut74 = 0.60; cutEGM = 0.71; }//EB2
	cut80 = (pt<20) ? cut80_1020 : cut80_20;
	slope = (cut80_1020 - cut80_20)/10.; // follow this slope between 15 GeV and 25 GeV, then stop
	cut80cont = std::min( cut80_1020, std::max(cut80_20, cut80_1020 - (pt-15)*slope  ) ); //bound by the two values

	
	if (mva74 > cut74)  makePlots(h_1d, Prompt+"pass74", iel);
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"pass80", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"pass80cont", iel);
	if (mva80 > cutEGM) makePlots(h_1d, Prompt+"passEGM", iel);

	// VLoose
	float cut80_10 = 0;
	if (fabs(eta) > 1.57)    { cut80_1020 = -0.49; cut80_20 =-0.83; cut80_10 = 0.06; cut74 = -0.74; }//EE
	else if (fabs(eta)<0.8)  { cut80_1020 = -0.48; cut80_20 =-0.85; cut80_10 = 0.46; cut74 = -0.16; }//EB1
	else if (fabs(eta)<1.44) { cut80_1020 = -0.67; cut80_20 =-0.91; cut80_10 =-0.03; cut74 = -0.65; }//EB2
	cut80 = (pt<20) ? cut80_1020 : cut80_20;
	slope = (cut80_1020 - cut80_20)/10.; // follow this slope between 10 GeV and 25 GeV, then stop
	cut80cont = std::min( cut80_1020, std::max(cut80_20, cut80_1020 - (pt-15)*slope  ) ); //bound by the two values
	
	if (mva74 > cut74)  makePlots(h_1d, Prompt+"passVLoose74", iel);
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLoose80", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLoose80cont", iel);

	if (pt < 10) { cut80 = cut80_10; cut80cont = cut80_10; }
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLoose80_10", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLoose80cont_10", iel);


	// VLooseFOIDEmu
	if (fabs(eta) > 1.57)    { cut80_1020 = -0.81; cut80_20 =-0.95; cut80_10 =-0.63; cut74 = -0.92; }//EE
	else if (fabs(eta)<0.8)  { cut80_1020 = -0.86; cut80_20 =-0.96; cut80_10 =-0.30; cut74 = -0.70; }//EB1
	else if (fabs(eta)<1.44) { cut80_1020 = -0.85; cut80_20 =-0.96; cut80_10 =-0.46; cut74 = -0.83; }//EB2
	cut80 = (pt<20) ? cut80_1020 : cut80_20;
	slope = (cut80_1020 - cut80_20)/10.; // follow this slope between 10 GeV and 25 GeV, then stop
	cut80cont = std::min( cut80_1020, std::max(cut80_20, cut80_1020 - (pt-15)*slope  ) ); //bound by the two values

	if (mva74 > cut74)  makePlots(h_1d, Prompt+"passVLooseFOIDEmu74", iel);
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLooseFOIDEmu80", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLooseFOIDEmu80cont", iel);
	
	//	if (pt>10 )//&& passSSVLooseFOIDEmu!=(mva80 > cut80cont))
	  //	  cout<<pt<<"/"<<fabs(eta)<<", "<<mva80<<" >? "<<cut80cont<<" : "<< (mva80 > cut80cont) <<", and passSSVLooseFOIDEmu is "<<passSSVLooseFOIDEmu<<endl;

	if (pt < 10) { cut80 = cut80_10; cut80cont = cut80_10; }
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLooseFOIDEmu80_10", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLooseFOIDEmu80cont_10", iel);


	// VLooseFOIDISOEmu
	if (fabs(eta) > 1.57)    { cut80_1020 = -0.51; cut80_20 =-0.84;  cut80_10 = 0.06; cut74 = -0.76; }//EE
	else if (fabs(eta)<0.8)  { cut80_1020 = -0.48; cut80_20 =-0.85;  cut80_10 = 0.46; cut74 = -0.155; }//EB1
	else if (fabs(eta)<1.44) { cut80_1020 = -0.61; cut80_20 =-0.88;  cut80_10 =-0.03; cut74 = -0.56; }//EB2
	cut80 = (pt<20) ? cut80_1020 : cut80_20;
	slope = (cut80_1020 - cut80_20)/10.; // follow this slope between 10 GeV and 25 GeV, then stop
	cut80cont = std::min( cut80_1020, std::max(cut80_20, cut80_1020 - (pt-15)*slope  ) ); //bound by the two values

	if (mva74 > cut74)  makePlots(h_1d, Prompt+"passVLooseFOIDISOEmu74", iel);
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLooseFOIDISOEmu80", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLooseFOIDISOEmu80cont", iel);

	if (pt < 10) { cut80 = cut80_10; cut80cont = cut80_10; }
	if (mva80 > cut80)  makePlots(h_1d, Prompt+"passVLooseFOIDISOEmu80_10", iel);
	if (mva80 > cut80cont)  makePlots(h_1d, Prompt+"passVLooseFOIDISOEmu80cont_10", iel);
	

	//plot2D("h_mva80VSmva74", mva74, mva80,  1, h_1d, "MVA80vsMVA74", 20, -1, 1, 20, -1, 1);
	
	if (passSSVLooseFOIDEmu)  makePlots(h_1d, Prompt+"passSSVLooseFOIDEmu", iel);

      }
      
    }// end of event loop
    
    //h_1d["hAll_mva80VSmva74"]->Print("all");


    

    file->Close();
    delete file;
    //delete tree;
    cout<<"\nFile done"<<endl;

  }//end of  file loop
  
  cout<<"\nWriting file"<<endl;
  savePlots(h_1d, output_name+".root");
  
  return 0;  
  
}


