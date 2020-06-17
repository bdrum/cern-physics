#pragma once

#include "Math/Vector4Dfwd.h"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RResultPtr.hxx"
#include "TError.h"
#include "TH1D.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TROOT.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace kinematics
{

  typedef std::pair<std::pair<int, int>, ROOT::Math::PxPyPzMVector> pIndexPair;
  typedef std::pair<int, int> intPair;

  static int netChargeValue = 0;

  enum calc
  {
    light,
    heavy,
    total,
    like,
    unlike,
    ptSig,
    ptTotal,
    ptBcg
  };
  static calc variant = total;
  static bool debug = false;
  static bool Psi2S = false;

  auto Mass(Int_t nTracks, ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0,
            ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1,
            ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,
            ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,
            ROOT::VecOps::RVec<Int_t> &TPCNcls,
            ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion,
            ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Float_t> &px,
            ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz,
            ROOT::VecOps::RVec<Float_t> &dca0,
            ROOT::VecOps::RVec<Float_t> &dca1)
  {

    Int_t netCharge{}, nGoodTracks{};
    Double_t massPion = 0.140;
    std::vector<ROOT::Math::PxPyPzMVector> posTracks;
    std::vector<ROOT::Math::PxPyPzMVector> negTracks;
    std::vector<pIndexPair> pairs;
    posTracks.reserve(2);
    negTracks.reserve(2);
    pairs.reserve(4);

    for (auto i = 0; i < nTracks; ++i)
    {
      if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i])
        continue;
      if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i])
        continue;
      if (std::abs(dca0[i]) > 3 || std::abs(dca1[i]) > 3)
        continue;
      if (TPCNcls[i] < 50)
        continue;

      if (std::abs(NumberOfSigmasTPCPion[i]) > 3)
        continue;

      if (debug)
      {
        std::cout << "p: " << px[i] << "|" << py[i] << "|" << pz[i] << std::endl;
        std::cout << "charge: " << charge[i] << std::endl;
      }

      if (charge[i] < 0)
        negTracks.push_back(
            ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));
      if (charge[i] > 0)
        posTracks.push_back(
            ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));

      netCharge += charge[i];
      nGoodTracks++;

      // nGoodTracks not more and equal than 4 because in case of more and equal
      // we add events that e.g. could have 5 good tracks!
      if (nGoodTracks > 4)
        break;
    }

    if (nGoodTracks != 4 || std::abs(netCharge) != netChargeValue)
      return -1.;

    for (auto i = 0; i < posTracks.size(); ++i)
    {
      for (auto j = 0; j < negTracks.size(); ++j)
        pairs.push_back(pIndexPair(intPair(i, j), (posTracks[i] + negTracks[j])));
    }

    auto comparer = [](const pIndexPair &a, const pIndexPair &b) {
      return (a.second.M() < b.second.M());
    };

    std::sort(pairs.begin(), pairs.end(), comparer);

    if (debug)
    {
      std::cout << "===============================" << std::endl;
      for (const auto &p : pairs)
        std::cout << p.first.first << "_" << p.first.second << "  |  "
                  << p.second.M() << std::endl;
      std::cout << "===============================" << std::endl;
    }

    auto lightPairVec = pairs[0].second;
    ROOT::Math::PxPyPzMVector heavyPairVec;

    auto invIndexes = intPair(TMath::Abs(pairs[0].first.first - 1),
                              TMath::Abs(pairs[0].first.second - 1));

    for (const auto &p : pairs)
    {
      if (p.first == invIndexes)
      {
        heavyPairVec = p.second;
        break;
      }
    }

    auto ttlVec = posTracks[0] + posTracks[1] + negTracks[0] + negTracks[1];

    switch (variant)
    {
    case light:
      return lightPairVec.M();
    case heavy:
    {
      if (Psi2S)
      {
        if (heavyPairVec.M() >= 3 && heavyPairVec.M() <= 3.2)
          return ttlVec.M();
        else
          return -1.;
      }

      return heavyPairVec.M();
    }
    case total:
    {
      if (ttlVec.Pt() > 0.15)
        return -1.;

      return ttlVec.M();
    }
    case ptTotal:
      return ttlVec.Pt();
    case ptBcg:
    {
      // if (ttlVec.Eta() <= 2)
      if (ttlVec.Pt() > 0.15)
        return ttlVec.Pt();
      else
        return -1.0;
    }
    case ptSig:
    {
      // if (ttlVec.Eta() > 2)
      if (ttlVec.Pt() <= 0.15)
        return ttlVec.Pt();
      else
        return -1.0;
    }
    }
  } // Mass

  auto Mass2(Int_t nTracks, ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer0,
             ROOT::VecOps::RVec<Int_t> &HasPointOnITSLayer1,
             ROOT::VecOps::RVec<Int_t> &StatusAndTPCRefit,
             ROOT::VecOps::RVec<Int_t> &StatusAndITSRefit,
             ROOT::VecOps::RVec<Int_t> &TPCNcls,
             ROOT::VecOps::RVec<Float_t> &NumberOfSigmasITSPion,
             ROOT::VecOps::RVec<Float_t> &NumberOfSigmasTPCPion,
             ROOT::VecOps::RVec<Int_t> &charge, ROOT::VecOps::RVec<Float_t> &px,
             ROOT::VecOps::RVec<Float_t> &py, ROOT::VecOps::RVec<Float_t> &pz)
  {

    Int_t netCharge{}, nGoodTracks{};
    Double_t massPion = 0.140;
    std::vector<ROOT::Math::PxPyPzMVector> posTracks;
    std::vector<ROOT::Math::PxPyPzMVector> negTracks;
    std::vector<pIndexPair> pairs;
    posTracks.reserve(2);
    negTracks.reserve(2);
    pairs.reserve(4);

    for (auto i = 0; i < nTracks; ++i)
    {
      if (!HasPointOnITSLayer0[i] && !HasPointOnITSLayer1[i])
        continue;
      if (!StatusAndTPCRefit[i] && !StatusAndITSRefit[i])
        continue;
      if (TPCNcls[i] < 50)
        continue;
      if (NumberOfSigmasTPCPion[i] > 3)
        continue;
      if (NumberOfSigmasITSPion[i] > 3)
        continue;

      if (charge[i] < 0)
        negTracks.push_back(
            ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));
      if (charge[i] > 0)
        posTracks.push_back(
            ROOT::Math::PxPyPzMVector(px[i], py[i], pz[i], 0.140));
      netCharge += charge[i];
      nGoodTracks++;
      if (nGoodTracks > 4)
        break;
    }

    if (nGoodTracks != 4 || TMath::Abs(netCharge) != netChargeValue)
      return -1.;
    if ((posTracks[0] + posTracks[1] + negTracks[0] + negTracks[1]).Pt() > 0.15)
      return -1.;

    for (auto i = 0; i < posTracks.size(); ++i)
    {
      for (auto j = 0; j < negTracks.size(); ++j)
        pairs.push_back(pIndexPair(intPair(i, j), (posTracks[i] + negTracks[j])));
    }

    auto comparer = [](const pIndexPair &a, const pIndexPair &b) {
      return (a.second.M() < b.second.M());
    };

    std::sort(pairs.begin(), pairs.end(), comparer);

    if (debug)
    {
      std::cout << "===============================" << std::endl;
      for (const auto &p : pairs)
        std::cout << p.first.first << "_" << p.first.second << "  |  "
                  << p.second.M() << std::endl;
      std::cout << "===============================" << std::endl;
    }

    auto lightPairVec = pairs[0].second;
    ROOT::Math::PxPyPzMVector heavyPairVec;

    auto invIndexes = intPair(TMath::Abs(pairs[0].first.first - 1),
                              TMath::Abs(pairs[0].first.second - 1));

    for (const auto &p : pairs)
    {
      if (p.first == invIndexes)
      {
        heavyPairVec = p.second;
        break;
      }
    }

    return heavyPairVec.M();
  } // Mass2

} // namespace kinematics
