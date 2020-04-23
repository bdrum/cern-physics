#include "TError.h"
#include "TFile.h"
#include "TMath.h"
#include "TStopwatch.h"
#include "TTree.h"
#include <algorithm>
#include <vector>

void RewriteTree(Int_t n = 1000) {
  auto stpw = new TStopwatch();
  stpw->Start();
  auto fin = new TFile(
      "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/ccup31.sel.root");
  TTree *tr = nullptr;
  fin->GetObject("events", tr);
  if (n < 1)
    n = tr->GetEntries(); // 7 259 517  // 99.9999% completed. Time has passed:
                          // 11662.2, sec

  Float_t TrackPara[177][17]{};
  Float_t LetsPara[177][2]{};
  std::fill_n(&TrackPara[0][0], 177 * 17, -1717.);
  std::fill_n(&LetsPara[0][0], 177 * 2, -1717.);
  Int_t TriggerType[16]{};
  Int_t TrigPara[177]{};
  Int_t nTracklets{};
  Int_t nTracks{};
  Int_t nTrig{};
  Float_t dV0[6]{};
  Float_t EnZDC[6]{};
  Float_t TDCa[4]{};
  Float_t TDCc[4]{};
  Float_t dAD[6]{};
  Float_t vertex[3]{};
  Int_t eventinfo[4]{};

  /*
    TrackPara[ntracks][0] = dca[0];
    TrackPara[ntracks][1] = dca[1];
    TrackPara[ntracks][2] = trk->AliAODTrack::GetITSNcls();
    TrackPara[ntracks][3] = trk->AliAODTrack::GetTPCNcls();q
    TrackPara[ntracks][4] = (trk->GetStatus()&AliAODTrack::kTPCrefit);
    TrackPara[ntracks][5] = trk->HasPointOnITSLayer(0);
    TrackPara[ntracks][6] = trk->HasPointOnITSLayer(1);
    TrackPara[ntracks][7] = trk->Charge();
    TrackPara[ntracks][8] = fPIDResponse->NumberOfSigmasTPC(trk, AliPID::kPion);
    TrackPara[ntracks][9] = fPIDResponse->NumberOfSigmasTPC(trk,
    AliPID::kElectron); TrackPara[ntracks][10] =
    (trk->GetStatus()&AliAODTrack::kITSrefit); TrackPara[ntracks][11] =
    trk->Px(); TrackPara[ntracks][12] = trk->Py(); TrackPara[ntracks][13] =
    trk->Pz(); TrackPara[ntracks][14] = fPIDResponse->NumberOfSigmasITS(trk,
    AliPID::kPion); TrackPara[ntracks][15] =
    fPIDResponse->NumberOfSigmasITS(trk, AliPID::kElectron);
    TrackPara[ntracks][16] = fPIDResponse->NumberOfSigmasITS(trk,
    AliPID::kKaon);
  */

  tr->SetBranchAddress("TrackPara", TrackPara);
  tr->SetBranchAddress("LetsPara", LetsPara);
  tr->SetBranchAddress("nTracks", &nTracks);
  tr->SetBranchAddress("nTrig", &nTrig);
  tr->SetBranchAddress("nTracklets", &nTracklets);
  tr->SetBranchAddress("TriggerType", TriggerType);
  tr->SetBranchAddress("TrigPara", TrigPara);
  tr->SetBranchAddress("dV0", dV0);
  tr->SetBranchAddress("EnZDC", EnZDC);
  tr->SetBranchAddress("TDCa", TDCa);
  tr->SetBranchAddress("TDCc", TDCc);
  tr->SetBranchAddress("dAD", dAD);
  tr->SetBranchAddress("vertex", vertex);
  tr->SetBranchAddress("eventinfo", eventinfo);

  // new values
  Float_t dca0[177]{};
  Float_t dca1[177]{};
  Int_t ITSNcls[177]{};
  Int_t TPCNcls[177]{};
  Int_t StatusAndTPCRefit[177]{};
  Int_t HasPointOnITSLayer0[177]{};
  Int_t HasPointOnITSLayer1[177]{};
  Int_t charge[177]{};
  Float_t NumberOfSigmasTPCPion[177]{};
  Float_t NumberOfSigmasTPCElectron[177]{};
  Int_t StatusAndITSRefit[177]{};
  Float_t Px[177]{};
  Float_t Py[177]{};
  Float_t Pz[177]{};
  Float_t Pt{};
  Float_t NumberOfSigmasITSPion[177]{};
  Float_t NumberOfSigmasITSElectron[177]{};
  Float_t NumberOfSigmasITSKaon[177]{};

  Float_t LetsPara1[177]{};
  Float_t LetsPara2[177]{};

  auto fot = new TFile(
      "/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/rho/ccup31.sel.new.root",
      "RECREATE");
  auto nTr = new TTree("events", "events");
  nTr->Branch("dV0", &dV0, "dV0[6]");
  nTr->Branch("EnZDC", &EnZDC, "EnZDC[6]");
  nTr->Branch("dAD", &dAD, "dAD[6]");
  nTr->Branch("vertex", &vertex, "vertex[3]");
  nTr->Branch("nTracks", &nTracks);
  nTr->Branch("nTracklets", &nTracklets);
  nTr->Branch("eventinfo", &eventinfo, "eventinfo[4]/I");
  nTr->Branch("TDCa", &TDCa, "TDCa[4]");
  nTr->Branch("TDCc", &TDCc, "TDCc[4]");

  nTr->Branch("TriggerType", &TriggerType, "TriggerType[16]/I");

  nTr->Branch("dca0", &dca0, "dca0[177]/F");
  nTr->Branch("dca1", &dca1, "dca1[177]/F");
  nTr->Branch("ITSNcls", &ITSNcls, "ITSNcls[177]/I");
  nTr->Branch("TPCNcls", &TPCNcls, "TPCNcls[177]/I");
  nTr->Branch("HasPointOnITSLayer0", &HasPointOnITSLayer0,
              "HasPointOnITSLayer0[177]/I");
  nTr->Branch("HasPointOnITSLayer1", &HasPointOnITSLayer1,
              "HasPointOnITSLayer1[177]/I");
  nTr->Branch("charge", &charge, "charge[177]/I");
  nTr->Branch("NumberOfSigmasTPCPion", &NumberOfSigmasTPCPion,
              "NumberOfSigmasTPCPion[177]/F");
  nTr->Branch("NumberOfSigmasTPCElectron", &NumberOfSigmasTPCElectron,
              "NumberOfSigmasTPCElectron[177]/F");
  nTr->Branch("NumberOfSigmasITSPion", &NumberOfSigmasITSPion,
              "NumberOfSigmasITSPion[177]/F");
  nTr->Branch("NumberOfSigmasITSElectron", &NumberOfSigmasITSElectron,
              "NumberOfSigmasITSElectron[177]/F");
  nTr->Branch("NumberOfSigmasITSKaon", &NumberOfSigmasITSKaon,
              "NumberOfSigmasITSKaon[177]/F");
  nTr->Branch("StatusAndTPCRefit", &StatusAndTPCRefit,
              "StatusAndTPCRefit[177]/I");
  nTr->Branch("StatusAndITSRefit", &StatusAndITSRefit,
              "StatusAndITSRefit[177]/I");
  nTr->Branch("LetsPara1", &LetsPara1, "LetsPara1[177]/F");
  nTr->Branch("LetsPara2", &LetsPara2, "LetsPara2[177]/F");
  nTr->Branch("TrigPara", &TrigPara, "TriggerPar[177]/I");
  nTr->Branch("Px", &Px, "Px[177]/F");
  nTr->Branch("Py", &Py, "Py[177]/F");
  nTr->Branch("Pz", &Pz, "Pz[177]/F");
  nTr->Branch("Pt", &Pt, "Pt/F");

  Float_t tempPx{};
  Float_t tempPy{};

  for (auto i = 0; i < n; ++i) {
    tempPx = 0;
    tempPy = 0;
    std::fill_n(&dca0[0], 177, -1717.);
    std::fill_n(&dca1[0], 177, -1717.);
    std::fill_n(&ITSNcls[0], 177, 1717);
    std::fill_n(&TPCNcls[0], 177, 1717);
    std::fill_n(&StatusAndTPCRefit[0], 177, 1717);
    std::fill_n(&HasPointOnITSLayer0[0], 177, 1717);
    std::fill_n(&HasPointOnITSLayer1[0], 177, 1717);
    std::fill_n(&charge[0], 177, 1717);
    std::fill_n(&NumberOfSigmasTPCPion[0], 177, 1717);
    std::fill_n(&NumberOfSigmasTPCElectron[0], 177, 1717);
    std::fill_n(&StatusAndITSRefit[0], 177, 1717);
    std::fill_n(&NumberOfSigmasITSPion[0], 177, 1717);
    std::fill_n(&NumberOfSigmasITSElectron[0], 177, 1717);
    std::fill_n(&NumberOfSigmasITSKaon[0], 177, 1717);
    std::fill_n(&Px[0], 177, -1717.);
    std::fill_n(&Py[0], 177, -1717.);
    std::fill_n(&Pz[0], 177, -1717.);

    std::fill_n(&LetsPara1[0], 177, -1717.);
    std::fill_n(&LetsPara2[0], 177, -1717.);

    if (n >= 10 && i % (Int_t)(n * 0.1) == 0)
      ::Info("", "%d%% completed. Time has passed: %f, sec",
             (Int_t)(100 * (((double)i) / n)), stpw->RealTime());
    stpw->Continue();
    tr->GetEntry(i);
    for (auto j = 0; j < nTracks; ++j) {
      dca0[j] = TrackPara[j][0];
      dca1[j] = TrackPara[j][1];
      ITSNcls[j] = TrackPara[j][2];
      TPCNcls[j] = TrackPara[j][3];
      StatusAndTPCRefit[j] = TrackPara[j][4];
      HasPointOnITSLayer0[j] = (Int_t)TrackPara[j][5];
      HasPointOnITSLayer1[j] = (Int_t)TrackPara[j][6];
      charge[j] = TrackPara[j][7];
      NumberOfSigmasTPCPion[j] = TrackPara[j][8];
      NumberOfSigmasTPCElectron[j] = TrackPara[j][9];
      StatusAndITSRefit[j] = TrackPara[j][10];
      Px[j] = TrackPara[j][11];
      Py[j] = TrackPara[j][12];
      Pz[j] = TrackPara[j][13];
      NumberOfSigmasITSPion[j] = TrackPara[j][14];
      NumberOfSigmasITSElectron[j] = TrackPara[j][15];
      NumberOfSigmasITSKaon[j] = TrackPara[j][16];
      tempPx += TrackPara[j][11];
      tempPy += TrackPara[j][12];
    }
    Pt = TMath::Sqrt(tempPx * tempPx + tempPy * tempPy);
    nTr->Fill();
  }
  nTr->Write("events");
  fot->Close();
  fin->Close();
}
