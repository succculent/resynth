#include "maximilian.h"

maxiOsc mod1, mod2, mod3, counter, test;
synthOsc oscA, oscB;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDelayline delay;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

void setup() {

}

double synth(
    int trigger, int freq, int detune,
    double sinAvol, double triAvol, double sqAvol,
    double sinBvol, double triBvol, double sqBvol,
    double mod1freq, double mod2freq, double mod3freq,
    int mod1amt, int mod2amt, int mod3amt,
    double loCutoff, double loRes, int loEnable,
    double hiCutoff, double hiRes, int hiEnable,
    double loA, double loD, double loS, double loR,
    double hiA, double hiD, double hiS, double hiR,
    int delay_size, double delay_feedback, double delay_wet,
    double dist_shape, double dist_wet,
    unsigned int flang_delay, double flang_feedback, double flang_speed, double flang_depth, double flang_wet,
    unsigned int chorus_delay, double chorus_feedback, double chorus_speed, double chorus_depth, double chorus_wet,
    double volA, double volD, double volS, double volR
    ) {
    /*
     TRIGGERS
     */
        if (trigger == 1) {
            mod1.phaseReset(0);
            mod2.phaseReset(0);
            mod3.phaseReset(0);
            oscA.phaseReset(0);
            oscB.phaseReset(0);
            
            //delay.phaseReset(0);
            
            lpfadsr.trigger=1;
            hpfadsr.trigger=1;
            voladsr.trigger=1;
        }

        else {
            lpfadsr.trigger=0;
            hpfadsr.trigger=0;
            voladsr.trigger=0;
        }
    /*
     DETUNE
     */
        double detuned_freq = exp(log(freq)+detune*log(2)/1200);
    /*
     FM
     */
        //modulation frequencies for Oscillator A
        //mod2 modulates mod1, and mod1 modulates Osc A
        double mod2val = mod2amt * mod2.sinewave(mod2freq);
        double mod1val = 0;
        if(mod2val == 0) mod1val = mod1amt * mod1.sinewave(mod1freq);
        else mod1val = mod1amt * mod1.sinewave(mod1freq + mod2val);
        double modA = freq+mod1val;
        
        //modulation frequencies for Oscillator B
        //mod3 modulates Osc B
        double mod3val = mod3amt * mod3.sinewave(mod3freq);
        double modB = detuned_freq + mod3val;
    /*
     OSCILLATORS
     */
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
        double osc;
        double combined_vol = sinAvol + triAvol + sqAvol + sinBvol + triBvol + sqBvol;
        if(combined_vol == 0) osc = 0;
        else osc = (oscA.output() + oscB.output()) / combined_vol;
    /*
     FILTERS
     */
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
            int max_value = freq*5; //maxiSettings::sampleRate*0.5 <--- should ideally be this but this breaks it?
            double hibound = max_value-(max_value-hiCutoff)*hpfadsr.adsr(1.,hpfadsr.trigger); //hibound is the envelope shape scaled by the min cutoff frequency... might need some work
            
            f2osc = hpf.hires(osc, hibound, hiRes);
        }
        else f2osc = osc;
    
        double fosc = (f1osc+f2osc)/2;
    /*
     FX
     */
        double fxosc = fosc;
        //Delay
        fxosc = fxosc*(1-delay_wet)+delay.dl(fxosc, delay_size, delay_feedback)*delay_wet;
        //Distortion
        //fxosc = fxosc*(1-dist_wet)+dist.atanDist(fxosc, dist_shape)*dist_wet;
        //Flanger
        //fxosc = fxosc+flang.flange(fxosc, flang_delay, flang_feedback, flang_speed, flang_depth);
        //Chorus
    /*
     VOLUME
     */
        //Volume envelope
        voladsr.setAttack(volA);
        voladsr.setDecay(volD);
        voladsr.setSustain(volS);
        voladsr.setRelease(volR);
        double volume = voladsr.adsr(1.,voladsr.trigger);
        //Output
        //double output = fxosc*volume;
        double output = fxosc;
        return output;
}

void play(double *output) {

    /*
     TESTING SETUP
     */
        int freq = 230;
        int trigger = counter.phasor(0.2, 1, 9); //test counter in place of MIDI input
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
        int detune = 500;
    /*
     FM
     */
        //modulation frequencies and amounts in Hz
        double mod1freq = 20;
        double mod2freq = 2.5;
        double mod3freq = 10;
        int mod1amt = 150;
        int mod2amt = 0;
        int mod3amt = 0;
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
        int loEnable = 0;
        double hiCutoff = 500;
        double hiRes = 10;
        int hiEnable = 0;
    /*
     FX
     */
        //Delay: size in samples, feedback 0-1, wet 0-1
        int delay_size = 44000;
        double delay_feedback = 0.9;
        double delay_wet = 0;
        //Distortion: shape 1-inf, wet 0-1
        double dist_shape = 1000;
        double dist_wet = 0;
        //Flanger
        unsigned int flang_delay = 800;
        double flang_feedback = 0.7;
        double flang_speed  = 4;
        double flang_depth = 0.9;
        double flang_wet = 0;
        //Chorus
        unsigned int chorus_delay = 800;
        double chorus_feedback = 0.7;
        double chorus_speed = 1;
        double chorus_depth = 0.7;
        double chorus_wet = 0;
    /*
     VOLUME
     */
        //volume envelope
        //NOTE: all values are in ms, except Sustain is 0-1. Decay needs to be at least 1!
        double volA = 0;
        double volD = 1;
        double volS = 1;
        double volR = 10000;

        //left speaker
        output[0] = synth(trigger, freq, detune,
                        sinAvol, triAvol, sqAvol,
                        sinBvol, triBvol, sqBvol,
                        mod1freq, mod2freq, mod3freq,
                        mod1amt, mod2amt, mod3amt,
                        loCutoff, loRes, loEnable,
                        hiCutoff, hiRes, hiEnable,
                        loA, loD, loS, loR,
                        hiA, hiD, hiS, hiR,
                        delay_size, delay_feedback, delay_wet,
                        dist_shape, dist_wet,
                        flang_delay, flang_feedback, flang_speed, flang_depth, flang_wet,
                        chorus_delay, chorus_feedback, chorus_speed, chorus_depth, chorus_wet,
                        volA, volD, volS, volR
                        );
        //right speaker
        output[1] = output[0];
}
