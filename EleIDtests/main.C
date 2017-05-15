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
    //    result->Add("/hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_1.root");
    result->Add("/nfs-7/userdata/bemarsh/scratch/TTJets_SingleLeptFromT_25ns_80X_All.root");

  }
  else {
    sample = (TString) argv[1];
    cout<<"Using files corresponding to sample "<<sample<<endl;
    //QCD_test (test with just one file)
    if (sample == "QCD_Test"){
      result->Add("/hadoop/cms/store/group/snt/phys14/QCD_Pt-20toInf_MuEnrichedPt15_PionKaonDecay_Tune4C_13TeV_pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v3/V07-02-08/merged_ntuple_1.root");
    }
    else if (sample == "DY_Test"){
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_1.root");
    }
    else if (sample == "DY_Full"){
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_1.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_2.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_3.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_4.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_5.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_6.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_7.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_8.root");
      result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_9.root");
      
    }
    else if (sample == "DY_Full_1")   result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_1.root");
    else if (sample == "DY_Full_2") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_2.root");
    else if (sample == "DY_Full_3") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_3.root");
    else if (sample == "DY_Full_4") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_4.root");
    else if (sample == "DY_Full_5") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_5.root");
    else if (sample == "DY_Full_6") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_6.root");
    else if (sample == "DY_Full_7") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_7.root");
    else if (sample == "DY_Full_8") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_8.root");
    else if (sample == "DY_Full_9") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_9.root");
    else if (sample == "DY_Full_10")   result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_10.root");
    else if (sample == "DY_Full_11")   result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_11.root");
    else if (sample == "DY_Full_12") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_12.root");
    else if (sample == "DY_Full_13") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_13.root");
    else if (sample == "DY_Full_14") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_14.root");
    else if (sample == "DY_Full_15") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_15.root");
    else if (sample == "DY_Full_16") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_16.root");
    else if (sample == "DY_Full_17") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_17.root");
    else if (sample == "DY_Full_18") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_18.root");
    else if (sample == "DY_Full_19") result->Add("/hadoop/cms/store/group/snt/run2_25ns_80MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext1-v1/V08-00-05/merged_ntuple_19.root");
    else {
      cout<<"Could not find files corresponding to sample, will try to add it directly as a root file: "<<sample<<endl;
      result->Add(sample);
      sample = "test";
    }
  }
  
  int nevents = 1000;
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


