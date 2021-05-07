from matplotlib import pyplot as plt


def HistsVertComparison(arrays, labels, bins, ranges, title='', figszs=(15, 7)):
    """
    Function allows to compare histograms in vertical mode with specific line for convenient view.
    """

    fig, axs = plt.subplots(len(arrays), figsize=fgiszs, sharex=True)

    fig.suptitle(title, fontsize=32)
    for i in range(len(arrays)):
    axs[i].hist(ptITSOnly, bins=bins, range=ranges,
                color='black', histtype='step', label=labels[i])
