%data = readtable('FILE');
data = csvread('../SW_Repartisseur/FILE');

plot(abs(data(:)-255))
