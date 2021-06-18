import lmfit
import cmath
from lmfit.parameter import Parameters
import numpy as np
import pandas as pd
from particle import Particle
from typing import Union
from lmfit import Model
from lmfit.model import ModelResult

Rho0 = Particle.from_pdgid(113)
Pi0 = Particle.from_pdgid(111)
PiPlus = Particle.from_pdgid(211)
pi_pl_mass = PiPlus.mass / 1000


def bw(
    x: Union[np.ndarray, pd.Series], M: float, G: float, amp: float
) -> Union[np.ndarray, pd.Series]:
    """
    Breit-Wigner function with params
    M - mass of a resonance
    G - $\Gamma$ of a resonance
    amp - amplitude coefficient
    x - Energy
    """
    q = np.sqrt((x ** 2) / 4 - pi_pl_mass ** 2)
    q_rho = np.sqrt((M ** 2) / 4 - pi_pl_mass ** 2)
    ratrho1 = ((q / q_rho) ** 3) / ((q / q_rho) ** 2 + 1) * 2
    g_tot = G * ratrho1
    fff = amp * G * g_tot * x * M / ((x ** 2 - M ** 2) ** 2 + M ** 2 * g_tot ** 2)

    return fff


def polyn(x, c0, c1, c2, c3, c4, c5, c6, c7, amp):
    """
    c - array of polynomial coefficients (including coefficients equal to zero) from highest degree to the constant term
    """
    return amp * np.polyval([c7, c6, c5, c4, c3, c2, c1, c0], x)


# def ff(
#     x, y, functions: list, params: Parameters, numpoints=100, **fit_kws
# ) -> tuple(ModelResult, pd.DataFrame):
#     """
#     x,
#     y,
#     functions - list of functions used in Model,
#     params - initial Parameters for Model,
#     numpoints - number of points for model evaluation
#     Returns:
#     pd.Dataframe with initial data and evaluation of fit functions
#     """
#     mod = Model(functions[0], prefix=functions[0].__name__ + "_")

#     for f in functions[1:]:
#         mod += Model(f, prefix=f.__name__ + "_")

#     result = mod.fit(y, params, x=x, weights=1 / np.sqrt(y), *fit_kws)
#     xx = np.linspace(x.min(), x.max(), numpoints)
#     xx = np.linspace(x.min(), x.max(), 100)

#     ff = result.eval(x=xx)

#     fbw1 = fit.bw(
#         x=xx,
#         M=result.best_values["bw1_M"],
#         G=result.best_values["bw1_G"],
#         amp=result.best_values["bw1_amp"],
#     )
#     fbw2 = fit.bw(
#         x=xx,
#         M=result.best_values["bw2_M"],
#         G=result.best_values["bw2_G"],
#         amp=result.best_values["bw2_amp"],
#     )
#     fbckg = fit.polyn(
#         xx,
#         result.best_values["bckg_c0"],
#         result.best_values["bckg_c1"],
#         result.best_values["bckg_c2"],
#         result.best_values["bckg_c3"],
#         result.best_values["bckg_c4"],
#         0,
#         0,
#         0,
#         result.best_values["bckg_amp"],
#     )
#     df = pd.DataFrame([xx, ff, fbw1, fbw2, fbckg]).T
#     df.columns = ["x", "fit", "bw1", "bw2", "bkgr"]
#     df = pd.DataFrame([xx, ff, fbw, fbckg]).T
#     df.columns = ["x", "fit", "bw", "bckg"]
#     return pd.DataFrame([])


def fTerm(
    x: Union[np.ndarray, pd.Series], M: float, G: float, amp: float
) -> Union[np.ndarray, pd.Series]:
    """
    """
    # rho mass-dependent  width
    val = ((x ** 2 - 4 * pi_pl_mass ** 2) / (M ** 2 - 4 * pi_pl_mass ** 2)) ** 1.5
    mdwidth = G * (M / x) * val  # mass dependent width

    denom = (x ** 2 - M ** 2) + (M * mdwidth * 1j)
    return amp * np.sqrt(x * M * mdwidth) / denom


def fInterBWs(
    x: Union[np.ndarray, pd.Series],
    M1: float,
    G1: float,
    amp1: float,
    M2: float,
    G2: float,
    amp2: float,
    amp: float,
) -> Union[np.ndarray, pd.Series]:
    """
    """
    aterm = fTerm(x, M1, G1, amp1)
    bterm = fTerm(x, M2, G2, amp2)

    amptot = np.abs((aterm + bterm) ** 2)
    amptwo = np.abs(aterm) ** 2 + np.abs(bterm) ** 2

    return amp * (amptot - amptwo)

