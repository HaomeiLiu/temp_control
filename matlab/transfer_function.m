% This code is obtained from https://www.mathworks.com/matlabcentral/answers/385254-how-can-i-get-transfer-function
% Modified for temperature control system
% The code gets a transfer function (1 pole, 0 zero, with delay) from time
% domain data

[D,S,R] = xlsread('data.csv');
tv = D(:,1);
vi = D(:,2);
vi(1) = 0;
vo = D(:,3);
[ti,ia,ic] = uniquetol(tv, 4.8E-7);                             % Get Unique Times
vi = vi(ia);                                                    % Corresponding Input Voltages
vo = vo(ia);                                                    % Corresponding Output Voltages
Ts = mean(diff(ti));                                            % Sampling Interval (sec)
ti = [(0 : 5E-7 : 1E-6)'; ti+1.5E-6];                           % Pad All Vectors With 3 Initial Time Samples
vi = [zeros(3,1); vi];                                          % Pad All Vectors With 3 Initial Time Samples
vo = [zeros(3,1); vo];                                          % Pad All Vectors With 3 Initial Time Samples
Fs = 1/Ts;                                                      % Sampling Frequency (Hz)
Fn = Fs/2;                                                      % Nyquist Frequency
L = numel(ti);                                                  % Vector LEngth
FTvi = fft(vi)/L;                                               % Input Fourier Transform
FTvo = fft(vo)/L;                                               % Output Fourier Transform
FTtf = FTvo./FTvi;                                              % Transfer Function Fourier Transform
Fv = linspace(0,1,fix(L/2)+1)*Fn;                               % Frequency Vector
Iv = 1:numel(Fv);                                               % Index Vector
figure(1)
plot(Fv, 20*log10(abs(FTtf(Iv))*2))
xlabel('Frequency (Hz)')
ylabel('Amplitude (dB)')
grid
dataobj = iddata(vo,vi,Ts);                                     % Prepare Data For Identification
%sys = tfest(data,np,nz, NaN) # of ports, # of zeros, unknow delay
tfobj = tfest(dataobj, 1, 0, NaN);                                   % Create Transfer Function Object
% with estimated delay:
% sys0 = idtf([nan nan nan],[1 nan nan]);
% sys0.Structure.IODelay.Value = 0.1; % initial guess
% sys0.Structure.IODelay.Maximum = 1; % maximum allowable value for delay 
% sys0.Structure.IODelay.Free = true; % treat delay as estimatable quantity
% sys = tfest(z1,sys0);
NumTF = tfobj.Numerator;                                        % Transfer Function Numerator
DenTF = tfobj.Denominator;                                      % Transfer Function Numerator
TF = tf(tfobj)                                                  % Transfer Function
figure(2)
plot(ti, vi,    ti, vo)                                         % Plot Input & Output
xlabel('Time (sec)')
ylabel('Amplitude (V)')
grid
[mag,phase,wout] = bode(tfobj);
figure(3)
subplot(2,1,1)
semilogx(wout, 20*log10(squeeze(mag)), '-b', 'LineWidth',1)     % Bode Plot: Magnitude
ylabel('H(f) (dB)')
grid
subplot(2,1,2)
semilogx(wout, squeeze(phase), '-b', 'LineWidth',1)             % Bode Plot: Phase
xlabel('Frequency (rad/sec)')
ylabel('Phase (°)')
grid
opt = stepDataOptions;
opt.StepAmplitude = vi(end);
[y,t] = step(tfobj, ti(end), opt);                                   % Calculate Step Response
figure(4)
plot(t,squeeze(y))                                              % Step Response
title('Step Response of Estimated Transfer Function')
xlabel('Time (sec)')
ylabel('Amplitude (V)')
grid