import collections
# from modules.data.selection import GetITSnTPCTracksDF
from modules import np, pd
import math
import json
from collections import ChainMap


def GetCrossSection(runs, tracks):

    runsEventsN = dict(collections.Counter(runs[np.unique(
        tracks.reset_index().entry.to_numpy())]))

    runsEventsNOrig = dict(collections.Counter(runs))

    runsLumi = {}

    with open('runsLumi.json') as json_file:
        data = json.load(json_file)
        for k, v in data.items():
            runsLumi[int(k)] = v

    # runsSigm = {}
    runsNFTEvents = {}
    runsNOrigEvents = {}
    runsLumis = {}
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

    return pd.DataFrame(df_base, columns=['run', 'nEvOrig', 'nEvFT', 'Lumi'])

# def ShowCrossSection():
#     fig = plt.figure(figsize=(50, 7))
#     fig.suptitle("Cross Section")
#     ax = fig.add_subplot()
#     bins = list(runsSigm.keys())
#     cnts = list(runsSigm.values())

#     x = np.arange(len(bins))
#     width = 0.15
#     ax.errorbar(x - width/2, cnts, yerr=errs.values(), fmt='.')
#     _ = ax.set_xticks(x)
#     _ = ax.set_xticklabels(
#         bins, rotation=90, rotation_mode="anchor", ha="right", fontsize=12)
