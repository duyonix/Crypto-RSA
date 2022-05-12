#!/bin/bash
set -e

# compile source.c then run
g++ -o run source.cpp -lcrypto
./run