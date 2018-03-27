close all;
clear all;
pkg load signal;

data=csvread("teste2.csv");


fs=1000000/mean(data(:,7));% sample rate

%magnetometro
fc = 1; %%cut-off frequency [Hz]
n=60;
Wn=fc/fs;
fm=fir1(n,Wn);
mx=filter(fm,1,data(:,1));
my=filter(fm,1,data(:,2));
mz=filter(fm,1,data(:,3));

subplot(2,1,1);
 plot(data(:,1:3)); hold on;
plot([mx(round(n/2):end) my(round(n/2):end) mz(round(n/2):end)],'LineWidth',3);
ylabel("Magnetometro"); legend("mx","my","mz","mx fil","my fil","mz fil");grid;

%acelerometro
%fc = 10; %%cut-off frequency [Hz]
%n=60;
%Wn=fc/fs;
%fa=fir1(n,Wn);
%ax=filter(fa,1,data(:,4));
%ay=filter(fa,1,data(:,5));
%az=filter(fa,1,data(:,6));

%subplot(2,1,2); plot(data(:,4:6)); hold on;
%plot([ax(round(n/2):end) ay(round(n/2):end) az(round(n/2):end)],'LineWidth',3);
%ylabel("Acelerometro"); legend("ax","ay","az","ax fil","ay fil","az fil");grid;

%gyro
%fc = 10; %%cut-off frequency [Hz]
%n=60;
%Wn=fc/fs;
%fg=fir1(n,Wn);
%gx=filter(fg,1,data(:,7));
%gy=filter(fg,1,data(:,8));
%gz=filter(fg,1,data(:,9));

%subplot(3,1,3); plot(data(:,7:9)); hold on;
%plot([gx(round(n/2):end) gy(round(n/2):end) gz(round(n/2):end)],'LineWidth',3);
%ylabel("Gyro"); legend("gx","gy","gz","gx fil","gy fil","gz fil");grid;
