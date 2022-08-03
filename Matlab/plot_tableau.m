%data = readtable('FILE');
data = csvread('FILE');
hold off
plot(data(:,1))
hold on
plot(data(:,2))
