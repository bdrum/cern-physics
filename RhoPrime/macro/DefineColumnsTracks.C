#include "DefineColumnsEvents.C"
#include "Math/Vector4Dfwd.h"
#include "TError.h"
#include "TH1D.h"
#include "TMath.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>
#include <thread>
#include <vector>

namespace kinematics {
void FillVectorsFromTracks(std::vector<Double_t> &tracksVecX,
                           std::vector<Double_t> &tracksVecY, TString fileName,
                           int evLimit) {

  if (!tracksVecX.empty())
    tracksVecX.clear();

  if (!tracksVecY.empty())
    tracksVecY.clear();

  TStopwatch stpw;
  stpw.Start();

  ::Info("Tracks processing", "Fill vector from tracks:");
  ROOT::RDataFrame rd("events", fileName.Data());
  auto EventsCnt{rd.Count().GetValue()};

  std::mutex values_mutex;

  tracksVecX.reserve(10000000);
  tracksVecY.reserve(10000000);

  auto pb = [&](Double_t x, Double_t y) {
    values_mutex.lock();
    tracksVecX.push_back(x);
    tracksVecY.push_back(y);
    values_mutex.unlock();
  };

  int evNumber = 0;
  int totTracks = 0;

  auto FillFunc =
      [&](Int_t nTracks, ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0,
          ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1,
          ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,
          ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,
          ROOT::VecOps::RVec<Int_t> &TPCNcls,
          ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion,
          ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Float_t> &px,
          ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz) {
        ++evNumber;
        // TODO: how to specify number of threads? now processors work not for a
        // 100%
        if (evNumber % 1000000 == 0)
          std::cout << "One more 1 000 000 events were processed " << evNumber
                    << std::endl;

        std::vector<std::thread> threads;

        if (evLimit > 0 && evNumber > evLimit)
          return;

        Int_t netCharge{}, nGoodTracks{};

        for (auto i = 0; i < nTracks; ++i) {
          if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i])
            continue;
          if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i])
            continue;
          if (TPCNcls[i] < 50)
            continue;

          if (NumberOfSigmasTPCPion[i] > 3)
            continue;

          netCharge += charge[i];

          threads.push_back(
              std::thread(pb, TMath::Sqrt(px[i] * px[i] + py[i] * py[i]),
                          (Double_t)TPCNcls[i]));
          nGoodTracks++;
        }

        for (auto &t : threads)
          t.join();
      };

  rd.Foreach(FillFunc, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                        "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                        "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz"});

  tracksVecX.shrink_to_fit();
  tracksVecY.shrink_to_fit();
  stpw.Stop();
  std::cout << "Elapsed time for vector filling is " << stpw.RealTime()
            << ", sec" << std::endl;
}

} // namespace kinematics
