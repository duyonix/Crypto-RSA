#~/bin/bash
set -e

# compile source.c then run
gcc -o source source.c -lcrypto
./source