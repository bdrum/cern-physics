from modules import data, events


def DataInfo():
    events.show()

    print()
    print('Tree name:', events.name)
    print('Tree title:', events.title)
    print('Events number:', events.numentries)
    print('Tracks number', data['nTracks'].sum())
