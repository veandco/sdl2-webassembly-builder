#!/bin/bash

mkdir -p dist
docker run -it -e EMMAKEN_CFLAGS='-s USE_SDL=2' -v $PWD/dist:/opt/dist -v $PWD/src:/opt/src emscripten-sdl2
