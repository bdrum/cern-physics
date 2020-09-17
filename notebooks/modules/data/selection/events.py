from modules import tree, np
from modules.data.selection.tracks import selectedTracksMask, selectedTracksWithTpcMask


def GetGoodEventsNumbers(TrackNum=4, ChargeEqualCondition=True, charge=0, WithGoodNTpcTracks=0):
    # get events with 4 good tracks
    # TODO: why I can't see four good track in events with more than 4 tracks?!
    GoodEventsNumbers = np.argwhere(
        selectedTracksMask.sum() == TrackNum).flatten()
#     GoodEvents = np.argwhere(tree.T_ITSNCls.counts==TrackNum).flatten() # get events with 4 good tracks

    # get number of events with more than 'WithGoodNTpcTracks' tracks that satisfied 'selectTpc' criteria
    GoodEventsTpcNumbers = np.argwhere(
        selectedTracksWithTpcMask.sum() >= WithGoodNTpcTracks).flatten()

    # add at least n tracks with tpc to selected
    GoodEventsNumbers = np.intersect1d(
        GoodEventsNumbers, GoodEventsTpcNumbers).flatten()

    # get events that have total charge from 4 tracks
    if ChargeEqualCondition:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(tree.T_Q[selectedTracksMask][GoodEventsNumbers].sum(
        ) == charge).flatten()].flatten()  # get good events witch total charge zero
    else:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(tree.T_Q[selectedTracksMask][GoodEventsNumbers].sum(
        ) != charge).flatten()].flatten()  # get good events witch total charge non zero

    return GoodEventsNumbers
