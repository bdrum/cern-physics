import numpy as np
import pandas as pd

from os import name as os_name

"""
The module upload data from files to DataFrames.
"""

tracks_path = r"D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oTracks.parquet"
events_path = r"D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oEvents.parquet"

if os_name == "posix":
    tracks_path = r"/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/4Prongs2015oTracks.parquet"
    events_path = r"/mnt/d/GoogleDrive/Job/cern/Alice/analysis/data/RhoPrime/2015/4Prongs2015oEvents.parquet"

orig_events = pd.read_parquet(events_path)
orig_tracks = pd.read_parquet(tracks_path)

# 4 tracks events mask
# NOTE: may be it's not obviously, but dataframe able to work with mask only in case mask cover whole dataframe.
# This means I have to find events with four tracks in all events, than events with zero total charge again in all events, and than put the zero charge mask  on the 4tracks mask.
# In this case e.g. we have 6 tracks in events (four_track_mask is false), but total charge is zero (zq_mask is true).
# Such event will threw out because of four_track_mask is false, but it could be a useful event.

_four_tracks_mask = orig_tracks.groupby("entry").count() == 4

# zero total charge mask for 4 tracks events
_four_tracks_zq_mask = _four_tracks_mask[orig_tracks.groupby("entry").sum().T_Q == 0]

# non zero total charge mask for 4 tracks events
_four_tracks_nzq_mask = _four_tracks_mask[orig_tracks.groupby("entry").sum().T_Q != 0]

# Returns only events with four tracks without any additional conditions
four_tracks = orig_tracks[_four_tracks_mask].dropna(how="any")

# Returns only events with four tracks and zero total charge
four_tracks_zq = four_tracks[_four_tracks_zq_mask].dropna(how="any")

# Returns only events with four tracks and non zero total charge
four_tracks_nzq = four_tracks[_four_tracks_nzq_mask].dropna(how="any")

del _four_tracks_mask
del _four_tracks_zq_mask
del _four_tracks_nzq_mask
