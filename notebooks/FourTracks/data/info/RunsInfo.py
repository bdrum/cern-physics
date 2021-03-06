from modules import tree, plt, np, hep


def ShowRunsInfo():
    runs = tree.RunNum  # [GoodEvents]

    counts = plt.hist(runs, bins=len(np.unique(runs)))

    bins = []
    counts = []

    for run in np.unique(runs):
        bins.append(run)
        counts.append((runs == run).sum())
        print(run, (runs == run).sum())

    plt.style. use(hep.style.ROOT)
    fig = plt.figure(figsize=(15, 7))
    ax = fig.add_axes([0, 0, 1, 1])
    fig.suptitle('4pr events by run', fontsize=32)
    ax.bar(bins, counts, width=5)
    ax.set_xticks(bins)
    ax.set_xticklabels(bins, rotation=90, rotation_mode="anchor", ha="right")
    plt.show()
