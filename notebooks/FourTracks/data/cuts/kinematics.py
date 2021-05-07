from FourTracks.analysis.kinematics import pt_events


def GetTracksWithPtCut(tracks, maxPt=0.15, minPt=0):
    pt = pt_events(tracks)
    return tracks.loc[pt[(pt < maxPt) & (pt >= minPt)].reset_index().entry]
