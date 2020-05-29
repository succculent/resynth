import scipy
import math

def loss(x):
	xFFT = scipy.fft.fft(x)
	y = [1, 0, 0, 0, 0, 0, 0, 0]
	yFFT = scipy.fft.fft(y)
	sum = 0.0
	sumI = 0.0j
	divideVal = 0
	for i in range(xFFT.size):
		sum += math.pow(xFFT[i].real - yFFT[i].real, 2)
		sumI += math.pow(xFFT[i].imag - yFFT[i].imag, 2)
		divideVal += 1
	return (sum + sumI.real)/divideVal