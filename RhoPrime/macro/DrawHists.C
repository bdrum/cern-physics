#include "TAxis.h"
#include "TCanvas.h"
#include "TCollection.h"
#include "TError.h"
#include "TFile.h"
#include "TH1D.h"
#include "TKey.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TList.h"
#include "TObjArray.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include <vector>

void DrawMasses(std::vector<TH1D *> &hms);
void DrawPt(std::vector<TH1D *> &hpt);
TLine *AddVLine(TH1D *h);

void DrawHists(const char *fileName) {

  TFile *fin(0);
  if (!gSystem->AccessPathName(fileName))
    fin = TFile::Open(fileName);

  if (!fin) {
    ::Error("", "ERROR: could not open data file");
    exit(1);
  }

  TIter keyList(fin->GetListOfKeys());
  TKey *key;

  std::vector<TH1D *> hvMass;
  hvMass.reserve(4);
  std::vector<TH1D *> hvPt;
  hvPt.reserve(4);

  while ((key = (TKey *)keyList())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1"))
      continue;
    TH1D *h = (TH1D *)key->ReadObj();
    ::Info(h->GetName(), TString::Format("Entries: %f", h->GetEntries()));
    if (TString(h->GetName()).Contains("Pt"))
      hvMass.push_back(h);
    else
      hvPt.push_back(h);
  }

  DrawMasses(hvMass);
  // DrawPt(hvPt);
}

void DrawMasses(std::vector<TH1D *> &hms) {
  auto cMass = new TCanvas();
  auto leg = new TLegend();
  cMass->cd();
  for (int i = hms.size() - 1; i >= 0; i -= 1) {
    // for (int i = 1; i < hms.size() - 1; i++) {
    // hms[i]->SetMarkerColor(i);
    // hms[i]->SetLineColor(i);
    // hms[i]->Scale(1.0 / hms[i]->GetMaximum());
    if (i != 4)
      hms[i]->DrawClone("SAME PE PLC PMC");
    else
      hms[i]->DrawClone("PE PLC PMC");

    leg->AddEntry(hms[i]->GetName());
    // AddVLine(hms[i])->Draw("same");
  }
  gStyle->SetOptStat(0);
  leg->Draw();
  // cMass->BuildLegend();
  TLatex xAxisLabel, yAxisLabel;
  TAxis *xax = hms[0]->GetXaxis();
  xAxisLabel.SetTextSizePixels(16);
  yAxisLabel.SetTextSizePixels(16);

  xAxisLabel.DrawLatexNDC(0.9, 0.1, "#pi^{+}#pi^{-}#pi^{+}#pi^{-}  Pt, GeV");
  yAxisLabel.DrawLatexNDC(
      0.1, 0.9,
      TString::Format("#frac{Counts}{%d MeV}",
                      (Int_t)(((xax->GetXmax() - xax->GetXmin()) * 1000) /
                              hms[0]->GetNbinsX())));
}

TLine *AddVLine(TH1D *h) {

  auto l = new TLine(h->GetBinCenter(h->GetMaximumBin()), 0,
                     h->GetBinCenter(h->GetMaximumBin()), h->GetMaximum());
  l->SetLineWidth(3);
  l->SetLineColor(h->GetMarkerColor());

  return l;
}

void DrawPt(std::vector<TH1D *> &hpt) {
  auto cPt = new TCanvas();
  for (auto &h : hpt) {
    if (TString(h->GetName()).Contains("Bcg"))
      hpt[0]->Fit("gaus", "WW", "", 0, 1);
    if (TString(h->GetName()).Contains("Sig"))
      hpt[1]->Draw("same");
  }
}
