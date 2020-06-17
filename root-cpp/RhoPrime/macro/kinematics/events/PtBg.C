#include "TError.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>


TH1D* PtBg() {
  auto stpw = new TStopwatch();
  stpw->Start();
  ::Info("PtBg", "New analysis method via using RDataFrame is starting:");
  auto rd = new ROOT::RDataFrame("events", "newResult.root");
  auto hm = new ROOT::RDF::TH1DModel("Pt", "Pt", 100,0,2);

  auto ptBg = [](Int_t n, ROOT::VecOps::RVec<Int_t> &x, ROOT::VecOps::RVec<Int_t> &y, ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Int_t> &z, ROOT::VecOps::RVec<Int_t> &t, ROOT::VecOps::RVec<Int_t> &c,  ROOT::VecOps::RVec<Float_t> &px, ROOT::VecOps::RVec<Float_t> &py,  ROOT::VecOps::RVec<Int_t> TrigType, ROOT::VecOps::RVec<Float_t> &sigm) {
    Int_t nGoodTracks{}, q{}, n2hit{}, n1hit{}, nnn{};
    Double_t tempPx{}, tempPy{}, tempPt{};
    if (n >= 177) return -1.;
    for(auto i = 0; i < n; ++i) {
      if (!x[i] && !y[i]) continue;
      if (!z[i] && !t[i]) continue;
      if (c[i] < 50) continue;
      if (sigm[i] > 3) nnn++;

      if ( x[i] &&  y[i]) n2hit++;
      
      nGoodTracks++;
      q += charge[i];
      tempPx += px[i];
      tempPy += py[i];
    }
    if (nGoodTracks != 4 || q != 2) return -1.;
    if (nnn != 0)  return -1.;
    if (n2hit < 2) return -1.;
    tempPt = TMath::Sqrt(tempPx*tempPx + tempPy*tempPy);
    return tempPt;
  };
    
  auto hPtBg = rd->Define("PtBg", ptBg, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1", "charge", "StatusAndTPCRefit", "StatusAndITSRefit","TPCNcls", "Px", "Py", "TriggerType", "NumberOfSigmasTPCPion"}).Filter("PtBg>0").Histo1D(*hm,"PtBg");

 // auto c = new TCanvas("c","PtBg");
  //hPtBg.OnPartialResult(10000, [&c](TH1D &hPtBg_) { c->cd(); hPtBg_.Draw(); c->Update(); });

//   hPtBg->DrawClone(); // event loop runs here, this `Draw` is executed after the event loop is finished
  TH1D* h1 = hPtBg.GetPtr();
  
//   h1->DrawClone();
//   TODO: after RDataFrame Filter or Define standart output switches to somewhere. Use std::cout!
//   ::Info("", "Elapsed time:  %f, sec", stpw->RealTime());
  std::cout <<"Elapsed time: " << stpw->RealTime() << ", sec" << std::endl;
  return (TH1D*) h1->Clone();
}
