from modules import dfs, events


def DataInfo():
    events.show()

    print()
    print('Tree name:', events.name)
    print('Tree title:', events.title)
    print('Events number:', dfs.reset_index().entry.max())
    print('Tracks number', len(dfs))
