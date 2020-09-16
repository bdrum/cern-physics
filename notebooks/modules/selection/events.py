def GetGoodEventsNumbers(TrackNum=4, ChargeEqualCondition=True, charge=0, WithGoodNTpcTracks=0):
    # get events with 4 good tracks
    GoodEventsNumbers = np.argwhere(select.sum() == TrackNum).flatten()
#     GoodEvents = np.argwhere(data['T_ITSNCls'].counts==TrackNum).flatten() # get events with 4 good tracks

    # get number of events with more than 'WithGoodNTpcTracks' tracks that satisfied 'selectTpc' criteria
    GoodEventsTpcNumbers = np.argwhere(
        selectTpc.sum() >= WithGoodNTpcTracks).flatten()

    # add at least n tracks with tpc to selected
    GoodEventsNumbers = np.intersect1d(
        GoodEventsNumbers, GoodEventsTpcNumbers).flatten()

    # get events that have total charge from 4 tracks
    if ChargeEqualCondition:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(data['T_Q'][select][GoodEventsNumbers].sum(
        ) == charge).flatten()].flatten()  # get good events witch total charge zero
    else:
        GoodEventsNumbers = GoodEventsNumbers[np.argwhere(data['T_Q'][select][GoodEventsNumbers].sum(
        ) != charge).flatten()].flatten()  # get good events witch total charge non zero

    return GoodEventsNumbers
