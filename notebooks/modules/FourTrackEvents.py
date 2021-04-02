import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from matplotlib.patches import Rectangle

from functools import cached_property
from os import name as os_name
from tqdm import tqdm
from particle import Particle


if os_name == 'posix':
    import ROOT
    from array import array

Rho0 = Particle.from_pdgid(113)
Pi0 = Particle.from_pdgid(111)
PiPlus = Particle.from_pdgid(211)


class FourTrackEvents:
    def __init__(self):

        tracks_path = r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oTracks.parquet'
        events_path = r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oEvents.parquet'

        if os_name == 'posix':
            tracks_path = r'/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/4Prongs2015oTracks.parquet'
            events_path = r'/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/4Prongs2015oEvents.parquet'

        self.orig_events = pd.read_parquet(events_path)
        self.orig_tracks = pd.read_parquet(tracks_path)

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

        # self.four_tracks_zq = self.orig_tracks[self._four_tracks_zq_mask].dropna(
        #     how='any')
        # self.four_tracks_nzq = self.orig_tracks[self._four_tracks_nzq_mask].dropna(
        #     how='any')

    @ cached_property
    def four_tracks(self):
        """
        Returns only events with four tracks without any additional conditions
        """
        return self.orig_tracks[self._four_tracks_mask].dropna(how='any')

    @ cached_property
    def four_tracks_zq(self):
        """
        Returns only events with four tracks and zero total charge
        """
        return self.orig_tracks[self._four_tracks_zq_mask].dropna(
            how='any')

    @ cached_property
    def four_tracks_nzq(self):
        """
        Returns only events with four tracks and non zero total charge
        """
        return self.orig_tracks[self._four_tracks_nzq_mask].dropna(
            how='any')

    @ cached_property
    def ft_zq_nTPC(self):
        """
        Returns list of the list of zero total charge four tracks events
        where index of main list correspondes to number of TPC tracks
        """
        _ft_zq_nTPC = []
        for i in range(5):
            _ft_zq_nTPC.append(self.GetTracksWithNTPC(self.four_tracks_zq, i))
        return _ft_zq_nTPC

    @ cached_property
    def ft_nzq_nTPC(self):
        """
        Returns list of the list of non zero total charge four tracks events
        where index of main list correspondes to number of TPC tracks
        """
        _ft_nzq_nTPC = []
        for i in range(5):
            _ft_nzq_nTPC.append(
                self.GetTracksWithNTPC(self.four_tracks_nzq, i))
        return _ft_nzq_nTPC

    @ staticmethod
    def GetTracksWithNTPC(tracks, n=3):
        TPCMask = (np.abs(tracks.T_NumberOfSigmaTPCPion) < 3) & (
            tracks.T_TPCNCls > 50) & (tracks.T_TPCRefit == 1)
        return tracks.loc[pd.unique(tracks.reset_index().entry)[
            TPCMask.groupby('entry').sum() >= n]]

    @staticmethod
    def GetTracksWithPtLt(tracks, maxPt=0.15, minPt=0):
        dfsPt = tracks[['T_Px', 'T_Py']]
        dfsPt = np.sqrt(dfsPt.groupby('entry').sum()[
            'T_Px']**2 + dfsPt.groupby('entry').sum()['T_Py']**2)
        return tracks.loc[dfsPt[(dfsPt < maxPt) & (dfsPt >= minPt)].reset_index().entry]
