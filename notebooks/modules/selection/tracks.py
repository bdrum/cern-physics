from modules import data, np

selectedTracksMask = data['T_ITSRefit']  # + True

selectedTracksWithTpcMask = data['T_TPCRefit'] * \
    (data['T_TPCNCls'] > 50) * (np.abs(data['T_NumberOfSigmaTPCPion']) < 3)
