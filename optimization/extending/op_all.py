import scipy
from scipy.optimize import minimize
from scipy.io import wavfile
import numpy as np
import math
from os.path import dirname, join as pjoin
import warnings

'''
    Class that handles optimization of the synth parameters from an input sample.
    Takes in a file path to the input sample .wav file, produces class variables
    originalSample, sampleLength, originalSynth, FFTSample, and FFTSynth.
    Contact vehling@usc.edu for questions
'''
class Optimize():
    def __init__(self, filePath):
        self.__path = filePath
        self.__originalSample = self.getSampleFile()
        self.__sampleLength = len(self.__originalSample)
        self.__originalSynth = self.getSampleFile() #FIXME change to getSynthOuput()
        self._FFTSample = self.FFT(self.__originalSample)
        self._FFTSynth = self.FFT(self.__originalSynth)
        self.startOptimization()


    #Converts an array from mono to stereo (actually converts from stereo to mono)
    def mono2Stereo(self, data):
        mono = (data[:,0] + data[:,1])/2 
        return mono


    #Reads in sample from .wav file, terminates on failure
    def getSampleFile(self):
        try:
            sampleRate, data = wavfile.read(self.__path)
            data = data.astype(np.float)
            if len(data[0]) == 2:
                return self.mono2Stereo(data)
            return data
        except FileNotFoundError:
            print("Error: Input file was not found. Terminating optimization")
            return 1
        # except scipy.io.wavfile.WavFileWarning: #uncomment to silence warnings
            #pass

    #TODO Retrieves the current synth output audio
    def getSynthOutput(self):
        #pass self.sampleLength to C++ function
            #Make call to Maximillian to get output audio
        #Convert returned array to python data
        #return results
        return


    #Transforms unprocessed array from .wav input into function of frequency
    def FFT(self, i):
        return scipy.fft.fft(i)
    

    #TODO Make a call to start the computatioin
    ''' #ADA# I don't think it is necessary to have the synth output before we
        start optimization, bc we will likely only be using the synth output 
        given the parameters from scipy.optimize.minimize - the current
        parameters may be useful as a starting point, but not the current audio
    '''
    def startOptimization(self):
        #Check that both the synth and sample input has been convereted 
        if(all(self._FFTSample) and all(self._FFTSynth)):
            compute = Compute()
            results = compute.performOptimization()
            self.updateSynthParams(results)
        else:
            print("FFT was not completed for either or both Sample/Synth input")
        

    #TODO
    def getSynthParameters(self):
        #gets the current parameters from synth
        sample = [1.0,2.0,3.0,4.0,5.0,6.0,7.0, 8.0,9.0,10.0] #FIXME replace later with actual synth params, this is just for testing purposes
        #returns array
        return sample

    #TODO
    #Update Maxamillian's syth parameters
    def updateSynthParams(self, params):
        #convert to C++
        #Extend w c++
        #send the updated synth parameters to maximillian
        #ADA# possibly wait until this parameter transfer has been confirmed
        return

#TODO
class Compute(Optimize):
    def __init__(self):
        self._parameters = super().getSynthParameters()

    #MSE comparison between sample audio and synth audio; returns float
    def MSELoss(self, parameters):
        #gets synth output based on given parameters and stores the FFT in super().FFTSynth
        super().updateSynthParams(parameters)
        super().FFTSynth = super().FFT(super().getSynthOutput())
        #use super().FFTSynth and super().FFTSample for MSE
        sum = 0.0
        sumI = 0.0j
        divideVal = 0
        for i in range(math.min(super().FFTSynth.size, super().FFTSample.size)):
            sum += math.pow(xFFT[i].real - yFFT[i].real, 2)
            sumI += math.pow(xFFT[i].imag - yFFT[i].imag, 2) #unsure what to do with imaginary components ATM
            divideVal += 1
        # return results
        return (sum + sumI.real)/divideVal
        
    #ADA# No documenation on the optimizeResult object, so this is honestly a shot in the dark - we'll have to test
    #Make call to minimize function
    def performOptimization(self):
        #self.parameters = minimize(MSELoss, self.parameters, method='L-BFGS-B', jac=False, options={'disp': None})

''' #ADA# Currently some issue passing the func, still haven't figured it out

        optimizeResult = minimize(self.MSELoss, self._parameters, method='L-BFGS-B', jac=False, options={'disp': None})
        # self.boundParameters() #FIXME uncomment once exending is done
        if (optimizeResult.success):
            print("Optimization successful, saving and loading generated parameters")
            self.parameters = optimizeResult.x
        else:
            print("Optimization terminated: " + optimizeResult.message)
'''
        #super().updateSynthParams(self.parameters) #FIXME uncomment once exending is done
        return

    #TODO #ADA# we will need to go through the synth w lorand and alex bit by bit to know how to bound each parameter...
    #Might be used to manually bound the oputput
    def boundParameters(self):
        #check each parameter in self.parameters and see if it's above/below accepted bound
        #adjust if necessary
        return

def main():
    print("Running optimization...")
    # warnings.filterwarnings("error") #FIXME uncomment with lines 42-43 to silence warnings (i think lol)
    op = Optimize("./samples/harp.wav") #FIXME change to make path flexible
    #op = Optimize("./optimize/samples/harp.wav") #FIXME change to make path flexible
    print("Done.")
    return

if __name__ == "__main__":
    main()