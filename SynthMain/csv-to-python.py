import numpy
import wave
import math
import struct

data = numpy.genfromtxt('programOutput.csv', delimiter=",")

print(data.shape)

wavefile = wave.open("testOutput.wav", "wb") #creates file (like an output stream)
wavefile.setnchannels(1) #mono
wavefile.setsampwidth(2) #sample width (how large numbers can be?)
wavefile.setframerate(44100) #frames per psecond
#wavefile.setnframes(data.shape[1]) #length of csv

for i in range(data.shape[1]):
    value = int(32767.0*math.cos(440*math.pi*float(i)/float(44100.0)))
    #value0 = data[0, i]
    #value1 = data[1, i]
    data = struct.pack('<h', value)
    wavefile.writeframesraw(data)

wavefile.writeframes('')
wavefile.close() #saves the file
