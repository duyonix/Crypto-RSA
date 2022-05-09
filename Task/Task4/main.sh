#~/bin/bash
set -e

# get the hex strings of 2 strings
python -c 'print("I owe you $2000".encode("hex"))'
python -c 'print("I owe you $3000".encode("hex"))'

# compile source.c then run
gcc -o source source.c -lcrypto
./source