import uproot4
import numpy as np
import pandas as pd
from particle import Particle

Rho0 = Particle.from_pdgid(113)
Pi0 = Particle.from_pdgid(111)
PiPlus = Particle.from_pdgid(211)


class FourTrackEvents:
    def __init__(self):
        self.orig_events = pd.read_parquet(
            r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oEvents.parquet')
        self.orig_tracks = pd.read_parquet(
            r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oTracks.parquet')

        # 4 tracks events mask
        # NOTE: may be it's not obviously, but dataframe able to work with mask only in case mask cover whole dataframe.
        # This means I have to find events with four tracks in all events, than events with zero total charge again in all events, and than put the zero charge mask  on the 4tracks mask.
        # In this case e.g. we have 6 tracks in events (four_track_mask is false), but total charge is zero (zq_mask is true).
        # Such event will threw out because of four_track_mask is false, but it could be a useful event.

        self._four_tracks_mask = (
            self.orig_tracks.reset_index().groupby('entry').count() == 4)

        # zero total charge mask for 4 tracks events
        self._four_tracks_zq_mask = self._four_tracks_mask[self.orig_tracks.groupby(
            'entry').sum().T_Q == 0]

        # non zero total charge mask for 4 tracks events
        self._four_tracks_nzq_mask = self._four_tracks_mask[self.orig_tracks.groupby(
            'entry').sum().T_Q != 0]

        self.four_tracks_zq = self.orig_tracks[self._four_tracks_zq_mask].dropna(
            how='any')
        self.four_tracks_nzq = self.orig_tracks[self._four_tracks_nzq_mask].dropna(
            how='any')

    @ property
    def four_tracks(self):
        """
        Returns only events with four tracks without any additional conditions
        """
        return self.orig_tracks[self._four_tracks_mask].dropna(how='any')


    @ staticmethod
    def GetTracksWithNTPC(tracks, n=3):
        TPCMask = (np.abs(tracks.T_NumberOfSigmaTPCPion) < 3) & (
            tracks.T_TPCNCls > 50) & (tracks.T_TPCRefit == 1)
        return tracks.loc[pd.unique(tracks.reset_index().entry)[
            TPCMask.groupby('entry').sum() >= n]]

    @staticmethod
    def GetTracksWithPtLt(tracks, lowPt=0.15):
        dfsPt = tracks[['T_Px', 'T_Py']]
        dfsPt = np.sqrt(dfsPt.groupby('entry').sum()[
            'T_Px']**2 + dfsPt.groupby('entry').sum()['T_Py']**2)
        return tracks.loc[dfsPt[(dfsPt < lowPt)].reset_index().entry]
