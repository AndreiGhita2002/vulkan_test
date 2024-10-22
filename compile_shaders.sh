#!/bin/sh

cd shaders || exit

glslc shader.vert -o vert.spv
glslc shader.frag -o frag.spv

cd ..
echo "Shaders compiled successfully!"
