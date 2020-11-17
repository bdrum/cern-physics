import collections
from modules.data.selection import GetITSnTPCTracksDF
from modules import events, np, plt
import math

runs = events.arrays(filter_name=['RunNum'], library='np')
ITSnTPCTracks = GetITSnTPCTracksDF(2)

runsEventsN = dict(collections.Counter(runs['RunNum'][np.unique(
    ITSnTPCTracks.reset_index().entry.to_numpy())]))

runs = dict(collections.Counter(runs['RunNum']))

runsLumi = {245145: 0.00143561, 245146: 0.00185012, 245151: 0.000161428,
            245152: 0.000183958, 245231: 0.000601497, 245232: 0.00103705, 245259: 0.000671727, 245345: 0.00777972, 245346: 0.00112074, 245347: 0.00580103, 245349: 0.00637507, 245353: 0.0129164, 245396: 0.00664161, 245397: 0.00713241, 245401: 0.00532924, 245407: 0.0168011, 245409: 0.0106843, 245410: 0.00335777, 245411: 0.0114888, 245441: 0.0071709, 245446: 0.000961314, 245450: 0.00209729, 245453: 0.00852385, 245454: 0.00319568, 245496: 0.00363011, 245497: 0.00742088, 245501: 0.00838291, 245504: 0.00556242, 245505: 0.00297038, 245507: 0.017919, 245540: 0.00330076, 245542: 0.00537795, 245543: 0.0119373, 245544: 0.000813985, 245545: 0.000819252, 245554: 0.0151783, 245683: 0.0103142, 245692: 0.007851, 245700: 0.00532454, 245702: 0.000949905, 245705: 0.00306468, 245775: 0.0145149, 245793: 0.00851174, 245829: 0.004749, 245831: 0.00690171, 245833: 0.00154217, 245923: 0.000582541, 245949: 0.00228008, 245952: 0.0133074, 245954: 0.010132, 245963: 0.0168748, 246001: 0.00873539, 246003: 0.00243163, 246012: 0.00368357, 246036: 0.000486882, 246037: 0.00256427, 246042: 0.00797101, 246048: 0.000849203, 246049: 0.00857329, 246052: 0.0005597, 246053: 0.00641678, 246087: 0.0281748,
            246089: 0.00108955, 246113: 0.00279161, 246115: 0.000783701, 246148: 0.0110441, 246151: 0.00620155, 246152: 0.00139748, 246153: 0.0133546, 246178: 0.00198469, 246180: 0.00448056, 246181: 0.00605391, 246182: 0.00644536, 246185: 0.000722027, 246217: 0.00794375, 246222: 0.00835456, 246225: 0.00430062, 246271: 0.00435355, 246272: 0.0114395, 246275: 0.00414386, 246276: 0.00225688, 246424: 0.00530442, 246428: 0.000437864, 246431: 0.00354339, 246434: 0.00753543, 246487: 0.00159426, 246488: 0.01435, 246493: 0.00460677, 246495: 0.00139649, 246675: 0.00766105, 246676: 0.00208353, 246750: 0.00388996, 246751: 0.00349452, 246757: 0.00119711, 246758: 0.00389657, 246759: 0.000339959, 246760: 0.003794, 246763: 0.00222457, 246765: 0.00125743, 246766: 0.000487837, 246804: 0.00221243, 246805: 0.0053587, 246807: 0.00549894, 246808: 0.00031606, 246809: 0.00784271, 246810: 0.00132936, 246844: 0.00261074, 246845: 0.00407461, 246846: 0.00241765, 246847: 0.00586984, 246851: 0.004099, 246864: 0.00709652, 246865: 0.00408179, 246867: 0.00795038, 246871: 0.00813839, 246928: 0.000519657, 246945: 0.00654527, 246948: 0.00289259, 246980: 0.0222057, 246982: 0.00123336, 246984: 0.0148896, 246989: 0.0216071, 246991: 0.00322292, 246994: 0.0123821}

runsSigm = {}
runsLumis = {}
errs = {}

ac = 1000

for k, v in runsLumi.items():
    if k in runsEventsN.keys():
        runsSigm[k] = runsEventsN[k]/(v*ac)
        runsLumis[k] = (v*ac)
        errs[k] = math.sqrt(runsEventsN[k])


def ShowCrossSection():
    fig = plt.figure(figsize=(50, 7))
    fig.suptitle("Cross Section")
    ax = fig.add_subplot()
    bins = list(runsSigm.keys())
    cnts = list(runsSigm.values())

    x = np.arange(len(bins))
    width = 0.15
    ax.errorbar(x - width/2, cnts, yerr=errs.values(), fmt='.')
    _ = ax.set_xticks(x)
    _ = ax.set_xticklabels(
        bins, rotation=90, rotation_mode="anchor", ha="right", fontsize=12)
