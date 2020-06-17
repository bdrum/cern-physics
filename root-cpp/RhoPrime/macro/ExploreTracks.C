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

auto Explore(
    Int_t nTracks, ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0,
    ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1,
    ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,
    ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,
    ROOT::VecOps::RVec<Int_t> &TPCNcls,
    ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion,
    ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Float_t> &px,
    ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz,
    ROOT::VecOps::RVec<Float_t> &dV0, ROOT::VecOps::RVec<Float_t> &EnZDC,
    ROOT::VecOps::RVec<Float_t> &dAD, ROOT::VecOps::RVec<Float_t> &vertex,
    ROOT::VecOps::RVec<Float_t> &TDCa, ROOT::VecOps::RVec<Float_t> &TDCc,
    ROOT::VecOps::RVec<Float_t> &dca0, ROOT::VecOps::RVec<Float_t> &dca1) {

  Int_t netCharge{};
  Double_t massPion = 0.140;

  std::vector<ROOT::Math::PxPyPzMVector> Tracks;
  std::vector<Float_t> dV0Vec;
  std::vector<Float_t> EnZDCVec;
  std::vector<Float_t> dADVec;
  std::vector<Float_t> vertexVec;
  std::vector<Float_t> TDCaVec;
  std::vector<Float_t> TDCcVec;
  std::vector<Float_t> dca0Vec;
  std::vector<Float_t> dca1Vec;

  Tracks.reserve(4);
  dV0Vec.reserve(4);
  EnZDCVec.reserve(4);
  dADVec.reserve(4);
  vertexVec.reserve(4);
  TDCaVec.reserve(4);
  TDCcVec.reserve(4);
  dca0Vec.reserve(4);
  dca1Vec.reserve(4);

  for (auto i = 0; i < nTracks; ++i) {
    if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i])
      continue;
    if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i])
      continue;
    if (TPCNcls[i] < 50)
      continue;

    if (std::abs(NumberOfSigmasTPCPion[i]) > 3)
      continue;

    Tracks.push_back(ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));
    dV0Vec.push_back(dV0[i]);
    EnZDCVec.push_back(EnZDC[i]);
    dADVec.push_back(dAD[i]);
    vertexVec.push_back(vertex[i]);
    TDCaVec.push_back(TDCa[i]);
    TDCcVec.push_back(TDCc[i]);
    dca0Vec.push_back(dca0[i]);
    dca1Vec.push_back(dca1[i]);

    netCharge += charge[i];

    if (Tracks.size() > 4)
      return -1.0;
  }

  if (Tracks.size() != 4 || std::abs(netCharge) != 0)
    return -1.0;

  auto ttlVec = Tracks[0] + Tracks[1] + Tracks[2] + Tracks[3];

  if (ttlVec.Pt() > 0.15)
    return -1.0;

  if (ttlVec.M() <= 1 && ttlVec.M() >= 0.6) {
    for (int i = 0; i < 4; ++i)
      std::cout << 0 << "," << ttlVec.P() << "," << dV0Vec[i] << ","
                << EnZDCVec[i] << "," << dADVec[i] << "," << vertexVec[i] << ","
                << TDCaVec[i] << "," << TDCcVec[i] << "," << dca0Vec[i] << ","
                << dca1Vec[i] << "," << ttlVec.M() << std::endl;
  } else {
    for (int i = 0; i < 4; ++i)
      std::cout << 1 << "," << ttlVec.P() << "," << dV0Vec[i] << ","
                << EnZDCVec[i] << "," << dADVec[i] << "," << vertexVec[i] << ","
                << TDCaVec[i] << "," << TDCcVec[i] << "," << dca0Vec[i] << ","
                << dca1Vec[i] << "," << ttlVec.M() << std::endl;
  }

  return ttlVec.M();

} // Explore

void ExploreTracks() {

  // ROOT::DisableImplicitMT();

  ROOT::RDF::TH1DModel histModel("Mass", "Mass", 100, 0.5, 3.5);

  ROOT::RDataFrame rd("events", "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/"
                                "data/rho/2018/ccup31.sel.new.root");

  auto hist =
      rd.Define("Mass", Explore,
                {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                 "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                 "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dV0",
                 "EnZDC", "dAD", "vertex", "TDCa", "TDCc", "dca0", "dca1"})
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