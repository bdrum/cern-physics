#include "DefineColumnsEvents.C"
#include "DefineColumnsTracks.C"
#include "TCanvas.h"
#include "TError.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TStyle.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>

void PlotTracks(int eventsLimit = 10000);
TGraph *PlotGraph(TString fileName, Int_t eventsLimit);

TGraph *gr = nullptr;

void PlotTracks(int eventsLimit) {

  TString file1 =
      "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/newResult.root";
  TString file2 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/"
                  "data2015.cup9.new.root";
  TString file3 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/2018/"
                  "esdccup30q.new.root";
  TString file4 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/2018/"
                  "ccup29.sel.new.root";
  TString file5 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/2018/"
                  "ccup30.sel.new.root";
  TString file6 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/2018/"
                  "ccup31.sel.new.root";

  gr = PlotGraph(file1, eventsLimit);
  gr->GetXaxis()->SetRangeUser(0, 3);
  gr->DrawClone("AP");
}

TGraph *PlotGraph(TString fileName, Int_t eventsLimit) {

  std::vector<Double_t> tracksP(1, 0.);
  std::vector<Double_t> tracksNTPCcl(1, 0.);

  kinematics::FillVectorsFromTracks(tracksP, tracksNTPCcl, fileName,
                                    eventsLimit);

  ::Info("GetPairsHist", "Starts filling of histogram:");

  return new TGraph(tracksP.size(), tracksP.data(), tracksNTPCcl.data());
}