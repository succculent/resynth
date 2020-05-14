#include "maximilian.h"

maxiOsc mod1, mod2, mod3;
synthOsc osc1, osc2;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

void setup() {//some inits

}



double synth(
    int trigger, int freq,
    double sin1vol, double tri1vol, double sq1vol,
    double sin2vol, double tri2vol, double sq2vol,
    double mod1f, double mod1v, double mod2f, double mod2v, double mod3f, double mod3v,
    int mod1ta, int mod2ta, int mod3ta, int mod1tb, int mod2tb, int mod3tb, //0 if off 1 if on
    double locutoff, double lores, double hicutoff, double hires,
    double loA, double loD, double loS, double loR,
    double hiA, double hiD, double hiS, double hiR,
    double volA, double volD, double volS, double volR
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

    if (trigger == 1) { //trigger the envelopes
        lpfadsr.trigger=1;
        hpfadsr.trigger=1;
        voladsr.trigger=1;
    }

    else { //release the envelopes to make it fade out only if it's been triggered
        lpfadsr.trigger=0;
        hpfadsr.trigger=0;
        voladsr.trigger=0;
    }

    //Filter envelopes
    lpfadsr.setAttack(loA);
    lpfadsr.setDecay(loD);
    lpfadsr.setSustain(loS);
    lpfadsr.setRelease(loR);
    double lobound = locutoff*lpfadsr.adsr(1.,lpfadsr.trigger); //lobound is the envelope shape scaled by the max cutoff frequency
    double f1osc = lpf.lores(osc, lobound, lores);

    hpfadsr.setAttack(hiA);
    hpfadsr.setDecay(hiD);
    hpfadsr.setSustain(hiS);
    hpfadsr.setRelease(hiR);
    double hibound = freq*5-(freq*5-hicutoff)*hpfadsr.adsr(1.,hpfadsr.trigger); //hibound is the envelope shape scaled by the max cutoff frequency... needs some work
    double f2osc = hpf.hires(f1osc, hibound, hires);

    //Volume envelope
    voladsr.setAttack(volA);
    voladsr.setDecay(volD);
    voladsr.setSustain(volS);
    voladsr.setRelease(volR);
    double volume = voladsr.adsr(1.,voladsr.trigger);


    //OUTPUT
    double output = volume*f2osc;
    return output;
}

maxiOsc counter;
void play(double *output) {
    int freq = 440;
    int trigger = counter.phasor(1, 1, 9); //basically just a counter 1-10, interates every second and loops
    //volumes of waveforms on 2 oscillators
    double sin1vol = 1;
    double tri1vol = 0;
    double sq1vol = 0;
    double sin2vol = 0;
    double tri2vol = 0;
    double sq2vol = 0;
    //modulation frequencies and amounts
    double mod1f = 0;
    double mod2f = 0;
    double mod3f = 0;
    double mod1v = 0;
    double mod2v = 0;
    double mod3v = 0;
    //enables for fm
    int mod1ta = 0;
    int mod2ta = 0;
    int mod3ta = 0;
    int mod1tb = 0;
    int mod2tb = 0;
    int mod3tb = 0;
    //filter envelopes
    double loA = 0;
    double loD = 1; //needs to be at least 1
    double loS = 1;
    double loR = 1000; //in ms
    double hiA = 0;
    double hiD = 1; //needs to be at least 1
    double hiS = 1;
    double hiR = 1000; //in ms
    //filter cutoffs and resonances
    double locutoff = 2000;
    double lores = 10; //awtch out 1-?
    double hicutoff = 440;
    double hires = 10;
    //volume envelope
    double volA = 0;
    double volD = 1; //needs to be at least 1
    double volS = 1;
    double volR = 1000;

    //left speaker
    output[0] = synth(trigger, freq,
                    sin1vol, tri1vol, sq1vol,
                    sin2vol, tri2vol, sq2vol,
                    mod1f, mod1v, mod2f, mod2v, mod3f, mod3v,
                    mod1ta, mod2ta, mod3ta, mod1tb, mod2tb, mod3tb,
                    locutoff, lores, hicutoff, hires,
                    loA, loD, loS, loR,
                    hiA, hiD, hiS, hiR,
                    volA, volD, volS, volR
                    );
    //right speaker
    output[1] = output[0];

    /*
    counter = myCounter.phasor(1, 0, 9);

    myOscOutput = myOsc.sawn(anotherFilter.lopass(frequencies[counter], 0.001));

    output[0] = myFilter.lopass(myOscOutput, myCutoff.phasor(0.1, 0.01, 1.5));

    output[1] = output[0];
    */
}


