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

double osc, osca, oscb, sine, tri, sq, sine2, tri2, sq2, mod1val, mod2val, mod3val;
int freq1 = 440;
int osc2Freq = 370;
int osc3Freq = 294;
//double sinevol, trivol, sqvol = 1;


void setup() {//some inits
    
}

double synth(
	double sinevol, double trivol, double sqvol,
	double sinevol1, double trivol1, double sqvol1,
	double mod1f, double mod1v, double mod2f, double mod2v, double mod3f, double mod3v,
	int mod1ta, int mod2ta, int mod3ta, int mod1tb, int mod2tb, int mod3tb //0 if off 1 if on
	) {
	sine = osc1.sinewave(freq1 + mod1.sinewave(mod1f)*mod1ta*mod1v + mod2.sinewave(mod2f)*mod2ta*mod2v + mod3.sinewave(mod3f)*mod3ta*mod3v);
	tri = osc2.triangle(freq1 + mod1.sinewave(mod1f)*mod1ta*mod1v + mod2.sinewave(mod2f)*mod2ta*mod2v + mod3.sinewave(mod3f)*mod3ta*mod3v);
	sq = osc3.square(freq1 + mod1.sinewave(mod1f)*mod1ta*mod1v + mod2.sinewave(mod2f)*mod2ta*mod2v + mod3.sinewave(mod3f)*mod3ta*mod3v);
	osca = (sine*sinevol + tri * trivol + sq * sqvol) / (sinevol + trivol + sqvol + 0.00000001);

	sine2 = osc4.sinewave(freq1 + mod1.sinewave(mod1f)*mod1tb*mod1v + mod2.sinewave(mod2f)*mod2tb*mod2v + mod3.sinewave(mod3f)*mod3tb*mod3v);
	tri2 = osc5.triangle(freq1 + mod1.sinewave(mod1f)*mod1tb*mod1v + mod2.sinewave(mod2f)*mod2tb*mod2v + mod3.sinewave(mod3f)*mod3tb*mod3v);
	sq2 = osc6.square(freq1 + mod1.sinewave(mod1f)*mod1tb*mod1v + mod2.sinewave(mod2f)*mod2tb*mod2v + mod3.sinewave(mod3f)*mod3tb*mod3v);
	oscb = (sine2*sinevol1 + tri2 * trivol1 + sq2 * sqvol1) / (sinevol1 + trivol1 + sqvol1 + 0.00000001);
	
	osc = (osca + oscb) / 2;

    //cout << "osca " << osca << " oscb " << oscb << " osc " << osc << endl;
	return osc;
}

double counter = 0.0;

void play(double *output) {
    
	counter+=0.0001;

	double a = sin(counter);
    double b = 0.5;
	double c = 0;
	double d = 0;
	double e = 0;
	double f = 0;

	output[0] = synth(a, b, c, d, e, f);
	output[1] = output[0];
    
    /*
    countIndex = myCounter.phasor(1, 0, 9);
    
    myOscOutput = myOsc.sawn(anotherFilter.lopass(frequencies[countIndex], 0.001));
    
    output[0] = myFilter.lopass(myOscOutput, myCutoff.phasor(0.1, 0.01, 0.5));
    
    output[1] = output[0];
    */
}


