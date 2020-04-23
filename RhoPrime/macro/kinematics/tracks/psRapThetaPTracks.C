#include "TError.h"
#include "TMath.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TROOT.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>
#include <vector>
#include <thread>

void DrawOnNewCanvas(TH1D* h);
void draftTracks(int evLimit);

void draftTracks(int evLimit = 10000) {
  auto stpw = new TStopwatch();
  stpw->Start();
  ::Info("Tracks processing", "Draft:");
  auto rd = new ROOT::RDataFrame("events", "../../../data/rho/newResult.root");
  Int_t EventsCnt = rd->Count().GetValue();
  std::vector<Double_t> trackVecX; 
  std::vector<Double_t> trackVecY; 
  std::mutex values_mutex;
  trackVecX.reserve(10000000);
  trackVecY.reserve(10000000);

  auto pbX = [&](Double_t v) {
    values_mutex.lock();
    trackVecX.push_back(v);
    values_mutex.unlock();
  };

  auto pbY = [&](Double_t v) {
    values_mutex.lock();
    trackVecY.push_back(v);
    values_mutex.unlock();
  };
  
  int evNumber = 0;  // event number
  auto func = [&] (Int_t nTracks, \
                  ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0, \
                  ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1, \
                  ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,   \
                  ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,   \
                  ROOT::VecOps::RVec<Int_t> &TPCNcls, \
                  ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion, \
                  ROOT::VecOps::RVec<Int_t> &charge, \
                  ROOT::VecOps::RVec<Float_t> &px, \
                  ROOT::VecOps::RVec<Float_t> &py, \
                  ROOT::VecOps::RVec<Float_t> &pz) 
  {
    ++evNumber;
    std::vector<Double_t> azim{};

   // TODO: make progress bar here
   // if (((int) (100 * ((double) evNumber) / EventsCnt)) % 10 == 0) std::cout << ((int) (100 * ((double) evNumber) / EventsCnt)) << "% has passed." << std::endl;
   // TODO: how to specify number of threads? now processors work not a 100%
    std::vector<std::thread> threads;

    if (evLimit > 0 && evNumber > evLimit) return;

    Int_t netCharge{}, nGoodTracks{};
    Double_t trTheta{}, trPsRap{}, trPt{}, trP;
    for (auto i = 0; i < nTracks; ++i)
    {
      if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i]) continue;
      if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i]) continue;
      if (TPCNcls[i] < 50) continue;
      if (NumberOfSigmasTPCPion[i] > 3) continue;
      netCharge += charge[i];
      nGoodTracks++;
      trTheta = TMath::RadToDeg() * TMath::ATan2(TMath::Sqrt(py[i] * py[i] + px[i] * px[i]), pz[i]);
      if( trTheta < 0 ) trTheta += 360; 
      trPt = TMath::Sqrt(px[i]*px[i] + py[i]*py[i]);

      // trP = px[i] + py[i] + pz[i];
      trP = TMath::Sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
      threads.push_back(std::thread(pbX, trTheta));
      trPsRap = 0.5 * TMath::Log((TMath::Sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]) + pz[i]) / (TMath::Sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]) - pz[i]));
      threads.push_back(std::thread(pbY, trPsRap));
    }
    for (auto& t: threads) t.join();
  };

  rd->Foreach(func, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1", "StatusAndTPCRefit", "StatusAndITSRefit","TPCNcls", "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz"});
  trackVecX.shrink_to_fit();
  trackVecY.shrink_to_fit();

  std::vector<Double_t> w(trackVecY.size(), 1.);

  auto grxy = new TGraph(trackVecX.size(), trackVecX.data(), trackVecY.data());
  grxy->DrawClone("ap");

  auto f2 = new TF1("pr-th", "-TMath::Log(TMath::Tan(TMath::DegToRad() * x/2))", 0, 180);
  f2->DrawClone("same");
  // auto h = new TH1D("pr", "pr", 10, -1,1);
  // h->FillN(trackVecY.size(), trackVecY.data(), w.data());
  // DrawOnNewCanvas(h);
  std::cout <<"Elapsed time: " << stpw->RealTime() << ", sec" << std::endl;
}

void DrawOnNewCanvas(TH1D* h) {
  auto c = new TCanvas();
  c->cd();
  h->DrawClone();
}
