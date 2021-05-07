import numpy as np
import pandas as pd


def GetTracksWithNTPC(tracks, n=3):
    TPCMask = (
        (np.abs(tracks.T_NumberOfSigmaTPCPion) < 3)
        & (tracks.T_TPCNCls > 50)
        & (tracks.T_TPCRefit == 1)
    )
    return tracks.loc[
        pd.unique(tracks.reset_index().entry)[TPCMask.groupby("entry").sum() >= n]
    ]
