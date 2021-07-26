import ROOT
import math


def recoverNeutrinoPz(lep, met): # W kinematical reconstruction
    pz = 0.
    a = 80.4**2 - lep.M()**2 + 2.*lep.Px()*met.Px() + 2.*lep.Py()*met.Py()
    A = 4.*( lep.E()**2 - lep.Pz()**2 )
    B = -4.*a*lep.Pz()
    C = 4*(lep.E()**2) * (met.Px()**2  + met.Py()**2) - a**2
    D = B**2 - 4*A*C
    # If there are real solutions, use the one with lowest pz                                            
    if D >= 0.:
        s1 = (-B+math.sqrt(D))/(2*A)
        s2 = (-B-math.sqrt(D))/(2*A)
        pz = s1 if abs(s1) < abs(s2) else s2
    # Otherwise, use real part                                                                           
    else:
        pz = -B/(2*A)
    return pz
