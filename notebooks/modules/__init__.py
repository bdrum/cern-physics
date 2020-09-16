import uproot
import numpy as np
import matplotlib.pyplot as plt
import mplhep as hep
import pandas as ps
import awkward

ccup9_2015_my_test = r"D:\GoogleDrive\Job\cern\Alice\analysis\dev\grid\selection\RhoPrime\macro\AnalysisResults.root"
ccup9_2015 = r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015o.root'
ccup9_2015_train = r'D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oTrain.root'

# mycache = uproot.ArrayCache(1024*1024 * 10)
events = uproot.open(ccup9_2015)['4Prongs/events']
# events.show()
data = events.arrays('*', namedecode="utf-8")
# data = events.lazyarrays('*', namedecode="utf-8")
# print(events.name, events.title, events.numentries, data['nTracks'].sum())
