#!/bin/bash
set -e

# compile source.c then run
gcc -o source source.c -lcrypto
./source

# decode the hex string into a plain ASCII string
python -c 'print("50617373776F72642069732064656573".decode("hex"))' # -> result: "Password is dees"