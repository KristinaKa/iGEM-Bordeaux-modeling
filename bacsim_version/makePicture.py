#-*-coding: utf-8-*-

from pylab import *
from math import *
import random


print("Drawing graph...\n")

file_name = "results.csv"


def read(file_name):

	f = open(file_name,"r")
	
	time = []
	nb = []
	nb_donor = []

	for line in f:
		line = line.strip()
		tmp = line.split(";")
		time.append(tmp[0])
		nb.append(tmp[1])
		nb_donor.append(tmp[2])

	f.close()
	 
	return time, nb, nb_donor


# table stores values from x and y to plot
time, nb , nb_donor = read(file_name)

figure(1)
plot(time, nb)
plot(time, nb_donor)

savefig("results.png", format="png")
