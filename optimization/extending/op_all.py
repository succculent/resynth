import scipy
from scipy.optimize import minimize
from scipy.io import wavfile
import numpy as np
import math
from os.path import dirname, join as pjoin
import warnings
import sys

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
        # self.__originalSynth = self.getSampleFile() #FIXME change to getSynthOuput()
        self._FFTSample = self.FFT(self.__originalSample)
        # self._FFTSynth = self.FFT(self.__originalSynth)
        self.startOptimization()


    #Converts an array from mono to stereo
    def stereo2Mono(self, data):
        mono = (data[:,0] + data[:,1])/2 
        return mono


    #Reads in sample from .wav file, terminates on failure
    def getSampleFile(self):
        try:
            sampleRate, data = wavfile.read(self.__path)
            data = data.astype(np.float)
            if len(data[0]) == 2:
                return self.stereo2Mono(data)
            return data
        except FileNotFoundError:
            print("Error: Input file was not found. Terminating optimization")
            sys.exit(1)
        #except scipy.io.wavfile.WavFileWarning: #uncomment to silence warnings
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
    def startOptimization(self):
        #Check that both the synth and sample input has been convereted 
        if(all(self._FFTSample)):
            compute = Compute(self._FFTSample)
            results = compute.performOptimization()
            self.updateSynthParams(results)
        else:
            print("FFT was not completed for either or both Sample/Synth input")
        

    #TODO
    def getSynthParameters(self):
        #gets the current parameters from synth
        sample = [1, 1, 1, 1, 1, 1, 0, 0] #FIXME replace later with actual synth params, this is just for testing purposes
        #returns array
        return sample

    #TODO
    #Update Maxamillian's syth parameters
    def updateSynthParams(self, params):
        print("Updated parameters:", params) #FIXME testing only
        #convert to C++
        #Extend w c++
        #send the updated synth parameters to maximillian
        #ADA# possibly wait until this parameter transfer has been confirmed
        return

#TODO
class Compute(Optimize):
    def __init__(self, FFTS):
        self.__parameters = super().getSynthParameters()
        self.__FFTSample = FFTS

    #MSE comparison between sample audio and synth audio; returns float
    def MSELoss(self, parameters):
        #gets synth output based on given parameters and stores the FFT in super().FFTSynth
        super().updateSynthParams(parameters)
        FFTSynth = super().FFT(super().getSynthOutput())

        sum = 0.0
        sumI = 0.0j
        divideVal = 0
        for i in range(min(len(FFTSynth), len(self.__FFTSample))):
            sum += math.pow(FFTSynth[i].real - self.__FFTSample[i].real, 2)
            sumI += math.pow(FFTSynth[i].imag - self.__FFTSample[i].imag, 2) #unsure what to do with imaginary components ATM
            divideVal += 1
        # return results
        loss = (sum + sumI.real)/divideVal
        print ("~~~~~~~~~~~~~~~~~~~~~")
        print("LOSS IS: " + str(loss))
        return loss
        
    #Make call to minimize function
    def performOptimization(self):
        temp = self.__parameters
        #_bounds = [(0, 1) for _ in temp] #template for declaring bounds for variables... after jac=False put bounds=_bounds
        opResult = minimize(self.MSELoss, temp, method='L-BFGS-B', jac=False, options={'disp': None})
        results = opResult.x
        print("~~~~~~~~~~~~~~~~~~~~~")
        print("~~~~~~~~~~~~~~~~~~~~~")
        print(opResult.success)
        print("Final parameters are... ")
        print(results)
        print("~~~~~~~~~~~~~~~~~~~~~")
        super().updateSynthParams(self.parameters) #FIXME uncomment once exending is done
        return

    #TODO
    #Might be used to manually bound the oputput
    def boundParameters(self):
        #check each parameter in self.parameters and see if it's above/below accepted bound
        #adjust if necessary
        return

def main():
    print("Running optimization...")
    # warnings.filterwarnings("error") #FIXME uncomment with lines 42-43 to silence warnings (i think lol)
    op = Optimize("samples/harp.wav") #FIXME change to make path flexible
    print("Done.")
    return

if __name__ == "__main__":
    main()