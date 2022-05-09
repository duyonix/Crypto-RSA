#~/bin/bash
set -e

# get the hex strings of 2 strings
python -c 'print("Hex code for `I owe you $2000`: " + "I owe you $2000".encode("hex"))'
python -c 'print("Hex code for `I owe you $3000`: " + "I owe you $2000".encode("hex"))'

# compile source.c then run
g++ -o source source.cpp -lcrypto
./source