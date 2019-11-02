FROM ubuntu:18.04

# Install Git, SDL2, and Python
RUN apt update && apt install -y git-core libsdl2-dev python

# Install Emscripten
RUN git clone https://github.com/emscripten-core/emsdk --depth 1
RUN /emsdk/emsdk install latest
RUN /emsdk/emsdk activate latest
RUN /emsdk/upstream/emscripten/embuilder.py build sdl2

# Make directories for putting source code from host and WebAssembly output
RUN mkdir dist src
VOLUME ["/opt/dist", "/opt/src"]

WORKDIR /opt/src
CMD [ "make" ]
