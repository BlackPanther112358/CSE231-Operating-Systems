#!/bin/bash
truncate -s 0 compile_time.txt
make compile
./compile 0 5 5
./compile 0 10 90
./compile 0 30 70
./compile 0 50 50
./compile 0 70 30
./compile 0 90 10