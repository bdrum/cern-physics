from FourTracks.analysis.kinematics import pt_events
import pandas as pd


def GetTracksWithPtCut(
    tracks: pd.DataFrame, maxPt: float = 0.15, minPt: float = 0
) -> pd.Series:
    pt = pt_events(tracks)
    return tracks.loc[pt[(pt < maxPt) & (pt >= minPt)].reset_index().entry]
