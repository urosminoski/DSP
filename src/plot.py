#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

IMG_NAME = "imag/fft.pdf"

def read_data_from_file(filename):
	data = []

	try:
		with open(filename, 'r') as file:
			for line in file:
				try:
					real, imag = map(float, line.strip().split(','))
					data.append(complex(real, imag))
				except ValueError:
					print("Error: Invalid data format in line:", line)
	except FileNotFoundError:
		print("Error: File " + filename + " not found!\n")
	else:
		print("Successfully read data from:", filename)
	
	return data

def plot_and_save(data_in, data_out):
	
	fig, axs = plt.subplots(3)

	try:
		axs[0].plot(np.real(data_in))
		axs[1].plot(np.abs(data_out))
		axs[2].plot(20 * np.log10(np.abs(data_out)))
		plt.tight_layout()

	except Exception as e:
		print("Error occurred while ploting:", e)

	else:
		try:
			plt.savefig(IMG_NAME)

		except Exception as e:
			print("Error occurred while saving figure:", e)
		else:
			print("Successfully saved figure!\n")

def main():
	filename1 = "data/input.txt"
	filename2 = "data/output.txt"

	data_in = read_data_from_file(filename1)
	data_out = read_data_from_file(filename2)

	plot_and_save(data_in, data_out)

if __name__ == "__main__":
	main()
