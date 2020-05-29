//
//  SynthParameters.h
//  Audio Plug-in Synth
//
//  Created by Lorand Cheng on 5/28/20.
//

#ifndef SynthParameters_h
#define SynthParameters_h
/*
 SETTINGS
 */
    #define NUMVOICES 5
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

#endif /* SynthParameters_h */
