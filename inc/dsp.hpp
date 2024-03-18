
#ifndef DSP_H
#define DSP

#include <complex>
#include <vector>
#include <cmath>

#define PI 	M_PI

void fft(std::vector<std::complex<double>>& a);
void ifft(std::vector<std::complex<double>>& a);

#endif // DSP
