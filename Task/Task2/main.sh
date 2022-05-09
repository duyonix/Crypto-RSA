#!/bin/bash
set -e

# convert string to hex string
python -c 'print("Hex code for `A top secret!`: " + "A top secret!".encode("hex"))' 
# -> result: "4120746f702073656372657421"

# compile source.c then run
g++ -o run source.cpp -lcrypto
./run