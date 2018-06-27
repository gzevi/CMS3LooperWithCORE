#include "ScanChain.h"
#include "TString.h"

//usage: ./main.exe QCD_Test 1000

int main(int argc, char **argv) {
  
  TString sample = "";
  ScanChain *mylooper = new ScanChain();
  TChain *result = new TChain("Events");
  
  if (argc < 2) {
    sample = "default";
    cout<<"Using default file. "<<endl;
    //    result->Add("merged_ntuple_1.root");
    result->Add("/hadoop/cms/store/group/snt/run2_mc2017//TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_CMS4_V09-04-13//merged_ntuple_1.root");
  }
  else {
    sample = (TString) argv[1];
    cout<<"Using files corresponding to sample "<<sample<<endl;
    //QCD_test (test with just one file)
    if (sample == "QCD_Test"){
      result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-20toInf_MuEnrichedPt15_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v3/V07-02-08/merged_ntuple_1.root");
    }
    else {
      cout<<"Could not find files corresponding to sample "<<sample<<endl;
    }
  }
  
  int nevents = 100;
  if (argc < 3) {
    cout<<"Number of events not specified. Running over "<<nevents<<" events"<<endl;
  }
  else {
    TString n = (TString) argv[2];
    nevents = n.Atoi();
    cout<<"Running over "<<nevents<<" events"<<endl;
  }
  
  mylooper->looper(result,  sample, nevents);
  return 0;
  
}


