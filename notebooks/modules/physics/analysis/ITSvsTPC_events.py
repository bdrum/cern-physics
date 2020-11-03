from modules import plt, hep
from matplotlib.patches import Rectangle


def ShowComparisonSame(title, arrs, xlabel, labels, colors, nBins=100, ranges=(0, 1)):

    l = len(arrs)

    if type(colors) != list:
        colors = ['black']*l

    plt.style.use(hep.style.ROOT)
    fig = plt.figure(figsize=(15, 7))
    fig.suptitle(title, fontsize=32)

    ax = fig.add_subplot()

    for i in range(l):
        ax.hist(arrs[i], bins=nBins, range=ranges,
                color=colors[i], histtype='step', linewidth=2, label=labels[i]+f' | {(arrs[i] < 0.15).sum()}')
        ax.legend(prop={'size': 10})

    ax.set_xlabel(xlabel)
    # ax.add_patch(Rectangle((0, 0.15), 0.15, 900, fc='lightgrey', alpha=0.4))
