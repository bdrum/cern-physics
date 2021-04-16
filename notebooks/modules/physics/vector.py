import numpy as np
import pandas as pd

def RotateToVector(dir_mom_tracks : pd.DataFrame, trans_tracks : pd.DataFrame):
    """
    Function defines components for rotation matrix that describes transition to the new
    coordinate system which OZ axis direct along momentum of input dir_mom_tracks and rotate provided dir_mom_tracks.
    """
    alpha_denom = np.sqrt(dir_mom_tracks.T_Py**2+dir_mom_tracks.T_Pz**2)

    dir_mom_tracks['sa'] = dir_mom_tracks.T_Py / alpha_denom
    dir_mom_tracks['ca'] = dir_mom_tracks.T_Pz / alpha_denom

    beta_denom = np.sqrt(dir_mom_tracks.T_Px**2 + (dir_mom_tracks.T_Py * dir_mom_tracks['sa'] + dir_mom_tracks.T_Pz*dir_mom_tracks['ca'])**2)

    dir_mom_tracks['sb'] = dir_mom_tracks.T_Px / beta_denom
    dir_mom_tracks['cb'] = (dir_mom_tracks.T_Py * dir_mom_tracks['sa'] + dir_mom_tracks.T_Pz*dir_mom_tracks['ca']) / beta_denom


    dir_mom_tracks['prx'] = dir_mom_tracks.T_Px * dir_mom_tracks['cb'] - dir_mom_tracks.T_Py * dir_mom_tracks['sa'] * dir_mom_tracks['sb'] - dir_mom_tracks.T_Pz * dir_mom_tracks['ca'] * dir_mom_tracks['sb']

    dir_mom_tracks['pry'] = dir_mom_tracks.T_Py * dir_mom_tracks['ca'] - dir_mom_tracks.T_Pz * dir_mom_tracks['sa']

    dir_mom_tracks['prz'] = dir_mom_tracks.T_Px * dir_mom_tracks['sb'] + dir_mom_tracks.T_Py * dir_mom_tracks['sa'] * dir_mom_tracks['cb'] + dir_mom_tracks.T_Pz * dir_mom_tracks['ca']* dir_mom_tracks['cb']

    dir_mom_tracks['l'] = np.sqrt(dir_mom_tracks.T_Px**2+dir_mom_tracks.T_Py**2+dir_mom_tracks.T_Pz**2)
    dir_mom_tracks['lr'] = np.sqrt(dir_mom_tracks.prx**2+dir_mom_tracks.pry**2+dir_mom_tracks.prz**2)
    dir_mom_tracks['E'] = np.sqrt(dir_mom_tracks.T_Px**2 + dir_mom_tracks.T_Py**2 +
                    dir_mom_tracks.T_Pz**2 + (0.001*Rho0.mass)**2)
    dir_mom_tracks['rE'] = np.sqrt(dir_mom_tracks.prx**2 + dir_mom_tracks.pry**2 +
                    dir_mom_tracks.prz**2 + (0.001*Rho0.mass)**2)
    
    trans_tracks['prx'] = trans_tracks.T_Px * dir_mom_tracks['cb'] - trans_tracks.T_Py * dir_mom_tracks['sa'] * dir_mom_tracks['sb'] - trans_tracks.T_Pz * dir_mom_tracks['ca'] * dir_mom_tracks['sb']
    
    trans_tracks['pry'] = trans_tracks.T_Py * dir_mom_tracks['ca'] - trans_tracks.T_Pz * dir_mom_tracks['sa']

    trans_tracks['prz'] = trans_tracks.T_Px * dir_mom_tracks['sb'] + trans_tracks.T_Py * dir_mom_tracks['sa'] * dir_mom_tracks['cb'] + trans_tracks.T_Pz * dir_mom_tracks['ca']* dir_mom_tracks['cb']

def BoostToSystem(y : pd.Series, G : pd.Series, tracks):
    """
    Lorentz boost to new system which move related original along OZ with
    y, G parameters.
    """
    
    tracks['y'] = y
    tracks['G'] = G

    tracks['oE'] = np.sqrt(tracks.T_Px**2 + tracks.T_Py**2 +
                    tracks.T_Pz**2 + (0.001*PiPlus.mass)**2)

    tracks['rE'] = np.sqrt(tracks.prx**2 + tracks.pry**2 +
                    tracks.prz**2 + (0.001*PiPlus.mass)**2)

    tracks['lpr'] = np.sqrt(tracks.prx**2 + tracks.pry**2 +
                    tracks.prz**2 )   

    tracks['brpz'] = tracks.y * tracks.prz - tracks.G * tracks.rE

def CosTheta(tracks1 : pd.DataFrame, tracks2 : pd.DataFrame) -> pd.Series:
    """
    Cosine of theta where a theta is an angle between vectors from tracks1 and tracks2.
    """
    l1 = np.sqrt(tracks1.iloc[:,0]**2 + tracks1.iloc[:,1]**2 + tracks1.iloc[:,2]**2)
    l2 = np.sqrt(tracks2.iloc[:,0]**2 + tracks2.iloc[:,1]**2 + tracks2.iloc[:,2]**2)
    t1t2 = tracks1.iloc[:,0]*tracks2.iloc[:,0] + tracks1.iloc[:,1]*tracks2.iloc[:,1] + tracks1.iloc[:,2]*tracks2.iloc[:,2]
    return t1t2 / (l1*l2)
