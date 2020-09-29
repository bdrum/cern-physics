# https://github.com/bdrum/cern-physics/issues/21
# https://docs.google.com/presentation/d/1RxAWkZTwhNdXUZpJXh1VQhhu5SjIoxIPGrmtEsBIVr0/edit?usp=sharing

from modules.physics.kinematics.rapidity import GetPseudoRapidityTracks, GetThetaTracks
from modules.physics.kinematics.momentum import GetPtTracks
from modules.data.selection import dfs4Tracks
from modules import np, plt, pd, hep

# take only tracks from events with total pt < 0.15
dfsPt = dfs4Tracks[['T_Px', 'T_Py']]
dfsPt = np.sqrt(dfsPt.groupby('entry').sum()[
                'T_Px']**2 + dfsPt.groupby('entry').sum()['T_Py']**2)
dfs4TracksLowPt = dfs4Tracks.loc[dfsPt[(dfsPt < 0.15)].reset_index().entry]
TPCMaskLowPt = (np.abs(dfs4TracksLowPt.T_NumberOfSigmaTPCPion) < 3) & (
    dfs4TracksLowPt.T_TPCNCls > 50) & (dfs4TracksLowPt.T_TPCRefit == 1)

# get only tpctracks
EventsWith4TPCTracks = pd.unique(dfs4TracksLowPt.reset_index().entry)[
    TPCMaskLowPt.groupby('entry').sum() == 4]
AllTPCTracks = dfs4TracksLowPt.loc[EventsWith4TPCTracks]

# find pt, h, theta for such tracks
AllTPCTracksPt = GetPtTracks(AllTPCTracks)
AllTPCTracksRap = GetPseudoRapidityTracks(AllTPCTracks)
AllTPCTracksTheta = GetThetaTracks(AllTPCTracks)

# now, get events with from 0 to 4 tpc tracks
EventsWithnTPCTracks = pd.unique(dfs4TracksLowPt.reset_index().entry)[
    TPCMaskLowPt.groupby('entry').sum() <= 4]
NTPCTracks = dfs4TracksLowPt.loc[EventsWithnTPCTracks]

# take only ITS tracks from events with n TPC tracks
FourDiffNITSTracks = NTPCTracks[~TPCMaskLowPt]
ITSDiffTPCTracksPt = GetPtTracks(FourDiffNITSTracks)
ITSDiffTPCTracksRap = GetPseudoRapidityTracks(FourDiffNITSTracks)
ITSDiffTPCTracksTheta = GetThetaTracks(FourDiffNITSTracks)

# # take events without TPC tracks
# ITSOnlyEvents = pd.unique(dfs4TracksLowPt.reset_index().entry)[TPCMaskLowPt.groupby('entry').sum() == 0]
# ITSOnlyTracks = dfs4TracksLowPt.loc[ITSOnlyEvents]
# ITSOnlyTracksPt = GetPtTracks(ITSOnlyTracks)
# ITSOnlyTracksRap =  GetPseudoRapidityTracks(ITSOnlyTracks)

# take total tracks from events with nTPC tracks, n=0,4
TotalLowPt = GetPtTracks(dfs4TracksLowPt)
TotalLowPtRap = GetPseudoRapidityTracks(dfs4TracksLowPt)
TotalLowPtTheta = GetThetaTracks(dfs4TracksLowPt)


def ShowComparison(param, arrs, units, labels, nBins=100, ranges=(0, 1)):
    plt.style.use(hep.style.ROOT)

    fig, axs = plt.subplots(len(arrs), figsize=(15, 7), sharex=True)
    fig.suptitle(
        f'tracks {param} from events with total $p_t<0.15$', fontsize=32)

    for i in range(len(arrs)):
        axs[i].hist(arrs[i], bins=nBins, range=ranges,
                    color='black', histtype='step', label=labels[i])
        axs[i].legend(prop={'size': 10})

    axs[-1].set_xlabel(f'{param}, {units}')
