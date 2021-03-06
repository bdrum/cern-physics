import collections
import numpy as np
import pandas as pd
import math
import json
from collections import ChainMap


def GetCrossSection(runs: pd.Series, tracks: pd.DataFrame) -> pd.DataFrame:

    runsEventsN = dict(
        collections.Counter(runs[np.unique(tracks.reset_index().entry.to_numpy())])
    )

    runsEventsNOrig = dict(collections.Counter(runs))

    runsLumi = {}

    with open("runsLumi.json") as json_file:
        data = json.load(json_file)
        for k, v in data.items():
            runsLumi[int(k)] = v

    # runsSigm = {}
    # runsNFTEvents = {}
    # runsNOrigEvents = {}
    # runsLumis = {}
    # errs = {}

    df_base = []

    for k, v in runsLumi.items():
        if k in runsEventsN.keys():
            df_base.append((k, runsEventsNOrig[k], runsEventsN[k], v))
            # runsLumis[k] = v
            # runsSigm[k] = runsEventsN[k]/runsLumis[k]
            # runsNFTEvents[k] = runsEventsN[k]
            # runsNOrigEvents[k] = runsEventsNOrig[k]
            # errs[k] = math.sqrt(runsEventsN[k])

    return pd.DataFrame(df_base, columns=["run", "nEvOrig", "nEvFT", "Lumi"])
