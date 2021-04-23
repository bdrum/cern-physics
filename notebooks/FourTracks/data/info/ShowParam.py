from modules import tree, np, plt, hep


def ShowParamHist(param, nBins, interv):
    treeParam = tree._asdict()[param].flatten()  # tracks

    counts, bins = np.histogram(treeParam, bins=nBins, range=interv)
    plt.style.use(hep.style.ROOT)
    _ = plt.hist(treeParam, bins=bins, histtype='step',
                 color='black', label=f'{param};Entries {np.sum(counts)}')
