#include "DefineColumnsEvents.cxx"
#include "TCanvas.h"
#include "TError.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TLine.h"
#include "TMath.h"
#include "TPad.h"
#include <ROOT/RResultPtr.hxx>
#include "TROOT.h"
#include "TStopwatch.h"
#include "TStyle.h"
#include <ROOT/RDataFrame.hxx>

void DrawOnNewCanvas(TH1D *h);

void PlotEvents();

TH1D PlotHist(TString col1Name, kinematics::calc var, TString file,
              TString drawOption, Int_t bins, Double_t xLow, Double_t xUp);

TH2D PlotHist2D(TString name, TString title, TString col1Name, TString col2Name,
                Int_t binsX, Double_t xLow, Double_t xUp, Int_t binsY = 0,
                Double_t yLow = 0, Double_t yUp = 0);

TGraph PlotGraph(TString col1Name, TString col1Title, TString col2Name,
                 TString col2Title);

void DrawHists(std::vector<TH1D> &hArr);
TLine *AddVLine(TH1D &h);

static bool showDraw = false;

TH1D h1, h2, h3, h4, h5, hBcg, hSig;
TH2D h2d;
std::vector<TH1D> v;

void PlotEvents()
{
  TStopwatch stpw;
  stpw.Start();
  std::cout << "PlotEvents::Start script execution" << std::endl;

  kinematics::netChargeValue = 0;

  // kinematics::debug = true;
  // ROOT::EnableImplicitMT();
  // detectors::v0Ind = 5;

  TString file1 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/pvn/"
                  "ccup8.sel.new.root";
  TString file2 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/pvn/"
                  "ccup9.sel.new.root";
  TString file3 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2018/pvn/"
                  "ccup29.sel.new.root";
  TString file4 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2018/pvn/"
                  "ccup30.sel.new.root";
  TString file5 = "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2018/pvn/"
                  "ccup31.sel.new.root";

  /////////////////////////////////JPSI////////////////////////////////////////

  // showDraw = true;
  // kinematics::Psi2S = true;
  // h1 = PlotHist("Mass4prPsi2s2018cup31", kinematics::calc::heavy,
  // file6.Data(),
  //               TString("pe"), 20, 3.5, 3.9);
  // kinematics::Psi2S = false;
  // h2 = PlotHist("Mass4prJPsi2018cup31", kinematics::calc::heavy,
  // file6.Data(),
  //               TString("pe"), 50, 2.5, 3.5);

  /////////////////////////////////JPSI////////////////////////////////////////

  /////////////////////////////////PWA////////////////////////////////////////
  // showDraw = false;

  // h1 = PlotHist("CUP8_9", kinematics::calc::light, file1.Data(),
  // TString("pe"),
  //               100, 0, 2);
  // h2 = PlotHist("CUP8_9", kinematics::calc::heavy, file1.Data(),
  // TString("pe"),
  //               100, 0, 2);
  /////////////////////////////////PWA///////////////////////////////////////

  showDraw = true;

  /////////////////////////////////PT////////////////////////////////////////

  // hBcg = PlotHist("Pt2015CUP8Bcg", kinematics::calc::ptBcg, file1.Data(),
  //                 TString("pe"), 100, 0, 2);
  // hSig = PlotHist("Pt2015CUP8Sig", kinematics::calc::ptSig, file1.Data(),
  //                 TString("pe"), 100, 0, 2);
  //  h1 = PlotHist("Pt2015CUP8", kinematics::calc::ptTotal, file1.Data(),
  //  TString("pe"), 100, 0, 2);
  h2 = PlotHist("Pt2015CUP9", kinematics::calc::ptTotal, file2.Data(),
                TString("pe"), 100, 0, 2);
  // h3 = PlotHist("Pt2018CUP29", kinematics::calc::ptTotal, file3.Data(),
  //               TString("pe"), 100, 0, 2);
  // h4 = PlotHist("Pt2018CUP30", kinematics::calc::ptTotal, file4.Data(),
  //               TString("pe"), 100, 0, 2);
  // h5 = PlotHist("Pt2018CUP31", kinematics::calc::ptTotal, file5.Data(),
  //               TString("pe"), 100, 0, 2);

  /////////////////////////////////PT////////////////////////////////////////
  return;
  /////////////////////////////////MASS////////////////////////////////////////

  // h1 = PlotHist("Mass2015CUP8", kinematics::calc::total, file1.Data(),
  //               TString("pe"), 100, 0.5, 3.5);
  // h2 = PlotHist("Mass2015CUP9", kinematics::calc::total, file2.Data(),
  //               TString("pe"), 100, 0.5, 3.5);
  // h3 = PlotHist("Mass2018CUP29", kinematics::calc::total, file3.Data(),
  //               TString("pe"), 100, 0.5, 3.5);
  // h4 = PlotHist("Mass2018CUP30", kinematics::calc::total, file4.Data(),
  //               TString("pe"), 100, 0.5, 3.5);
  // h5 = PlotHist("Mass2018CUP31", kinematics::calc::total, file5.Data(),
  //               TString("pe"), 100, 0.5, 3.5);

  /////////////////////////////////MASS////////////////////////////////////////

  // scaling factor from pts - 1.144
  // v.push_back(hBcg);
  // v.push_back(hSig);
  v.push_back(h1);
  v.push_back(h2);
  v.push_back(h3);
  v.push_back(h4);
  v.push_back(h5);

  // DrawHists(v);
  // std::cout << "PlotEvents::Elapsed time: " << stpw.RealTime() << ", sec "
  //           << std::endl;
  // return;

  TFile f("4tracks.hists.root", "UPDATE");
  f.cd();
  for (const auto &h : v)
    h.Write(h.GetName());
  f.Close();

  std::cout << "PlotEvents::Elapsed time: " << stpw.RealTime() << ", sec"
            << std::endl;
}

void DrawHists(std::vector<TH1D> &hArr)
{

  for (auto i = 0; i < hArr.size(); ++i)
  {
    hArr[i].SetMarkerColor(i + 1);
    hArr[i].SetLineColor(i + 1);
    hArr[i].Scale(1.0 / hArr[i].GetMaximum());
    if (i != 0)
      hArr[i].DrawClone("pesame");
    else
      hArr[i].DrawClone("pe");

    // AddVLine(hArr[i])->Draw();
  }
  gPad->BuildLegend();
  TLatex xAxisLabel, yAxisLabel;
  TAxis *xax = hArr[0].GetXaxis();
  xAxisLabel.SetTextSizePixels(16);
  yAxisLabel.SetTextSizePixels(16);

  xAxisLabel.DrawLatexNDC(0.9, 0.1, "#pi^{+}#pi^{-}#pi^{+}#pi^{-}  M, GeV");
  yAxisLabel.DrawLatexNDC(
      0.1, 0.9,
      TString::Format("#frac{Counts}{%d MeV}",
                      1 + (Int_t)(((xax->GetXmax() - xax->GetXmin()) * 1000) /
                                  hArr[0].GetNbinsX())));
}

TH1D PlotHist(TString col1Name, kinematics::calc var, TString file,
              TString drawOption, Int_t bins, Double_t xLow, Double_t xUp)
{
  kinematics::variant = var;
  std::cout << "PlotHist::Initialising of creating histograms based on " << file
            << std::endl;
  ROOT::RDataFrame rd("events", file.Data());

  //auto profileModel = new ROOT::RDF::TProfile1DModel(TString::Format("%s<=>%s",col1Name.Data(),col2Name.Data()).Data(), \
  //TString::Format("%s<=>%s",col1Title.Data(),col2Title.Data()).Data(), \
  //360, \
  //0, \
  //360);

  ROOT::RDF::TH1DModel histModel(col1Name.Data(), col1Name.Data(), bins, xLow,
                                 xUp);

  auto hist =
      rd.Define(col1Name.Data(), kinematics::Mass,
                {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                 "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                 "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dca0",
                 "dca1"})
          .Filter((col1Name + TString(">0")).Data())
          .Histo1D(histModel, col1Name.Data());

  // auto hist = rd.Define(col1Name.Data(),\
  //                     detectors::VZeroPar,\
  //                     {"dV0"}).\
  //                 Histo1D(histModel, col1Name.Data());

  if (showDraw)
  {
    auto c = new TCanvas(col1Name.Data(), col1Name.Data());
    hist.OnPartialResult(10000, [&](TH1D &hist_) {
      c->cd();
      hist_.Draw(drawOption.Data());
      c->Update();
    });
    hist->DrawClone(drawOption.Data());
  }

  return hist.GetValue();
}

TH2D PlotHist2D(TString name, TString title, TString col1Name, TString col2Name,
                Int_t binsX, Double_t xLow, Double_t xUp, Int_t binsY,
                Double_t yLow, Double_t yUp)
{
  ::Info("Analysis", "Draft");

  if (binsY + yLow + yUp == 0)
  {
    binsY = binsX;
    yLow = xLow;
    yUp = xUp;
  }

  ROOT::RDataFrame rd(
      "events",
      "/mnt/c/GoogleDrive/Job/cern/Alice/analysis/data/rho/newResult.root");

  ROOT::RDF::TH2DModel histModel(name.Data(), title.Data(), binsX, xLow, xUp,
                                 binsY, yLow, yUp);

  auto hist =
      rd.Define(col1Name.Data(), kinematics::Mass,
                {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                 "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                 "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dca0",
                 "dca1"})
          .Define(col2Name.Data(), kinematics::Mass2,
                  {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                   "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                   "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dca0",
                   "dca1"})
          .Filter((col1Name + TString(" > 0 && ") + col2Name + TString(" > 0"))
                      .Data())
          .Histo2D(histModel, col1Name.Data(), col2Name.Data());

  if (showDraw)
  {
    auto c = new TCanvas(col1Name.Data(), col1Name.Data());
    hist.OnPartialResult(10000, [&c](TH2D &hist_) {
      c->cd();
      hist_.Draw("colz");
      c->Update();
    });
    hist->DrawClone("colz");
  }

  return hist.GetValue();
}

TGraph PlotGraph(TString col1Name, TString col1Title, TString col2Name,
                 TString col2Title)
{

  ::Info("Analysis", "Draft");
  // ROOT::RDataFrame rd("events", "../../../data/rho/newResult.root");
  ROOT::RDataFrame rd("events", "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/"
                                "data/rho/data2015.cup9.new.root");

  auto graph =
      rd.Define(col1Name.Data(), kinematics::Mass,
                {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                 "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                 "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dca0",
                 "dca1"})
          .Define(col2Name.Data(), kinematics::Mass2,
                  {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1",
                   "StatusAndTPCRefit", "StatusAndITSRefit", "TPCNcls",
                   "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz", "dca0",
                   "dca1"})
          .Filter((col1Name + TString(" > 0 && ") + col2Name + TString(" > 0"))
                      .Data())
          .Graph(col1Name.Data(), col2Name.Data());
  if (showDraw)
  {
    auto c = new TCanvas(
        TString::Format("%s<=>%s", col1Name.Data(), col2Name.Data()).Data(),
        TString::Format("%s<=>%s", col1Title.Data(), col2Title.Data()).Data());

    graph.OnPartialResult(10000, [&c](TGraph &graph_) {
      c->cd();
      graph_.Draw("ap");
      c->Update();
    });
    graph->DrawClone("ap");
  }

  return graph.GetValue();
}

TLine *AddVLine(TH1D &h)
{

  auto l = new TLine(h.GetMean(), 0, h.GetMean(), h.GetMaximum());
  l->SetLineWidth(3);
  l->SetLineColor(h.GetMarkerColor());

  return l;
}
