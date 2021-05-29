from matplotlib.pyplot import xlabel
from FourTracks import pd, np, plt, hep
from typing import Sized, Union


def DrawErrorHists(
    data: list,
    bins: int,
    range: tuple,
    title: str,
    label: list,
    x_label: list,
    y_label: list,
    color: list,
    showBinWidth: bool = True,
) -> pd.DataFrame:
    """
    """

    # if (
    #     pd.DataFrame([data, label, x_label, y_label, color]).count(axis=1).nunique()
    #     != 1
    # ):
    #     raise IndexError("Input lists have different sizes")

    plt.style.use(hep.style.ROOT)
    fig = plt.figure()
    ax = fig.add_subplot()
    fig.suptitle(title)

    for i in np.arange(len(data)):
        hep.histplot(
            np.histogram(data[i], bins=bins, range=range),
            yerr=True,
            color=color[i],
            histtype="errorbar",
            label=label[i],
        )

        val = (range[1] - range[0]) * 1000 // bins
        ax.set_xlabel(x_label[i])
        ylabel = y_label[i]
        if showBinWidth:
            ylabel = ylabel + "/" + f"{val}MeV"
        ax.set_ylabel(ylabel)

    _ = plt.legend()
    return pd.DataFrame(map(pd.DataFrame.describe, data), index=label)


def DrawErrorHist(
    data: Union[list, pd.Series, np.ndarray],
    bins: int,
    range: tuple,
    title: str,
    label: str,
    x_label: str,
    y_label: str,
    color: str,
    showBinWidth: bool = True,
):
    return DrawErrorHists(
        [data],
        bins=bins,
        range=range,
        title=title,
        label=[label],
        x_label=[x_label],
        y_label=[y_label],
        color=[color],
        showBinWidth=showBinWidth,
    )

