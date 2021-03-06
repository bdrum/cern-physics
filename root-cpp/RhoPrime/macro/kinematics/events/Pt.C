#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TROOT.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>
#include "PtBg.C"

void Pt() {
  auto stpw = new TStopwatch();
  stpw->Start();
  auto rd = new ROOT::RDataFrame("events", "../../../../../data/rho/newResult.root");
  auto hm = new ROOT::RDF::TH1DModel("Pt", "Pt", 100,0,2);
  auto h  = new TH1D("diff", "diff", 180, 0 ,180);
  auto ptAll = [&](Int_t n, \
                   ROOT::VecOps::RVec<Int_t> &x, \
                   ROOT::VecOps::RVec<Int_t> &y, \
                   ROOT::VecOps::RVec<Int_t> &charge, \
                   ROOT::VecOps::RVec<Int_t> &z, \
                   ROOT::VecOps::RVec<Int_t> &t, \
                   ROOT::VecOps::RVec<Int_t> &c, \
                   ROOT::VecOps::RVec<Float_t> &px, \
                   ROOT::VecOps::RVec<Float_t> &py, \
                   ROOT::VecOps::RVec<Float_t> &pz, \
                   ROOT::VecOps::RVec<Int_t> TrigType, \
                   ROOT::VecOps::RVec<Float_t> &sigm)
{

    Int_t nGoodTracks{}, q{}, n2hit{}, n1hit{}, nnn{};
    Double_t tempPx{}, tempPy{}, tempPz{}, tempPt{}, evPRap{};
    
//  if (!TrigType[0]) return -1.;
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
      tempPz += pz[i];
    }

    if (nGoodTracks != 4 || q != 0) return -1.;
    if (nnn != 0)  return -1.;
    if (n2hit < 2) return -1.;
    evPRap = TMath::Abs(0.5 * TMath::Log((TMath::Sqrt(tempPx*tempPx + tempPy*tempPy + tempPz*tempPz) + tempPz) / (TMath::Sqrt(tempPx*tempPx + tempPy*tempPy + tempPz*tempPz) - tempPz)));
    if (evPRap > 2) return -1.;
     tempPt = TMath::Sqrt(tempPx*tempPx + tempPy*tempPy);

    std::cout << TString::Format("%f %f %f %f %f", tempPx, tempPy, tempPt, tempPz, evPRap) << std::endl;


    return tempPt;

  };
    
  auto hPtAll = rd->Define("PtNew", ptAll, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1", "charge", "StatusAndTPCRefit", "StatusAndITSRefit","TPCNcls", "Px", "Py", "Pz", "TriggerType", "NumberOfSigmasTPCPion"}).Filter("PtNew>0").Histo1D(*hm,"PtNew");

  auto c = new TCanvas("c","PtAll");
  hPtAll.OnPartialResult(25000, [&c](TH1D &hPtAll_) { c->cd(); hPtAll_.Draw(); c->Update(); });

  hPtAll->DrawClone(); // event loop runs here, this `Draw` is executed after the event loop is finished
//    TH1D* h1 = hPtAll.GetPtr();
//    TH1D* h1div = (TH1D*)h1->Clone("CloneDiv");
//    h1div->Divide(PtBg(), h1, 1., 1., "b");
//    h1div->DrawClone();
//    h1->Add(PtBg(),-(2.613));
//    h1->DrawClone();
//   TODO: after RDataFrame Filter or Define standart output switches to somewhere. Use std::cout!
//   ::Info("", "Elapsed time:  %f, sec", stpw->RealTime());
  std::cout <<"Elapsed time: " << stpw->RealTime() << ", sec" << std::endl;
}
