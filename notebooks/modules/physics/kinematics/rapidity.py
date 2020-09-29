from modules import np, pd
from modules.physics.kinematics.momentum import GetPTracks, GetPEvents


def GetPseudoRapidityTracks(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    lenP = np.sqrt(tracks.T_Px**2 + tracks.T_Py**2 + tracks.T_Pz**2)
    return 0.5*np.log((lenP + tracks.T_Pz) / (lenP - tracks.T_Pz))


def GetThetaTracks(tracks):

    if (type(tracks) != pd.core.frame.DataFrame):
        print('Input data should be a pd DataFrame')
        return

    h = GetPseudoRapidityTracks(tracks)
    return np.rad2deg(2*np.arctan(np.exp(-h)))
