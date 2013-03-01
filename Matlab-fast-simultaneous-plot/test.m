       
clc;
clf;
close('all');
clear all;
load fusion-analyzer-data.log
fast_plot(fusion_analyzer_data(:,15),fusion_analyzer_data(:,1));
fast_plot(fusion_analyzer_data(:,15),fusion_analyzer_data(:,2));
fast_plot(fusion_analyzer_data(:,1),fusion_analyzer_data(:,2));