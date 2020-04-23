#include "TError.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>


TH1D* InvMassBg() {
  auto stpw = new TStopwatch();
  stpw->Start();
  ::Info("InvMass", "Invariant mass for 4Pions");
  auto rd = new ROOT::RDataFrame("events", "newResult.root");
  auto hm = new ROOT::RDF::TH1DModel("InvMass", "InvMass", 70,0.5,3);

  auto ptBg = [](Int_t n, ROOT::VecOps::RVec<Int_t> &x, ROOT::VecOps::RVec<Int_t> &y, ROOT::VecOps::RVec<Int_t> &z, ROOT::VecOps::RVec<Float_t> &px, ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz, ROOT::VecOps::RVec<Int_t> TrigType) {
    int nGoodTracks = 0;
    int q = 0;
    Double_t massPion = 0.140;
    Double_t tempPx{};
    Double_t tempPy{};
    Double_t tempPz{};
    Double_t tempEnergy{};
    Double_t tempInvMass{};
  //  if (!TrigType[0]) return -1.;
    if (n >= 177) return -1.;
    for(auto i = 0; i < n; ++i) {
      if(!x[i] && !y[i]) continue;
      nGoodTracks++;
      q += z[i];
      tempPx += px[i];
      tempPy += py[i];
      tempPz += pz[i];
      tempEnergy += TMath::Sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i] + massPion*massPion);
    }
    if (nGoodTracks != 4 || TMath::Abs(q) != 2) return -1.;
    tempInvMass = TMath::Sqrt(tempEnergy*tempEnergy - tempPx*tempPx - tempPy*tempPy - tempPz*tempPz);

    return tempInvMass;
  };
    
  auto hInvMass = rd->Define("InvMass", ptBg, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1", "charge", "Px", "Py", "Pz", "TriggerType"}).Filter("InvMass>0").Histo1D(*hm,"InvMass");

 auto c = new TCanvas("c","InvMass");
 hInvMass.OnPartialResult(100000, [&c](TH1D &hInvMass_) { c->cd(); hInvMass_.Draw(); c->Update(); });

 hInvMass->DrawClone(); // event loop runs here, this `Draw` is executed after the event loop is finished
  TH1D* h1 = hInvMass.GetPtr();
  
//   h1->DrawClone();
//   TODO: after RDataFrame Filter or Define standart output switches to somewhere. Use std::cout!
//   ::Info("", "Elapsed time:  %f, sec", stpw->RealTime());
  std::cout <<"Elapsed time: " << stpw->RealTime() << ", sec" << std::endl;
  return (TH1D*) h1->Clone();
}
