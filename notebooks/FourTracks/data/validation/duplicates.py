import math
from modules import tree, np, plt, hep
from modules.data.selection.tracks import selectedTracksMask


def ShowDifferencesFor3Params(param1, param2, param3):
    differences = []
    # GoodEvents = GetGoodEvents(TrackNum=4, WithGoodNTpcTracks=0)
    # GoodEvents = GetUniqueGoodEvents()
    entries = len(tree._asdict()[param1][selectedTracksMask])
    ddpx = tree._asdict()[param1][selectedTracksMask]
    ddpy = tree._asdict()[param2][selectedTracksMask]
    ddpz = tree._asdict()[param3][selectedTracksMask]
    for event in range(entries):
        dpx = ddpx[event]
        dpy = ddpx[event]
        dpz = ddpx[event]
        N = len(dpx)
        for n in range(N):
            for j in range(n+1, N):

                differences.append(
                    math.sqrt((dpx[n]-dpx[j])**2 + (dpy[n]-dpy[j])**2 + (dpz[n]-dpz[j])**2))

    counts, bins = np.histogram(differences, bins=100, range=(0, 0.2))
    plt.style.use(hep.style.ROOT)
    _ = plt.hist(differences, bins=bins, histtype='step', color='black')


def ShowDifferencesFor2Params(param1, param2):
    differences = []
    # GoodEvents = GetGoodEvents(TrackNum=4, WithGoodNTpcTracks=0)
    # GoodEvents = GetUniqueGoodEvents()
    entries = len(tree._asdict()[param1][selectedTracksMask])
    dca0 = tree._asdict()[param1][selectedTracksMask]
    dca1 = tree._asdict()[param2][selectedTracksMask]
    for event in range(entries):
        ddca0 = dca0[event]
        ddca1 = dca1[event]
        N = len(ddca0)
        for n in range(N):
            for j in range(n+1, N):
                differences.append(
                    math.sqrt((ddca0[n]-ddca0[j])**2 + (ddca1[n]-ddca1[j])**2))

    counts, bins = np.histogram(differences, bins=100, range=(0, 0.02))
    plt.style.use(hep.style.ROOT)
    _ = plt.hist(differences, bins=bins, histtype='step', color='black')
