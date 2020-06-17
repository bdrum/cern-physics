#include "TCanvas.h"
#include "TError.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TMath.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TStyle.h"
#include "TF1.h"
#include "TFile.h"
#include "TStyle.h"

void CompareHists(std::vector<TH1D> &hArr);
void CompareHists(TH1D *h1, TH1D *h2);
void TuneHist(TH1D *h);
void FitHist(TH1D *h);
double bw(double *x, double *par);
TH1D *LoadHist(const char *name);

/*
Mass4prPsi2s2018cup31
Mass4prJPsi2018cup31
Pt4pr2018CUP31
Mass4prCharged2018CUP31
Mass4pr2018CUP31
*/

void FitAndDraw()
{
  auto h = LoadHist("Pt4pr2018CUP31");

  /* 
  auto fitFunc = new TF1("bw", bw, h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax(), 3);
  fitFunc->SetParName(0, "const");
  fitFunc->SetParameter(0, 5);
  fitFunc->SetParName(1, "Gamma");
  fitFunc->SetParameter(1, h->GetRMS());
  fitFunc->SetParName(2, "Mass");
  fitFunc->SetParameter(2, h->GetMean());
  h->Fit(fitFunc, "IWR");  
  */
  h->GetXaxis()->SetTitle("#pi^{+}#pi^{-}#pi^{+}#pi^{-}, p_{t} GeV");
  h->GetYaxis()->SetTitle(TString::Format("#frac{Counts}{%d MeV}", (int)(h->GetBinWidth(0) * 1000)));
  gStyle->SetOptStat(1);
  h->DrawClone("pe");
}

TH1D *LoadHist(const char *name)
{
  TFile f("4pr.hists.root");
  f.cd();
  TH1D *h = nullptr;
  f.GetObject(name, h);
  h->SetDirectory(0);
  f.Close();
  return h;
}

double bw(double *x, double *par)
{
  double arg1 = 1; //2.0 / TMath::Pi(); //14.0 / 22.0;
  double arg2 = par[1] * par[1] * par[2] * par[2];
  double arg3 = ((x[0] * x[0]) - (par[2] * par[2])) * ((x[0] * x[0]) - (par[2] * par[2]));
  double arg4 = x[0] * x[0] * x[0] * x[0] * ((par[1] * par[1]) / (par[2] * par[2]));
  return par[0] * arg1 * arg2 / (arg3 + arg4);
}
