#include "maximilian.h"

maxiOsc osc1, osc2, osc3, osc4, osc5, osc6, mod1, mod2, mod3;
maxiEnv voladsr, lpfadsr, hpfadsr;
maxiFilter volfilter, lpf, hpf;
maxiDistortion dist;
maxiFlanger flang;
maxiChorus chorus;

int freq1 = 440;

void setup() {//some inits
    
}

double synth(
	double sin1vol, double tri1vol, double sq1vol,
	double sin2vol, double tri2vol, double sq2vol,
	double mod1f, double mod1v, double mod2f, double mod2v, double mod3f, double mod3v,
	int mod1ta, int mod2ta, int mod3ta, int mod1tb, int mod2tb, int mod3tb, //0 if off 1 if on
	double cutoff1, double res1, double cutoff2, double res2
	) {

	double mod1double = mod1.sinewave(mod1f)*mod1v;
	double mod2double = mod2.sinewave(mod2f)*mod2v;
	double mod3double = mod3.sinewave(mod3f)*mod3v;

	double sine = osc1.sinewave(freq1 + mod1double*mod1ta + mod2double*mod2ta + mod3double*mod3ta);
	double tri = osc2.triangle(freq1 + mod1double*mod1ta + mod2double*mod2ta + mod3double*mod3ta);
	double sq = osc3.square(freq1 + mod1double*mod1ta + mod2double*mod2ta + mod3double*mod3ta);
	double osca = (sine*sin1vol + tri * tri1vol + sq * sq1vol) / (sin1vol + tri1vol + sq1vol + 0.00000001);

	double sine2 = osc4.sinewave(freq1 + mod1double*mod1tb + mod2double*mod2tb + mod3double*mod3tb);
	double tri2 = osc5.triangle(freq1 + mod1double*mod1tb + mod2double*mod2tb + mod3double*mod3tb);
	double sq2 = osc6.square(freq1 + mod1double*mod1tb + mod2double*mod2tb + mod3double*mod3tb);
	double oscb = (sine2*sin2vol + tri2 * tri2vol + sq2 * sq2vol) / (sin2vol + tri2vol + sq2vol + 0.00000001);
	
	double osc = (osca + oscb) / 2;

	double f1osc = lpf.lores(osc, cutoff1, res1);
	double f2osc = hpf.hires(f1osc, cutoff2, res2);

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
    double mod1f = 5;
    double mod2f = 21;
    double mod3f = 0;
    double mod1v = 30;
    double mod2v = 10;
    double mod3v = 1;
	int mod1ta = 1;
    int mod2ta = 1;
    int mod3ta = 0;
    int mod1tb = 0;
    int mod2tb = 0;
    int mod3tb = 0;
	double cutoff1 = 1000;
	double res1 = 10; //awtch out 1-?
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


