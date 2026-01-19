i#!/usr/bin/env bash

set -e

cd build

cmake -G Ninja ..

ninja

cd ..

cd bin

./buku_game

