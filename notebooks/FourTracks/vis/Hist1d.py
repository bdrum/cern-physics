from modules import tree, np, plt, hep, events


def Draw(inpArray, title='', nBins='auto', xMin=0, xMax=0, figSize=(15, 7), xLabel='', yLabel=''):
    if xMin == xMax:
        xMin = inpArray.min()
        xMax = inpArray.max()
    counts, bins = np.histogram(inpArray, bins=nBins, range=(xMin, xMax))
    fig = plt.figure(figsize=figSize)
    ax = fig.add_axes([0, 0, 1, 1])
    fig.suptitle(title, fontsize=16)
    plt.style.use(hep.style.ROOT)
    ax.hist(inpArray, bins=bins, histtype='step', color='black',
            label=f'Entries {np.sum(counts)}')
    plt.xlabel(xLabel)
    plt.ylabel(yLabel)
    ax.legend()


def DrawComparison()
