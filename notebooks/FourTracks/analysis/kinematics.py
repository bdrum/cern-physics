import numpy as np
import pandas as pd
from particle import Particle

PiPlus = Particle.from_pdgid(211)


def pt_tracks(tracks: pd.DataFrame) -> pd.Series:
    return np.sqrt(tracks.T_Px ** 2 + tracks.T_Py ** 2)


def pt_events(tracks: pd.DataFrame) -> pd.Series:
    return np.sqrt(
        tracks.T_Px.groupby("entry").sum() ** 2
        + tracks.T_Py.groupby("entry").sum() ** 2
    )


def mass_events(tracks: pd.DataFrame) -> pd.Series:
    ETracks = E_events(tracks)
    SumTracks = tracks.groupby("entry").sum()
    return np.sqrt(
        ETracks ** 2 - SumTracks.T_Px ** 2 - SumTracks.T_Py ** 2 - SumTracks.T_Pz ** 2
    )


def E_events(tracks: pd.DataFrame) -> pd.Series:
    return (
        np.sqrt(
            (
                tracks.T_Px ** 2
                + tracks.T_Py ** 2
                + tracks.T_Pz ** 2
                + (0.001 * PiPlus.mass) ** 2
            )
        )
        .groupby("entry")
        .sum()
    )


def P_events(tracks: pd.DataFrame) -> pd.Series:
    return np.sqrt(
        tracks.T_Px.groupby("entry").sum() ** 2
        + tracks.T_Py.groupby("entry").sum() ** 2
        + tracks.T_Pz.groupby("entry").sum() ** 2
    )


def cos_theta_events(tracks1: pd.DataFrame, tracks2: pd.DataFrame) -> pd.Series:
    p1p2 = (
        tracks1.T_Px.groupby("entry").sum() * tracks2.T_Px.groupby("entry").sum()
        + tracks1.T_Py.groupby("entry").sum() * tracks2.T_Py.groupby("entry").sum()
        + tracks1.T_Pz.groupby("entry").sum() * tracks2.T_Pz.groupby("entry").sum()
    )
    p1 = np.sqrt(
        tracks1.T_Px.groupby("entry").sum() ** 2
        + tracks1.T_Py.groupby("entry").sum() ** 2
        + tracks1.T_Pz.groupby("entry").sum() ** 2
    )
    p2 = np.sqrt(
        tracks2.T_Px.groupby("entry").sum() ** 2
        + tracks2.T_Py.groupby("entry").sum() ** 2
        + tracks2.T_Pz.groupby("entry").sum() ** 2
    )
    return p1p2 / (p1 * p2)
