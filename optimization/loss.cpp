double* b;
int arraySize;
//calculate FFT of sample
double* bFFT;

double loss(double* a) {
	//calculate synth output with parameters in a
	//calculate FFT of the synth output
	double* aFFT;
	double errorSUM = 0;
	for (int i = 0; i < arraySize; i++) {
		errorSUM += (a[i] - b[i]) * (a[i] - b[i]);
	}
	return errorSUM / arraySize;
}