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
	nb_recipient = []

	for line in f:
		line = line.strip()
		tmp = line.split(";")
		time.append(tmp[0])
		nb.append(tmp[1])
		nb_donor.append(tmp[2])
		nb_recipient.append(float(tmp[1])-float(tmp[2]))

	f.close()
	 
	return time, nb, nb_donor, nb_recipient


# table stores values from x and y to plot
time, nb , nb_donor, nb_recipient = read(file_name)

figure(1)
plot(time, nb, label="Total bacteria", color="black")
plot(time, nb_donor, label="Donor bacteria", color="red")
plot(time, nb_recipient, label="Recipient bacteria", color="blue")

xlabel("Time (h)")
ylabel("Number of bacteria")
title("Bacterial growth")
legend(loc="upper left")

savefig("results.png", format="png")
