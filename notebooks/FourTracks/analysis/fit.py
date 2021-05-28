import numpy as np
import pandas as pd
from particle import Particle
from typing import Union

Rho0 = Particle.from_pdgid(113)
Pi0 = Particle.from_pdgid(111)
PiPlus = Particle.from_pdgid(211)
pi_pl_mass = PiPlus.mass / 1000

bckg_y = None


def bw(x: float, M: float, G: float, amp: float) -> Union[np.ndarray, pd.Series]:
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


def bw_bckg(
    x: float, M: float, G: float, amp: float, amp_bckg: float
) -> Union[np.ndarray, pd.Series]:
    return bw(x=x, M=M, G=G, amp=amp) + amp_bckg * bckg_y
