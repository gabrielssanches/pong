#!/bin/bash

docker run \
    -v `pwd`:/app \
    -ti \
    raylib/c \
    /bin/bash -c "cd /app && make"
