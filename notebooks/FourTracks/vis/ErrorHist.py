from FourTracks import pd, np, plt, hep


def DrawErrorHist(
    data: list,
    bins: int,
    range: tuple,
    title: str,
    x_label: str,
    y_label: str,
    showBinWidth: bool = True,
    MeV: bool = True,
    **histplot_kwargs,
) -> pd.DataFrame:
    """
    Function draws histogram list with errors bars.
    """

    plt.style.use(hep.style.ROOT)
    fig = plt.figure()
    ax = fig.add_subplot()
    fig.suptitle(title)

    val = (range[1] - range[0]) / bins

    hep.histplot(
        [np.histogram(d, bins=bins, range=range) for d in data],
        yerr=True,
        xerr=[0, val/2][showBinWidth],
        **histplot_kwargs,
    )

    ax.set_xlabel(x_label)
    ylabel = y_label
    if showBinWidth:
        ylabel = (
            ylabel + " per " + f"{[1,1000][MeV] * val:.0f} {['GeV/c','MeV/c'][MeV]}"
        )
    ax.set_ylabel(ylabel)

    _ = plt.legend()
    return pd.DataFrame(
        map(pd.DataFrame.describe, data), index=histplot_kwargs["label"]
    )
