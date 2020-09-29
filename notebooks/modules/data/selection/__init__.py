from modules import dfs, np

# only 4 tracks events
dfs4Tracks = (dfs.reset_index().groupby(
    'entry').count() == 4)

# only zero total charge from 4 tracks events
dfs4Tracks = dfs4Tracks[dfs.reset_index().groupby('entry').sum().T_Q == 0]

# remove tracks that not passed the criteria
dfs4Tracks = dfs[dfs4Tracks].dropna(how='any')


TPCMask = (np.abs(dfs4Tracks.T_NumberOfSigmaTPCPion) < 3) & (
    dfs4Tracks.T_TPCNCls > 50) & (dfs4Tracks.T_TPCRefit == 1)
