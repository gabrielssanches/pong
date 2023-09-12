#!/bin/bash

docker build -t raylib/c -f ./docker/Dockerfile.c ./docker
docker build -t raylib/wasm -f ./docker/Dockerfile.wasm ./docker
