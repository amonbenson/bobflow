#!/bin/bash

gcc -Wall -Wextra -Werror -std=c17 -oD -g3 -Iinclude -o build/bobflow src/bobflow/*.c src/*.c -lm -lSDL2 && \
    ./build/bobflow
