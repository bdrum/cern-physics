from modules import dfs, np, pd


def Get4TracksEvents(Q=0, nTPC=3, lowPt=0.15, Q_EQ=True):

    # only 4 tracks events
    dfs4Tracks = (dfs.reset_index().groupby('entry').count() == 4)

    # only zero total charge from 4 tracks events
    if Q_EQ:
        dfs4Tracks = dfs4Tracks[dfs.reset_index().groupby(
            'entry').sum().T_Q == 0]
    else:
        dfs4Tracks = dfs4Tracks[dfs.reset_index().groupby(
            'entry').sum().T_Q != 0]

    # remove tracks that not passed the criteria
    dfs4Tracks = dfs[dfs4Tracks].dropna(how='any')

    TPCMask = (np.abs(dfs4Tracks.T_NumberOfSigmaTPCPion) < 3) & (
        dfs4Tracks.T_TPCNCls > 50) & (dfs4Tracks.T_TPCRefit == 1)

    dfsPt = dfs4Tracks[['T_Px', 'T_Py']]
    dfsPt = np.sqrt(dfsPt.groupby('entry').sum()[
                    'T_Px']**2 + dfsPt.groupby('entry').sum()['T_Py']**2)

    dfs4TracksLowPt = dfs4Tracks.loc[dfsPt[(
        dfsPt < lowPt)].reset_index().entry]
    TPCMaskLowPt = (np.abs(dfs4TracksLowPt.T_NumberOfSigmaTPCPion) < 3) & (
        dfs4TracksLowPt.T_TPCNCls > 50) & (dfs4TracksLowPt.T_TPCRefit == 1)

    ITSnTPCEvents = pd.unique(dfs4TracksLowPt.reset_index().entry)[
        TPCMaskLowPt.groupby('entry').sum() >= nTPC]
    return dfs4Tracks.loc[ITSnTPCEvents]
