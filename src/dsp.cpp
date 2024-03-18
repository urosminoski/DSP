#include <iostream>
#include "../inc/dsp.hpp"

// Function that adds zeros to a vector if vector size is not power of 2
static void padding(std::vector<std::complex<double>>& a)
{
	// Get size of a vector
	unsigned int old_size = a.size();
	// Calculate new size of a vector
	unsigned int new_size = pow(2, ceil(log2(old_size)));
	// Calculate number of zeros needed
	unsigned int num_zeros = new_size - old_size;
	// Append num_zeros zeros to a vector
	a.insert(a.end(), num_zeros, 0);
}

// Function that performs FFT in recursion
static void fft_recur(std::vector<std::complex<double>>& a,
					 bool inverse)
{
	// Asign vector size to variable n
	unsigned int n = a.size();
	// If size is equal to 1, return
	if(n == 1)
		return;

	// Devide a to even and odd coefficients
	std::vector<std::complex<double>> a_even(n / 2), a_odd(n / 2);
	for(unsigned int i = 0; i < n/2; i++)
	{
		a_even[i] 	= a[2*i];
		a_odd[i]	= a[2*i + 1];
	}

	// Performe recursion, call fft_stat on a_even and a_odd
	fft_recur(a_even, inverse);
	fft_recur(a_odd, inverse);
	
	// Definig angle
	double ang = 2 * PI / n * (inverse ? -1 : 1);
	// Defining w = exp(1j * ang)
	std::complex<double> w(1);
	std::complex<double> wn(cos(ang), sin(ang));

	// Performing operations
	for(unsigned int i = 0; i < n/2; i++)
	{
		a[i] 		= a_even[i] + w * a_odd[i];
		a[i + n/2] 	= a_even[i] - w * a_odd[i];
		
		if(inverse)
		{
			a[i] 		/= 2;
			a[i + n/2] 	/= 2;
		}

		w *= wn;
	}
}

// Function that performs inpalce FFT
static void fft_inPlace(std::vector<std::complex<double>>& a,
						bool inverse)
{
	// Size of vector
	unsigned int n = a.size();

	// Perform reverse-bit prermutation
	unsigned int bit;
	for(unsigned int i = 1, j = 0; i < n; i++)
	{
		bit = n >> 1;
		for(; j & bit; bit >>= 1)
		{
			j ^= bit;
		}
		j ^= bit;

		if(i < j)
		{
			std::swap(a[i], a[j]);
		}
	}

	// Perform radix-2 algorithm
	double ang;
	std::complex<double> w, wn;
	std::complex<double> even_part, odd_part;

	for(unsigned int len = 1; len < n; len <<= 1)
	{
		ang = PI / len * (inverse ? -1 : 1);
		wn	= std::complex<double>(cos(ang), sin(ang));

		for(unsigned int i = 0; i < n; i += 2*len)
		{
			w = std::complex<double>(1, 0);

			for(unsigned int j = 0; j < len; j++)
			{
				even_part 	= a[i + j];
				odd_part 	= a[i + j + len] * w;
				
				a[i + j] 		= even_part + odd_part;
				a[i + j + len] 	= even_part - odd_part;

				w *= wn;
			}
		}
	}

	// If inverse is true, devide each element by n
	if(inverse)
	{
		for(auto& x : a)
		{
			x /= n;
		}
	}
}

void fft(std::vector<std::complex<double>>& a)
{
	// Perform zero padding if needed
	padding(a);
	// Perform FFT
	//fft_recur(a, false);	
	fft_inPlace(a, false);
}

void ifft(std::vector<std::complex<double>>& a)
{
	// Perform padding if needed
	padding(a);
	// Perform FFT
	//fft_recur(a, true);
	fft_inPlace(a, true);
}
