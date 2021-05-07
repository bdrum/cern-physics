import uproot4
import numpy as np
import pandas as pd
import concurrent.futures

# TODO: not a method! (still specific script)


def convert_root_file_to_parquet(root_path, tree_name, branches, parq_path):

    ccup9_2015_file = r"D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015o_withZDCTimes.root"

    tree_name = "4Prongs/events"

    executor = concurrent.futures.ThreadPoolExecutor()

    branches = [
        "T_Px",
        "T_Py",
        "T_Pz",
        "T_Q",
        "T_NumberOfSigmaTPCPion",
        "T_TPCRefit",
        "T_TPCNCls",
        "T_Phi",
        "T_Eta",
        "T_HasPointOnITSLayer0",
        "T_HasPointOnITSLayer1",
        "T_ITSModuleInner",
        "T_ITSModuleOuter",
    ]

    evColumns = [
        "RunNum",
        "PeriodNumber",
        "OrbitNumber",
        "BunchCrossNumber",
        "Mass",
        "Pt",
        "Q",
        "Rapidity",
        "Phi",
        "ZNAenergy",
        "ZNCenergy",
        "ZPAenergy",
        "ZPCenergy",
        "VtxX",
        "VtxY",
        "VtxZ",
        "VtxContrib",
        "VtxChi2",
        "VtxNDF",
        "SpdVtxX",
        "SpdVtxY",
        "SpdVtxZ",
        "SpdVtxContrib",
        "V0Adecision",
        "V0Cdecision",
        "ADAdecision",
        "ADCdecision",
        "V0Afired",
        "V0Cfired",
        "ADAfired",
        "ADCfired",
        "STPfired",
        "SMBfired",
        "SM2fired",
        "SH1fired",
        "OM2fired",
        "OMUfired",
        "IsTriggered",
        "nTracklets",
        "nTracks",
        "ZDCAtime_0",
        "ZDCAtime_1",
        "ZDCAtime_2",
        "ZDCAtime_3",
        "ZDCCtime_0",
        "ZDCCtime_1",
        "ZDCCtime_2",
        "ZDCCtime_3",
    ]

    events = uproot4.open(
        ccup9_2015_file,
        object_cache=5000,
        num_workers=12,
        interpretation_executor=executor,
    )[tree_name]

    data_tracks = events.arrays(
        filter_name=branches, library="pd", array_cache=5000
    )  # , entry_stop=1000000)
    data_tracks.to_parquet(
        r"D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oTracks.parquet"
    )
    data_events = events.arrays(filter_name=evColumns, library="pd")
    chips = events.arrays(filter_name=["FORChip"], library="pd")
    chips = chips.groupby("entry").FORChip.apply(list)
    data_events["FORChip"] = chips
    data_events.to_parquet(
        r"D:\GoogleDrive\Job\cern\Alice\analysis\data\RhoPrime\2015\4Prongs2015oEvents.parquet"
    )


if __name__ == "__main__":
    convert_root_file_to_parquet("", "", "", "")
