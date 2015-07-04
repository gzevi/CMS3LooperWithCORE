#ifndef LOOPER_H
#define LOOPER_H

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TRandom.h"
#include "TF1.h"
#include "Math/VectorUtil.h"
#include <vector>
#include "TString.h"

#include "CORE/CMS3.h"
#include "CORE/SSSelections.h"  //remove this one eventually!!!
#include "CORE/ElectronSelections.h"
#include "CORE/MuonSelections.h"
#include "CORE/MetSelections.h"
#include "CORE/JetSelections.h"
#include "CORE/VertexSelections.h"
#include "CORE/TriggerSelections.h"
#include "CORE/MCSelections.h"
#include "CORE/IsolationTools.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

#include "Math/Vector4D.h" 
#include "Math/LorentzVector.h"

#include "PlotUtilities.h"


typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;

//Classes
class ScanChain {

public:
  int looper(TChain* chain, TString output_name, int nEvents = -1);

protected:

private:

  std::string path = "./";

    
};


#endif
