#include "maximilian.h"

maxiOsc osc1, osc2, osc3, osc4, osc5, osc6, mod1, mod2, mod3;
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

double osc, osca, oscb, sine, tri, sq, sine2, tri2, sq2 = 0.0;
int freq1 = 440;
int osc2Freq = 370;
int osc3Freq = 294;
double sinevol, trivol, sqvol = 1;


void setup() {//some inits
    
}

double synth() {
	sine = osc1.sinewave(freq1);
	tri = osc2.triangle(freq1);
	sq = osc3.square(freq1);
	osca = (sine*sinevol + tri * trivol + sq * sqvol) / (sinevol + trivol + sqvol);

	sine2 = osc4.sinewave(freq1);
	tri2 = osc5.triangle(freq1);
	sq2 = osc6.square(freq1);
	oscb = (sine2*sinevol + tri2 * trivol + sq2 * sqvol) / (sinevol + trivol + sqvol);

	osc = (osca + oscb) / 2;

	return osc;
}

void play(double *output) {
    
	output[0] = synth();
	output[1] = output[0];
    
    /*
    countIndex = myCounter.phasor(1, 0, 9);
    
    myOscOutput = myOsc.sawn(anotherFilter.lopass(frequencies[countIndex], 0.001));
    
    output[0] = myFilter.lopass(myOscOutput, myCutoff.phasor(0.1, 0.01, 0.5));
    
    output[1] = output[0];
    */
}


