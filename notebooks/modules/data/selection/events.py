from modules import tree, np
from modules.data.selection.tracks import selectedTracksMask, selectedTracksWithTpcMask


def Get4TracksEventsNumbers(tracksMask, TrackNum=4, ChargeEqualityCondition=True, TotalCharge=0, WithGoodNTpcTracks=0, TPCStrictCriteria=False):
    # get events with 4 good tracks
    # TODO: why I can't see four good track in events with more than 4 tracks?!
    GoodEventsNumbers = np.argwhere(np.sum(tracksMask, axis=1) == 4).flatten()

    # get number of events with more than 'WithGoodNTpcTracks' tracks that satisfied 'selectTpc' criteria
    if not TPCStrictCriteria:
        GoodEventsTpcNumbers = np.argwhere(
            np.sum(selectedTracksWithTpcMask, axis=1) >= WithGoodNTpcTracks).flatten()
    else:
        GoodEventsTpcNumbers = np.argwhere(
            np.sum(selectedTracksWithTpcMask, axis=1) == WithGoodNTpcTracks).flatten()

    # # add at least n tracks with tpc to selected
    GoodEventsNumbers = np.intersect1d(
        GoodEventsNumbers, GoodEventsTpcNumbers).flatten()

    # get events that have total charge from 4 tracks
    if ChargeEqualityCondition:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(np.sum(
            tree.T_Q[tracksMask][GoodEventsNumbers], axis=1) == TotalCharge).flatten()].flatten()  # get good events witch total charge zero
    else:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(np.sum(tree.T_Q[tracksMask][GoodEventsNumbers], axis=1) == TotalCharge).flatten(
        )].flatten()  # get good events witch total charge non zero

    return GoodEventsNumbers
