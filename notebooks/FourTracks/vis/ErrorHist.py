from FourTracks import pd, np, plt, hep


def DrawErrorHist(data: list, b: int, range: tuple, title: str, x_label: str):
    plt.style.use(hep.style.ROOT)
    fig = plt.figure()
    ax = fig.add_subplot()

    fig.suptitle(title)
    counts, bin_edges = np.histogram(total_heavy_pairs_masses, bins=b, range=r)


hep.histplot(
    (counts, bin_edges),
    yerr=True,
    color="black",
    histtype="errorbar",
    label="4tr_zq_all_cuts",
)

val = (r[1] - r[0]) * 1000 // b
ax.set_xlabel("$M, GeV$")
ax.set_ylabel(f"#events / {val}MeV")

mass_nzq = mass_events(kinematics.GetTracksWithPtCut(data.four_tracks_nzq))
counts_bckg, bin_edges_bckg = np.histogram(total_light_pairs_masses, bins=b, range=r)
hep.histplot(
    (counts_bckg, bin_edges_bckg),
    yerr=True,
    color="red",
    histtype="errorbar",
    label="4tr_nzq_pt_cut",
)
_ = plt.legend()

pd.DataFrame(
    [mass_after_all_cuts.describe(), mass_nzq.describe()],
    index=["mass_ft_zq", "mass_ft_nzq"],
)

