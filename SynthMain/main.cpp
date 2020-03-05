#include "maximilian.h"

maxiOsc osc1, osc2, osc3, mod1, mod2, mod3;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

/*
int countIndex;
int frequencies[10] = {100, 200, 400, 340, 440, 880, 660, 120, 333};

double lastOutput = 0.0;
double myOscOutput = 0.0;
double myCutoff = 0.2;
*/

double osc, sine, tri, sq = 0.0;
int osc1Freq = 440;
int osc2Freq = 370;
int osc3Freq = 294;
double sinevol, trivol, sqvol = 1;


void setup() {//some inits
    
}

void play(double *output) {
    sine = osc1.sinewave(osc1Freq);
    tri = osc2.triangle(osc2Freq);
    sq = osc3.square(osc3Freq); 
    osc = (sine*sinevol+tri*trivol+sq*sqvol)/(sinevol+trivol+sqvol);
    
    
    
    
    /*
    countIndex = myCounter.phasor(1, 0, 9);
    
    myOscOutput = myOsc.sawn(anotherFilter.lopass(frequencies[countIndex], 0.001));
    
    output[0] = myFilter.lopass(myOscOutput, myCutoff.phasor(0.1, 0.01, 0.5));
    
    output[1] = output[0];
    */
    
    output[0] = osc;
    output[1] = output[0];
}


