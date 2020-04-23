#pragma once

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RResultPtr.hxx"
#include "TROOT.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void GetEventInfo(std::string fileName) {

  ROOT::DisableImplicitMT();
  auto PrintEventInfo = [&](ROOT::VecOps::RVec<Int_t> &eventinfo) {
    std::cout << eventinfo[0] << "  " << eventinfo[1] << "  " << eventinfo[2]
              << "  " << eventinfo[3] << std::endl;
  };

  ROOT::RDataFrame rd("events", fileName.data());

  std::cout << "RunNumber" << std::endl;

  rd.Foreach(PrintEventInfo, {"eventinfo"});
}
