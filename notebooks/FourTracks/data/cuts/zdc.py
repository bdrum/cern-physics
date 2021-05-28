import numpy as np
import pandas as pd
from FourTracks import data


def GetTracksWithZDCCut(
    tracks: pd.DataFrame,
    ZDC_En: float = 5000,
    ZDC_Time_Delta: float = 100,
    passed: bool = True,
) -> pd.Series:
    """
    Here is the function that returns only events from given tracks grouped by events that passed or not passed ZDC criteria for one side A or C depends on given parameter 'passed'.
    Event will pass in case such criteria are satisfied:
    - neutrons energy less or equal than given parameter ZDC_En value
    - or
    - one of ZDC times not in an interval of +- ZDC_Time_Delta parameter value 
    """
    zdc_a_unpassed_events = (data.orig_events.ZNAenergy > ZDC_En) & (
        np.abs(
            data.orig_events[["ZDCAtime_0", "ZDCAtime_1", "ZDCAtime_2", "ZDCAtime_3"]]
        )
        <= ZDC_Time_Delta
    ).any(axis=1)
    zdc_c_unpassed_events = (data.orig_events.ZNCenergy > ZDC_En) & (
        np.abs(
            data.orig_events[["ZDCCtime_0", "ZDCCtime_1", "ZDCCtime_2", "ZDCCtime_3"]]
        )
        <= ZDC_Time_Delta
    ).any(axis=1)

    zdc_events = ~(zdc_a_unpassed_events | zdc_c_unpassed_events)
    if not passed:
        zdc_events = ~zdc_events

    return tracks.loc[zdc_events[zdc_events].index]
