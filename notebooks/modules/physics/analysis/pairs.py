from modules import PiPlus, np, pd, hep, plt
from modules.data.validation import IsDataFrame


def GetPairMass(tracks1, tracks2):
    EPair = np.sqrt(tracks1.T_Px**2 + tracks1.T_Py**2 +
                    tracks1.T_Pz**2 + (0.001*PiPlus.mass)**2)
    EPair += np.sqrt(tracks2.T_Px**2 + tracks2.T_Py**2 +
                     tracks2.T_Pz**2 + (0.001*PiPlus.mass)**2)
    SPair = tracks1 + tracks2
    return np.sqrt(EPair**2 - SPair.T_Px**2 - SPair.T_Py**2 - SPair.T_Pz**2)


def GetPairs(tracks):
    PosFirstTrack = tracks[tracks.T_Q > 0].groupby('entry').first()
    PosSecTrack = tracks[tracks.T_Q > 0].groupby('entry').last()
    NegFirstTrack = tracks[tracks.T_Q < 0].groupby('entry').first()
    NegSecTrack = tracks[tracks.T_Q < 0].groupby('entry').last()

    # test for matching taken tracks and their positions in the inital data
    assert ((tracks.loc[217].loc[2] == PosFirstTrack.loc[217]).all() and
            (tracks.loc[217].loc[0] == NegFirstTrack.loc[217]).all() and
            (tracks.loc[217].loc[3] == PosSecTrack.loc[217]).all() and
            (tracks.loc[217].loc[1] == NegSecTrack.loc[217]).all()), \
        'Tracks in pairs are not matched with initial data'

    # get first possible combinations of pairs
    FirstPairMass = GetPairMass(PosFirstTrack, NegFirstTrack)
    SecPairMass = GetPairMass(PosSecTrack,   NegSecTrack)

    # get second possible combinations of pairs
    ThirdPairMass = GetPairMass(PosFirstTrack, NegSecTrack)
    FourthPairMass = GetPairMass(PosSecTrack,   NegFirstTrack)

    # find lightest pairs in combinations
    firstComb = pd.DataFrame(
        {"FirstPair": FirstPairMass, "SecondPair": SecPairMass})
    secondComb = pd.DataFrame(
        {"FirstPair": ThirdPairMass, "SecondPair": FourthPairMass})

    # order pairs as lite - heavy in first combinations and take only those that lighter then pairs from second combination
    firstCombSorted = pd.DataFrame(
        {"Lite": firstComb[firstComb.min(axis=1) < secondComb.min(axis=1)].min(axis=1),
         "Heavy": firstComb[firstComb.min(axis=1) < secondComb.min(axis=1)].max(axis=1)
         })

    # order pairs as lite - heavy in second combinations and take only those that lighter then pairs from first combination
    secondCombSorted = pd.DataFrame(
        {"Lite": secondComb[firstComb.min(axis=1) > secondComb.min(axis=1)].min(axis=1),
         "Heavy": secondComb[firstComb.min(axis=1) > secondComb.min(axis=1)].max(axis=1)
         })

    # combine getting pairs into one dataframe
    array = np.concatenate(
        (firstCombSorted.to_numpy(), secondCombSorted.to_numpy()))

    LiteHeavyRecoil = pd.DataFrame(
        {'Lite': array[:, 0], 'Recoil': array[:, 1]})

    LiteHeavyTotal = pd.DataFrame({
        'Lite': pd.concat([firstComb.min(axis=1), secondComb.min(axis=1)]),
        'Recoil': pd.concat([firstComb.max(axis=1), secondComb.max(axis=1)])
    })

    return LiteHeavyRecoil, LiteHeavyTotal


def ShowMassComaprison(MassPairs, title):

    IsDataFrame(MassPairs)

    plt.style.use(hep.style.ROOT)
    fig, ax = plt.subplots(2, 1, figsize=(10, 10))
    fig.suptitle(title, fontsize=32)
    _ = ax[0].hist(MassPairs.Lite, bins=100, range=(
        0, 2), histtype='step', color='blue', linewidth=2, label=r'$\pi^+\pi^-$')
    _ = ax[0].hist(MassPairs.Recoil, bins=100, range=(
        0, 2), histtype='step', color='red', linewidth=2, label=r'$\rho^0$')
    ax[0].set_xlabel('$Mass, GeV$')
    ax[0].set_ylabel('# events')
    ax[0].legend()

    _ = ax[1].hist2d(MassPairs.Recoil, MassPairs.Lite, bins=(
        50, 50), range=[(0, 2), (0, 2)], cmap=plt.cm.jet)
    ax[1].set_ylabel(r'$\pi^+\pi^-$ Mass, GeV')
    ax[1].set_xlabel(r'$\rho^0$ Mass, GeV')
    # ax[1].yaxis.set_label_position("right")
    ax[1].yaxis.tick_right()
    ax[1].legend()
