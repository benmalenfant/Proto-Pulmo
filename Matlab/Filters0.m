%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% vcom_test.m
%
% This is a demonstration how to use the class *vcom_xep_radar_connector*
%
% Copyright: 2020 Sensor Logic
% Written by: Justin Hadella
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;
clc;

r = vcom_xep_radar_connector('COM5'); % adjust for *your* COM port!
r.Open('X4');

% As a side-effect many settings on write will cause the numSamplers
% variable to update
fprintf('bins = %d\n', r.numSamplers);

% Actually every variable from the radar is requested in this manner.
iterations = r.Item('iterations');
fprintf('iterations = %d\n', iterations);

% Setting some variables
r.TryUpdateChip('rx_wait', 0);
r.TryUpdateChip('frame_start', 0);
r.TryUpdateChip('frame_end', 4.0);
%r.TryUpdateChip('ddc_en', 1);
r.TryUpdateChip('PPS', 100);

% Set up time plot signal
frameSize = r.numSamplers;   % Get # bins/samplers in a frame
frame = zeros(1, frameSize); % Preallocate frame
h_fig = figure;
ax1 = gca;
subplot(2,1,1)
h1 = plot( 1:frameSize, frame);
axis([0,623,-10,10])
% title(ax1, 'radar time waveform');
% xlabel(ax1, 'bin');
% ylabel(ax1, 'amplitude');
subplot(2,1,2)
h2 = plot( 1:frameSize, frame);
% title(ax1, 'radar time waveform');
% xlabel(ax1, 'bin');
% ylabel(ax1, 'amplitude');
axis([0,623,-10,10])
gain0 = 0.3
gain = 0.8;
gain2 = 0.1;
y = [.1 .1 .1 .1 .1 .1 .1 .1 .1 .1];
x = [1];
framebuff = zeros(10,623);

outframe = zeros(2,623);

        

% Plot data while window is open
while isgraphics(h_fig)
    try
        frame = abs(r.GetFrameNormalizedDouble-255);
        frame = filter(y,x,frame);
        framebuff(2,:) = framebuff(1,:);
        framebuff(1,:) = frame;

        outframe(1,:) = (1+gain)/2*(framebuff(1,:)-framebuff(2,:))+gain*outframe(1,:);
        %outframe(2,:) = (1-gain2)*(outframe(1,:)) + gain2*outframe(2,:);
        set(h1, 'xdata', 1:frameSize, 'ydata', frame(1,:));
        set(h2, 'xdata', 1:frameSize, 'ydata', outframe(1,:));
        drawnow;
    catch ME
    end
end

r.Close();
