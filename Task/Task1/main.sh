#~/bin/bash
set -e

# compile source.c then run
g++ -o source source.cpp -lcrypto
./source