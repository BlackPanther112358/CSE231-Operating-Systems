#!/bin/bash
make
echo "Starting first run."
./count 0 0 0
sleep 20
echo "Starting second run."
./count 10 0 0
sleep 20
echo "Starting third run."
./count 10 0 10
sleep 20
echo "Starting fourth run."
./count 10 5 0
sleep 20
echo "Starting fifth run."
./count 10 10 0
sleep 20
echo "Starting sixth run."
./count 0 10 10