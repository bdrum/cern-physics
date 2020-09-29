from modules import np, pd


def GetPtTracks(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    return np.sqrt(tracks.T_Px**2 + tracks.T_Py**2).to_numpy()


def GetPTracks(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    return np.sqrt(tracks.T_Px**2 + tracks.T_Py**2 + tracks.T_Pz**2).to_numpy()


def GetPtEvents(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    return np.sqrt(tracks.groupby('entry').T_Px.sum()**2 + tracks.groupby('entry').T_Py.sum()**2)


def GetPEvents(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    return np.sqrt(tracks.groupby('entry').T_Px.sum()**2 + tracks.groupby('entry').T_Py.sum()**2 + tracks.groupby('entry').T_Pz.sum()**2)
