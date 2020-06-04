import scipy as sp
from scipy.optimize import minimize
import numpy as np
import math


'''
    Written by Elisabeth Vehling (vehling@usc.edu) for the project
    Neural Audio Resynth. Loss function written by Ada Toydemir
'''


# Function for testing optimization 
def rosen(x):
    return sum(100.0*(x[1:]-x[:-1]**2.0)**2.0 + (1-x[:-1])**2.0)

# Derivative of function for testing optimization
def rosen_der(x):
    xm = x[1:-1]
    xm_m1 = x[:-2]
    xm_p1 = x[2:]
    der = np.zeros_like(x)
    der[1:-1] = 200*(xm-xm_m1**2) - 400*(xm_p1 - xm**2)*xm - 2*(1-xm)
    der[0] = -400*x[0]*(x[1]-x[0]**2) - 2*(1-x[0])
    der[-1] = 200*(x[-1]-x[-2]**2)
    return der
#---------------------------------------------------------

#Loss function
#call synth, get audio, FFT transform, compare with sample audio
def loss():
	xFFT = sp.fft.fft(x)
	y = [1, 0, 0, 0, 0, 0, 0, 0]
	yFFT = sp.fft.fft(y)
	sum = 0.0
	sumI = 0.0j
	divideVal = 0
	for i in range(xFFT.size):
		sum += math.pow(xFFT[i].real - yFFT[i].real, 2)
		sumI += math.pow(xFFT[i].imag - yFFT[i].imag, 2)
		divideVal += 1
	return (sum + sumI.real)/divideVal

# Finds the minimum of a given function using the included parameters
def min(x):
    #synth parameters
    x0 = np.array(x)
    res = minimize(rosen, x0, method='L-BFGS-B', jac=False, options={'disp': None})
    ret = []
    for i in range(len(res.x)):
        ret.append(res.x[i])
    return ret
    
def optimize(a,b,c,d,e):
    params = []
    params.append(a)
    params.append(b)
    params.append(c)
    params.append(d)
    params.append(e)

    # ret = min(params)
    ret = [1.0]
    return ret


