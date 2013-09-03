% Sine wave analysis using FFT
% set the sampling freq
Fs = 150;  % Hz
% time vector for time domain analysis - 1s simulation
t = 0:1/Fs:1;
% create a sine wave of 5 Hz 
f_sine = 5;
sine = sin(2*pi*f_sine*t);
% length of FFT 
n_samples = 1024;
% take a FFT and pad with zerosso that length(x) = n_samples
X = fft(sine, n_samples);
% FFT is symmetric so we can ignore half
X = X(1:n_samples/2);
% compute the magnitude of X 
mX = abs(X);
% compute the frequency vector 
f_fft = (0:n_samples/2-1)*Fs/n_samples;
% plot analysis
figure;
subplot(2,1,1);
plot(t, sine);
title('Time domain signal');
xlabel('Time(s)');
ylabel('Amplitude');
subplot(2,1,2);
plot(f_fft, mX);
title('Freq domain analysis');
xlabel('Freq (Hz)');
ylabel('Amplitude');