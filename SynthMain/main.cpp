#include "maximilian.h"

maxiOsc mod1, mod2, mod3;
synthOsc osc1, osc2;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

void setup() {

}

double synth(
    int trigger, int freq,
    double sin1vol, double tri1vol, double sq1vol,
    double sin2vol, double tri2vol, double sq2vol,
    double mod1freq, double mod1amt, double mod2freq,
    double mod2amt, double mod3freq, double mod3amt,
    int mod1aEnable, int mod2aEnable, int mod3aEnable,
    int mod1bEnable, int mod2bEnable, int mod3bEnable,
    double loCutoff, double loRes, int loEnable,
    double hiCutoff, double hiRes, int hiEnable,
    double loA, double loD, double loS, double loR,
    double hiA, double hiD, double hiS, double hiR,
    double volA, double volD, double volS, double volR
    ) {

    //modulation frequencies
    double mod1val = mod1.sinewave(mod1freq)*mod1amt;
    double mod2val = mod2.sinewave(mod2freq)*mod2amt;
    double mod3val = mod3.sinewave(mod3freq)*mod3amt;
    
    //modulated carrier frequencies
    double modA = freq + mod1val*mod1aEnable + mod2val*mod2aEnable + mod3val*mod3aEnable;
    double modB = freq + mod1val*mod1bEnable + mod2val*mod2bEnable + mod3val*mod3bEnable;
    
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
    double f1osc;
    if(loEnable) {
        lpfadsr.setAttack(loA);
        lpfadsr.setDecay(loD);
        lpfadsr.setSustain(loS);
        lpfadsr.setRelease(loR);
        double lobound = loCutoff*lpfadsr.adsr(1.,lpfadsr.trigger); //lobound is the envelope shape scaled by the max cutoff frequency
        f1osc = lpf.lores(osc, lobound, loRes);
    }
    else f1osc = osc;
    
    double f2osc;
    if(hiEnable) {
        hpfadsr.setAttack(hiA);
        hpfadsr.setDecay(hiD);
        hpfadsr.setSustain(hiS);
        hpfadsr.setRelease(hiR);
        double hibound = freq*5-(freq*5-hiCutoff)*hpfadsr.adsr(1.,hpfadsr.trigger); //hibound is the envelope shape scaled by the min cutoff frequency... needs some work
        f2osc = hpf.hires(f1osc, hibound, hiRes);
    }
    else f2osc = f1osc;
    
    //Volume envelope
    voladsr.setAttack(volA);
    voladsr.setDecay(volD);
    voladsr.setSustain(volS);
    voladsr.setRelease(volR);
    double volume = voladsr.adsr(1.,voladsr.trigger);

    //Output
    double output = volume*f2osc;
    return output;
}

maxiOsc counter;
void play(double *output) {

/*
 TESTING SETUP
 */
    int freq = 200;
    int trigger = counter.phasor(1, 1, 9); //test counter in place of MIDI input
/*
 OSCILLATORS
 */
    //volumes of waveforms on 2 oscillators
    double sin1vol = 1;
    double tri1vol = 0;
    double sq1vol = 0;
    double sin2vol = 0;
    double tri2vol = 0;
    double sq2vol = 0;
/*
 FM
 */
    //modulation frequencies and amounts in Hz
    double mod1freq = 0.3;
    double mod2freq = 3;
    double mod3freq = 0;
    double mod1amt = 1;
    double mod2amt = 1;
    double mod3amt = 1;
    //enables for fm
    int mod1aEnable = 0;
    int mod2aEnable = 0;
    int mod3aEnable = 0;
    int mod1bEnable = 0;
    int mod2bEnable = 0;
    int mod3bEnable = 0;
/*
 FILTERS
 */
    //filter envelopes
    //NOTE: all values are in ms, except Sustain is 0-1. Decay needs to be at least 1!
    double loA = 0;
    double loD = 1;
    double loS = 1;
    double loR = 1000;
    double hiA = 0;
    double hiD = 1;
    double hiS = 1;
    double hiR = 1000;
    //filter cutoffs, resonances, and enables
    double loCutoff = 2000;
    double loRes = 10; //awtch out 1-?
    int loEnable = 0;
    double hiCutoff = 0;
    double hiRes = 10;
    int hiEnable = 0;
/*
 VOLUME
 */
    //volume envelope
    //NOTE: all values are in ms, except Sustain is 0-1. Decay needs to be at least 1!
    double volA = 0;
    double volD = 1;
    double volS = 1;
    double volR = 1000;

    //left speaker
    output[0] = synth(trigger, freq,
                    sin1vol, tri1vol, sq1vol,
                    sin2vol, tri2vol, sq2vol,
                    mod1freq, mod1amt, mod2freq,
                    mod2amt, mod3freq, mod3amt,
                    mod1aEnable, mod2aEnable, mod3aEnable,
                    mod1bEnable, mod2bEnable, mod3bEnable,
                    loCutoff, loRes, loEnable,
                    hiCutoff, hiRes, hiEnable,
                    loA, loD, loS, loR,
                    hiA, hiD, hiS, hiR,
                    volA, volD, volS, volR
                    );
    //right speaker
    output[1] = output[0];

// output[0]=mod1.sinewave(mod2.sinewave(mod3.sinewave(0.3)*30)*200);//awesome bassline
// output[1]=output[0];

}
