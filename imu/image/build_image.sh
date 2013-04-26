#!/bin/sh

./parser ./Rec00.txt
awk -f yaw.awk out.txt > plot.dat
gnuplot ./Plot.param
sudo cp xxx.png /mnt/
