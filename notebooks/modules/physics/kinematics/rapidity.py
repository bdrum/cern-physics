from modules import tree, np, plt, hep, events, pd
from modules.physics.kinematics.momentum import GetPTracks, GetPEvents


def GetPseudoRapidity(tracks):
    return 0.5*np.log((np.sqrt(tracks.T_Px**2 + tracks.T_Py**2 + tracks.T_Pz**2) + tracks.T_Pz) / (np.sqrt(tracks.T_Px**2 + tracks.T_Py**2 + tracks.T_Pz**2) - tracks.T_Pz))


def GetTheta(tracksMask, eventsNumbers):
    h = GetPseudoRapidity(tracksMask, eventsNumbers)
    theta = 2*np.arctan(np.exp(-h))
    return theta
