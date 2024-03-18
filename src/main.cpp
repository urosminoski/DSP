
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <complex>
#include <../inc/dsp.hpp>

#define PI M_PI

bool write_to_file(const char *file, std::vector<std::complex<double>>& a)
{
	// Write vector to a file
	std::ofstream outfile(file);
	if(outfile.is_open())
	{
		for(const auto& val : a)
		{
			outfile << val.real() << " , " << val.imag() << "\n";
		}
		outfile.close();
		std::cout << "Data has been written to a file" << std::endl;
		return true;
	}
	else
	{
		std::cerr << "Error: Unable to open file for writing!" << std::endl;
		return false;
	}
}

int main(void)
{
	unsigned int n = 1024;
	double ang = 2 * PI  * 1/8;
	std::vector<std::complex<double>> a(n);
	
	for(unsigned int i = 0; i < n; i++)
	{
		a[i] = std::complex<double>(cos(ang * i), 0);
	}

	// Write vector to a file
	if(false == write_to_file("data/input.txt", a))
		return 1;

	// Perform FFT and write to a file
	fft(a);
	if(false == write_to_file("data/output.txt", a))
		return 1;

	return 0;
}
