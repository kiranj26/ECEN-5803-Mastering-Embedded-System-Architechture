% ------------------------------------------------------------------
% Title: Flow Meter Simulation Parameters Loader
% Brief: This file loads parameters for the simulation of a model called Flow_Meter_Simulink.slx.
% Author: Kian Jojare, Viraj Patel
% Course: ECEN 5803 : Mastering Embedded System Architecture
% Date: 23 Oct 2023
% ------------------------------------------------------------------

% Clear console, variables, and all loaded functions
clc;          % Clear console output
clear;        % Clear workspace variables
clear all;    % Clear loaded functions and data

% Prompt user for the stop time of the simulation
Stop_Time = input('Enter The Stop Time In Seconds: ');

% Prompt user for the frequency of the wave in cycles/sec (Hz)
Frequency = input('Enter The Frequency In Hz: ');

% Convert frequency from cycles/sec (Hz) to radian/sec
Frequency = Frequency * 2 * pi;

% The number of samples in a single period of the wave is crucial for its accurate representation.
% Given by the formula: Samples per period = 2*pi / (Frequency * Sample time)
% We keep it greater than 256 for better resolution.
Samples_Per_Period = 1024;  % Define the number of samples per period

% Calculate the time interval between two consecutive samples
Sample_Time = (2 * pi) / (Frequency * Samples_Per_Period);

% Load and run the Simulink model
Model_Name = 'Flow_Meter_Simulink';
open_system(Model_Name);   % Open the Simulink model
sim(Model_Name);           % Run the Simulink simulation