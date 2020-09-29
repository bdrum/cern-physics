import uproot4
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
import pandas as pd


ccup9_2015 = r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015o.root'

events = uproot4.open(ccup9_2015)['4Prongs/events']
# events.show()
# dfs.loc[0] # get dataframe part with entry = 0

dfs = events.arrays(filter_name=['T_Px', 'T_Py', 'T_Pz',  'T_Q',
                                 'T_NumberOfSigmaTPCPion', 'T_TPCRefit', 'T_TPCNCls'], library='pd')
