#include "maximilian.h"

maxiOsc mod1, mod2, mod3;
synthOsc osc1, osc2;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

int freq = 440;



void setup() {//some inits
    
}

double synth(
    double sin1vol, double tri1vol, double sq1vol,
    double sin2vol, double tri2vol, double sq2vol,
    double mod1f, double mod1v, double mod2f, double mod2v, double mod3f, double mod3v,
    int mod1ta, int mod2ta, int mod3ta, int mod1tb, int mod2tb, int mod3tb, //0 if off 1 if on
    double cutoff1, double res1, double cutoff2, double res2
    ) {
    //carrier frequencies
    double mod1double = mod1.sinewave(mod1f)*mod1v;
    double mod2double = mod2.sinewave(mod2f)*mod2v;
    double mod3double = mod3.sinewave(mod3f)*mod3v;
    //modified FM frequencies
    double modA = freq + mod1double*mod1ta + mod2double*mod2ta + mod3double*mod3ta;
    double modB = freq + mod1double*mod1tb + mod2double*mod2tb + mod3double*mod3tb;
    //Oscillator 1
    osc1.setFreq(modA);
    osc1.setSinvol(sin1vol);
    osc1.setTrivol(tri1vol);
    osc1.setSqvol(sq1vol);
    //Oscillator 2
    osc2.setFreq(modB);
    osc2.setSinvol(sin2vol);
    osc2.setTrivol(tri2vol);
    osc2.setSqvol(sq2vol);
    //Combined oscillator output
    double osc = (osc1.output() + osc2.output()) / 2;
    //Filters
    double f1osc = lpf.lores(osc, cutoff1, res1);
    double f2osc = hpf.hires(f1osc, cutoff2, res2);

    //OUTPUT
    double out = f2osc;
    return out;
}

double counter = 0.0;

void play(double *output) {

    double sin1vol = 1;
    double tri1vol = 0;
    double sq1vol = 0;
    double sin2vol = 0;
    double tri2vol = 0;
    double sq2vol = 0;
    double mod1f = 2;
    double mod2f = 0;
    double mod3f = 0;
    double mod1v = 100;
    double mod2v = 0;
    double mod3v = 0;
    int mod1ta = 1;
    int mod2ta = 1;
    int mod3ta = 0;
    int mod1tb = 0;
    int mod2tb = 0;
    int mod3tb = 0;
    double cutoff1 = 340;
    double res1 = 1; //awtch out 1-?
    double cutoff2 = 0;
    double res2 = 10;

    output[0] = synth(sin1vol, tri1vol, sq1vol,
                    sin2vol, tri2vol, sq2vol,
                    mod1f, mod1v, mod2f, mod2v, mod3f, mod3v,
                    mod1ta, mod2ta, mod3ta, mod1tb, mod2tb, mod3tb,
                      cutoff1, res1, cutoff2, res2);
    output[1] = output[0];
    
    /*
    countIndex = myCounter.phasor(1, 0, 9);
    
    myOscOutput = myOsc.sawn(anotherFilter.lopass(frequencies[countIndex], 0.001));
    
    output[0] = myFilter.lopass(myOscOutput, myCutoff.phasor(0.1, 0.01, 0.5));
    
    output[1] = output[0];
    */
}


