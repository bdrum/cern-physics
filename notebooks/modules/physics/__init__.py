
from modules import np, pd, Pi0, PiPlus, Rho0
from modules.data import validation
import uproot_methods.classes.TLorentzVector as tlv


class kinematics:
    def __init__(self, tracks):
        validation.IsDataFrame(tracks)
        self.TracksVectors = tlv.TLorentzVectorArray(
            tracks.T_Px, tracks.T_Py, tracks.T_Pz, PiPlus.mass)
        self.EventsVectors = tlv.TLorentzVectorArray(
            tracks.groupby('entry').T_Px.sum(), tracks.groupby('entry').T_Py.sum(), tracks.groupby('entry').T_Pz.sum(), 4*PiPlus.mass)
