#!/bin/bash

docker run \
    -v `pwd`:/game \
    -ti \
    raylib/${1}
