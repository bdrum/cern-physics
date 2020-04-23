// see description in ## Angle distribution section
#include "TError.h"
#include "TMath.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TStopwatch.h"
#include "TROOT.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RResultPtr.hxx>

void DrawOnNewCanvas(TH1D* h);
void draftEvents();

void draftEvents() {
  auto stpw = new TStopwatch();
  stpw->Start();
  ::Info("Analysis", "AngleDistribution");
  auto rd = new ROOT::RDataFrame("events", "../../../data/rho/newResult.root");
 
  auto func = [&](Int_t nTracks, \
                  ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0, \
                  ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1, \
                  ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,   \
                  ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,   \
                  ROOT::VecOps::RVec<Int_t> &TPCNcls, \
                  ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion, \
                  ROOT::VecOps::RVec<Int_t> &charge, \
                  ROOT::VecOps::RVec<Float_t> &px, \
                  ROOT::VecOps::RVec<Float_t> &py, \
                  ROOT::VecOps::RVec<Float_t> &pz) 
{

    Int_t netCharge{}, nGoodTracks{};
    Int_t cntDiffTracks{}; //number of tracks with opposit direction
    Double_t tempPx{}, tempPy{}, tempPz{}, evPt{}, evPhi{}, trPhi{};
    std::vector<Double_t> phiTracks;

    for (auto i = 0; i < nTracks; ++i)
    {
      if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i]) continue;
      if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i]) continue;
      if (TPCNcls[i] < 50) continue;
      if (NumberOfSigmasTPCPion[i] > 3) continue;
      netCharge += charge[i];
      nGoodTracks++;
      tempPx += px[i];
      tempPy += py[i];
      tempPz += pz[i];
      trPhi = TMath::RadToDeg() * TMath::ATan2(py[i], px[i]);
      if( py[i] < 0 ) trPhi += 360; 
      phiTracks.push_back(trPhi);
    }

    for (auto i = 1; i < phiTracks.size(); ++i)
    {
      trPhi = TMath::Abs(phiTracks[0] - phiTracks[i]);
      if (trPhi > 180) trPhi = 360 - trPhi;
      if (trPhi > 150) cntDiffTracks++;
    }

    evPhi = TMath::RadToDeg() * TMath::ATan2(tempPy,tempPx);
    if( tempPy < 0 ) evPhi += 360;  
    if (nGoodTracks != 4 || netCharge != 0) return -1;
    if (TMath::Abs(0.5 * TMath::Log((TMath::Sqrt(tempPx*tempPx + tempPy*tempPy + tempPz*tempPz) + tempPz)/(TMath::Sqrt(tempPx*tempPx + tempPy*tempPy + tempPz*tempPz) - tempPz))) > 2) return -1;

    return cntDiffTracks;
  };

  const char* varName = "cntDiffTracks";
  const char* varTitle = "cntDiffTracks-AngleDiff>150-PR>2";

  auto hm = new ROOT::RDF::TH1DModel(varTitle, varTitle, 4, 0, 4);

  auto hNetCharge = rd->Define(varName, func, {"nTracks", "HasPointOnITSLayer0", "HasPointOnITSLayer1", "StatusAndTPCRefit", "StatusAndITSRefit","TPCNcls", "NumberOfSigmasTPCPion", "charge", "Px", "Py", "Pz"}).Filter("cntDiffTracks >= 0").Histo1D(*hm, varName);
 
  auto c = new TCanvas(varTitle, varTitle);
  hNetCharge.OnPartialResult(10000, [&c](TH1D &hNetCharge_) { c->cd(); hNetCharge_.Draw(); c->Update(); });
  hNetCharge->DrawClone(); // event 
  std::cout <<"Elapsed time: " << stpw->RealTime() << ", sec" << std::endl;
}

void DrawOnNewCanvas(TH1D* h) {
  auto c = new TCanvas();
  c->cd();
  h->DrawClone();
}
