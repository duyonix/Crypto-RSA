#!/bin/bash
set -e

# convert string to hex string
python -c 'print("A top secret!".encode("hex"))' # -> result: "4120746f702073656372657421"

# compile source.c then run
gcc -o source source.c -lcrypto
./source