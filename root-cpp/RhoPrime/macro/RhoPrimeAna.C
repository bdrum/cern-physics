#include "TCanvas.h"
#include "TDirectoryFile.h"
#include "TError.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLine.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TStyle.h"
#include "TTree.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>

/*
  rd.GetColumnNames()
  (ROOT::RDF::RInterface::ColumnNames_t) { "RunNum", "PeriodNumber",
  "OrbitNumber", "BunchCrossNumber", "Mass", "Pt", "Q", "Rapidity", "Phi",
  "ZNAenergy", "ZNCenergy", "ZPAenergy", "ZPCenergy", "ZDCAtime", "ZDCCtime",
  "PIDTPCPion", "PIDTPCElectron", "TPCsignal", "TrackP", "TrackEta", "TrackPhi",
  "TrackPx", "TrackPy", "TrackPz", "TrackQ", "VtxX", "VtxY", "VtxZ",
  "VtxContrib", "VtxChi2", "VtxNDF", "SpdVtxX", "SpdVtxY", "SpdVtxZ",
  "SpdVtxContrib", "V0Adecision", "V0Cdecision", "ADAdecision", "ADCdecision",
  "UBAfired", "UBCfired", "VBAfired", "VBCfired", "Ntracklets", "IsCUP2",
  "IsCUP4", "IsCUP9", "IsC1ZED", "TrackHasPointOnITSLayer0",
  "TrackHasPointOnITSLayer1", "TrackITSModuleInner", "TrackITSModuleOuter" }
  */

enum calc { pt, mass };
static int netChargeValue = 0;
static calc variant = mass;
static bool showDraw = false;
TH1D h1;

void Rho0Ana();
auto Calc(ROOT::VecOps::RVec<Float_t> &Pt,
          ROOT::VecOps::RVec<Bool_t> &TrackHasPointOnITSLayer0,
          ROOT::VecOps::RVec<Bool_t> &TrackHasPointOnITSLayer1,
          ROOT::VecOps::RVec<Short_t> &TrackQ,
          ROOT::VecOps::RVec<Float_t> &TrackPx,
          ROOT::VecOps::RVec<Float_t> &TrackPy,
          ROOT::VecOps::RVec<Float_t> &TrackPz, Bool_t IsCUP9);
TH1D PlotHist(TString col1Name, calc var, TString file, TString drawOption,
              Int_t bins, Double_t xLow, Double_t xUp);

void RhoPrimeAna() {
  TString file = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/"
                 "2015/RhoPrime2015.root";

  showDraw = true;

  h1 = PlotHist("Pt2015CUP9", calc::pt, file.Data(), TString("pe"), 100, 0, 2);
}

// Calc Func
auto Calc(ROOT::VecOps::RVec<Float_t> &Pt,
          ROOT::VecOps::RVec<Bool_t> &TrackHasPointOnITSLayer0,
          ROOT::VecOps::RVec<Bool_t> &TrackHasPointOnITSLayer1,
          ROOT::VecOps::RVec<Short_t> &TrackQ,
          ROOT::VecOps::RVec<Float_t> &TrackPx,
          ROOT::VecOps::RVec<Float_t> &TrackPy,
          ROOT::VecOps::RVec<Float_t> &TrackPz, Bool_t IsCUP9) {

  Int_t netCharge{0}, nGoodTracks{0};
  Double_t massPion{0.140};
  std::vector<ROOT::Math::PxPyPzMVector> TracksVec;
  TracksVec.reserve(4);

  if (IsCUP9)
    return -1.0;

  for (auto i = 0; i < 4; ++i) {
    if (!(TrackHasPointOnITSLayer0[i] && TrackHasPointOnITSLayer1[i]))
      continue;

    TracksVec.push_back(
        ROOT::Math::PxPyPzMVector(TrackPx[i], TrackPy[i], TrackPz[i], 0.140));

    netCharge += TrackQ[i];
    nGoodTracks++;
  }

  if (nGoodTracks != 4 || std::abs(netCharge) != netChargeValue)
    return -1.;

  auto ttlVec = TracksVec[0] + TracksVec[1] + TracksVec[2] + TracksVec[3];

  switch (variant) {
  case mass: {
    if (ttlVec.Pt() > 0.15)
      return -1.;

    return ttlVec.M();
  }
  case pt:
    return ttlVec.Pt();
  }
}
// Calc Func

// Draw Func
TH1D PlotHist(TString col1Name, calc var, TString file, TString drawOption,
              Int_t bins, Double_t xLow, Double_t xUp) {
  variant = var;
  std::cout << "PlotHist::Initialising of creating histograms based on " << file
            << std::endl;
  TFile *f = new TFile(file.Data());
  TDirectoryFile *fd;
  f->GetObject("RhoPrimeCentral", fd);

  ROOT::RDataFrame rd("events", fd);

  ROOT::RDF::TH1DModel histModel(col1Name.Data(), col1Name.Data(), bins, xLow,
                                 xUp);

  auto hist =
      rd.Define(col1Name.Data(), Calc,
                {"Pt", "TrackHasPointOnITSLayer0", "TrackHasPointOnITSLayer1",
                 "TrackQ", "TrackPx", "TrackPy", "TrackPz", "IsCUP9"})
          .Filter((col1Name + TString(">0")).Data())
          .Histo1D(histModel, col1Name.Data());

  if (showDraw) {
    auto c = new TCanvas(col1Name.Data(), col1Name.Data());
    hist.OnPartialResult(10000, [&](TH1D &hist_) {
      c->cd();
      hist_.Draw(drawOption.Data());
      c->Update();
    });
    hist->DrawClone(drawOption.Data());
  }

  // delete f;
  return hist.GetValue();
}
// Draw Func

// void Flow() {
//   TFile *f = new TFile("/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/"
//                        "2015/RhoPrime2015.root");

//   TDirectoryFile *fd;
//   f->GetObject("RhoPrimeCentral", fd);

//   ROOT::RDataFrame rd("events", fd);

//   ::Info("Flow. IsCup9 sum", "%d", rd.Mean("IsCUP9"));

//   auto c1 = new TCanvas();
//   c1->cd();
//   ROOT::RDF::TH1DModel histModelPt("Pt", "Pt", 100, 0, 2);
//   auto hPt = rd.Filter("Q==0").Histo1D(histModelPt, "Pt");
//   hPt->DrawClone();

//   auto c2 = new TCanvas();
//   c2->cd();
//   ROOT::RDF::TH1DModel histModelMass("Mass", "Mass", 100, 0.2, 3.2);
//   auto hMass = rd.Filter("Pt<0.11 && Q==0").Histo1D(histModelMass, "Mass");
//   hMass->DrawClone();
// }