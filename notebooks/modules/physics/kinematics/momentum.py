from modules import tree, np, plt, hep, events


def GetPtTracks(tracksMask, eventsNumbers):

    pxg = tree.T_Px[tracksMask][eventsNumbers]
    pyg = tree.T_Py[tracksMask][eventsNumbers]

    pt = np.sqrt(pxg**2 + pyg**2)

    return pt


def GetPTracks(tracksMask, eventsNumbers):

    pxg = tree.T_Px[tracksMask][eventsNumbers]
    pyg = tree.T_Py[tracksMask][eventsNumbers]
    pzg = tree.T_Pz[tracksMask][eventsNumbers]

    p = np.sqrt(pxg**2 + pyg**2 + pzg**2)

    return p


def GetPtEvents(tracksMask, eventsNumbers):

    pxg = tree.T_Px[tracksMask][eventsNumbers]
    pyg = tree.T_Py[tracksMask][eventsNumbers]

    pt = np.sqrt(pxg.sum()**2 + pyg.sum()**2)

    return pt


def GetPEvents(tracksMask, eventsNumbers):

    pxg = tree.T_Px[tracksMask][eventsNumbers]
    pyg = tree.T_Py[tracksMask][eventsNumbers]
    pzg = tree.T_Pz[tracksMask][eventsNumbers]

    p = np.sqrt(pxg.sum()**2 + pyg.sum()**2 + pzg.sum()**2)

    return p
