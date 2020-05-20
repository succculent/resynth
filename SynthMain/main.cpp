#include "maximilian.h"

maxiOsc mod1, mod2, mod3;
synthOsc oscA, oscB;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

void setup() {

}

double synth(
    int trigger, int freq, int detune,
    double sinAvol, double triAvol, double sqAvol,
    double sinBvol, double triBvol, double sqBvol,
    double mod1Afreq, double mod1Bfreq, double mod2Afreq,
    double mod2Bfreq, double mod3Afreq, double mod3Bfreq,
    int mod1AEnable, int mod2AEnable, int mod3AEnable,
    int mod1BEnable, int mod2BEnable, int mod3BEnable,
    double loCutoff, double loRes, int loEnable,
    double hiCutoff, double hiRes, int hiEnable,
    double loA, double loD, double loS, double loR,
    double hiA, double hiD, double hiS, double hiR,
    double volA, double volD, double volS, double volR
    ) {
    
    double detuned_freq = exp(log(freq)+detune*log(2)/1200);
    
    double mod3val;
    double mod2val;
    double mod1val;
    //modulation frequencies for Oscillator A
    if(mod3AEnable) mod3val = mod3.sinewave(mod3Afreq);
    else mod3val = 1;
    
    if(mod2AEnable) mod2val = mod2.sinewave(mod3val*mod2Afreq);
    else mod2val = 1;
    
    if(mod1AEnable) mod1val = mod1.sinewave(mod2val*mod1Afreq);
    else mod1val = 1;
    
    double modA = freq + freq*mod1val;
    
    //modulation frequencies for Oscillator B
    if(mod3BEnable) mod3val = mod3.sinewave(mod3Bfreq);
    else mod3val = 1;
    
    if(mod2BEnable) mod2val = mod2.sinewave(mod3val*mod2Bfreq);
    else mod2val = 1;
    
    if(mod1BEnable) mod1val = mod1.sinewave(mod2val*mod1Bfreq);
    else mod1val = 1;
    
    double modB = detuned_freq + detuned_freq*mod1val;
    
    //Oscillator A
    oscA.setFreq(modA);
    oscA.setSinvol(sinAvol);
    oscA.setTrivol(triAvol);
    oscA.setSqvol(sqAvol);
    
    //Oscillator B
    oscB.setFreq(modB);
    oscB.setSinvol(sinBvol);
    oscB.setTrivol(triBvol);
    oscB.setSqvol(sqBvol);
    //Combined oscillator output
    double osc = (oscA.output() + oscB.output()) / 2;

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
        int max_value = freq*5; //maxiSettings::sampleRate*0.5 <--- should ideally be this but this breaks it
        double hibound = max_value-(max_value-hiCutoff)*hpfadsr.adsr(1.,hpfadsr.trigger); //hibound is the envelope shape scaled by the min cutoff frequency... might need some work
        
        f2osc = hpf.hires(osc, hibound, hiRes);
    }
    else f2osc = osc;
    //try mutually recursive filters instead of average?
    double fosc = (f1osc+f2osc)/2;
    
    //Volume envelope
    voladsr.setAttack(volA);
    voladsr.setDecay(volD);
    voladsr.setSustain(volS);
    voladsr.setRelease(volR);
    double volume = voladsr.adsr(1.,voladsr.trigger);
    //Output
    double output = fosc*volume;
    return output;
}

maxiOsc counter;
void play(double *output) {

/*
 TESTING SETUP
 */
    int freq = 440;
    int trigger = counter.phasor(1, 1, 9); //test counter in place of MIDI input
/*
 OSCILLATORS
 */
    //volumes of waveforms on 2 oscillators
    double sinAvol = 1;
    double triAvol = 0;
    double sqAvol = 0;
    double sinBvol = 0;
    double triBvol = 1;
    double sqBvol = 0;
    //detune oscillator B, input in cents
    int detune = 10;
/*
 FM
 */
    //modulation frequencies and amounts in Hz
    double mod1Afreq = 10;
    double mod2Afreq = 30;
    double mod3Afreq = 0.3;
    double mod1Bfreq = 0;
    double mod2Bfreq = 0;
    double mod3Bfreq = 0;
    //enables for fm
    int mod1AEnable = 0;
    int mod2AEnable = 0;
    int mod3AEnable = 0;
    int mod1BEnable = 0;
    int mod2BEnable = 0;
    int mod3BEnable = 0;
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
    double loCutoff = 300;
    double loRes = 10; //awtch out 1-?
    int loEnable = 1;
    double hiCutoff = 500;
    double hiRes = 10;
    int hiEnable = 1;
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
    output[0] = synth(trigger, freq, detune,
                    sinAvol, triAvol, sqAvol,
                    sinBvol, triBvol, sqBvol,
                    mod1Afreq, mod1Bfreq, mod2Afreq,
                    mod2Bfreq, mod3Afreq, mod3Bfreq,
                    mod1AEnable, mod2AEnable, mod3AEnable,
                    mod1BEnable, mod2BEnable, mod3BEnable,
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
