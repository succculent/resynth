import scipy
import numpy
import math

def loss(parameters):
	#call synth function with parameters and store value into x
	x = []
	xFFT = scipy.fft.fft(x)
	y = data = numpy.genfromtxt('targetSound.csv', delimiter=",")
	yFFT = scipy.fft.fft(y)
	sum = 0.0
	sumI = 0.0j
	divideVal = 0
	for i in range(math.min(xFFT.size, yFFT.size)):
		sum += math.pow(xFFT[i].real - yFFT[i].real, 2)
		sumI += math.pow(xFFT[i].imag - yFFT[i].imag, 2)
		divideVal += 1
	return (sum + sumI.real)/divideVal