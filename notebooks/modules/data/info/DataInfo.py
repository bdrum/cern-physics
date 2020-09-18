from modules import tree, events, ps
from modules.data.selection.tracks import selectedTracksMask, selectedTracksWithTpcMask
from modules.physics.kinematics.momentum import GetPtTracks, GetPtEvents
from IPython.display import display, HTML


def DataInfo():
    events.show()

    print()
    print('Tree name:', events.name)
    print('Tree title:', events.title)
    print('Events number:', events.numentries)
    print('Tracks number', tree.nTracks.sum())


def ShowTracksInEvent(n):

    df = events.pandas.df(["T_Q", "T_P[xyz]", "*Cls", "*Refit", "RunNum", "PeriodNumber",
                           "OrbitNumber", "BunchCrossNumber", "T_Dca1", "T_Dca0",
                           "T_NumberOfSigmaTPCPion"], entrystart=n, entrystop=n+1)

    df.insert(0, "Selected", selectedTracksMask[n])
    pt = GetPtTracks(selectedTracksMask+True, n).flatten()
    df.insert(5, "T_Pt", pt)
    pte = GetPtEvents(selectedTracksMask, n)
    df.insert(6, 'E_Pt4Selected', pte)

    display(df)
    # if AllTracksInEvent:
    #     display(df)
    # else:
    #     display(df[df['Selected']])


# GoodEvents = GetGoodEvents(WithGoodNTpcTracks=0)
# print("Selected events list: \n", GoodEvents, len(GoodEvents))
# n = 27  # 16385
# ShowTracks(n, AllTracksInEvent=True)
