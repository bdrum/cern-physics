# let's form fired FORs numbers for 4 tracks zq EVENT
for_sensors = pd.DataFrame(
    ft.orig_events.FORChip.loc[ft.four_tracks_zq.reset_index().entry]
)
for_sensors["subentry"] = for_sensors.groupby(level=0).cumcount()
for_sensors.index.name = "entry"
for_sensors.set_index("subentry", append=True, inplace=True)

# form arrays of numbers of sensor that linked with TRACKS
df = ft.four_tracks_zq[["T_ITSModuleInner", "T_ITSModuleOuter"]] // 1000000

# combine into one dataframe
df["T_ITSSensorNum"] = for_sensors
df = df.reset_index()

# check that sensor linked with track will provide trigger (match with FOR sensor)
df["Inner_matched"] = (
    abs(abs(df.T_ITSModuleInner * 5 - df.T_ITSSensorNum) - 2).apply(lambda x: x <= 2)
) * df.T_ITSSensorNum.apply(lambda x: x < 400)

df["Outer_matched"] = (
    abs(abs(df.T_ITSModuleOuter * 5 - df.T_ITSSensorNum) - 2).apply(lambda x: x <= 2)
) * df.T_ITSSensorNum.apply(lambda x: x >= 400)
df["vPhiInner"] = np.nan
df.vPhiInner = df.vPhiInner.astype("object")
df["vPhiOuter"] = np.nan
df.vPhiOuter = df.vPhiOuter.astype("object")

df["vPhiInnerValue"] = np.nan
df.vPhiInnerValue = df.vPhiInnerValue.astype("object")
df["vPhiOuterValue"] = np.nan
df.vPhiOuterValue = df.vPhiOuterValue.astype("object")

for i in tqdm(range(len(df))):
    vPhiInner1 = np.zeros(20, dtype=bool)
    vPhiOuter1 = np.zeros(40, dtype=bool)

    vPhiInnerValues = pd.unique(df.T_ITSSensorNum[i][df.Inner_matched[i]] // 20)
    vPhiOuterValues = pd.unique((df.T_ITSSensorNum[i][df.Outer_matched[i]] - 400) // 20)

    vPhiInner1[vPhiInnerValues] = True
    df.vPhiInner[i] = vPhiInner1

    vPhiOuter1[vPhiOuterValues] = True
    df.vPhiOuter[i] = vPhiOuter1

    df.vPhiInnerValue[i] = vPhiInnerValues
    df.vPhiOuterValue[i] = vPhiOuterValues

df_dbg = df.copy()

# take only matched tracks and fill vPhi arrays for inner and outer
# df = df[(df.Inner_matched.apply(any) | df.Outer_matched.apply(any))][['entry', 'vPhiInner', 'vPhiOuter']].groupby('entry').sum()
df = df[["entry", "vPhiInner", "vPhiOuter"]].groupby("entry").sum()

df["triggered"] = False

# check incorrect topology

for t in tqdm(df.index):
    for i in range(10):
        for j in range(2):
            k = 2 * i + j
            if (
                (df.vPhiOuter[t][k] or df.vPhiOuter[t][k + 1] or df.vPhiOuter[t][k + 2])
                and (
                    df.vPhiOuter[t][k + 20]
                    or df.vPhiOuter[t][(k + 21) % 40]
                    or df.vPhiOuter[t][(k + 22) % 40]
                )
                and (df.vPhiInner[t][i] or df.vPhiInner[t][i + 1])
                and (df.vPhiInner[t][i + 10] or df.vPhiInner[t][(i + 11) % 20])
            ):
                df.at[t, "triggered"] = True

triggered_events = df.index[df.triggered]
untriggered_events = df.index[~df.triggered]

ft_zq_Pt_nTpc_triggered = []
ft_zq_Pt_nTpc_UNtriggered = []

ft_nzq_Pt_nTpc_triggered = []
ft_nzq_Pt_nTpc_UNtriggered = []

for i in range(5):
    ft_zq_Pt_nTpc_triggered.append(
        ft_zq_Pt_nTpc[i][
            np.intersect1d(ft_zq_Pt_nTpc[i].index.values, triggered_events.values)
        ]
    )
    ft_zq_Pt_nTpc_UNtriggered.append(
        ft_zq_Pt_nTpc[i][
            np.intersect1d(ft_zq_Pt_nTpc[i].index.values, untriggered_events.values)
        ]
    )
