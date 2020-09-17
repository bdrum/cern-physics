from modules import tree, np

selectedTracksMask = tree.T_ITSRefit  # + True

selectedTracksWithTpcMask = tree.T_TPCRefit * \
    (tree.T_TPCNCls > 50) * (np.abs(tree.T_NumberOfSigmaTPCPion) < 3)
