from modules import tree, np, plt, hep
from modules.data.selection.events import GetGoodEventsNumbers
from modules.data.selection.tracks import selectedTracksMask


def GetPt(tracksMask, eventsNumbers, Draw=True, ChargeEqualCondition=True):

    pxg = tree.T_Px[tracksMask][eventsNumbers]
    pyg = tree.T_Py[tracksMask][eventsNumbers]

    pt = np.sqrt(pxg.sum()**2 + pyg.sum()**2)

    if Draw:
        counts, bins = np.histogram(pt, bins=100, range=(0, 2))
        fig = plt.figure(figsize=(15, 7))
        ax = fig.add_axes([0, 0, 1, 1])
        fig.suptitle('CCUP9 4pr Pt q = 0', fontsize=16)
        if ChargeEqualCondition:
            fig.suptitle('CCUP9 4pr Pt q = 0', fontsize=16)
        else:
            fig.suptitle('CCUP9 4pr Pt q != 0', fontsize=16)

        plt.style.use(hep.style.ROOT)
        ax.hist(pt, bins=bins, histtype='step', color='black',
                label=f'Entries {np.sum(counts)}')
        plt.xlabel('Pt, GeV')
        plt.ylabel('# events')
        ax.legend()
    else:
        return pt
