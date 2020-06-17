#include "TCanvas.h"
#include "TError.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLine.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TStyle.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>

auto Explore(Int_t nTracks, ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0,
             ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1,
             ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,
             ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,
             ROOT::VecOps::RVec<Int_t> &TPCNcls,
             ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion,
             ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Float_t> &px,
             ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz,
             ROOT::VecOps::RVec<Int_t> &eventinfo,
             ROOT::VecOps::RVec<Float_t> &dca0,
             ROOT::VecOps::RVec<Float_t> &dca1) {

  Int_t netCharge{};
  Double_t massPion = 0.140;

  std::vector<ROOT::Math::PxPyPzMVector> Tracks;

  Tracks.reserve(4);

  for (auto i = 0; i < nTracks; ++i) {
    if (!HasPointOnITSLayer0[i] || !HasPointOnITSLayer1[i])
      continue;
    if (std::abs(dca0[i]) > 3 || std::abs(dca1[i]) > 3)
      continue;
    if (!StatusAndTPCRefit[i] || !StatusAndITSRefit[i])
      continue;
    if (TPCNcls[i] < 50)
      continue;

    if (std::abs(NumberOfSigmasTPCPion[i]) > 3)
      continue;

    Tracks.push_back(ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));

    netCharge += charge[i];

    if (Tracks.size() > 4)
      break;
    // return -1.0;
  }

  if (Tracks.size() != 4 || std::abs(netCharge) != 0)
    return -1.0;

  auto ttlVec = Tracks[0] + Tracks[1] + Tracks[2] + Tracks[3];

  // return ttlVec.Pt();

  if (ttlVec.Pt() > 0.15)
    return -1.0;

  if (ttlVec.M() < 1)
    std::cout << eventinfo[0] << "  " << eventinfo[1] << "  " << eventinfo[2]
              << "  " << eventinfo[3] << std::endl;
  return ttlVec.M();

} // Explore

void PlotEventsNew() {

  // ROOT::DisableImplicitMT();

  ROOT::RDF::TH1DModel histModel("Mass", "Mass", 200, 0, 4);

  ROOT::RDataFrame rd("events", "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/"
                                "data/rho/2018/ccup31.sel.new.root");
  std::cout << "eventinfo[0]"
            << "  "
            << "eventinfo[1]"
            << "  "
            << "eventinfo[2]"
            << "  "
            << "eventinfo[3]" << std::endl;
  auto hist =
      rd.Define("Mass", Explore,
                {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                 "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                 "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz",
                 "eventinfo", "dca0", "dca1"})
          .Filter("Mass>0")
          .Histo1D(histModel, "Mass");

  auto c = new TCanvas("Mass", "Mass");
  hist.OnPartialResult(10000, [&](TH1D &hist_) {
    c->cd();
    hist_.Draw("pe");
    c->Update();
  });
  hist->DrawClone("pe");
}