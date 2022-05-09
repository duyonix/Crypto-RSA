#!/bin/bash
set -e

# compile source.c then run
g++ -o source source.cpp -lcrypto
./source

# decode the hex string into a plain ASCII string
python -c 'print("Decode Hex to ASCII string: " +"50617373776F72642069732064656573".decode("hex"))' # -> result: "Password is dees"