from modules import plt, hep
from matplotlib.patches import Rectangle


def ShowComparisonSame(title, arrs, xlabel, labels, colors, nBins=100, ranges=(0, 1), showPatch=False):

    l = len(arrs)

    if type(colors) != list:
        colors = ['black']*l

    plt.style.use(hep.style.ROOT)
    fig = plt.figure(figsize=(20, 10))
    fig.suptitle(title, fontsize=32)

    ax = fig.add_subplot()

    for i in range(l):
        ax.hist(arrs[i], bins=nBins, range=ranges,
                color=colors[i], histtype='step', linewidth=2, label=labels[i]+f' | {(arrs[i] < 0.15).sum()}')
        ax.legend(prop={'size': 24})

        ax.set_xlabel(xlabel)

    if (showPatch):
        ax.add_patch(Rectangle((0, 0.15), 0.15, 900,
                               fc='lightgrey', alpha=0.4))
        ax.text(0.15, 0, "0.15", size=14)

    return fig
