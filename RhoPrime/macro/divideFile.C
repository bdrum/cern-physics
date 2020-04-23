#include "TROOT.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>

void divideFile(char *fileName) {

  auto tt = [](ROOT::VecOps::RVec<Int_t> &TriggerType) {
    // TriggerType[0] = 1 - CUP9
    // TriggerType[1] = 1 - CUP8
    if (TriggerType[1])
      return 1;
    return -1;
  };

  ROOT::RDataFrame rd("events", fileName);

  auto rdNew = rd.Define("TrigType", tt, {"TriggerType"}).Filter("TrigType==1");

  rdNew.Snapshot("events", "data2015.cup8.root");
}
