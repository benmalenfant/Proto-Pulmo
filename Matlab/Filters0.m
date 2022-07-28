%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% vcom_test.m
% This is a demonstration how to use the class *vcom_xep_radar_connector*
% Copyright: 2020 Sensor Logic
% Written by: Justin Hadella
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;
clc;

%Communication avec le port USB contenant le capteur
r = vcom_xep_radar_connector('COM3'); % adjust for *your* COM port!
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%PR: Initialisation de la variable
%max
maxy = 0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(4,1,1)
h1 = plot( 1:frameSize, frame);
axis([0,623,-10 10])
title('radar time waveform');
xlabel('bin');
ylabel('amplitude');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(4,1,2)
h2 = plot( 1:frameSize, frame);
axis([0,623 -2 2]);
title('Radar with Butterworth 3rd filter [0.1-5] Hz');
xlabel('bin');
ylabel('amplitude');

legend('y(x)', sprintf('Maximum y = %0.3f', maxy))
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(4,1,3)
h3 = plot( 1:frameSize, frame);
axis([0,623 -2 2]);
title('Radar with Butterworth 3rd filter [0.1-5] Hz');
xlabel('bin');
ylabel('amplitude');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(4,1,4)
h4 = plot( 1:frameSize, frame);
axis([0,623 -2 2]);
title('Radar with Butterworth 3rd filter [0.1-5] Hz');
xlabel('bin');
ylabel('amplitude');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

gain0 = 0.3;
gain = 0.8;
gain2 = 0.1;
y = [.1 .1 .1 .1 .1 .1 .1 .1 .1 .1];
x = [1];

%Initialisation des variables framebuff et outframe:
framebuff = zeros(10,623);
outframe = zeros(4,623);

        
% Plot data while window is open
while isgraphics(h_fig)
    try
        frame = abs(r.GetFrameNormalizedDouble-255);
        frame = filter(y,x,frame);
        framebuff(2,:) = framebuff(1,:);
        framebuff(1,:) = frame;

        %Filtre passe-haut ou passe-bas???
        outframe(1,:) = (1+gain)/2*(framebuff(1,:)-framebuff(2,:)) + gain*outframe(1,:);
        %outframe(2,:) = (1-gain2)*(outframe(1,:)) + gain2*outframe(2,:);
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %TEST PHIL:
        %Doit ajouter un second filtre passe-bande avec les
        %fréquences de coupure de 0.1 à 5 Hz
        
        %Ajout d'un second filtre sur les données suite au premier 
        %filtre:
        %outframe(2,:) = ;

        %Utiliser le outframe(2,:) et le mettre dans l'afficheur pour 
        %voir l'agissement de ce type de filtre.
        %[b,a] = butter(order, [lowFreq hiFreq]/(fs/2), 'bandpass');
        %y = filter(b,a,x)
        %Suite à des tests, le butterworth ordre 3 est le meilleur
        %candidat

        [b,a] = butter(3, [0.1 5]/(frameSize/2), 'bandpass');
        outframe(2,:) = filter(b,a,outframe(1,:));
        
        [d,c] = butter(3, [0.1 5]/(frameSize/2), 'bandpass');
        outframe(3,:) = filter(d,c,outframe(1,:));
        
        [f,e] = butter(3, [0.1 5]/(frameSize/2), 'bandpass');
        outframe(4,:) = filter(f,e,outframe(1,:));
        
        set(h1, 'xdata', 1:frameSize, 'ydata', frame(1,:));
        set(h2, 'xdata', 1:frameSize, 'ydata', outframe(2,:));
        set(h3, 'xdata', 1:frameSize, 'ydata', outframe(3,:));
        set(h4, 'xdata', 1:frameSize, 'ydata', outframe(4,:));

        %Aller chercher le MAX des valeurs pour ensuite l'afficher dans le
        %display:
        maxy = max(abs(outframe(2,:)));
        disp(maxy);
            
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%        
        %set(h1, 'xdata', 1:frameSize, 'ydata', frame(1,:));
        %set(h2, 'xdata', 1:frameSize, 'ydata', outframe(1,:));
        drawnow;
    catch ME
    end
end

r.Close();
