from modules import tree, np, plt, hep, events
from modules.physics.kinematics.momentum import GetPTracks, GetPEvents


def GetPseudoRapidity(tracksMask, eventsNumbers):
    pz = tree.T_Pz[tracksMask][eventsNumbers]
    pAbs = np.abs(GetPTracks(tracksMask, eventsNumbers))
    tempH = (pAbs + pz)/(pAbs-pz)
    h = 0.5*np.log(tempH)
    return h


def GetTheta(tracksMask, eventsNumbers):
    h = GetPseudoRapidity(tracksMask, eventsNumbers)
    theta = 2*np.arctan(np.exp(-h))
    return theta
