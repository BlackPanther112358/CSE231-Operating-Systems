#!/bin/bash
truncate -s 0 count_time.txt
make count
./count 0 5 5
./count 0 10 90
./count 0 20 80
./count 0 30 70
./count 0 40 60
./count 0 50 50
./count 0 60 40
./count 0 70 30
./count 0 80 20
./count 0 90 10